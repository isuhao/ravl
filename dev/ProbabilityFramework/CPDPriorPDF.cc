// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Omni/Prob/CPDPriorPDF.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  CPDPriorPDFBodyC::CPDPriorPDFBodyC(const ProbabilityDistributionC& probabilityDistribution)
    : CPDAbstractBodyC(probabilityDistribution.RandomVariable(), DomainC(HSetC<RandomVariableC>())) {
    SetProbabilityDistribution(probabilityDistribution);
  }

  CPDPriorPDFBodyC::~CPDPriorPDFBodyC() {
  }

  ProbabilityDistributionC CPDPriorPDFBodyC::ConditionalDistribution(const PropositionC& parentValues) const {
    HSetC<RandomVariableValueC> values = parentValues.Values();
    if (values.Size() != 0)
      throw ExceptionC("CPDPriorPDFBodyC::ConditionalDistribution(), must have empty proposition");
    return m_pdf;
  }
  
  void CPDPriorPDFBodyC::SetProbabilityDistribution(const ProbabilityDistributionC& probabilityDistribution) {
    // check that the pdf is valid
    if (!probabilityDistribution.IsValid())
      throw ExceptionC("CPDPriorPDFBodyC::SetProbabilityDistribution(), pdf is invalid");
    m_pdf = probabilityDistribution;
  }

}
