// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/MeanNd.hh"

namespace RavlN {
  
  MeanNdC::MeanNdC(const SArray1dC<VectorC> &vecs) {
    number = vecs.Size();
    if(number == 0)
      return ;
    SArray1dIterC<VectorC> it(vecs);
    Mean() = it->Copy();
    it++;
    for(;it;it++)
      Mean() += *it;
    Mean() /= ((RealT) number);
  }
  
  MeanNdC MeanNdC::Copy() const 
  { return MeanNdC(number, VectorC::Copy()); }
  
  ostream &operator<<(ostream & s, const MeanNdC & mean) {
    s << mean.Number() << ' ' << mean.Mean();
    return s;
  }
  
  istream &operator>>(istream & s, MeanNdC & mean) {
    s >>  mean.number >>  mean.Mean();
    return s;
  }
  
}
