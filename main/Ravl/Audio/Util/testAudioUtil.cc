// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAudioUtil

#include "Ravl/Audio/WindowSignal.hh"
#include "Ravl/DP/ListIO.hh"
#include "Ravl/Random.hh"
#include "Ravl/DP/Compose.hh"

using namespace RavlAudioN;
using namespace RavlN;

int testSignalWindowFilters();
int testSignalWindow();

int main() {
  int ln;
  if((ln = testSignalWindowFilters()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testSignalWindow()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  return 0;
}

bool CheckSymmetric(SArray1dC<RealT> &filter) {
  if(filter.Size() & 1)
    return false;
  int size = filter.Size()-1;
  int halfSize = size/2;
  for(int i = 0;i < halfSize;i++) {
    if(Abs(filter[i] - filter[size - i]) > 0.02) {
      cerr << i << " " << filter[i] << " " << filter[size - i] <<"\n";
      return false;
    }
  }
  cerr << "Gain=" << (filter.Sum() / ((RealT) filter.Size())) << "\n";
  return true;
}

int testSignalWindowFilters() {
    
  WindowSignalC<IntT,IntT> test1(RAWRamp,128);
  //cerr <<" Filter=" << test1.Filter() << "\n";
  if(test1.Filter().Size() != 128) return __LINE__;
  if(!CheckSymmetric(test1.Filter())) return __LINE__;
  
  WindowSignalC<IntT,IntT> test2(RAWHamming,128);
  //cerr <<" Filter=" << test2.Filter() << "\n";
  if(!CheckSymmetric(test2.Filter())) return __LINE__;
  if(test2.Filter().Size() != 128) return __LINE__;

  WindowSignalC<IntT,IntT> test3(RAWHanning,128);
  //cerr <<" Filter=" << test3.Filter() << "\n";
  if(!CheckSymmetric(test3.Filter())) return __LINE__;
  if(test3.Filter().Size() != 128) return __LINE__;
  
  WindowSignalC<IntT,IntT> test4(RAWBlackman,128);
  if(!CheckSymmetric(test4.Filter())) return __LINE__;
  if(test4.Filter().Size() != 128) return __LINE__;
  //cerr <<" Filter=" << test4.Filter() << "\n";
  
  return 0;
}

int testSignalWindow() {
  DListC<IntT> list;
  for(int i= 0;i < (128*2);i++)
    list.InsLast((IntT)(Random1() * 1000.0));
  DPISListC<IntT> ip(list);
  WindowSignalC<IntT,IntT> filter(RAWHanning,128);
  DPIPortC<SArray1dC<IntT> > op = ip >> filter;
  SArray1dC<IntT> data;
  if(!op.Get(data)) return __LINE__;
  if(data.Size() != 128) return __LINE__;
  //cerr << data << "\n";
  return 0;
}
