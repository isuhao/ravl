// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPPLUG_HEADER
#define RAVL_DPPLUG_HEADER 1
////////////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing.Ports" 
//! rcsid="$Id$"
//! file="Ravl/Core/IO/Plug.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="8/6/2002"
//! userlevel=Normal

#include "Ravl/DP/Port.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Input plug base.
  
  class DPPlugBaseBodyC 
    : public RCBodyVC
  {
  public:
    DPPlugBaseBodyC()
      : hold(true)
    {}
    //: Default constructor.
    
    DPPlugBaseBodyC(const DPEntityC &nhold)
      : hold(nhold)
    {}
    //: Constructor.

    DPPlugBaseBodyC(const StringC &nPlugId,const DPEntityC &nhold)
      : plugId(nPlugId),
	hold(nhold)
    {}
    //: Constructor.
    
    const StringC &PlugId() const
    { return plugId; }
    //: Get ID for plug.
    
  protected:
    StringC plugId; 
    DPEntityC hold; // Make sure object is not deleted.
  };

  //! userlevel=Advanced
  //: Input plug base.
  
  class DPPlugBaseC 
    : public RCHandleC<DPPlugBaseBodyC>
  {
  public:
    DPPlugBaseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DPPlugBaseC(DPPlugBaseBodyC &bod)
      : RCHandleC<DPPlugBaseBodyC>(bod)
    {}
    //: Body constructor.
    
    DPPlugBaseBodyC &Body()
    { return RCHandleC<DPPlugBaseBodyC>::Body(); }
    //: Access body.
    
    const DPPlugBaseBodyC &Body() const
    { return RCHandleC<DPPlugBaseBodyC>::Body(); }
    //: Access body.
    
  public:
    const StringC &PlugId() const
    { return Body().PlugId(); }
    //: Get ID for plug.
    
  };

  ///////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Input plug base.
  
  class DPIPlugBaseBodyC 
    : public DPPlugBaseBodyC
  {
  public:
    DPIPlugBaseBodyC()
    {}
    //: Default constructor.
    
    DPIPlugBaseBodyC(const DPEntityC &nhold)
      : DPPlugBaseBodyC(nhold)
    {}
    //: Constructor.

    DPIPlugBaseBodyC(const StringC &nPlugId,const DPEntityC &nhold)
      : DPPlugBaseBodyC(nPlugId,nhold)
    {}
    //: Constructor.
    
    virtual bool SetPort(const DPIPortBaseC &port);
    //: set port.
    
    virtual const type_info &InputType() const;
    //: Return type of port.
  protected:
  };
  
  //! userlevel=Advanced
  //: Input plug base.
  
  class DPIPlugBaseC 
    : public DPPlugBaseC
  {
  public:
    DPIPlugBaseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DPIPlugBaseC(DPIPlugBaseBodyC &bod)
      : DPPlugBaseC(bod)
    {}
    //: Body constructor.
    
    DPIPlugBaseBodyC &Body()
    { return static_cast<DPIPlugBaseBodyC &>(DPPlugBaseC::Body()); }
    //: Access body.
    
    const DPIPlugBaseBodyC &Body() const
    { return static_cast<const DPIPlugBaseBodyC &>(DPPlugBaseC::Body()); }
    //: Access body.
    
  public:
    bool SetPort(const DPIPortBaseC &port)
    { return Body().SetPort(port); }
    //: Set port.
    
    const type_info &InputType() const
    { return Body().InputType(); }
    //: Return type of port.
    
  };
  
  ///////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Input plug base.
  
  class DPOPlugBaseBodyC 
    : public DPPlugBaseBodyC
  {
  public:
    DPOPlugBaseBodyC()
    {}
    //: Default constructor.
    
    DPOPlugBaseBodyC(const DPEntityC &nhold)
      : DPPlugBaseBodyC(nhold)
    {}
    //: Constructor.
    
    DPOPlugBaseBodyC(const StringC &nPlugId,const DPEntityC &nhold)
      : DPPlugBaseBodyC(nPlugId,nhold)
    {}
    //: Constructor.
    
    virtual bool SetPort(const DPOPortBaseC &port);
    //: set port.

    virtual const type_info &OutputType() const;
    //: Return type of port.    
  };
  
  //! userlevel=Advanced
  //: Input plug base.
  
  class DPOPlugBaseC 
    : public DPPlugBaseC
  {
  public:
    DPOPlugBaseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DPOPlugBaseC(DPOPlugBaseBodyC &bod)
      : DPPlugBaseC(bod)
    {}
    //: Body constructor.
    
    DPOPlugBaseBodyC &Body()
    { return static_cast<DPOPlugBaseBodyC &>(DPPlugBaseC::Body()); }
    //: Access body.
    
    const DPOPlugBaseBodyC &Body() const
    { return static_cast<const DPOPlugBaseBodyC &>(DPPlugBaseC::Body()); }
    //: Access body.
    
  public:
    bool SetPort(const DPOPortBaseC &port)
    { return Body().SetPort(port); }
    //: Set port.
    
    const type_info &OutputType() const
    { return Body().OutputType(); }
    //: Return type of port.
    
  };

  
  ////////////////////////////////////
  //! userlevel=Develop
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPIPlugBodyC 
    : public DPIPlugBaseBodyC
  {
  public:
    explicit DPIPlugBodyC(const DPIPortC<DataT> &nport,const DPEntityC &nhold)
      : DPIPlugBaseBodyC(nhold),
	port(const_cast<DPIPortC<DataT> &>(nport))
    {}
    //: Constructor.

    explicit DPIPlugBodyC(const DPIPortC<DataT> &nport,const StringC &nPlugId,const DPEntityC &nhold)
      : DPIPlugBaseBodyC(nPlugId,nhold),
	port(const_cast<DPIPortC<DataT> &>(nport))
    {}
    //: Constructor.
    
    inline const DPPlugC<DataT> &operator= (DPIPortC<DataT> &othport)
    { port = othport; return *this; }
    //: Assignment.
    
    DPIPortC<DataT> &Port()
    { return port; }
    //: Access port.
    
    virtual bool SetPort(const DPIPortBaseC &nport) { 
      port = DPIPortC<DataT>(const_cast<DPIPortBaseC &>(nport));
      return port.IsValid();
    }
    //: set port.
    
    virtual const type_info &InputType() const
    { return typeid(DataT); }
    //: Return type of port.
    
  private:
    DPIPortC<DataT> &port;
  };
  
  ////////////////////////////////////
  //! userlevel=Advanced
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPIPlugC 
    : public DPIPlugBaseC
  {
  public:
    explicit DPIPlugC(const DPIPortC<DataT> &nport,const DPEntityC &nhold = DPEntityC(true))
      : DPIPlugBaseC(*new DPIPlugBodyC<DataT>(nport,nhold))
    {}
    //: Constructor.

    DPIPlugC(const DPIPortC<DataT> &nport,const StringC &nPlugId,const DPEntityC &nhold = DPEntityC(true))
      : DPIPlugBaseC(*new DPIPlugBodyC<DataT>(nport,nPlugId,nhold))
    {}
    //: Constructor.
    
  protected:
    DPIPlugBodyC<DataT> &Body()
    { return static_cast<DPIPlugBodyC<DataT> &>(DPIPlugBaseC::Body()); }
    //: Access body.
    
    const DPIPlugBodyC<DataT> &Body() const
    { return static_cast<const DPIPlugBodyC<DataT> &>(DPIPlugBaseC::Body()); }
    //: Access body.
  public:
    
    DPIPortC<DataT> &Port()
    { return Body().Port(); }
    //: Access handle to port.
    
    
  };
  
  /////////////////////////////
  //: Use a plug
  
  template<class DataT>
  void operator>> (DPIPortC<DataT> &source,DPIPlugC<DataT> &input)  { 
    input = source; 
  }
  
  
  //////////////////////////////////////////////////////////////////////////
  //! userlevel=Develop
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPOPlugBodyC 
    : public DPOPlugBaseBodyC
  {
  public:
    explicit DPOPlugBodyC(const DPOPortC<DataT> &nport,const DPEntityC &nhold)
      : DPOPlugBaseBodyC(nhold),
	port(const_cast<DPOPortC<DataT> &>(nport))
    {}
    //: Constructor.

    DPOPlugBodyC(const DPOPortC<DataT> &nport,const StringC &nPlugId,const DPEntityC &nhold)
      : DPOPlugBaseBodyC(nPlugId,nhold),
	port(const_cast<DPOPortC<DataT> &>(nport))
    {}
    //: Constructor.
    
    DPOPortC<DataT> &Port()
    { return port; }
    //: Access handle to port.
    
    virtual bool SetPort(const DPOPortBaseC &nport) { 
      port = DPOPortC<DataT>(const_cast<DPOPortBaseC &>(nport));
      return port.IsValid();
    }
    //: set port.
    
    virtual const type_info &OutputType() const
    { return typeid(DataT); }
    //: Return type of port.
    
  private:
    DPOPortC<DataT> &port;
  };
  
  ////////////////////////////////////
  //! userlevel=Advanced
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPOPlugC 
    : public DPOPlugBaseC
  {
  public:
    explicit DPOPlugC(const DPOPortC<DataT> &nport,const DPEntityC &nhold = DPEntityC(true))
      : DPOPlugBaseC(*new DPOPlugBodyC<DataT>(nport,nhold))
    {}
    //: Constructor.

    DPOPlugC(const DPOPortC<DataT> &nport,const StringC &nPlugId,const DPEntityC &nhold = DPEntityC(true))
      : DPOPlugBaseC(*new DPOPlugBodyC<DataT>(nport,nPlugId,nhold))
    {}
    //: Constructor.
    
  protected:
    DPOPlugBodyC<DataT> &Body()
    { return static_cast<DPOPlugBodyC<DataT> &>(DPOPlugBaseC::Body()); }
    //: Access body.
    
    const DPOPlugBodyC<DataT> &Body() const
    { return static_cast<const DPOPlugBodyC<DataT> &>(DPOPlugBaseC::Body()); }
    //: Access body.
    
  public:
    DPOPortC<DataT> &Port()
    { return Body().Port(); }
    //: Access handle to port.
    
  };
  
  /////////////////////////////
  //: Use a plug
  
  template<class DataT>
  void operator>> (DPOPortC<DataT> &source,DPOPlugC<DataT> &output)  { 
    output = source; 
  }

}

#endif
