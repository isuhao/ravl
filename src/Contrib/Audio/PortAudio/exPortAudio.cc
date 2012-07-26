// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlPortAudio
//! author="Lee Gregory"
//! docentry="Ravl.API.Audio.IO"
//! file="Ravl/Contrib/Audio/PortAudio/exPortAudio.cc"

#include "Ravl/IO.hh"
#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Audio/Types.hh"
#include "Ravl/DP/AttributeType.hh"
#include "Ravl/SysLog.hh"
#include "Ravl/OS/Date.hh"

using namespace RavlN;
using namespace RavlAudioN ; 

// This example reads from a wav file and outputs to a sound device.
// This example needs to be linked against RavlDevAudio as well as RavlPortAudio.


int main(int nargs,char **argv) {
  
  // get some options
  OptionC opt(nargs,argv);
  StringC idev = opt.String("i","test.wav","Input  device.");
  StringC odev = opt.String("o","@PORTAUDIO","Output device.");
  opt.Check();


  RavlN::SysLogOpen("exPortAudio",false,true,true,-1,true);

  // open the input port 
  DPIPortC<SampleElemC<2,float> > in;
  if(!OpenISequence(in,idev)) {
    RavlError("Failed to open input : %s ",idev.c_str());
    return 1;
  }
  
  
  // now lets setup an output port 
  DPOPortC<SampleElemC<2,float> > out;
  if(!OpenOSequence(out,odev)) {
    RavlError("Failed to open output : %s ",odev.c_str());
    return 1;
  }
 
  
  // lets look at the attributes available 
  DListC<AttributeTypeC> attrList ; 
  in.GetAttrTypes(attrList) ; 
  //cout << "\nAvailable Attributes are :\n" << attrList ;
  
  // lets get some attributes 
  RealT sampleRate ; 
  IntT  sampleBits ; 
  in.GetAttr("samplerate", sampleRate) ; 
  in.GetAttr("samplebits", sampleBits) ; 
    
  // now lets read data from file and play to device
  RavlInfo("Using a sample rate of %f ",sampleRate);
  out.SetAttr("samplerate",sampleRate) ; 
  RavlN::SArray1dC<SampleElemC<2,float> > samples(16);
  while (in.GetArray(samples)) {
    out.PutArray(samples) ; // play sample
  }
  RavlN::Sleep(1);
  return 0;
}
