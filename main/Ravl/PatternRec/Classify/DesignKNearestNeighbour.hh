// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNKNEARESTNEIGHBOUR_HEADER
#define RAVL_DESIGNKNEARESTNEIGHBOUR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Classifier"
//! file="Ravl/PatternRec/Classifier/DesignKNearestNeighbour.hh"

#include "Ravl/PatternRec/DesignClassifierSupervised.hh"
#include "Ravl/PatternRec/DesignFunctionSupervised.hh"
#include "Ravl/PatternRec/DistanceSqrEuclidean.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a discriminat function classifier.
  
  class DesignKNearestNeighbourBodyC
    : public DesignClassifierSupervisedBodyC
  {
  public:
    DesignKNearestNeighbourBodyC(UIntT k,const DistanceC &distMetric = DistanceSqrEuclideanC(),bool useAverageKNN = false);
    //: Constructor.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out);
    //: Create a clasifier.
    
    virtual ClassifierC Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out,const SampleC<RealT> &weight);
    //: Create a clasifier with weights for the samples.
    
  protected:
    UIntT k;
    DistanceC distanceMetric;
    bool useAverageKNN;
  };
  
  //! userlevel=Normal
  //: Design a discriminat function classifier.
  
  class DesignKNearestNeighbourC
    : public DesignClassifierSupervisedC
  {
  public:
    DesignKNearestNeighbourC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignKNearestNeighbourC(UIntT k,const DistanceC &distanceMetric = DistanceSqrEuclideanC(),bool useAverageKNN = false)
      : DesignClassifierSupervisedC(*new DesignKNearestNeighbourBodyC(k,distanceMetric,useAverageKNN))
    {}
    //: Create a new designer.
    // Values for k are typically 1 to 7 and should be odd.
    
  protected:
    DesignKNearestNeighbourC(DesignKNearestNeighbourBodyC &bod)
      : DesignClassifierSupervisedC(bod)
    {}
    //: Body constructor.
    
    DesignKNearestNeighbourBodyC &Body()
    { return static_cast<DesignKNearestNeighbourBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
    const DesignKNearestNeighbourBodyC &Body() const
    { return static_cast<const DesignKNearestNeighbourBodyC &>(DesignClassifierSupervisedC::Body()); }
    //: Access body.
    
  public:
    
  };

}

#endif
