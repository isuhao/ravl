// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETOPORTSERVER_HEADER
#define RAVL_NETOPORTSERVER_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! docentry="Ravl.OS.Network.NetPort"
//! example=exNetPort.cc
//! file="Ravl/OS/Network/NetOPortServer.hh"

#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/OS/NetPort.hh"
#include "Ravl/DP/SPort.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/OS/NetAttributeCtrlServer.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Base class for NetOports.
  
  class NetOSPortServerBaseBodyC 
    : public NetAttributeCtrlServerBodyC
  {
  public:
    NetOSPortServerBaseBodyC(const AttributeCtrlC &attrCtrl,const DPSeekCtrlC &seekCtrl,const StringC &portName);
    //: Default constructor.
    
    ~NetOSPortServerBaseBodyC();
    //: Destructor.
    
    const StringC &Name() const
    { return portName; }
    //: Access port name.
    
    virtual StringC PortType();
    //: Get the port type.
    
    virtual bool Connect(NetEndPointC &ep);
    //: Connect to an end point.
    // Returns false if port is already in use..
    
    bool Disconnect();
    //: Disonnect to an end point.
    
    NetEndPointC &NetEndPoint()
    { return ep; }
    //: Access net end point.

  protected:
    virtual bool Init();
    //: Initalise stream.
    
    bool ReqStats();
    //: Request information on the stream.. 
    
    StringC portName;
    DPSeekCtrlC seekCtrl;
    UIntT at;
  };
  
  //! userlevel=Develop
  //: Input port body
  
  template<class DataT>
  class NetOSPortServerBodyC
    : public NetOSPortServerBaseBodyC
  {
  public:
    NetOSPortServerBodyC(const DPOSPortC<DataT> &noport,const StringC &portName)
      : NetOSPortServerBaseBodyC(noport,noport,portName),
	oport(noport)
    {}
    //: Constructor.
    
    ~NetOSPortServerBodyC() 
    {}
    //: Destructor
    
    virtual StringC PortType()
    { return TypeName(typeid(DataT)); }
    //: Get the port type.
    
    bool PutData(UIntT &pos,DataT &data);
    //: Request information on the stream.. 
    
  protected:
    bool Init();
    //: Initalise link.
    
    DPOSPortC<DataT> oport;
  };
  
  //! userlevel=Advanced
  //: Input port server base.

  class NetOSPortServerBaseC
    : public NetAttributeCtrlServerC
  {
  public:
    NetOSPortServerBaseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

  protected:
    NetOSPortServerBaseC(NetOSPortServerBaseBodyC &bod)
      : NetAttributeCtrlServerC(bod)
    {}
    //: Body constructor.
    
    NetOSPortServerBaseBodyC &Body()
    { return static_cast<NetOSPortServerBaseBodyC &>(NetAttributeCtrlServerC::Body()); }
    //: Access body.
    
    const NetOSPortServerBaseBodyC &Body() const
    { return static_cast<const NetOSPortServerBaseBodyC &>(NetAttributeCtrlServerC::Body()); }
    //: Access body.
    
  public:
    const StringC &Name() const
    { return Body().Name(); }
    //: Access port name.
    
    bool Connect(NetEndPointC &ep)
    { return Body().Connect(ep); }
    //: Connect to an end point.
    // Returns false if port is already in use..
    
    bool Disconnect()
    { return Body().Disconnect(); }
    //: Disonnect to an end point.
    
    StringC PortType()
    { return Body().PortType(); }
    //: Get the port type.
    
    NetEndPointC &NetEndPoint()
    { return Body().NetEndPoint(); }
    //: Access net end point.
    
  };
  
  //! userlevel=Advanced
  //: Input port.
  // This class manages the information needed to serve a particular port.
  
  template<class DataT>
  class NetOSPortServerC
    : public NetOSPortServerBaseC
  {
  public:
    NetOSPortServerC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    NetOSPortServerC(const DPOSPortC<DataT> &oport,const StringC &portName)
      : NetOSPortServerBaseC(*new NetOSPortServerBodyC<DataT>(oport,portName))
    {}
    //: Constructor.
    
  protected:
    NetOSPortServerC(NetOSPortServerBodyC<DataT> &bod)
      : NetOSPortServerBaseC(bod)
    {}
    //: Body constructor.

    NetOSPortServerBodyC<DataT> &Body()
    { return static_cast<NetOSPortServerBodyC<DataT> &>(NetOSPortServerBaseC::Body()); }
    //: Access body.
    
    const NetOSPortServerBodyC<DataT> &Body() const
    { return static_cast<const NetOSPortServerBodyC<DataT> &>(NetOSPortServerBaseC::Body()); }
    //: Access body.
    
    bool PutData(UIntT &pos,DataT &data)
    { return Body().PutData(pos,data); }
    //: Request information on the stream.. 
    
    friend class NetOSPortServerBodyC<DataT>;
  };

  ///////////////////////////////////////////////////
  
  bool NetExportBase(const StringC &name,NetOSPortServerBaseC &isp);
  //! userlevel=Develop
  //: Export  port.
  
  template<class DataT>
  bool NetExport(const StringC &portName,DPOSPortC<DataT> &port) {
    NetOSPortServerC<DataT> ips(port,portName);
    return NetExportBase(portName,ips);
  }
  //! userlevel=Normal 
  //: Export an SPort with a given portName.
  
  template<class DataT>
  bool NetExport(const StringC &portName,DPOPortC<DataT> &port) {
    NetOSPortServerC<DataT> ips(SPort(port),portName);
    return NetExportBase(portName,ips);
  }
  //! userlevel=Normal 
  //: Export an SPort with a given portName.
  
  ///////////////////////////////////////////////////
  
  template<class DataT>  
  bool NetOSPortServerBodyC<DataT>::Init() {
    NetOSPortServerC<DataT> me(*this);
    RavlAssert(ep.IsValid());
    ep.Register(NPMsg_Data,"Data",me,&NetOSPortServerC<DataT>::PutData);
    bool ret =NetOSPortServerBaseBodyC::Init();
    return ret;
  }
  
  //: Request information on the stream.. 
  
  template<class DataT>
  bool NetOSPortServerBodyC<DataT>::PutData(UIntT &pos,DataT &data) {
    if(!oport.IsValid()) {
      //cerr << "NetOSPortServerBodyC<DataT>::ReqData(), Invalid output port.\n";      
      ep.Send(NPMsg_ReqFailed,1); // Report end of stream.
      return true;
    }
    //cerr << "NetOSPortServerBodyC<DataT>::ReqData(), Pos=" << pos << " at=" << at << " Tell=" << oport.Tell() <<"\n";
    if(at != pos && pos != (UIntT)(-1)) {
      oport.Seek(pos);
      at = pos;
    }
    if(oport.Put(data)) {
      at++;
    } else { // Failed to get data.
      //cerr << "NetOSPortServerBodyC<DataT>::ReqData(), Put failed. \n";
      if(!oport.IsPutReady())
	ep.Send(NPMsg_ReqFailed,1); // Ug
      else
	ep.Send(NPMsg_ReqFailed,2); // Just get failed.
    }
    return true;
  }
  

}


#endif
