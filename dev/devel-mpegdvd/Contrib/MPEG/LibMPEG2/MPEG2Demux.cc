// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// Demultiplexer based upon parts of mpeg2dec, which can be found at
// http://libmpeg2.sourceforge.net/
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id$"
//! lib = RavlLibMPEG2
//! author = "Warren Moore"

#include "Ravl/Image/MPEG2Demux.hh"
#include "Ravl/DP/AttributeValueTypes.hh"

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#define DEMUX_HEADER 0
#define DEMUX_DATA 1
#define DEMUX_SKIP 2

namespace RavlImageN
{
  
  using namespace RavlN;
  
  static const int mpeg1_skip_table[16] = { 0, 0, 4, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  MPEG2DemuxBodyC::MPEG2DemuxBodyC(ByteT track) :
    m_track(track),
    m_state(DEMUX_SKIP),
    m_stateBytes(0),
    m_dataIn(2048),
    m_bufStart(0),
    m_bufEnd(0)
  {
    BuildAttributes();
  }
  
  MPEG2DemuxBodyC::~MPEG2DemuxBodyC()
  {
  }
  
  bool MPEG2DemuxBodyC::Get(ByteT &data)
  {
    // Check we're not at the end of the stream
    if (IsGetEOS())
      return false;
    
    SArray1dC<ByteT> dataOut(1);
    bool read = GetArray(dataOut) > 0;
    if (read)
      data = dataOut[0];
    return read;
  }
  
  IntT MPEG2DemuxBodyC::GetArray(SArray1dC<ByteT> &data)
  {
    cerr << "MPEG2DemuxBodyC::GetArray" << endl;
    
    if (m_bufStart == m_bufEnd)
      ReadInput();
    
    Demultiplex();
    
    return 0;
  }
  
  bool MPEG2DemuxBodyC::IsGetEOS() const
  {
    if (m_dataIn.IsEmpty() && m_dataOut.IsEmpty() && input.IsGetEOS())
    {
      ONDEBUG(cerr << "MPEG2DemuxBodyC::IsGetEOS at EOS" << endl;)
      return true;
    }
    
    return false;
  }

  bool MPEG2DemuxBodyC::GetAttr(const StringC &attrName, IntT &attrValue)
  {
    if (attrName == "track")
    {
      attrValue = m_track;
      return true; 
    }
    return DPPortBodyC::GetAttr(attrName, attrValue);
  }

  bool MPEG2DemuxBodyC::ReadInput()
  {
    if (!input.IsValid() || input.IsGetEOS())
      return false;
    
    // Read the next amount of data
    RavlAssertMsg(m_bufStart == m_bufEnd, "MPEG2DemuxBodyC::ReadInput unread data still in buffer");
    UIntT len = input.GetArray(m_dataIn);
    
    // Set the buffer pointers
    m_bufStart = (ByteT*)&(m_dataIn[0]);
    m_bufEnd = m_bufStart + len;
    
    return true;
  }
  
  void MPEG2DemuxBodyC::AppendOutput(ByteT *start, ByteT *end)
  {
  }
  
  bool MPEG2DemuxBodyC::Demultiplex()
  {
    ByteT *header;
    int bytes;
    int len;
  
#define NEEDBYTES(x)                                                    \
    do {                                                                \
      int missing;                                                      \
                                                                        \
      missing = (x) - bytes;                                            \
      if (missing > 0) {                                                \
        if (header == m_headBuf) {                                      \
          if (missing <= m_bufEnd - m_bufStart) {                       \
            memcpy(header + bytes, m_bufStart, missing);                \
            m_bufStart += missing;                                      \
            bytes = (x);				                                        \
          } else {					                                            \
            memcpy(header + bytes, m_bufStart, m_bufEnd - m_bufStart);  \
            m_stateBytes = bytes + m_bufEnd - m_bufStart;               \
            return false;                                               \
          }                                                             \
        } else {						                                            \
          memcpy(m_headBuf, header, bytes);		                          \
          m_state = DEMUX_HEADER;                                       \
          m_stateBytes = bytes;                                         \
          return false;                                                 \
        }                                                               \
      }                                                                 \
    } while (false)
  
#define DONEBYTES(x)                                                    \
    do {                                                                \
      if (header != m_headBuf)                                          \
        m_bufStart = header + (x);                                      \
    } while (false)
  
    switch (m_state)
    {
      case DEMUX_HEADER:
        if (m_stateBytes > 0)
        {
          header = m_headBuf;
          bytes = m_stateBytes;
          goto continue_header;
        }
        break;
        
      case DEMUX_DATA:
        if (m_stateBytes > m_bufEnd - m_bufStart)
        {
          AppendOutput(m_bufStart, m_bufEnd);

          m_stateBytes -= m_bufEnd - m_bufStart;
          return 0;
        }

        AppendOutput(m_bufStart, m_bufStart + m_stateBytes);

        m_bufStart += m_stateBytes;
        break;
        
      case DEMUX_SKIP:
        if (m_stateBytes > m_bufEnd - m_bufStart)
        {
          m_stateBytes -= m_bufEnd - m_bufStart;

          return 0;
        }
        m_bufStart += m_stateBytes;
        break;
    }
    
    while (true)
    {
    payload_start:
      header = m_bufStart;
      bytes = m_bufEnd - m_bufStart;

    continue_header:
      NEEDBYTES(4);
      if (header[0] || header[1] || (header[2] != 1))
      {
        if (header != m_headBuf)
        {
          m_bufStart++;
          goto payload_start;
        }
        else
        {
          header[0] = header[1];
          header[1] = header[2];
          header[2] = header[3];
          bytes = 3;
          goto continue_header;
        }
      }

      switch (header[3])
      {
        case 0xb9:	/* program end code */
          /* DONEBYTES (4); */
          /* break;         */

          return 1;
          
        case 0xba:	/* pack header */
          NEEDBYTES(5);
          if ((header[4] & 0xc0) == 0x40)
          {	/* mpeg2 */
            NEEDBYTES(14);
            len = 14 + (header[13] & 7);
            NEEDBYTES(len);
            DONEBYTES(len);
            /* header points to the mpeg2 pack header */
          }
          else
          {
            if ((header[4] & 0xf0) == 0x20)
            {	/* mpeg1 */
              NEEDBYTES(12);
              DONEBYTES(12);
              /* header points to the mpeg1 pack header */
            }
            else
            {
              cerr << "ImgILibMPEG2BodyC::Demultiplex weird pack header" << endl;
              DONEBYTES(5);
            }
          }
          break;
          
        default:
          if (header[3] == m_track)
          {
            NEEDBYTES(7);
            if ((header[6] & 0xc0) == 0x80)
            {	/* mpeg2 */
              NEEDBYTES(9);
              len = 9 + header[8];
              NEEDBYTES(len);
              /* header points to the mpeg2 pes header */
              if (header[7] & 0x80)
              {
                /*
                uint32_t pts;
          
                pts = (((header[9] >> 1) << 30) |
                       (header[10] << 22) | ((header[11] >> 1) << 15) |
                       (header[12] << 7) | (header[13] >> 1));
                mpeg2_pts(m_decoder, pts);
                */
              }
            }
            else
            {	/* mpeg1 */
              int len_skip;
              uint8_t * ptsbuf;
          
              len = 7;
              while (header[len - 1] == 0xff)
              {
                len++;
                NEEDBYTES(len);
                if (len > 23)
                {
                  cerr << "ImgILibMPEG2BodyC::Demultiplex too much stuffing" << endl;
                  break;
                }
              }
              if ((header[len - 1] & 0xc0) == 0x40)
              {
                len += 2;
                NEEDBYTES(len);
              }
              len_skip = len;
              len += mpeg1_skip_table[header[len - 1] >> 4];
              NEEDBYTES(len);
              /* header points to the mpeg1 pes header */
              ptsbuf = header + len_skip;
              if (ptsbuf[-1] & 0x20)
              {
                /*
                uint32_t pts;
                
                pts = (((ptsbuf[-1] >> 1) << 30) |
                       (ptsbuf[0] << 22) | ((ptsbuf[1] >> 1) << 15) |
                       (ptsbuf[2] << 7) | (ptsbuf[3] >> 1));
                mpeg2_pts(m_decoder, pts);
                */
              }
            }
            DONEBYTES(len);
            bytes = 6 + (header[4] << 8) + header[5] - len;
            if (bytes > m_bufEnd - m_bufStart)
            {
              AppendOutput(m_bufStart, m_bufEnd);
              
              m_state = DEMUX_DATA;
              m_stateBytes = bytes - (m_bufEnd - m_bufStart);
              return 0;
            }
            else
            {
              if (bytes > 0)
              {
                AppendOutput(m_bufStart, m_bufStart + bytes);

                m_bufStart += bytes;
              }
            }
          }
          else
          {
            if (header[3] < 0xb9)
            {
              cerr << "ImgILibMPEG2BodyC::Demultiplex looks like a video stream, not system stream" << endl;
              DONEBYTES(4);
            }
            else
            {
              NEEDBYTES(6);
              DONEBYTES(6);
              bytes = (header[4] << 8) + header[5];
              if (bytes > m_bufEnd - m_bufStart)
              {
                m_state = DEMUX_SKIP;
                m_stateBytes = bytes - (m_bufEnd - m_bufStart);

                return 0;
              }
              m_bufStart += bytes;
            }
          }
          break;
      }
    }
  }
  
  void MPEG2DemuxBodyC::BuildAttributes()
  {
    RegisterAttribute(AttributeTypeNumC<ByteT>("track", "MPEG demultiplexed track", true, false));
  }

}

