// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSIGNAL1_HEADER
#define RAVLSIGNAL1_HEADER 1
/////////////////////////////////////////////////////
//! docentry="Ravl.OS.Signals"
//! rcsid="$Id$"
//! lib=RavlThreads
//! author="Charles Galambos"
//! date="23/09/99"
//! file="Ravl/OS/Threads/Tools/Signal1.hh"

#include "Ravl/Threads/Signal.hh"
#include "Ravl/InDLIter.hh"

class ostream;

namespace RavlN {

  template<class DataT> class Signal1C;
  
  ////////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 connector.
  
  template<class DataT>
  class SignalConnector1BodyC
    : virtual public SignalConnector0BodyC
  {
  public:
    inline SignalConnector1BodyC(const DataT &def)
      : defaultVal(def)
      {}
    //: Default constructor.
    
    inline SignalConnector1BodyC(Signal0C &from)
      : SignalConnector0BodyC(from)
      {}
    //: Constructor.
    
    inline SignalConnector1BodyC(Signal0C &from,const DataT &def)
      : SignalConnector0BodyC(from),
      defaultVal(def)
      {}
    //: Constructor.
    
    virtual void Invoke(DataT &) = 0;
    //: Pass signal on.
    
    virtual void Invoke()
      { Invoke(defaultVal); }
    //: Pass signal on, use default value.
    
  protected:
    DataT defaultVal;
  };
  
  //! userlevel=Develop
  //: Signal 1 inter connector.
  
  template<class DataT>
  class SignalInterConnect1BodyC
    : virtual public SignalConnector1BodyC<DataT>,
      virtual public SignalInterConnect0BodyC
  {
  public:
    SignalInterConnect1BodyC()
      {}
    //: Constructor.
    
    SignalInterConnect1BodyC(Signal0C &from,Signal1C<DataT> &targ);
  //: Constructor.
    
    inline virtual void Invoke(DataT &);
    //: Invoke signal, with value.
    
    inline virtual void Invoke();
  //: Invoke signal, with default value.
  };

  ///////////////////////////
  //! userlevel=Normal
  //: class for signal interconnector with 1 arg.
  
  template<class DataT>
  class SignalInterConnect1C
    : public SignalConnectorC
  {
  public:
    SignalInterConnect1C(Signal0C &from,Signal1C<DataT> &targ)
      : SignalConnectorC(*new SignalInterConnect1BodyC<DataT>(from,targ))
      {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 function connector.
  
  template<class DataT>
  class Signal1FuncBodyC
    : public SignalConnector1BodyC<DataT>
  {
  public:
    typedef void (*Func1T)(DataT &val);
    
    Signal1FuncBodyC(Signal0C &from,Func1T nFunc,const DataT &def)
      : SignalConnector0BodyC(from),
      SignalConnector1BodyC<DataT>(from,def),
      func(nFunc)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { func(defaultVal); }
    //: Call function.
    // Use default value.
    
    virtual void Invoke(DataT &val)
      { func(val); }
    //: Call function.
    
  protected:
    Func1T func;
  };
  
  //! userlevel=Normal
  //: Signal a function
  
  template<class DataT>
  class Signal1FuncC 
    : public SignalConnectorC
  {
  public:
    Signal1FuncC(Signal0C &from,Signal1FuncBodyC<DataT>::Func1T nFunc,const DataT &def = DataT())
      : SignalConnectorC(*new Signal1FuncBodyC<DataT>(from,nFunc,def))
      {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 method connector.
  
  template<class DataT,class ObjT>
  class Signal1MethodBodyC
    : public SignalConnector1BodyC<DataT>
  {
  public:
    typedef void (ObjT::*Func1T)(DataT &dat);
    
    Signal1MethodBodyC(Signal0C &from,
		       const ObjT &nobj,
		       Func1T nFunc,
		       const DataT &dat = DataT())
      : SignalConnector0BodyC(from),
      SignalConnector1BodyC<DataT>(from,dat),
      obj(nobj),
      func(nFunc)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(defaultVal); }
    //: Call function.
    
    virtual void Invoke(DataT &val)
      { (obj.*func)(val); }
    //: Call function.
    
    inline void operator()(DataT &val)
      { Invoke(val); }
    //: Simple invokation.
    
  protected:
    ObjT obj;
    Func1T func;
  };
  
  //! userlevel=Normal
  //: Signal a method.
  
  template<class DataT,class ObjT>
  class Signal1MethodC
    : public SignalConnectorC
  {
  public:
    Signal1MethodC(Signal0C &from,
		   const ObjT &nobj,
		   void (ObjT::*nFunc)(DataT &),
		   const DataT &dat = DataT())
      : SignalConnectorC(*new Signal1MethodBodyC<DataT,ObjT>(from,nobj,nFunc,dat))
      {}
    //: Constructor.
  };
  
  ///////////////////////////////////////////////////
  //! userlevel=Develop
  //: Signal 1 method connector.
  // Uses refrence to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.
  
  template<class DataT,class ObjT>
  class Signal1MethodRefBodyC
    : public SignalConnector1BodyC<DataT>
  {
  public:
    typedef void (ObjT::*Func1T)(DataT &dat);
    
    Signal1MethodRefBodyC(Signal0C &from,
			  ObjT &nobj,
			  Func1T nFunc,
			  const DataT &dat = DataT())
      : SignalConnector0BodyC(from),
      SignalConnector1BodyC<DataT>(from,dat),
      obj(nobj),
      func(nFunc)
      {}
    //: Constructor.
    
    virtual void Invoke()
      { (obj.*func)(defaultVal); }
    //: Call function.
    
    virtual void Invoke(DataT &val)
      { (obj.*func)(val); }
    //: Call function.
    
    inline void operator()(DataT &val)
      { Invoke(val); }
    //: Simple invokation.
    
  protected:
    ObjT &obj;
    Func1T func;
  };
  
  ///////////////////////////////
  //! userlevel=Normal
  //: Signal a method.
  // Uses refrence to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.
  
  template<class DataT,class ObjT>
  class Signal1MethodRefC
    : public SignalConnectorC
  {
  public:
    Signal1MethodRefC(Signal0C &from,
		      ObjT &nobj,
		      void (ObjT::*nFunc)(DataT &),
		      const DataT &dat = DataT())
      : SignalConnectorC(*new Signal1MethodRefBodyC<DataT,ObjT>(from,nobj,nFunc,dat))
      {}
  //: Constructor.
  };

  ////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal 1 body.
  
  template<class DataT>
  class Signal1BodyC
    : public Signal0BodyC
  {
  public:
    Signal1BodyC(const DataT &def)
      : defaultVal(def)
      {}
    //: Constructor.
    
    virtual void Invoke(DataT &v) {
      RWLockHoldC hold(access,true);
      SArray1dIterC<SignalConnectorC> it(outputs);
      hold.Unlock();
      for(;it;it++) {
	SignalConnector1BodyC<DataT> *sc1 = dynamic_cast<SignalConnector1BodyC<DataT> *>(&it.Data().Body());
	if(sc1 != 0)
	  sc1->Invoke(v);
	else
	  it.Data().Invoke();
      }
    }
    //: Send signal with value.
    
    virtual void Invoke() { 
      RWLockHoldC hold(access,true); 
      SArray1dIterC<SignalConnectorC> it(outputs);
      hold.Unlock();
      for(;it;it++) {
	SignalConnector1BodyC<DataT> *sc1 = dynamic_cast<SignalConnector1BodyC<DataT> *>(&it.Data().Body());
	if(sc1 != 0)
	  sc1->Invoke(defaultVal);
	else
	  it.Data().Invoke();
      }
    }
  //: Send signal with default value where needed.
  
  protected:
    DataT defaultVal; // Default data value.
  };
  
  //! userlevel=Normal
  //: Signal 1 handle.
  
  template<class DataT>
  class Signal1C
    : public Signal0C
  {
  public:
    typedef void (*Func1T)(DataT &dat);
    
    Signal1C()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    Signal1C(const Signal0C &base)
      : Signal0C(base)
      {
	if(dynamic_cast<const Signal1BodyC<DataT> *>(&Signal0C::Body()) == 0)
	Invalidate();
      }
    //: Base constructor.
    // Creates an invalid handle if body type
    // is correct.
    
    Signal1C(const DataT &defV)
      : Signal0C(*new Signal1BodyC<DataT>(defV))
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    Signal1C(Signal1BodyC<DataT> &sig)
      : Signal0C(sig)
      {}
    //: Body constructor.
    
    inline Signal1BodyC<DataT> &Body() 
      { return static_cast<Signal1BodyC<DataT> &>(Signal0C::Body()); }
    //: Access body.
    
    inline const Signal1BodyC<DataT> &Body() const 
      { return static_cast<const Signal1BodyC<DataT> &>(Signal0C::Body()); }
    //: Access body.
    
  public:
    inline void Invoke(DataT &dat)
      { Body().Invoke(dat); }
    //: Send default signal.
    
    inline void operator()(DataT &dat)
      { Body().Invoke(dat); }
    //: Simple invokation.
    
    inline void operator()(const DataT &dat)
      { 
	DataT tmp(dat);
	Body().Invoke(tmp); 
      }
    //: Simple invokation.  
  };
  
  
  template<class DataT>
  ostream &operator<<(ostream &out,const Signal1C<DataT> &) { 
    assert(0); // Not implemented.
    return out;
  }
  //: IO Operator.
  // Not implemented
  
  ////////////////////////////
  
  template<class DataT>
  SignalInterConnect1BodyC<DataT>::SignalInterConnect1BodyC(Signal0C &from,Signal1C<DataT> &targ)
  : SignalConnector0BodyC(from),
    SignalConnector1BodyC<DataT>(from),
    SignalInterConnect0BodyC(from,targ)
  {}
  
  template<class DataT>
  inline
  void SignalInterConnect1BodyC<DataT>::Invoke(DataT &dat) { 
    assert(dynamic_cast<Signal1BodyC<DataT> *>(&Target()) != 0);
    dynamic_cast<Signal1BodyC<DataT> &>(Target()).Invoke(dat);
  }
  
  template<class DataT>
  inline
  void SignalInterConnect1BodyC<DataT>::Invoke()
  { Invoke(defaultVal); }
  
  template<class DataT>
  inline 
  SignalConnectorC Connect(Signal0C &from,Signal1C<DataT> &oth) { 
    assert(from.IsValid());
    assert(oth.IsValid());
    return SignalInterConnect1C<DataT>(from,oth);  
  }
  
  // Connect to another signal
  
  template<class DataT>  
  inline 
  SignalConnectorC Connect(Signal0C &from,void (*func)(DataT &),const DataT &def = DataT()) {
    assert(from.IsValid());
    return Signal1FuncC<DataT>(from,func,def);  
  }
  //: Connect to a function.

  template<class ObjT,class DataT>
  inline
  SignalConnectorC Connect(Signal0C &from,const ObjT &obj,void (ObjT::* func)(DataT &arg),const DataT &def = DataT()) { 
    assert(from.IsValid());
    return Signal1MethodC<DataT,ObjT>(from,obj,func,def);
  }
  //:Connect to a method.
  
  template<class ObjT,class DataT>
  inline
  SignalConnectorC ConnectRef(Signal0C &from,ObjT &obj,void (ObjT::* func)(DataT &arg),const DataT &def = DataT()) { 
    assert(from.IsValid());
    return Signal1MethodRefC<DataT,ObjT>(from,obj,func,def);
  }
  //:Connect to a method.
  // Uses refrence to object not instance. <p>
  // NB. It is the users responsibility to ensure the object
  // remains valid while being used.
}
#endif
