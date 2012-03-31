// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2011, Charles Galambos
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GENETIC_GENETICOPTIMISER_HH
#define RAVL_GENETIC_GENETICOPTIMISER_HH 1
//! lib=RavlGeneticOptimisation
//! author=Charles Galambos
//! docentry=Ravl.API.Math.Genetic.Optimisation

#include "Ravl/Genetic/EvaluateFitness.hh"
#include "Ravl/Genetic/Genome.hh"
#include "Ravl/Genetic/GenePalette.hh"
#include "Ravl/Threads/Mutex.hh"
#include <vector>
#include <map>

namespace RavlN { namespace GeneticN {


  //! Optimiser

  class GeneticOptimiserC
   : public RavlN::RCBodyVC
  {
  public:
    //! Factory constructor
    GeneticOptimiserC(const XMLFactoryContextC &factory);

    //! Set fitness function to use
    void SetFitnessFunction(EvaluateFitnessC &fitness);

    //! Run generation.
    void RunGeneration(UIntT generation);

    //! Save population to file
    //! Note: This thread safe
    bool SavePopulation(const StringC &filename) const;

    //! Save population to file
    //! Note: This thread safe
    bool LoadPopulation(const StringC &filename);

    //! Extract population from optimisers
    //! Note: This thread safe
    void ExtractPopulation(SArray1dC<RavlN::Tuple2C<float,GenomeC::RefT> > &population) const;

    //! Add population to optimisers, not this does not remove any entries already there
    //! Note: This thread safe
    void AddPopulation(const SArray1dC<RavlN::Tuple2C<float,GenomeC::RefT> > &population);

    //! Run whole optimisation
    void Run();

    //! Test if we're using a randomised domain
    bool IsUsingRandomisedDomain() const
    { return m_randomiseDomain; }

    //! Handle to optimiser
    typedef SmartPtrC<GeneticOptimiserC> RefT;

  protected:
    void Evaluate(const std::vector<GenomeC::RefT> &pop);

    void EvaluateWorker();

    //! Evaluate a single genome
    bool Evaluate(EvaluateFitnessC &evaluator,const GenomeC &genome,GenePaletteC &palette,float &score);

    float m_mutationRate;
    float m_crossRate;
    float m_keepFraction;
    float m_randomFraction;
    UIntT m_populationSize;
    UIntT m_numGenerations;
    float m_runLengthVirtual;
    float m_runLengthCPU;
    float m_terminateScore;
    bool m_createOnly; // Used for debugging.
    UIntT m_threads;

    EvaluateFitnessC::RefT m_evaluateFitness;
    RavlN::SArray1dC<GenomeC::RefT> m_currentSeeds;
    std::vector<GenomeC::RefT> m_startPopulation;
    std::multimap<float,GenomeC::RefT> m_population;
    GeneTypeC::RefT m_rootGeneType;

    RavlN::MutexC m_access;
    std::vector<GenomeC::RefT> m_workQueue;
    UIntT m_atWorkQueue;
    bool m_randomiseDomain; // Change the problem for each new generation
    UIntT m_runningAverageLength;

    GenePaletteC::RefT m_genePalette;
  };

}}

#endif
