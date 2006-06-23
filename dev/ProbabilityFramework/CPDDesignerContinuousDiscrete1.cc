// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/CPDDesignerContinuousDiscrete1.hh"
#include "Ravl/Prob/CPDContinuousDiscrete1.hh"
#include "Ravl/Prob/PDFDesignerFactory.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  CPDDesignerContinuousDiscrete1BodyC::CPDDesignerContinuousDiscrete1BodyC() {
  }

  CPDDesignerContinuousDiscrete1BodyC::~CPDDesignerContinuousDiscrete1BodyC() {
  }

  ConditionalProbabilityDistributionC CPDDesignerContinuousDiscrete1BodyC::CreateCPD(const DListC<Tuple2C<RandomVariableValueC,PropositionC> >& propositionPairs) const {
    // check that there is at least one sample!
    if (propositionPairs.Size() == 0)
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), propositionPairs must contain at least one sample!");
    RandomVariableContinuousC dependentVariable = CheckDependentVariable(propositionPairs.First().Data1().RandomVariable());
    // check that the domain is suitable
    DomainC parentDomain = propositionPairs.First().Data2().Domain();
    if (parentDomain.NumVariables() != 1)
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), parent domain must have 1 variable");
    RandomVariableDiscreteC parentVariable = CheckParentVariable(parentDomain.Variable(0));
    // create a list for each value of the parent variable
    RCHashC<RandomVariableValueDiscreteC,DListC<RealT> > valuesByParent;
    // put each entry into the correct list
    for (DLIterC<Tuple2C<RandomVariableValueC,PropositionC> > it(propositionPairs); it; it++) {
      if (it->Data1().RandomVariable() != dependentVariable)
        throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), incorrect dependent value in sample");
      if (it->Data2().Domain() != parentDomain)
        throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), all propositions must belong to correct domain");
      if (it->Data2().NumValues() != 1)
        throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), all propositions must have 1 fixed value");
      RandomVariableValueDiscreteC parent(it->Data2().Value(0));
      RealT value = ((RandomVariableValueContinuousC)it->Data1()).Value();
      valuesByParent[parent].InsLast(value);
    }
    // check that there are samples for each parent value
    if (valuesByParent.Size() != parentVariable.NumValues())
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), there must be examples for each parent value");
    // create all the probability distributions
    RCHashC<RandomVariableValueDiscreteC,PDFContinuousAbstractC> probabilityDistributionTable;
    for (HashIterC<RandomVariableValueDiscreteC,DListC<RealT> > ht(valuesByParent); ht; ht++) {
      PDFContinuousAbstractC pdf = PDFDesignerFactoryC::GetInstance().DesignPDFContinuous(dependentVariable, ht.Data());
      probabilityDistributionTable.Insert(ht.Key(), pdf);
    }
    // and finally create the CPD
    return CPDContinuousDiscrete1C(dependentVariable, parentVariable, probabilityDistributionTable);
  }

  RandomVariableContinuousC CPDDesignerContinuousDiscrete1BodyC::CheckDependentVariable(const RandomVariableContinuousC& dependentVariable) {
    if (!dependentVariable.IsValid())
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::SetDependentVariable(), dependent variable must be valid continuous");
    return dependentVariable;
  }

  RandomVariableDiscreteC CPDDesignerContinuousDiscrete1BodyC::CheckParentVariable(const RandomVariableDiscreteC& parentVariable) {
    if (!parentVariable.IsValid())
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::SetParentVariable(), parent variable must be valid discrete");
    return parentVariable;
  }

  CPDDesignerContinuousDiscrete1C CPDDesignerContinuousDiscrete1C::m_instance;

  CPDDesignerContinuousDiscrete1C CPDDesignerContinuousDiscrete1C::GetInstance() {
    if (!m_instance.IsValid())
      m_instance = CPDDesignerContinuousDiscrete1C(true);
    return m_instance;
  }

}