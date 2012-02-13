// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2011, Charles Galambos
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GENETIC_GPInstIncrement_HH
#define RAVL_GENETIC_GPInstIncrement_HH 1
//! lib=RavlGeneticProgram
//! author=Charles Galambos
//! docentry=Ravl.API.Math.Genetic.Programming

#include "Ravl/Genetic/GPInstruction.hh"
#include "Ravl/Genetic/GPVariable.hh"
#include "Ravl/Genetic/GeneFactory.hh"

namespace RavlN { namespace GeneticN {

  //! An environment for an agent.

  template<typename DataT>
  class GPInstIncrementC
   : public GPInstructionC
  {
  public:
    //! Factory constructor
    GPInstIncrementC(const GeneFactoryC &factory)
    {
      factory.Get("var1",m_variable1,*GPVariableC<DataT>::GeneType());
    }

    //! Constructor
    GPInstIncrementC()
    {}

    //! Access gene type for instructions
    static GeneTypeC::RefT &GeneType() {
      static GeneTypeC::RefT x = new GeneTypeClassC(typeid(typename GPInstIncrementC<DataT>::RefT));
      return x;
    }

    //! Execute instruction
    virtual bool Execute(GPExecutionContextC &context) {
      if(!m_variable1->IsSet()) {
        m_variable1->Set(0);
      }
      m_variable1->Set(m_variable1->Data() + 1);
      return m_variable1->Data() > 0;
    }

    //! Handle to this class.
    typedef RavlN::SmartPtrC<GPInstIncrementC<DataT> > RefT;

  protected:
    typename GPVariableC<DataT>::RefT m_variable1;
  };


}}

#endif
