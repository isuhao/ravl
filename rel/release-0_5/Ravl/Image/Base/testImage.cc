// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/Base/testImage.cc"

#include "Ravl/String.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/RGBcYUV.hh"
#include <fstream.h>

using namespace RavlImageN;

int TestBasic();
int TestIO();
int TestColorCnv();

template class ImageC<int>; // Make sure all functions are compiled.

int main()
{
  cerr << "Testing basic image ops. \n";
  int lineno;
  if((lineno = TestBasic()) != 0) {
    cerr << "Image io test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestIO()) != 0) {
    cerr << "Image io test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestColorCnv()) != 0) {
    cerr << "Image io test failed : " << lineno << "\n";
     return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

////////////////////////////////
// Check iterators, and image copying

int TestBasic()
{
  cerr << "Starting basic tests... \n";
  // Create test image.
  
  ImageRectangleC rect(5,10,6,9);
  cerr << "Size1:" << rect.Range1().Size() << " Size2:" << rect.Range2().Size() << "\n";
  ImageC<int> testImg(rect);
  
  int i = 0;
  
  Array2dIterC<int> it(testImg);
  if(it.Index() != rect.Origin()) {
    cerr << "Origin check failed. \n";
    return __LINE__;
  }
  
  for(;it.IsElm();it.Next()) 
    it.Data() = i++;

  if(rect.Area() != (UIntT) i) {
    cerr << "Iterator check failed. Area mis-match. Count:" << i << " should be " << rect.Area() <<  "\n";
    return __LINE__;
  }
  if(testImg[10][9] != (i-1)) {
    cerr<< "Inital spot value check failed. " << testImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testImg;
    return __LINE__;
  }
  // Make copy...
  
  ImageC<int> testInImg = testImg.Copy();

  if(testInImg[10][9] != (i-1)) {
    cerr<< "Spot value check 2 failed. " << testInImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testInImg;
    return __LINE__;
  }
  if(testImg[10][9] != (i-1)) {
    cerr<< "Spot value check 3 failed. " << testImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testImg;
    return __LINE__;
  }
  cerr <<"Copy " << testInImg<<"\n";
  // check image.
  
  if(testInImg[6][7] != testImg[6][7]) {
    cerr<< "Spot value check failed. \n";
    return __LINE__;
  }

  if(testInImg[5][6] != 0 || testImg[5][6] != 0) {
    cerr<< "Spot value check failed. \n";
    return __LINE__;
  }
  
  if(testInImg.Rectangle() != testImg.Rectangle()) {
    cerr<< "Rectangle size mismatch. \n";
    return __LINE__;
  }
  
  for(Array2dIter2C<int,int> it2(testInImg,testImg);it2;it2++) {
    if(it2.Data1() != it2.Data2()) {
      cerr<< "Image contents mismatch at " <<it2.Index() << ":" << it2.Data1() << " " << it2.Data2() << "\n";
      return __LINE__;
    }
  }
  
  testImg[10][9] = 0;
  if(testInImg[10][9] != (i-1)) {
    cerr<< "Spot value check 4 failed. " << testInImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testImg;
    return __LINE__;
  }

  return 0;
}

////////////////////////////////
// Check image io opreators.

int TestIO()
{
  cerr << "Starting IO test... \n";
  StringC testFn("/tmp/testImage");
  //testFn = testFn.MkTemp();
  
  // Create test image.
  
  ImageRectangleC rect(5,10,4,11);
  ImageC<int> testImg(rect);
  
  int i = 0;
  Array2dIterC<int> it(testImg);
  if(it.Index() != rect.Origin()) {
    cerr << "Origin check failed. \n";
    return __LINE__;
  }
  
  for(;it.IsElm();it.Next()) 
    it.Data() = i++;
  
  if(testImg.Rectangle().Area() != ((UIntT) i)) {
    cerr << "Area test failed! \n";
    return __LINE__;
  }
  
  // Write out test image.
  {
    ofstream out(testFn);
    out << testImg;
    if(!out) {
      cerr << "Image write failed! \n";
      return __LINE__;
    }
  }
  
  ImageC<int> testInImg;
  
  // Read in test image.
  {
    ifstream in(testFn); 
    if(!in) {
      cerr << "Image read failed! \n";
      return __LINE__;
    }
    in >> testInImg;
  }
  
  if(testInImg.Rectangle() != testImg.Rectangle()) {
    cerr<< "Rectangle size mismatch. \n";
    return __LINE__;
  }
  
  for(Array2dIter2C<int,int> it2(testInImg,testImg);it2.IsElm();it2.Next()) {
    if(it2.Data1() != it2.Data2()) {
      cerr<< "Image contents mismatch at " <<it2.Index() << ":" << it2.Data1() << " " << it2.Data2() << "\n";
      return __LINE__;
    }
  }
  
#if 0
  if(testFn.Exists())
    testFn.Remove();
#endif
  
  return 0;
}

int TestColorCnv() {
  RealYUVValueC yuv(20,30,40);
  cerr << "yuv=" << yuv << "\n";
  RealRGBValueC rgb(yuv);
  cerr << "rgb=" << rgb << "\n";
  RealYUVValueC yuv2(rgb);
  cerr << "yuv2=" << yuv2 << "\n";
  RealT diff = (yuv - yuv2).SumSqr();
  if(diff > 0.002) return __LINE__;
  return 0;
}