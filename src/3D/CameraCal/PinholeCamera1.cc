#include "Ravl/3D/PinholeCamera1.hh"

namespace Ravl3DN
{
  using namespace RavlN;
  using namespace RavlImageN;

  //: Load from stream.
  bool
  PinholeCameraBody1C::Load(istream &s)
  {
    s >> 
      m_frame >>
      m_fx >> 
      m_fy >> 
      m_cx >> 
      m_cy >> 
      m_k1 >> 
      m_R  >> 
      m_t;
    return true;
  }
    
  //: Load from binary stream.
  bool
  PinholeCameraBody1C::Load(BinIStreamC &s)
  {
    s >> 
      m_frame >>
      m_fx >> 
      m_fy >> 
      m_cx >> 
      m_cy >> 
      m_k1 >> 
      m_R  >> 
      m_t;
    return true;
  }
    
  //: Writes object to stream, can be loaded using constructor
  bool 
  PinholeCameraBody1C::Save(ostream &s) const
  {
    s << m_frame
      << endl << m_fx 
      << " " << m_fy
      << " " << m_cx
      << " " << m_cy
      << endl;
    s << m_k1 << endl; 
    s << m_R;
    s << m_t << endl;
    return true;
  }
    
  //: Writes object to stream, can be loaded using constructor
  bool 
  PinholeCameraBody1C::Save(BinOStreamC &s) const
  {
    s << m_frame
      << m_fx 
      << m_fy 
      << m_cx 
      << m_cy 
      << m_k1 
      << m_R
      << m_t;
    return true;
  }
  
};