// $Id$

#include "Ravl/VectorT.hh"
#include "Ravl/MatrixT.hh"

using namespace RavlN;

int main() {
  MatrixTC<int> mInts(5,5);
  VectorTC<int> ints(5);
  mInts.Fill(2);
  mInts += mInts;
  ints.Fill(1);
  ints += ints;
  ints = ints + ints;
  return 0;
}
