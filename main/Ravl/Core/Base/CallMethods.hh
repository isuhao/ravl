// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CALLMETHODS_HEADER
#define RAVL_CALLMETHODS_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Calls"
//! lib=RavlCore
//! author="Charles Galambos"
//! file="Ravl/Core/Base/CallMethods.hh"
//! date="24/01/2001"

#include "Ravl/Calls.hh"

namespace RavlN {
  
  //////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class ObjT,class RetT = bool>
  class CallMethod0BodyC
    : public CallFunc0BodyC<RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    
    CallMethod0BodyC(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)())
      : CallFunc0BodyC<RetT>((VoidFuncPtrT) 0),
	mPtr(nfunc),
	obj(const_cast<BaseObjT &>(nobj))
    {}
    //: Constructor.
    
    virtual void Invoke()
    { (obj.*FuncPtr())(); }
    //: Invoke event.
    
  protected:
    typedef RetT (BaseObjT::*FuncT)();
    //: Function ptr type.
    
    virtual RCBodyVC &Copy() const
    { return *new CallMethod0BodyC<ObjT,RetT>(const_cast<BaseObjT &>(obj),FuncPtr()); }
    //: Copy call.
    
    FuncT mPtr;
    
    inline
    FuncT FuncPtr() const
    { return mPtr; }
    //: Function.
    
    ObjT obj;
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class ObjT,class RetT = bool>
  class CallMethod0C
    : public CallFunc0C<RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    
    CallMethod0C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallMethod0C(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)())
      : CallFunc0C<RetT>(*new CallMethod0BodyC<ObjT,RetT>(nobj,nfunc))
    {}
    //:  Constructor.
  };

  /////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class ObjT,class DataT,class RetT = bool>
  class CallMethod1BodyC
    : public CallFunc1BodyC<DataT,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    
    CallMethod1BodyC(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(DataT),const Arg1T &ndat)
      : CallFunc1BodyC<DataT,RetT>((VoidFuncPtrT) 0,ndat),
	mPtr(nfunc),
        obj(const_cast<BaseObjT &>(nobj))
    {}
    //: Constructor.
    
    virtual void Invoke()
    { (obj.*FuncPtr())(dat1); }
    //: Invoke event.

    virtual RetT Call()
    { return (obj.*FuncPtr())(dat1); }
    //: Invoke event, with paramiter.
    
    virtual RetT Call(Arg1T &pd)
    { return (obj.*FuncPtr())(pd); }
    //: Invoke event, with paramiter.

  protected:
    typedef RetT (BaseObjT::*FuncT)(DataT);
    //: Function ptr type.
    
    virtual RCBodyVC &Copy() const
    { return *new CallMethod1BodyC<ObjT,DataT,RetT>(const_cast<BaseObjT &>(obj),FuncPtr(),dat1); }
    //: Copy call.

    FuncT mPtr;
    
    inline
    FuncT FuncPtr() const
    { return mPtr; }
    //: Function.
    
    ObjT obj;
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class ObjT,class DataT,class RetT = bool>
  class CallMethod1C
    : public CallFunc1C<DataT,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<DataT>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    
    CallMethod1C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallMethod1C(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(DataT), const Arg1T &dat = Arg1T())
      : CallFunc1C<DataT,RetT>(*new CallMethod1BodyC<ObjT,DataT,RetT>(nobj,nfunc,dat))
    {}
    //: Constructor.
  };

  /////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class RetT = bool>
  class CallMethod2BodyC
    : public CallFunc2BodyC<Data1T,Data2T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    typedef RetT (BaseObjT::*FuncT)(Data1T,Data2T);    //: Function ptr type.
    
    CallMethod2BodyC(const BaseObjT &nobj,FuncT nfunc,const Arg1T &ndat1,const Arg2T &ndat2)
      : CallFunc2BodyC<Data1T,Data2T,RetT>((VoidFuncPtrT) 0,ndat1,ndat2),
	mPtr(nfunc),
	obj(const_cast<BaseObjT &>(nobj))
    {}
    //: Constructor.
    
    virtual void Invoke()
    { (obj.*FuncPtr())(dat1,dat2); }
    //: Invoke event.
    
    virtual RetT Call()
    { return (obj.*FuncPtr())(dat1,dat2); }
    //: Invoke event, with paramiter.
    
    virtual RetT Call(Arg1T &pd)
    { return (obj.*FuncPtr())(pd,dat2); }
    //: Invoke event, with paramiter.

    virtual RetT Call(Arg1T &pd1,Arg2T &pd2)
    { return (obj.*FuncPtr())(pd1,pd2); }
    //: Invoke event, with paramiter.
    
  protected:
    
    inline
    FuncT FuncPtr() const
    { return mPtr; }
    //: Function.

    virtual RCBodyVC &Copy() const
    { return *new CallMethod2BodyC<ObjT,Data1T,Data2T,RetT>(const_cast<BaseObjT &>(obj),FuncPtr(),dat1,dat2); }
    //: Copy call.
    
    FuncT mPtr;
    
    ObjT obj;
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class RetT = bool>
  class CallMethod2C
    : public CallFunc2C<Data1T,Data2T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    
    CallMethod2C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallMethod2C(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(Data1T,Data2T),
		 const Arg1T &ndat1 = Arg1T(),const Arg2T &ndat2 = Arg2T())
      : CallFunc2C<Data1T,Data2T,RetT>(*new CallMethod2BodyC<ObjT,Data1T,Data2T,RetT>(nobj,nfunc,ndat1,ndat2))
    {}
    //: Default constructor.
    // Creates an invalid handle.
  };
  
  /////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class RetT = bool>
  class CallMethod3BodyC
    : public CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data3T>::BaseTypeT Arg3T; //: Basic type of arg, ignore references and const's
    
    CallMethod3BodyC(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(Data1T,Data2T,Data3T),
		     const Arg1T &ndat1,const Arg2T &ndat2,const Arg3T &ndat3)
      : CallFunc3BodyC<Data1T,Data2T,Data3T,RetT>((VoidFuncPtrT) 0,ndat1,ndat2,ndat3),
	mPtr(nfunc),
        obj(const_cast<BaseObjT &>(nobj))
    {}
    //: Constructor.
    
    virtual void Invoke()
    { (obj.*FuncPtr())(dat1,dat2,dat3); }
    //: Invoke event.
    
    virtual RetT Call()
    { return (obj.*FuncPtr())(dat1,dat2,dat3); }
    //: Invoke event, with paramiter.

    virtual RetT Call(Arg1T &pd)
    { return (obj.*FuncPtr())(pd,dat2,dat3); }
    //: Invoke event, with paramiter.

    virtual RetT Call(Arg1T &pd1,Arg2T &pd2)
    { return (obj.*FuncPtr())(pd1,pd2,dat3); }
    //: Invoke event, with paramiter.
    
    virtual RetT Call(Arg1T &pd1,Arg2T &pd2,Arg3T &pd3)
    { return (obj.*FuncPtr())(pd1,pd2,pd3); }
    //: Invoke event, with paramiter.
    
  protected:
    typedef RetT (BaseObjT::*FuncT)(Data1T,Data2T,Data3T);
    //: Function ptr type.

    virtual RCBodyVC &Copy() const
    { return *new CallMethod3BodyC<ObjT,Data1T,Data2T,Data3T,RetT>(const_cast<BaseObjT &>(obj),FuncPtr(),dat1,dat2,dat3); }
    //: Copy call.
    
    FuncT mPtr;
    
    inline
    FuncT FuncPtr() const
    { return mPtr; }
    //: Function.
    
    ObjT obj;
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class RetT = bool>
  class CallMethod3C
    : public CallFunc3C<Data1T,Data2T,Data3T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data3T>::BaseTypeT Arg3T; //: Basic type of arg, ignore references and const's
    
    CallMethod3C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallMethod3C(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(Data1T,Data2T,Data3T),
		 const Arg1T &ndat1 = Arg1T(),const Arg2T &ndat2 = Arg2T(),const Arg3T &ndat3 = Arg3T())
      : CallFunc3C<Data1T,Data2T,Data3T,RetT>(*new CallMethod3BodyC<ObjT,Data1T,Data2T,Data3T,RetT>(nobj,nfunc,ndat1,ndat2,ndat3))
    {}
    //: Constructor.
  };
  
  /////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class RetT = bool>
  class CallMethod4BodyC
    : public CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data3T>::BaseTypeT Arg3T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data4T>::BaseTypeT Arg4T; //: Basic type of arg, ignore references and const's
    
    CallMethod4BodyC(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T),const Arg1T &ndat1,const Arg2T &ndat2,const Arg3T &ndat3,const Arg4T &ndat4)
      : CallFunc4BodyC<Data1T,Data2T,Data3T,Data4T,RetT>((VoidFuncPtrT) 0,ndat1,ndat2,ndat3,ndat4),
	mPtr(nfunc),
	obj(const_cast<BaseObjT &>(nobj))
    {}
    //: Constructor.
    
    virtual void Invoke()
    { (obj.*FuncPtr())(dat1,dat2,dat3,dat4); }
    //: Invoke event.

    virtual RetT Call()
    { return (obj.*FuncPtr())(dat1,dat2,dat3,dat4); }
    //: Invoke event.

    virtual RetT Call(Arg1T &pd)
    { return (obj.*FuncPtr())(pd,dat2,dat3,dat4); }
    //: Invoke event, with paramiters.

    virtual RetT Call(Arg1T &pd1,Arg2T &pd2)
    { return (obj.*FuncPtr())(pd1,pd2,dat3,dat4); }
    //: Invoke event, with paramiters.
    
    virtual RetT Call(Arg1T &pd1,Arg2T &pd2,Arg3T &pd3)
    { return (obj.*FuncPtr())(pd1,pd2,pd3,dat4); }
    //: Invoke event, with paramiters.
    
    virtual RetT Call(Arg1T &pd1,Arg2T &pd2,Arg3T &pd3,Arg4T &pd4)
    { return (obj.*FuncPtr())(pd1,pd2,pd3,pd4); }
    //: Invoke event, with paramiters.
    
  protected:
    typedef RetT (BaseObjT::*FuncT)(Data1T,Data2T,Data3T,Data4T);
    //: Function ptr type.

    virtual RCBodyVC &Copy() const
    { return *new CallMethod4BodyC<ObjT,Data1T,Data2T,Data3T,Data4T,RetT>(const_cast<BaseObjT &>(obj),FuncPtr(),dat1,dat2,dat3,dat4); }
    //: Copy call.
    
    FuncT mPtr;

    inline
    FuncT FuncPtr() const
    { return mPtr; }
    //: Function.
    
    ObjT obj;
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class RetT = bool>
  class CallMethod4C
    : public CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data3T>::BaseTypeT Arg3T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data4T>::BaseTypeT Arg4T; //: Basic type of arg, ignore references and const's
    
    CallMethod4C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallMethod4C(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T),
		 const Arg1T &ndat1 = Arg1T(),const Arg2T &ndat2 = Arg2T(),const Arg3T &ndat3 = Arg3T(),const Arg4T &ndat4 = Arg4T())
      : CallFunc4C<Data1T,Data2T,Data3T,Data4T,RetT>(*new CallMethod4BodyC<ObjT,Data1T,Data2T,Data3T,Data4T,RetT>(nobj,nfunc,ndat1,ndat2,ndat3,ndat4))
    {}
    //: Constructor.
  };

  /////////////////////////////////////////////////////////

  //! userlevel=Develop
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class RetT = bool>
  class CallMethod5BodyC
    : public CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data3T>::BaseTypeT Arg3T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data4T>::BaseTypeT Arg4T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data5T>::BaseTypeT Arg5T; //: Basic type of arg, ignore references and const's
    
    CallMethod5BodyC(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T,Data5T),
		     const Arg1T &ndat1 = Arg1T(),
		     const Arg2T &ndat2 = Arg2T(),
		     const Arg3T &ndat3 = Arg3T(),
		     const Arg4T &ndat4 = Arg4T(),
		     const Arg5T &ndat5 = Arg5T())
      : CallFunc5BodyC<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>((VoidFuncPtrT) 0,ndat1,ndat2,ndat3,ndat4,ndat5),
	mPtr(nfunc),
	obj(const_cast<BaseObjT &>(nobj))
    {}
    //: Constructor.
    
    virtual void Invoke()
    { (obj.*FuncPtr())(dat1,dat2,dat3,dat4,dat5); }
    //: Invoke event.

    virtual RetT Call()
    { return (obj.*FuncPtr())(dat1,dat2,dat3,dat4,dat5); }
    //: Invoke event.

    virtual RetT Call(Arg1T &pd)
    { return (obj.*FuncPtr())(pd,dat2,dat3,dat4,dat5); }
    //: Invoke event, with paramiters.

    virtual RetT Call(Arg1T &pd1,Arg2T &pd2)
    { return (obj.*FuncPtr())(pd1,pd2,dat3,dat4,dat5); }
    //: Invoke event, with paramiters.
    
    virtual RetT Call(Arg1T &pd1,Arg2T &pd2,Arg3T &pd3)
    { return (obj.*FuncPtr())(pd1,pd2,pd3,dat4,dat5); }
    //: Invoke event, with paramiters.
    
    virtual RetT Call(Arg1T &pd1,Arg2T &pd2,Arg3T &pd3,Arg4T &pd4)
    { return (obj.*FuncPtr())(pd1,pd2,pd3,pd4,dat5); }
    //: Invoke event, with paramiters.

    virtual RetT Call(Arg1T &pd1,Arg2T &pd2,Arg3T &pd3,Arg4T &pd4,Arg5T &pd5)
    { return (obj.*FuncPtr())(pd1,pd2,pd3,pd4,pd5); }
    //: Invoke event, with paramiters.
    
  protected:
    typedef RetT (BaseObjT::*FuncT)(Data1T,Data2T,Data3T,Data4T,Data5T);
    //: Function ptr type.
    
    FuncT mPtr;
    
    virtual RCBodyVC &Copy() const
    { return *new CallMethod5BodyC<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(const_cast<BaseObjT &>(obj),FuncPtr(),dat1,dat2,dat3,dat4,dat5); }
    //: Copy call.
    
    inline
    FuncT FuncPtr() const
    { return mPtr; }
    //: Function.
    
    ObjT obj;
  };
  
  //! userlevel=Advanced
  //: Signal Event handle
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class RetT = bool>
  class CallMethod5C
    : public  CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>
  {
  public:
    typedef typename TraitsC<ObjT>::BaseTypeT BaseObjT; //: Basic type of object, ignore references and const's
    typedef typename TraitsC<Data1T>::BaseTypeT Arg1T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data2T>::BaseTypeT Arg2T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data3T>::BaseTypeT Arg3T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data4T>::BaseTypeT Arg4T; //: Basic type of arg, ignore references and const's
    typedef typename TraitsC<Data5T>::BaseTypeT Arg5T; //: Basic type of arg, ignore references and const's
    
    CallMethod5C()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    CallMethod5C(const BaseObjT &nobj,RetT (BaseObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T,Data5T),const Arg1T &ndat1,const Arg2T &ndat2,const Arg3T &ndat3,const Arg4T &ndat4,const Arg5T &ndat5)
      :  CallFunc5C<Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(*new CallMethod5BodyC<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(nobj,nfunc,ndat1,ndat2,ndat3,ndat4,ndat5))
    {}
    //: Constructor.
  };

  //! userlevel=Normal

#if !defined(VISUAL_CPP)

  template<class ObjT,class RetT>
  inline
  CallMethod0C<ObjT,RetT> 
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)())
  { return CallMethod0C<ObjT,RetT>(const_cast<ObjT &>(nobj),nfunc); }
  
  template<class ObjT,class DataT,class RetT>
  inline
  CallMethod1C<ObjT,DataT,RetT> 
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(DataT),const typename TraitsC<DataT>::BaseTypeT &dat)
  { return CallMethod1C<ObjT,DataT,RetT>(const_cast<ObjT &>(nobj),nfunc,dat); }
  
  template<class ObjT,class Data1T,class Data2T,class RetT>
  inline
  CallMethod2C<ObjT,Data1T,Data2T,RetT> 
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2
	  )
  { return CallMethod2C<ObjT,Data1T,Data2T,RetT>(nobj,nfunc,dat1,dat2); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class RetT>
  inline
  CallMethod3C<ObjT,Data1T,Data2T,Data3T,RetT>
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3
	  )
  { return CallMethod3C<ObjT,Data1T,Data2T,Data3T,RetT>(nobj,nfunc,dat1,dat2,dat3); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class RetT>
  inline
  CallMethod4C<ObjT,Data1T,Data2T,Data3T,Data4T,RetT>
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4
	  )
  { return CallMethod4C<ObjT,Data1T,Data2T,Data3T,Data4T,RetT>(nobj,nfunc,dat1,dat2,dat3,dat4); }

  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class RetT>
  inline
  CallMethod5C<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T,RetT>
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T,Data5T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4,
	  const typename TraitsC<Data5T>::BaseTypeT &dat5
	  )
  { return CallMethod5C<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(nobj,nfunc,dat1,dat2,dat3,dat4,dat5); }
  
  // Refrence methods.
  
  template<class ObjT,class RetT>
  inline
  CallMethod0C<ObjT &,RetT> 
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)())
  { return CallMethod0C<ObjT &,RetT>(nobj,nfunc); }
  
  template<class ObjT,class DataT,class RetT>
  inline
  CallMethod1C<ObjT &,DataT,RetT> 
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(DataT),const typename TraitsC<DataT>::BaseTypeT &dat)
  { return CallMethod1C<ObjT &,DataT,RetT>(nobj,nfunc,dat); }
  
  template<class ObjT,class Data1T,class Data2T,class RetT>
  inline
  CallMethod2C<ObjT &,Data1T,Data2T,RetT> 
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2
	  )
  { return CallMethod2C<ObjT &,Data1T,Data2T,RetT>(nobj,nfunc,dat1,dat2); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class RetT>
  inline
  CallMethod3C<ObjT &,Data1T,Data2T,Data3T,RetT>
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3
	  )
  { return CallMethod3C<ObjT &,Data1T,Data2T,Data3T,RetT>(nobj,nfunc,dat1,dat2,dat3); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class RetT>
  inline
  CallMethod4C<ObjT &,Data1T,Data2T,Data3T,Data4T,RetT>
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4
	  )
  { return CallMethod4C<ObjT &,Data1T,Data2T,Data3T,Data4T,RetT>(nobj,nfunc,dat1,dat2,dat3,dat4); }

  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class RetT>
  inline
  CallMethod5C<ObjT &,Data1T,Data2T,Data3T,Data4T,Data5T,RetT>
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T,Data5T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4,
	  const typename TraitsC<Data5T>::BaseTypeT &dat5
	  )
  { return CallMethod5C<ObjT &,Data1T,Data2T,Data3T,Data4T,Data5T,RetT>(nobj,nfunc,dat1,dat2,dat3,dat4,dat5); }
  
#else
  
  template<class ObjT>
  inline
  CallMethod0C<ObjT,bool> 
  Trigger(const ObjT &nobj,bool (ObjT::*nfunc)())
  { return CallMethod0C<ObjT,bool>(const_cast<ObjT &>(nobj),nfunc); }
  
  template<class ObjT,class DataT>
  inline
  CallMethod1C<ObjT,DataT,bool> 
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(DataT),const typename TraitsC<DataT>::BaseTypeT &dat)
  { return CallMethod1C<ObjT,DataT,bool>(const_cast<ObjT &>(nobj),nfunc,dat); }
  
  template<class ObjT,class Data1T,class Data2T>
  inline
  CallMethod2C<ObjT,Data1T,Data2T,bool> 
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2
	  )
  { return CallMethod2C<ObjT,Data1T,Data2T,bool>(nobj,nfunc,dat1,dat2); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  inline
  CallMethod3C<ObjT,Data1T,Data2T,Data3T,bool>
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3
	  )
  { return CallMethod3C<ObjT,Data1T,Data2T,Data3T,bool>(nobj,nfunc,dat1,dat2,dat3); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T>
  inline
  CallMethod4C<ObjT,Data1T,Data2T,Data3T,Data4T,bool>
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4
	  )
  { return CallMethod4C<ObjT,Data1T,Data2T,Data3T,Data4T,bool>(nobj,nfunc,dat1,dat2,dat3,dat4); }

  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  inline
  CallMethod5C<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T,bool>
  Trigger(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T,Data5T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4,
	  const typename TraitsC<Data5T>::BaseTypeT &dat5
	  )
  { return CallMethod5C<ObjT,Data1T,Data2T,Data3T,Data4T,Data5T,bool>(nobj,nfunc,dat1,dat2,dat3,dat4,dat5); }
  
  // Refrence methods.
  
  template<class ObjT>
  inline
  CallMethod0C<ObjT &,bool> 
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)())
  { return CallMethod0C<ObjT &,bool>(nobj,nfunc); }
  
  template<class ObjT,class DataT>
  inline
  CallMethod1C<ObjT &,DataT,bool> 
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(DataT),const typename TraitsC<DataT>::BaseTypeT &dat)
  { return CallMethod1C<ObjT &,DataT,bool>(nobj,nfunc,dat); }
  
  template<class ObjT,class Data1T,class Data2T>
  inline
  CallMethod2C<ObjT &,Data1T,Data2T,bool> 
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2
	  )
  { return CallMethod2C<ObjT &,Data1T,Data2T,bool>(nobj,nfunc,dat1,dat2); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T>
  inline
  CallMethod3C<ObjT &,Data1T,Data2T,Data3T,bool>
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3
	  )
  { return CallMethod3C<ObjT &,Data1T,Data2T,Data3T,bool>(nobj,nfunc,dat1,dat2,dat3); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T>
  inline
  CallMethod4C<ObjT &,Data1T,Data2T,Data3T,Data4T,bool>
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4
	  )
  { return CallMethod4C<ObjT &,Data1T,Data2T,Data3T,Data4T,bool>(nobj,nfunc,dat1,dat2,dat3,dat4); }
  
  template<class ObjT,class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  inline
  CallMethod5C<ObjT &,Data1T,Data2T,Data3T,Data4T,Data5T,bool>
  TriggerR(const ObjT &nobj,RetT (ObjT::*nfunc)(Data1T,Data2T,Data3T,Data4T,Data5T),
	  const typename TraitsC<Data1T>::BaseTypeT &dat1,
	  const typename TraitsC<Data2T>::BaseTypeT &dat2,
	  const typename TraitsC<Data3T>::BaseTypeT &dat3,
	  const typename TraitsC<Data4T>::BaseTypeT &dat4,
	  const typename TraitsC<Data5T>::BaseTypeT &dat5
	  )
  { return CallMethod5C<ObjT &,Data1T,Data2T,Data3T,Data4T,Data5T,bool>(nobj,nfunc,dat1,dat2,dat3,dat4,dat5); }

#endif

}


#endif
