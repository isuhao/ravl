// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet

#include "Ravl/OS/NetPortManager.hh"
#include "Ravl/OS/NetPortClient.hh"
#include "Ravl/Threads/LaunchThread.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetPortManagerBodyC::NetPortManagerBodyC(const StringC &nname)
    : name(nname),
      managerOpen(false)
  {}
  
  //: Open manager at address.
  
  bool NetPortManagerBodyC::Open(const StringC &addr) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Open(), Called for " << addr << " \n");

    RWLockHoldC hold(access,false);
    if(managerOpen) {
      cerr << "NetPortManagerBodyC::Open(), Attempt to re-open port manager at '" << addr << "'\n";
      return false; 
    }
    
    sktserv = SocketC(addr,true);
    if(!sktserv.IsOpen()) {
      cerr << "NetPortManagerBodyC::Run(), Failed to open server socket. '" << addr << "' \n";
      return false;
    }
    
    managerOpen = true;
    NetPortManagerC manager(*this);
    LaunchThread(manager,&NetPortManagerC::Run);
    
    return true;
  }


  //: Run port manager.
  
  bool NetPortManagerBodyC::Run() {
    ONDEBUG(cerr << "NetPortManagerBodyC::Run(), Called. \n");
    RavlAssert(sktserv.IsOpen());
    NetPortManagerC manager(*this);
    while(1) {
      SocketC skt = sktserv.Listen();
      // When a socket connects, make and end point and send a 'hello' message.
      NetPortClientC cl(skt,manager);
      // Register client somewhere ?
    }
    return true;
  }

  //: Search for port in table.
  
  NetISPortServerBaseC NetPortManagerBodyC::Lookup(const StringC &name) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Lookup(),  Called. Port='" << name << "' \n");
    NetISPortServerBaseC ret; 
    RWLockHoldC hold(access,true);
    iports.Lookup(name,ret);
    return ret;
  }

  //: Register new port.
  
  bool NetPortManagerBodyC::Register(const StringC &name,NetISPortServerBaseC &ips) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Register(),  Called. Port='" << name << "' \n");
    RWLockHoldC hold(access,false);
    if(iports.IsElm(name)) 
      return false; // Already registered.
    iports[name] = ips;
    return true;
  }
  
  //: Unregister port.
  
  bool NetPortManagerBodyC::Unregister(const StringC &name) {
    RWLockHoldC hold(access,false);
    return iports.Del(name);
  }
  
  //: Access global net port manager.

  NetPortManagerC &GlobalNetPortManager() {
    static NetPortManagerC npm("global");
    return npm;
  }
  
  //: Open net port manager.
  
  bool NetPortOpen(const StringC &addr) {
    return GlobalNetPortManager().Open(addr);
  }

}