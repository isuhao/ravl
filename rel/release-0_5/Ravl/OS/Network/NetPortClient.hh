// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETPORTCLIENT_HEADER
#define RAVL_NETPORTCLIENT_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! docentry="Ravl.OS.Network"

#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/OS/NetPortManager.hh"

namespace RavlN {
  
  class NetPortClientC;
  class NetPortManagerC;
  
  //! userlevel=Develop
  //: NetPortClient.
  // This class manages incoming connection requests.
  
  class NetPortClientBodyC 
    : public NetEndPointBodyC
  {
  public:
    NetPortClientBodyC(SocketC &skt,NetPortManagerC &manager);
    //: Construct from open socket.
    
  protected:
    bool Init();
    //: Initalise connection.
    
    bool MsgConnectTo(StringC &port,StringC &datatype);
    //: Handle connect to message.
    
    NetPortManagerC manager;

    friend class NetPortClientC;
  };
  
  //! userlevel=Normal
  //: NetPortClient.
  // This class manages incoming connection requests.
  
  class NetPortClientC 
    : public NetEndPointC
  {
  public:
    NetPortClientC()
    {}
    //: Default constructor.
    
    NetPortClientC(SocketC &skt,NetPortManagerC &manager)
      : NetEndPointC(*new NetPortClientBodyC(skt,manager))
    {}
    //: Socket constructor.
    
  protected:
    NetPortClientC(NetPortClientBodyC &bod)
      : NetEndPointC(bod)
    {}
    //: Body constructor.
    
    NetPortClientBodyC &Body()
    { return static_cast<NetPortClientBodyC &>(NetEndPointC::Body()); }
    //: Access body.

    const NetPortClientBodyC &Body() const
    { return static_cast<const NetPortClientBodyC &>(NetEndPointC::Body()); }
    //: Access body.
    
  public:
    
    friend class NetPortClientBodyC;
  };


}

#endif