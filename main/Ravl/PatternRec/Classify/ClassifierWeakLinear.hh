// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_WEAKLINEAR_HEADER
#define RAVL_WEAKLINEAR_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Robert Crida"
//! userlevel=Normal
//! docentry="Ravl.Pattern Recognition.Classifier"
//! file="Ravl/PatternRec/Classifier/ClassifierWeakLinear.hh"

#include "Ravl/PatternRec/Classifier.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Weak linear classifier
  // A weak linear classifier which uses a single feature to classify into one
  // of two classes using a threshold.
  
  class ClassifierWeakLinearBodyC 
    : public ClassifierBodyC
  {
  public:
    ClassifierWeakLinearBodyC(RealT threshold, RealT parity);
    //: Constructor
    //!param: threshold - a positive threshold value
    //!param: parity    - parity (+1 or -1) used to indicate direction of inequality
    // Classification is label 1 if parity*feature < parity*threshold
    
    ClassifierWeakLinearBodyC(istream &strm);
    //: Load from stream.
    
    ClassifierWeakLinearBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual UIntT Classify(const VectorC &data) const
    { 
      RavlAssert(data.Size() == 1);
      return Classify(data,m_featureSet);
    }
    //: Classifier vector 'data' return the most likely label.

    virtual UIntT Classify(const VectorC &data,const SArray1dC<IndexC> &featureSet) const
    { 
      RavlAssert(featureSet.Size() == 1); 
      return m_parity * data[featureSet[0]] < m_parityThreshold;
    }
    //: Classify vector using only the feature in the set
    
    virtual VectorC Confidence(const VectorC &data) const { 
      VectorC vec(2);
      vec.Fill(0.0);
      vec[Classify(data)] = 1.0;
      return vec;
    }
     //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the classifier used. The higher the confidence the more likely
    // it is the label is correct.
    
  protected:
    SArray1dC<IndexC> m_featureSet;
    RealT m_parityThreshold;
    RealT m_parity;
  };
  
  //! userlevel=Normal
  //: Weak linear classifier
  // A weak linear classifier which uses a single feature to classify into one
  // of two classes using a threshold.

  class ClassifierWeakLinearC 
    : public ClassifierC
  {
  public:
    ClassifierWeakLinearC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
    ClassifierWeakLinearC(RealT threshold, RealT parity)
      : ClassifierC(*new ClassifierWeakLinearBodyC(threshold,parity))
    {}
    //: Constructor.
    //!param: threshold - a positive threshold value
    //!param: parity    - parity (+1 or -1) used to indicate direction of inequality
    // Classification is label 1 if parity*feature < parity*threshold
   
    ClassifierWeakLinearC(istream &strm);
    //: Load from stream.
    
    ClassifierWeakLinearC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    ClassifierWeakLinearC(ClassifierWeakLinearBodyC &bod)
      : ClassifierC(bod)
    {}
    //: Body constructor.

    ClassifierWeakLinearC(ClassifierWeakLinearBodyC *bod)
      : ClassifierC(bod)
    {}
    //: Body ptr constructor.
  };
      
}
#endif
