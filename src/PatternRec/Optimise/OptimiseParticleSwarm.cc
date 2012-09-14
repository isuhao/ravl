// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Optimisation
//! file="Ravl/PatternRec/Optimise/OptimiseParticleSwarm.cc"

#include "Ravl/PatternRec/OptimiseParticleSwarm.hh"
#include "Ravl/PatternRec/DataSet4.hh"
#include "Ravl/PatternRec/DataSet4Iter.hh"
#include "Ravl/PatternRec/SampleReal.hh"
#include "Ravl/Random.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/SobolSequence.hh"
#include "Ravl/Plot/Plot2d.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/OS/Date.hh"

namespace RavlN {

  OptimiseParticleSwarmBodyC::OptimiseParticleSwarmBodyC(UIntT numberOfParticles,
      RealT omega,
      RealT phiP,
      RealT phiG,
      UIntT numberOfIterations,
      RealT terminationCriterion,
      UIntT numberOfThreads) :
      OptimiseBodyC("OptimiseParticleSwarmBodyC"),
      m_numberOfParticles(numberOfParticles),
      m_omega(omega),
      m_phiP(phiP),
      m_phiG(phiG),
      m_numberOfIterations(numberOfIterations),
      m_terminationCriterion(terminationCriterion),
      m_numberOfThreads(numberOfThreads)
  {
  }
  
  OptimiseParticleSwarmBodyC::OptimiseParticleSwarmBodyC(std::istream &in) :
      OptimiseBodyC("OptimiseParticleSwarmBodyC", in)
  {
    in >> m_numberOfParticles >> m_omega >> m_phiP >> m_phiG >> m_numberOfIterations >> m_terminationCriterion >> m_numberOfThreads;
  }
  
  VectorC RandomVectorPSO(int dim, RealT scale)
  {
    VectorC ret(dim);
    for (SArray1dIterC<RealT> it(ret); it; it++)
      *it = Random1() * scale;
    return ret;
  }

  VectorC RandomVelocityPSO(const VectorC & min, const VectorC & max)
  {
    VectorC ret(min.Size());
    for (SArray1dIter3C<RealT, RealT, RealT> it(ret, min, max); it; it++)
      it.Data1() = ((Random1() * Abs(it.Data3() - it.Data2())) + it.Data2()) * 2.0;
    return ret;
  }

  void BoundVectorPSO(const VectorC & min, const VectorC & max, VectorC & in)
  {
    for (SArray1dIter3C<RealT, RealT, RealT> it(min, max, in); it; it++) {
      if (it.Data3() < it.Data1())
        it.Data3() = it.Data1();
      if (it.Data3() > it.Data2())
        it.Data3() = it.Data2();
    }
  }

  // ------------------------------------------------------------------------
  // **********  OptimalX    ************************************************
  // ------------------------------------------------------------------------
  //
  // Random optimizer with uniform density. Randomly samples the parameter
  // space to find the minimum cost position.
  
  VectorC OptimiseParticleSwarmBodyC::MinimalX(const CostC &domain, RealT &minimumCost) const
  {

    /*
     * First lets make our random distribution.
     */
    VectorC startX = domain.StartX();
    UIntT dim = startX.Size();
    SobolSequenceC sobol(dim);
    sobol.First();
    sobol.Next(); // JUST WHILE TESTING!!!
    VectorC diff = domain.MaxX() - domain.MinX();
    // Current position, best position, best cost, velocity
    DataSet4C<SampleVectorC, SampleVectorC, SampleRealC, SampleVectorC> dset(m_numberOfParticles);
    RealT bestGlobalCostSoFar = RavlConstN::maxReal;
    VectorC bestGlobalXSoFar;
    VectorC boundVelocityMax = diff;
    VectorC boundVelocityMin = diff * -1.0;
    for (UIntT i = 0; i < m_numberOfParticles; i++) {

      // Create initial position
      VectorC X(sobol.Data());
      X = (X * diff) + domain.MinX();
      // Make an initial velocity
      VectorC V = RandomVelocityPSO(domain.MinX(), domain.MaxX());

      // work out initial cost
      RealT cost = domain.Cost(X);
      dset.Append(X, X, cost, V); // initially the particles initial and best position are the same

      // Is it the best one
      if (cost < bestGlobalCostSoFar) {
        bestGlobalCostSoFar = cost;
        bestGlobalXSoFar = X;
      }

      // unlikely this will happen
      if (!sobol.Next()) {
        RavlError("Run out of Sobol Samples...");
        return VectorC();
      }
    }
    RavlDebug("Initial best particle '%s' in population has cost %0.4f", StringOf(bestGlobalXSoFar).data(), bestGlobalCostSoFar);

    // make a plot of the initial population
    Plot2dC::RefT plot = CreatePlot2d("PSO");
    if (dim == 2) {
      plot->SetXRange(RealRangeC(domain.MinX()[0], domain.MaxX()[0]));
      plot->SetYRange(RealRangeC(domain.MinX()[1], domain.MaxX()[1]));
      plot->Plot(dset.Sample1());
    }

    for (UIntT i = 0; i < m_numberOfIterations; i++) {

      for (DataSet4IterC<SampleVectorC, SampleVectorC, SampleRealC, SampleVectorC> it(dset); it; it++) {

#if 0
        RealT rP = Random1();
        RealT rG = Random1();
        VectorC currentVelocity = (it.Data4() * m_omega);
        VectorC updateOnParticleBestPosition = (it.Data2() - it.Data1()) * rP * m_phiP;
        VectorC updateOnGlobalBestPosition = (bestGlobalXSoFar - it.Data1()) * rG * m_phiG;
#else
        VectorC randomParticleVec = RandomVectorPSO(dim, m_phiP);
        VectorC randomGlobalVec = RandomVectorPSO(dim, m_phiG);
        VectorC currentVelocity = (it.Data4() * m_omega);
        VectorC updateOnParticleBestPosition = randomParticleVec * (it.Data2() - it.Data1());
        VectorC updateOnGlobalBestPosition = randomGlobalVec * (bestGlobalXSoFar - it.Data1());
#endif
        VectorC velocity = currentVelocity + updateOnParticleBestPosition + updateOnGlobalBestPosition;
        BoundVectorPSO(boundVelocityMin, boundVelocityMax, velocity);

        VectorC particleNewPosition = it.Data1() + velocity;
        BoundVectorPSO(domain.MinX(), domain.MaxX(), particleNewPosition);

        RealT newCost = domain.Cost(particleNewPosition);

        //RavlDebug("New Position '%s' -> '%s' %0.2f", StringOf(it.Data1()).data(), StringOf(particleNewPosition).data(), newCost);
        //RavlDebug("New Velocity '%s' -> '%s'", StringOf(it.Data4()).data(), StringOf(velocity).data());

        // Has the particle beaten its own previous best
        if (newCost < it.Data3()) {
          it.Data2() = particleNewPosition;
          it.Data3() = newCost;
        }

        // Update global if we have a best new particle....
        if (newCost < bestGlobalCostSoFar) {
          bestGlobalCostSoFar = newCost;
          bestGlobalXSoFar = particleNewPosition;
          RavlDebug("New best particle '%s' in population has cost %0.12f at iter %d", StringOf(bestGlobalXSoFar).data(), bestGlobalCostSoFar, i);

        }

        // Update the position and velocity
        it.Data1() = particleNewPosition;
        it.Data4() = velocity;

      }

      if (bestGlobalCostSoFar < m_terminationCriterion) {
        RavlDebug("Reached best solution, terminating early.");
        break;
      }

      if (dim == 2) {
        RavlN::Sleep(0.1); // otherwise it goes too fast!
        plot->Plot(dset.Sample1());
      }

    }
    minimumCost = bestGlobalCostSoFar;
    return domain.ConvertX2P(bestGlobalXSoFar); // Return final estimate

  }
  
  const StringC OptimiseParticleSwarmBodyC::GetInfo() const
  {
    StrOStreamC stream;
    stream << OptimiseBodyC::GetInfo() << "\n";
    stream << "Particle Swarm Optimisation with population " << m_numberOfParticles;
    return stream.String();
  }
  
  bool OptimiseParticleSwarmBodyC::Save(std::ostream &out) const
  {
    OptimiseBodyC::Save(out);
    out << m_numberOfParticles << '\n';
    out << m_omega << '\n';
    out << m_phiP << '\n';
    out << m_phiG << '\n';
    out << m_numberOfIterations << '\n';
    out << m_terminationCriterion << '\n';
    out << m_numberOfThreads << '\n';
    return true;
  }

}
