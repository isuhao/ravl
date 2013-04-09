// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioFeatures
//! file="Ravl/Audio/Features/MelSpectrum.cc"

#include "Ravl/Audio/MelSpectrum.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Array1dIter2.hh"
#include "Ravl/XMLFactoryRegister.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlAudioN {

  //: Default constructor.
  
  MelSpectrumC::MelSpectrumC()
  {}
  
  //: Constructor
  // Frequency's is in Hz.
  
  MelSpectrumC::MelSpectrumC(RealT sampleRate,IntT frameSize,RealRangeC freqRange,IntT nfilters)
  {
    InitFilters(sampleRate,frameSize,freqRange,nfilters);
  }

  //: XMLFactory constructor.
  
  MelSpectrumC::MelSpectrumC(const XMLFactoryContextC &factory)
   : DPProcessBodyC<SArray1dC<RealT>,SArray1dC<RealT> >(factory)
  {
    RealT sampleRate = factory.AttributeReal("sampleRate",8000);
    IntT frameSize = factory.AttributeUInt("frameSize",512);
    IntT nfilters = factory.AttributeUInt("numberOfFilter",14);
    RealRangeC freqRange(factory.AttributeReal("minFrequency",133.333334),
                         factory.AttributeReal("maxFrequency",6855.4976)
                         );
    InitFilters(sampleRate,frameSize,freqRange,nfilters);
  }

  //: Compute mel spectrum from power spectrum
  
  SArray1dC<RealT> MelSpectrumC::Apply(const SArray1dC<RealT> &powerSpectrum) {
    SArray1dC<RealT> ret(filters.Size());
    Array1dC<RealT> spec(powerSpectrum);
    for(SArray1dIter2C<Array1dC<RealT>,RealT > it(filters,ret);it;it++) {
      RealT sum = 0;
      for(Array1dIter2C<RealT,RealT> fit(it.Data1(),spec,it.Data1().Range());fit;fit++)
	sum += fit.Data1() * fit.Data2();
      it.Data2() = sum;
    }
    
    return ret;
  }
  
  //: Initialise filters.
  // Frequency's is in Hz.
  
  bool MelSpectrumC::InitFilters(RealT sampleRate,IntT frameSize,RealRangeC freqRange,IntT numFilters)
  {
    // Compute edge values for filters.
    
    RealT dfreq = sampleRate / frameSize;
    ONDEBUG(std::cerr << "DFreq=" << dfreq << "\n");
    SArray1dC<RealT> edges(numFilters+2);
    {
      RealRangeC melRng(Lin2Mel(freqRange.Min()),Lin2Mel(freqRange.Max()));
      RealT rStep = melRng.Size() / (RealT)(numFilters+1);
      RealT at = melRng.Min();
      // Compute edge frequency's and round them to fit nicely to results of dft
      for(SArray1dIterC<RealT> it(edges);it;it++,at += rStep) 
        *it = (RealT) Round(Mel2Lin(at) / dfreq) * dfreq;
      //cerr << "Edges=" << edges << "\n";
    }
    
    // Compute values for filter banks
    
    filters = SArray1dC<Array1dC<RealT> >(numFilters);
    {
      int i = 0;
      for(SArray1dIterC<Array1dC<RealT> > it(filters);it;it++,i++) {
        Array1dC<RealT> &filt = *it;
        IntT imin = Round(edges[i]/dfreq)+1;
        IntT imax = Round(edges[i+2]/dfreq)-1;
        if(imax < imin)
          imax = imin;
        filt = Array1dC<RealT>(imin,imax);
        ONDEBUG(cerr << "Range=" << filt.Range() << "\n");

        RealT left = edges[i];
        RealT cent = edges[i+1];
        RealT right = edges[i+2];
        ONDEBUG(cerr << "Left=" << left << " Cent=" << cent << " Right=" << right << "\n");
        RealT width = right - left;
        RealT height = (2 * dfreq)/width;
        RealT slope1 = height / (cent - left);
        RealT slope2 = height / (cent - right);
        RealT freq = (filt.Range().Min()) * dfreq;
        ONDEBUG(cerr << "Width=" << width << " Slope1=" << slope1 << " Slope2=" << slope2 << "\n");

        if(filt.Size() == 1) { // Range small ?
          filt[filt.IMin()] = 1;
          ONDEBUG(cerr << " 1");
        } else {
          for(Array1dIterC<RealT> fit(filt);fit;fit++) {
            if(freq <= cent)
              *fit = (freq - left) * slope1;
            else
              *fit = (freq - right) * slope2;
            ONDEBUG(cerr << " " << *fit);
            freq += dfreq;
          }
        }
        ONDEBUG(cerr << "\n\n");
      }
    }
    return true;
  }
  
  void LinkMelSpectrum()
  {}

  static RavlN::XMLFactoryRegisterConvertC<MelSpectrumC,DPProcessBodyC<SArray1dC<RealT>,SArray1dC<RealT> > > g_registerVectorDelta012("RavlAudioN::MelSpectrumC");


}
