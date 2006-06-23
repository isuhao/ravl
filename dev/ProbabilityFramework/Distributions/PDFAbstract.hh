// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFABSTRACT_HEADER
#define RAVLPROB_PDFABSTRACT_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/ProbabilityDistribution.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Abstract implementation for probability distributions containing common variable
  class PDFAbstractBodyC
    : public ProbabilityDistributionBodyC {
  public:
    PDFAbstractBodyC(const RandomVariableC& randomVariable);
    //: Constructor

    virtual ~PDFAbstractBodyC();
    //: Destructor
    
    virtual RandomVariableC RandomVariable() const;
    //: Get the variable for the probability distribution

  private:
    void SetRandomVariable(const RandomVariableC& randomVariable);
    //: Set the variable for the probability distribution

  private:
    RandomVariableC m_randomVariable;
    //: The variable for the probability distribution
  };

  //! userlevel=Normal
  //: Abstract implementation for probability distributions containing common variable
  //!cwiz:author
  
  class PDFAbstractC
    : public ProbabilityDistributionC
  {
  public:
    PDFAbstractC()
    {}
    //: Default constructor makes invalid handle

  protected:
    PDFAbstractC(PDFAbstractBodyC &bod)
     : ProbabilityDistributionC(bod)
    {}
    //: Body constructor. 
    
    PDFAbstractC(const PDFAbstractBodyC *bod)
     : ProbabilityDistributionC(bod)
    {}
    //: Body constructor. 
    
    PDFAbstractBodyC& Body()
    { return static_cast<PDFAbstractBodyC &>(ProbabilityDistributionC::Body()); }
    //: Body Access. 
    
    const PDFAbstractBodyC& Body() const
    { return static_cast<const PDFAbstractBodyC &>(ProbabilityDistributionC::Body()); }
    //: Body Access. 
    
  };

}

#endif