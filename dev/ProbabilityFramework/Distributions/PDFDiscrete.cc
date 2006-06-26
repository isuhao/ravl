// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFDiscreteBodyC::PDFDiscreteBodyC(const RandomVariableDiscreteC& variable, const RCHashC<RandomVariableValueDiscreteC,RealT>& probabilityLookupTable)
    : PDFAbstractBodyC(variable)
  {
    SetProbabilityLookupTable(probabilityLookupTable);
  }

  PDFDiscreteBodyC::PDFDiscreteBodyC(const RandomVariableDiscreteC& variable)
    : PDFAbstractBodyC(variable)
  {
    // Note that the probability table has not been set up, hope you know what you are doing!
  }

  PDFDiscreteBodyC::~PDFDiscreteBodyC() {
  }

  RealT PDFDiscreteBodyC::MeasureProbability(const RandomVariableValueC& value) const {
    if (value.Variable() != Variable())
      throw ExceptionC("ProbabilityDistributionDiscreteBodyC::MeasureProbability(), value doesn't match variable of this distribution");
    RealT probability = 0.0;
    if (!m_probabilityLookupTable.Lookup(value, probability))
      throw ExceptionC("ProbabilityDistributionDiscreteBodyC::MeasureProbability(), couldn't find value in table");
    return probability;
  }

  RandomVariableDiscreteC PDFDiscreteBodyC::RandomVariableDiscrete() const {
    return RandomVariableDiscreteC(Variable());
  }

  void PDFDiscreteBodyC::SetProbabilityLookupTable(const RCHashC<RandomVariableValueDiscreteC,RealT>& probabilityLookupTable) {
    if (probabilityLookupTable.Size() != RandomVariableDiscrete().NumValues())
      throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), table must have entry for each value of variable");
    // check that the table has been initialized properly and that all values sum to 1.0
    RealT sum = 0.0;
    for (HashIterC<RandomVariableValueDiscreteC,RealT> it(probabilityLookupTable); it; it++) {
      if (*it < 0.0)
        throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), table can't have negative entries");
      if (it.Key().Variable() != Variable())
        throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), lookup table entry doesn't match random variable!");
      sum += *it;
    }
    // check that the sum is close to 1
    if (Abs(sum - 1.0) > 1e-6)
      throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), table doesn't sum to 1.0");
    m_probabilityLookupTable = probabilityLookupTable.Copy();
  }

  StringC PDFDiscreteBodyC::ToString() const {
    StringC string = RandomVariableDiscrete().ToString() + "=<";
    HSetIterC<StringC> ht(RandomVariableDiscrete().Values());
    RandomVariableValueDiscreteC discreteValue(RandomVariableDiscrete(), *ht);
    string += StringC(MeasureProbability(discreteValue));
    for (ht++ ; ht; ht++) {
      string += ",";
      RandomVariableValueDiscreteC discreteValue(RandomVariableDiscrete(), *ht);
      string += StringC(MeasureProbability(discreteValue));
    }
    string += ">";
    return string;
  }

}
