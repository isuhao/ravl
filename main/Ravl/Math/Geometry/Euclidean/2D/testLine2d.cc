// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/testLine2d.cc"

#include "Ravl/Line2dIter.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Moments2d2.hh"
#include "Ravl/Curve2dLineSegment.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/LinePP2d.hh"
#include "Ravl/LineABC2d.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/Array1d.hh"

using namespace RavlN;

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

int testMoments();
int testLines();
int testLine2d();
int testClip2d();
int testLineFitLSQ();

int main() {
  int ln;
  if((ln = testLines()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testLine2d()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testClip2d()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testLineFitLSQ()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testLines() {  
  cout << "Checking basic lines. \n";
  Index2dC start(0,0);
  Index2dC end(10,5);
  int c = 0;
  ONDEBUG(cerr << "From " << start << " to " << end << "\n");
  for(Line2dIterC it(start,end);it && c < 20;it++,c++) {
    ONDEBUG(cerr << "Line " << it.Data() << "\n");
  }
  if(c > 19) return __LINE__;  
  for(RealT x = 0;x < RavlConstN::pi * 2; x += 0.1) {
    end = Index2dC(Round(Sin(x) * 10.0),Round(Cos(x) * 10.0));
    c = 0;
    ONDEBUG(cerr << "From " << start << " to " << end << "\n");
    for(Line2dIterC it(start,end);it && c < 20;it++,c++) {
      ONDEBUG(cerr << "Line " << it.Data() << "\n");
    }
    if(c > 19) return __LINE__;
  }
  return 0;
}

int testLine2d() {
  cout << "Checking misc line methods. \n";
  Point2dC org(321,123);
  for(int i = 0;i < 360;i++) {
    RealT angle = ((RealT) i/180.0) * RavlConstN::pi;
    Vector2dC vec = Angle2Vector2d(angle) * 4.3;
    Point2dC end(org + vec);
    Curve2dLineSegmentC line1(org,end);
    //cerr << "End=" << line1.Closest(line1.EndPnt()) - line1.Start()  << "\n";
    if(line1.Closest(line1.EndPnt()) - line1.Start() <= 0) return __LINE__;
  }
  return 0;
}

int testClip2d() {
  cout << "Checking clipping. \n";
  RealRange2dC rng(0,15,10,25);
  Point2dC pnt0(0,0);
  Point2dC pnt1(5,15);
  Point2dC pnt2(10,20);
  Point2dC pnt3(35,30);
  Point2dC pnt4(40,45);

  // This line shouldn't be clipped.
  LinePP2dC l1(pnt1,pnt2);
  if(!l1.ClipBy(rng)) return __LINE__;
  if((pnt1 - l1.P1()).SumOfSqr() > 0.00001) return __LINE__;
  if((pnt2 - l1.P2()).SumOfSqr() > 0.00001) return __LINE__;

  // Should clip point 0.
  LinePP2dC l2(pnt0,pnt2);
  if(!l2.ClipBy(rng)) return __LINE__;
  if((pnt0 - l2.P1()).SumOfSqr() < 0.00001) return __LINE__;
  if((pnt2 - l2.P2()).SumOfSqr() > 0.00001) return __LINE__;
  if(!rng.Contains(l2.P1())) return __LINE__;

  // Should clip point 1.
  LinePP2dC l3(pnt1,pnt3);
  if(!l3.ClipBy(rng)) return __LINE__;
  if((pnt1 - l3.P1()).SumOfSqr() > 0.00001) return __LINE__;
  if((pnt3 - l3.P2()).SumOfSqr() < 0.00001) return __LINE__;
  if(!rng.Contains(l3.P2())) return __LINE__;
  
  // Line entirely outside region.
  LinePP2dC l4(pnt3,pnt4);
  if(l4.ClipBy(rng)) return __LINE__;

  RealRange2dC rng2(0.51,239.49,0.51,239.49);
  LinePP2dC l5(Point2dC(1.5,0.5),Point2dC(1.5,720.5));
  //cerr << " CP1=" << l5.P1() << " CP2=" << l5.P2() << "\n";
  if(!l5.ClipBy(rng2)) return __LINE__;
  //cerr << " CP1=" << l5.P1() << " CP2=" << l5.P2() << "\n";
  if(!rng2.Contains(l5.P1())) return __LINE__;
  if(!rng2.Contains(l5.P2())) return __LINE__;
  return 0;
}

int testLineFitLSQ() {
  
  Array1dC<Point2dC> points(4);
  for(UIntT i = 0;i < points.Size();i++)
    points[i] = Point2dC(i+1, i * 4);
  LineABC2dC line;
  RealT res;
  line.FitLSQ(points,res);
  cerr << "Line=" << line << " Res=" << res <<"\n";
  
  for(UIntT i = 0;i < points.Size();i++)
    points[i] = Point2dC(i+1, i * 0.5);
  RealT res;
  line.FitLSQ(points,res);
  cerr << "Line=" << line << " Res=" << res <<"\n";

  return 0;
}
