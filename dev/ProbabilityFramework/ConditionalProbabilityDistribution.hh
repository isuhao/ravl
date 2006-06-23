// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CONDITIONALPROBABILITYDISTRIBUTION_HEADER
#define RAVLPROB_CONDITIONALPROBABILITYDISTRIBUTION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/Proposition.hh"
#include "Ravl/Prob/ProbabilityDistribution.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Base class for conditional probability distributions
  class ConditionalProbabilityDistributionBodyC
    : public RCBodyVC {
  public:
    ConditionalProbabilityDistributionBodyC();
    //: Constructor

    virtual ~ConditionalProbabilityDistributionBodyC();
    //: Destructor
    
    virtual RealT ConditionalProbability(const RandomVariableValueC& value, const PropositionC& parentValues) const=0;
    //: Calculate the conditional probability P(value|parentValues)
    //!param: value - a value for the random variable
    //!param: parentValues - a proposition with fixed values for some (or all) parent variables
    //!return: the conditional probability of the proposition
    // This is the sum of probabilities for the subset of variable values

    virtual ProbabilityDistributionC ConditionalDistribution(const PropositionC& parentValues) const=0;
    //: Calculate the probability distribution for P(V|parentValues)
    //!param: parentValues - a proposition with fixed values for some (or all) parent variables
    //!return: the probability distribution of the random variable

    virtual RandomVariableC RandomVariable() const=0;
    //: Get the random variable that is the subject of the distribution

    virtual DomainC ParentDomain() const=0;
    //: Get the domain for the parent variables
  };

  //! userlevel=Normal
  //: Base class for conditional probability distributions
  //!cwiz:author
  
  class ConditionalProbabilityDistributionC
    : public RCHandleC<ConditionalProbabilityDistributionBodyC>
  {
  public:
    ConditionalProbabilityDistributionC()
    {}
    //: Default constructor makes invalid handle

    RealT ConditionalProbability(const RandomVariableValueC& value, const PropositionC& parentValues) const
    { return Body().ConditionalProbability(value, parentValues); }
    //: Calculate the conditional probability P(value|parentValues)
    //!param: value - a value for the random variable
    //!param: parentValues - a proposition with fixed values for some (or all) parent variables
    //!return: the conditional probability of the proposition
    // This is the sum of probabilities for the subset of variable values

    ProbabilityDistributionC ConditionalDistribution(const PropositionC& parentValues) const
    { return Body().ConditionalDistribution(parentValues); }
    //: Calculate the probability distribution for P(V|parentValues)
    //!param: parentValues - a proposition with fixed values for some (or all) parent variables
    //!return: the probability distribution of the random variable

    RandomVariableC RandomVariable() const
    { return Body().RandomVariable(); }
    //: Get the random variable that is the subject of the distribution

    DomainC ParentDomain() const
    { return Body().ParentDomain(); }
    //: Get the domain for the parent variables

  protected:
    ConditionalProbabilityDistributionC(ConditionalProbabilityDistributionBodyC &bod)
     : RCHandleC<ConditionalProbabilityDistributionBodyC>(bod)
    {}
    //: Body constructor. 
    
    ConditionalProbabilityDistributionC(const ConditionalProbabilityDistributionBodyC *bod)
     : RCHandleC<ConditionalProbabilityDistributionBodyC>(bod)
    {}
    //: Body constructor. 
    
    ConditionalProbabilityDistributionBodyC& Body()
    { return static_cast<ConditionalProbabilityDistributionBodyC &>(RCHandleC<ConditionalProbabilityDistributionBodyC>::Body()); }
    //: Body Access. 
    
    const ConditionalProbabilityDistributionBodyC& Body() const
    { return static_cast<const ConditionalProbabilityDistributionBodyC &>(RCHandleC<ConditionalProbabilityDistributionBodyC>::Body()); }
    //: Body Access. 
    
  };

}

#endif