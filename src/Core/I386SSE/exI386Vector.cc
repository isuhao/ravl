// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/Vector.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Date.hh"

template<class DataT>
static DataT PlainDotProduct(const DataT* v1, const DataT* v2, size_t Size) {
  DataT sum = 0.0;
  const DataT* ptr1 = v1;
  const DataT* ptr2 = v2;
  for(unsigned int i=Size; i>0; --i)
    sum += *ptr1++ * *ptr2++;
  return sum;  
}

// Small program usefull for checking SSE usage

int main (int nargs,char **argv) {
  RavlN::OptionC opts(nargs,argv);
  bool testFloat = opts.Boolean("f",false,"Test floats");
  int vectorLen = opts.Int("vl",1024,"Vector length. ");
  int loops = opts.Int("l",100000,"Test loops. ");
  bool lengthTest = opts.Boolean("lt","Do length test. ");
  opts.Check();
  
  using namespace RavlN;
  if(testFloat) 
    std::cerr << "Testing float. \n";
  else
    std::cerr << "Testing double. \n";
  
  RealT r = 0;
  int startLen = 1;
  if(!lengthTest)
    startLen = vectorLen;
  for(int vl = startLen;vl <= vectorLen;vl++) {
    RavlN::DateC start = RavlN::DateC::NowUTC();
    if(testFloat) {
      TVectorC<float> a(vl);
      a.Fill(0.96);
      double s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += a.Dot(a);
      r += s;
    } else {
      VectorC a(vl); 
      a.Fill(0.96);
      RealT s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += a.Dot(a);
      r += s;
    }
    RavlN::DateC finish = RavlN::DateC::NowUTC();
    RavlN::DateC startr = RavlN::DateC::NowUTC();
    if(testFloat) {
      TVectorC<float> a(vl);
      a.Fill(0.96);
      float s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += PlainDotProduct(&a[0],&a[0],vl);
      r += s;
    } else {
      TVectorC<double> a(vl);
      a.Fill(0.96);
      double s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += PlainDotProduct(&a[0],&a[0],vl);
      r += s;
    }
    RavlN::DateC finishr = RavlN::DateC::NowUTC();
    
    std::cout << " " << vl << " SSE:" << (finish - start).Double() << " Original:" << (finishr - startr).Double() << "\n";
  }
  std::cout << r << std::endl;
  return 0;
}
