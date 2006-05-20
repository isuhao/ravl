// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/NetEndPoint.cc"

#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/OS/NetStream.hh"
#include "Ravl/OS/NetMsgCall.hh"
#include "Ravl/Threads/LaunchThread.hh"
//#include "Ravl/BinStream.hh"
//#include "Ravl/BinString.hh"

#include <stdlib.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.

  NetEndPointBodyC::NetEndPointBodyC(const StringC &addr) 
    : skt(addr,false),
      transmitQ(15),
      receiveQ(5),
      shutdown(false)
  { Init(skt); }
  
  //:  Constructor.

  NetEndPointBodyC::NetEndPointBodyC(SocketC &nskt) 
    : skt(nskt),
      transmitQ(15),
      receiveQ(5),
      shutdown(false)
  { Init(nskt); }

  
  //: Default constructor.
  
  NetEndPointBodyC::NetEndPointBodyC() 
    : transmitQ(15),
      receiveQ(5),
      shutdown(false)
  {}
  
  //: Destructor.

  NetEndPointBodyC::~NetEndPointBodyC() {
    //cerr << "NetEndPointBodyC::~NetEndPointBodyC(), Called. \n";
    setupComplete.Post(); // Make sure nothings waiting for setup to complete.
  }
  
  //: Setup and startup the aproprate threads.
  
  //  NetMsgRegisterItemC<NetMsgCall1C<NetEndPointC,StringC,&NetEndPointC::MsgInit> > netMsgReg(1,"NetEndPointC.MsgInit");

  //: Register new message handler.
  
  bool NetEndPointBodyC::Register(const NetMsgRegisterC &nmsg) {
#if AMMA_CHECK
    if(msgReg.IsElm(nmsg.Id()))
      cerr << "NetEndPointBodyC::Register(), WARNING: Overriding handling of message id:" << nmsg.Id() << "\n";
#endif
    msgReg[nmsg.Id()] = nmsg;
    return true;
  }
  
  //: Search for message decode/encode of type 'id'.
  
  NetMsgRegisterC NetEndPointBodyC::Find(UIntT msgTypeID) const {
    // Check local decode table.
    NetMsgRegisterC *msg = const_cast<NetMsgRegisterC *>(msgReg.Lookup(msgTypeID));
    if(msg != 0) 
      return *msg;
    // Check global decode table.
    msg = NetMsgRegisterC::MsgTypes().Lookup(msgTypeID);
    if(msg != 0) 
      return *msg;
    return NetMsgRegisterC();
  }

  //: Send init message.
  
  void NetEndPointBodyC::SndInit(StringC &user) {
    Send(1,user);
  }
  
  bool NetEndPointBodyC::Init(SocketC &nskt) {
    skt = nskt;
    if(!skt.IsOpen()) {
      cerr << "NetEndPointBodyC::Init(), Socket not opened. \n";
      return false;
    }
    
    RegisterR(1,"Init",*this,&NetEndPointBodyC::MsgInit);
    
    const char *un = getenv("USER"); // This isn't really secure!!
    if(un == 0)
      un = "*unknown*";
    StringC auser(un);
    SndInit(auser);
    
    //Transmit(initMsg);
    
    NetEndPointC me(*this);
    LaunchThread(me,&NetEndPointC::RunReceive);
    LaunchThread(me,&NetEndPointC::RunTransmit);
    LaunchThread(me,&NetEndPointC::RunDecode);
    return true;
  }

  //: Wait for setup to complete.
  
  bool NetEndPointBodyC::WaitSetupComplete() {
    setupComplete.Wait();
    return true;
  }

  //: Send a 0 paramiter message.
  
  bool NetEndPointBodyC::Send(UIntT id) {
    BufOStreamC os;
    BinOStreamC bos(os);
    bos << id ;
    Transmit(NetPacketC(os.Data()));
    return true;
  }


  //: Close connection.
  
  bool NetEndPointBodyC::Close() {
    if(!shutdown) {
      shutdown = true;
      skt.Close();
      receiveQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
      transmitQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
    }
    return true;
  }
  
  
  //: Handle packet transmition.
  
  bool NetEndPointBodyC::RunTransmit() {
    NetOStreamC nos(skt,false);
    ONDEBUG(cerr << "NetEndPointBodyC::RunTransmit(), Started. \n");
    if(!nos) {
      cerr << "NetEndPointBodyC::RunTransmit(), ERROR: No connection. \n";    
      return false; 
    }
    nos << "\n<ABPS>\n";
    BinOStreamC bos(nos);
    ONDEBUG(cerr << "NetEndPointBodyC::RunTransmit(), Starting transmit loop. \n");
    try {
      while(!shutdown && nos) {
	NetPacketC pkt = transmitQ.Get();
	if(shutdown || !nos)
	  break;
	if(!pkt.IsValid())
	  continue;
	ONDEBUG(cerr << "Transmit packet:\n");
	ONDEBUG(pkt.Dump(cerr));
	pkt.Transmit(bos);
      ONDEBUG(cerr << "Sent packet. \n");
      }
    } catch(ExceptionC &e) {
      cerr << "AMMA Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. \n";
    } catch(exception &e) {
      cerr << "C++ Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. \n";
    } catch(...) {
      cerr << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. \n";
    }
    Close();
    if(!nos)
      cerr << "NetEndPointBodyC::RunTransmit(), Connection broken \n";    
    ONDEBUG(cerr << "NetEndPointBodyC::RunTransmit(), Terminated \n"); 
    return true;
  }
  
  
  //: Handle packet reception.
  
  bool NetEndPointBodyC::RunReceive() {
    NetIStreamC nis(skt,false);
    ONDEBUG(cerr << "NetEndPointBodyC::RunReceive(), Started. \n");
    if(!nis) {
      cerr << "NetEndPointBodyC::RunReceive(), ERROR: No connection. \n";    
      return false; 
    }
    StringC x;
    while(nis) {
      readline(nis,x);
      if(x == "<ABPS>")
	break;
    }
    ONDEBUG(cerr << "NetEndPointBodyC::RunReceive(), Connection type confirmed. '" << x << "'\n");
    BinIStreamC bis(nis);
    try {
      while(!shutdown && nis) {	
	if(!nis.WaitForData())
	  continue; // Check for shutdown.
	NetPacketC pkt(bis);
	if(pkt.IsValid()) {
	  ONDEBUG(cerr << "Got packet. size :" << pkt.Data().Size() << "\n");
	  receiveQ.Put(pkt);
	}
      }
    } catch(ExceptionC &e) {
      cerr << "AMMA Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. \n";
    } catch(exception &e) {
      cerr << "C++ Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. \n";
    } catch(...) {
      cerr << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. \n";
    }
    if(!nis)
      cerr << "NetEndPointBodyC::RunReceive(), Connection broken \n";
    Close();
    ONDEBUG(cerr << "NetEndPointBodyC::RunRecieve(), Terminated \n"); 
    return true;
  }


  //: Decodes incoming packets.
  
  bool NetEndPointBodyC::RunDecode() {
    ONDEBUG(cerr << "NetEndPointBodyC::RunDecode(), Startup. \n"); 
    NetPacketC pkt;
    NetEndPointC me(*this);
    try {
      while(!shutdown) {
	NetPacketC pkt = receiveQ.Get();
	if(shutdown)
	  break;
	if(!pkt.IsValid()) 
	  continue;
	//ONDEBUG(cerr << "Recieved packet:\n");
	//ONDEBUG(pkt.Dump(cerr));
	// Decode....
	BinIStreamC is(pkt.DecodeStream());
	UIntT msgTypeID = 0;
	is >> msgTypeID;
	ONDEBUG(cerr << "Incoming packet type id:" << msgTypeID << "\n");
	// Check local decode table.
	NetMsgRegisterC msg = Find(msgTypeID);
	if(!msg.IsValid()) {
	  cerr << "NetEndPointBodyC::RunDecode(), WARNING: Don't know how to decode message type " << msgTypeID << " \n";
	  continue;
	}
	ONDEBUG(cerr << "Decoding incoming packet. Type: '" << msg.Name() << "'\n");
	msg.Decode(me,is);
	if(is.Tell() != pkt.Size()) {
	  cerr << "WARNING: Not all of packet processed Stream:" << is.Tell() << " Packet size:" << pkt.Size() <<"\n"; 
	}
      }
    } catch(ExceptionC &e) {
      cerr << "AMMA Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. \n";
    } catch(exception &e) {
      cerr << "C++ Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. \n";
    } catch(...) {
      cerr << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. \n";
    }
    shutdown = true;
    transmitQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
    // Can't to much about recieve...
    ONDEBUG(cerr << "NetEndPointBodyC::RunDecode(), Terminated. \n"); 
    return true;
  }
  

  //: Init message.
  
  bool NetEndPointBodyC::MsgInit(StringC &user) {
    ONDEBUG(cerr << "NetEndPointBodyC::MsgInit(), Called. User:" << user << "\n");
    remoteUser = user;
    setupComplete.Post();
    return true;
  }

}