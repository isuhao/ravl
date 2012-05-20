// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2012, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNKNEARESTNEIGHBOUR_HEADER
#define RAVL_DESIGNKNEARESTNEIGHBOUR_HEADER 1
//! lib=RavlPatternRec
//! docentry="Ravl.API.Pattern Recognition.Classifier.DesignClassifier"
//! file="Ravl/PatternRec/Classify/DesignClassifierLogisticRegression.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"
#include "Ravl/PatternRec/DesignFunctionSupervised.hh"
#include "Ravl/PatternRec/DistanceSqrEuclidean.hh"
#include "Ravl/PatternRec/Optimise.hh"

namespace RavlN {
  

  //! userlevel=Develop
  //: Design a k nearest neighbour classifier
  
  class DesignClassifierLogisticRegressionBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignClassifierLogisticRegressionBodyC(RealT regularisation = 0,const OptimiseC &optimiser = OptimiseC());
    //: Constructor.

    DesignClassifierLogisticRegressionBodyC(const XMLFactoryContextC &factory);
    //: Construct from XML factory

    DesignClassifierLogisticRegressionBodyC(istream &strm);
    //: Load from stream.
    
    DesignClassifierLogisticRegressionBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor

    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.

    RealT Regularisation() const
    { return m_regularisation; }
    //: Access current regularisation parameter.

    void SetRegularisation(RealT regularisation)
    { m_regularisation = regularisation; }
    //: Set current regularisation parameter.

  protected:
    OptimiseC m_optimiser;
    RealT m_regularisation;
  };
  
  //! userlevel=Normal
   //: Design a k nearest neighbour classifier

  class DesignClassifierLogisticRegressionC
    : public DesignClassifierSupervisedC
  {
  public:
    DesignClassifierLogisticRegressionC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignClassifierLogisticRegressionC(RealT regularisation,const OptimiseC &optimiser = OptimiseC())
      : DesignClassifierSupervisedC(*new DesignClassifierLogisticRegressionBodyC(regularisation,optimiser))
    {}
    //: Create a new designer.

    DesignClassifierLogisticRegressionC(const XMLFactoryContextC &factory)
      :  DesignClassifierSupervisedC(*new DesignClassifierLogisticRegressionBodyC(factory))
    {}
    //: Construct from XML factory
    
    DesignClassifierLogisticRegressionC(istream &strm);
    //: Load from stream.
    
    DesignClassifierLogisticRegressionC(BinIStreamC &strm);
    //: Load from binary stream.

  protected:
    DesignClassifierLogisticRegressionC(DesignClassifierLogisticRegressionBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.

    DesignClassifierLogisticRegressionC(DesignClassifierLogisticRegressionBodyC *bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body ptr constructor.
    
    DesignClassifierLogisticRegressionBodyC &Body()
    { return static_cast<DesignClassifierLogisticRegressionBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
    const DesignClassifierLogisticRegressionBodyC &Body() const
    { return static_cast<const DesignClassifierLogisticRegressionBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
  public:
    
    RealT Regularisation() const
    { return Body().Regularisation(); }
    //: Access current regularisation parameter.

    void SetRegularisation(RealT regularisation)
    { Body().SetRegularisation(regularisation); }
    //: Set current regularisation parameter.


  };
  
  inline istream &operator>>(istream &strm,DesignClassifierLogisticRegressionC &obj) {
    obj = DesignClassifierLogisticRegressionC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const DesignClassifierLogisticRegressionC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,DesignClassifierLogisticRegressionC &obj) {
    obj = DesignClassifierLogisticRegressionC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const DesignClassifierLogisticRegressionC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}

#endif
