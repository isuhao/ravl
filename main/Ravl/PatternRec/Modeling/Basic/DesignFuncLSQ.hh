// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNFUNCLSQ_HEADER
#define RAVL_DESIGNFUNCLSQ_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Numerical Modeling"

#include "Ravl/PatternRec/DesignFunctionSupervised.hh"
#include "Ravl/PatternRec/FuncLinearCoeff.hh"

namespace RavlN {
  class MatrixRUTC;
  
  //! userlevel=Normal
  //: Design function with Least Squares Fitting.
  
  class DesignFuncLSQBodyC
    : public DesignFunctionSupervisedBodyC
  {
  public:
    DesignFuncLSQBodyC()
    {}
    //: Default constructor.
    
    DesignFuncLSQBodyC(UIntT norder,bool northogonal);
    //: Create least squares designer.
    
    virtual FuncLinearCoeffC CreateFunc(UIntT nin,UIntT nout);
    //: Create new function.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out);
    //: Create function from the given data.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight);
    //: Create function from the given data, and sample weights.
    
    SArray1dC<IntT> FindCorelatedParameters(const MatrixRUTC &mat,RealT thresh = 1e-6);
    //: Find correlated paramiters.
    // The array contains -1 if the paramiter is independant or the number of the 
    // paramiter it corelates with.
    
  protected:
    UIntT order;
    bool orthogonal;
  };

  //! userlevel=Normal
  //: Design function with Least Squares Fitting.
  
  class DesignFuncLSQC
    : public DesignFunctionSupervisedC
  {
  public:
    DesignFuncLSQC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignFuncLSQC(UIntT order,bool orthogonal)
      : DesignFunctionSupervisedC(*new DesignFuncLSQBodyC(order,orthogonal))
    {}
    //: Create designer.
    
  protected:
    
  };
  
}


#endif
