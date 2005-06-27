// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETPORTMANAGER_HEADER
#define RAVL_NETPORTMANAGER_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! docentry="Ravl.OS.Network.NetPort"
//! file="Ravl/OS/Network/NetPortManager.hh"
//! example=exNetPort.cc

#include "Ravl/String.hh"
#include "Ravl/OS/Socket.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/Hash.hh"
#include "Ravl/OS/NetIPortServer.hh"
#include "Ravl/OS/NetOPortServer.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/Calls.hh"

namespace RavlN {
  
  class NetPortManagerC;
  
  //! userlevel=Develop
  //: Port server.
  
  class NetPortManagerBodyC 
    : public RCBodyVC
  {
  public:
    NetPortManagerBodyC(const StringC &name);
    //: Constructor.
    
    bool Lookup(const StringC &name,const StringC &dataType,NetISPortServerBaseC &isp,bool attemptCreate = true);
    //: Search for port in table.
    //!param: name - Name of connection
    //!param: dataType - Type of data requested.
    //!param: isp - Place to store new connection.
    //!param: attemptCreate - When true, use requestIPort call to attempt to create connection if its not already registered.
    
    bool Lookup(const StringC &name,const StringC &dataType,NetOSPortServerBaseC &osp,bool attemptCreate = true);
    //: Search for port in table.
    //!param: name - Name of connection
    //!param: dataType - Type of data requested.
    //!param: osp - Place to store new connection.
    //!param: attemptCreate - When true, use requestIPort call to attempt to create connection if its not already registered.
    
    bool Register(const StringC &name,NetISPortServerBaseC &ips);
    //: Register new port.
    
    bool Register(const StringC &name,NetOSPortServerBaseC &ops);
    //: Register new port.
    
    bool Unregister(const StringC &name);
    //: Unregister port.
    
    bool Open(const StringC &addr);
    //: Open manager at address.
    
    bool Close();
    //: Close down manager.
    
    bool WaitForTerminate();
    //: Wait until the server has exited.
    // NB. Can only be called after 'Open' has returned.
    
    virtual bool RegisterConnection(NetISPortServerBaseC &isport);
    //: Called when a connection is established.
    
    virtual bool RegisterConnection(NetOSPortServerBaseC &isport);
    //: Called when a connection is established.
    
    bool RegisterIPortRequestManager(const CallFunc3C<StringC,StringC,NetISPortServerBaseC &,bool> &requestIPort);
    //: Register IPort request manager.
    // Return false if this replaces another request manager.
    
    bool RegisterOPortRequestManager(const CallFunc3C<StringC,StringC,NetOSPortServerBaseC &,bool> &requestOPort);
    //: Register OPort request manager.
    // Return false if this replaces another request manager.
    
  protected:
    bool Run();
    //: Run port manager.
    
    StringC name;
    
    CallFunc3C<StringC,StringC,NetISPortServerBaseC &,bool> requestIPort; // Args: PortName,DataType,Place to open port to
    CallFunc3C<StringC,StringC,NetOSPortServerBaseC &,bool> requestOPort; // Args: PortName,DataType,Place to open port to
    
    HashC<StringC,NetISPortServerBaseC> iports; // List of IPorts waiting for incomming connections.
    HashC<StringC,NetOSPortServerBaseC> oports; // List of OPorts waiting for incomming connections.
    RWLockC access;
    bool managerOpen;
    SocketC sktserv;         // Server socket.
    SemaphoreC ready;        // Semaphore used to indicate the server setup is complete.
    volatile bool terminate; // Shutdown flag.
    UInt64T conIdAlloc;       // Connection id allocator.
    friend class NetPortManagerC;
  };

  //! userlevel=Advanced
  //: Port server.
  // Server side exported port manager. <br>
  // This class manages the ports to exported on a server.  The server listens for
  // connections on network socket, and does setup.
  // It should be noted registered connection's are 1 to 1, it isn't possible for
  // two clients to use a connection simultaneously.
  
  class NetPortManagerC 
    : public RCHandleC<NetPortManagerBodyC>
  {
  public:
    NetPortManagerC(const StringC &name)
      : RCHandleC<NetPortManagerBodyC>(*new NetPortManagerBodyC(name))
    {}
    //: Constructor.
    
    NetPortManagerC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

  protected:
    NetPortManagerC(NetPortManagerBodyC &bod)
      : RCHandleC<NetPortManagerBodyC>(bod)
    {}
    //: Body constructor.
    
    NetPortManagerBodyC &Body()
    { return RCHandleC<NetPortManagerBodyC>::Body(); }
    //: Access body.

    const NetPortManagerBodyC &Body() const
    { return RCHandleC<NetPortManagerBodyC>::Body(); }
    //: Access body.

    bool Run()
    { return Body().Run(); }
    //: Run manager thread.
  public:
    
    bool Lookup(const StringC &name,const StringC &dataType,NetISPortServerBaseC &isp,bool attemptCreate = true)
    { return Body().Lookup(name,dataType,isp,attemptCreate); }
    //: Search for port in table.
    
    bool Lookup(const StringC &name,const StringC &dataType,NetOSPortServerBaseC &osp,bool attemptCreate = true)
    { return Body().Lookup(name,dataType,osp,attemptCreate); }
    //: Search for port in table.
    
    bool Register(const StringC &name,NetISPortServerBaseC &ips)
    { return Body().Register(name,ips); }
    //: Register port.
    
    bool Register(const StringC &name,NetOSPortServerBaseC &ops)
    { return Body().Register(name,ops); }
    //: Register port.
    
    bool Unregister(const StringC &name)
    { return Body().Unregister(name); }
    //: Unregister port.
    
    bool Open(const StringC &addr)
    { return Body().Open(addr); }
    //: Open manager at address.
    
    bool Close()
    { return Body().Close(); }
    //: Close down manager.
    
    bool WaitForTerminate()
    { return Body().WaitForTerminate(); }
    //: Wait until the server has exited.
    // NB. Can only be called after 'Open' has returned.
    
    bool RegisterConnection(NetISPortServerBaseC &isport)
    { return Body().RegisterConnection(isport); }
    //: Called when a connection is established.
    
    bool RegisterConnection(NetOSPortServerBaseC &osport)
    { return Body().RegisterConnection(osport); }
    //: Called when a connection is established.
    
    bool RegisterIPortRequestManager(const CallFunc3C<StringC,StringC,NetISPortServerBaseC &,bool> &requestIPort)
    { return Body().RegisterIPortRequestManager(requestIPort); }
    //: Register IPort request manager.
    // Return false if this replaces another request manager.
    
    bool RegisterOPortRequestManager(const CallFunc3C<StringC,StringC,NetOSPortServerBaseC &,bool> &requestOPort)
    { return Body().RegisterOPortRequestManager(requestOPort); }
    //: Register OPort request manager.
    // Return false if this replaces another request manager.
    
    friend class NetPortManagerBodyC;
  };
  
  NetPortManagerC &GlobalNetPortManager();
  //: Access global net port manager.
  
  //! userlevel=Normal
  
  bool NetPortOpen(const StringC &address);
  //: Open net port manager.
  // The 'address' has the format  'host:port' where port may be a
  // host name or its ip (dotted numbers) address and port is the 
  // number of the port to use.
  
  bool NetPortClose();
  //: Close down net port manager.
  
}

#endif
