// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2DSQR33ITER2_HEADER
#define RAVL_ARRAY2DSQR33ITER2_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Arrays.2D"
//! author="Charles Galambos"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/Array2dSqr33Iter2.hh"

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter2.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate through an array accessing 3x3 area in two arrays.
  // The square can be accessed with DataBL,DataBR etc...
  // which access the following array elements. <p>
  //  TL TM TR <br>
  //  ML MM MR <br>
  //  BL BM BR <br>
  // for the first array.
  
  template<class Data1T,class Data2T>
  class Array2dSqr33Iter2C 
    : protected BufferAccess2dIter2C<Data1T,Data2T>
  {
  public:
    Array2dSqr33Iter2C()
    {}
    //: Default constructor.
    
    Array2dSqr33Iter2C(const Array2dC<Data1T> &narray1,
		       const Array2dC<Data2T> &narray2) 
      : array1(narray1),
	array2(narray2)
    { First(); }
    //: Constructor.
    
    bool First() {
      this->rng1 = IndexRangeC(array1.Range2().Min()+1,array1.Range2().Max()-1);
      this->rng2 = array2.Range2();
      this->rng2.ClipBy(this->rng1);
      IndexRangeC srng1(array1.Range1().Min()+1,array1.Range1().Max()-1);
      IndexRangeC srng2 = array2.Range1();
      srng2.ClipBy(srng1);
      if(!this->rit.First(array1,srng1,
                          array2,srng2)) {
	this->cit.Invalidate();
	return false;
      }
      this->cit.First(this->rit.Data1(),this->rng1,
                      this->rit.Data2(),this->rng2);
      if(!this->cit) {
	this->cit.Invalidate();
	return false;
      }
      up1 = &((&(this->rit.Data1()))[-1][this->rng1.Min()]);
      dn1 = &((&(this->rit.Data1()))[ 1][this->rng1.Min()]);
      up2 = &((&(this->rit.Data2()))[-1][this->rng2.Min()]);
      dn2 = &((&(this->rit.Data2()))[ 1][this->rng2.Min()]);
      return true;
    }
    //: Goto first element in the array.
    
    bool Next() { 
      up1++;
      dn1++;
      up2++;
      dn2++;
      this->cit++;
      if(this->cit)
	return true;
      this->rit++;
      if(!this->rit)
	return false;
      up1 = &((&(this->rit.Data1()))[-1][this->rng1.Min()]);
      dn1 = &((&(this->rit.Data1()))[ 1][this->rng1.Min()]);
      up2 = &((&(this->rit.Data2()))[-1][this->rng2.Min()]);
      dn2 = &((&(this->rit.Data2()))[ 1][this->rng2.Min()]);
      this->cit.First(this->rit.Data1(),this->rng1,
                      this->rit.Data2(),this->rng2);
      return false;
    }
    //: Goto next element.
    
    bool IsElm() const
    { return this->cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
    { return this->cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() 
    { Next(); }
    //: Goto next element.

    void operator++(int) 
    { Next(); }
    //: Goto next element.
    
    Data1T &DataBL1() 
    { return dn1[-1]; }
    //: Access bottom left data element from array 1

    const Data1T &DataBL1() const
    { return dn1[-1]; }
    //: Access bottom left data element from array 1 

    Data1T &DataBM1() 
    { return *dn1; }
    //: Access bottom mid data element from array 1

    const Data1T &DataBM1() const
    { return *dn1; }
    //: Access bottom mid data element from array 1

    Data1T &DataBR1() 
    { return dn1[1]; }
    //: Access bottom right data element from array 1

    const Data1T &DataBR1() const
    { return dn1[1]; }
    //: Access bottom right data element from array 1

    Data1T &DataML1() 
    { return (&(this->cit.Data1()))[-1]; }
    //: Access middle left data element from array 1
    
    const Data1T &DataML1() const
    { return (&(this->cit.Data1()))[-1]; }
    //: Access middle left data element from array 1
    
    Data1T &DataMM1() 
    { return this->cit.Data1(); }
    //: Access middle data element from array 1
    
    const Data1T &DataMM1() const
    { return this->cit.Data1(); }
    //: Access middle data element from array 1
    
    Data1T &Data1() 
    { return this->cit.Data1(); }
    //: Access middle data element from array 1
    
    const Data1T &Data1() const
    { return this->cit.Data1(); }
    //: Access middle data element from array 1
    
    Data1T &DataMR1() 
    { return (&(this->cit.Data1()))[1]; }
    //: Access middle right data element from array 1
    
    const Data1T &DataMR1() const
    { return (&(this->cit.Data1()))[1]; }
    //: Access middle right data element from array 1

    Data1T &DataTL1() 
    { return up1[-1]; }
    //: Access top left data element from array 1
    
    const Data1T &DataTL1() const
    { return up1[-1]; }
    //: Access top left data element from array 1

    Data1T &DataTM1() 
    { return *up1; }
    //: Access top middle element from array 1
    
    const Data1T &DataTM1() const
    { return *up1; }
    //: Access top middle element from array 1
    
    Data1T &DataTR1() 
    { return up1[1]; }
    //: Access top right data element from array 1
    
    const Data1T &DataTR1() const
    { return up1[1]; }
    //: Access top right data element from array 1
    
    Data2T &DataBL2() 
    { return dn2[-1]; }
    //: Access bottom left data element from array 2 

    const Data2T &DataBL2() const
    { return dn2[-1]; }
    //: Access bottom left data element from array 2

    Data2T &DataBM2() 
    { return *dn2; }
    //: Access bottom mid data element from array 2

    const Data2T &DataBM2() const
    { return *dn2; }
    //: Access bottom mid data element from array 2

    Data2T &DataBR2() 
    { return dn2[1]; }
    //: Access bottom right data element from array 2

    const Data2T &DataBR2() const
    { return dn2[1]; }
    //: Access bottom right data element from array 2

    Data2T &DataML2() 
    { return (&(this->cit.Data2()))[-1]; }
    //: Access middle left data element from array 2
    
    const Data2T &DataML2() const
    { return (&(this->cit.Data2()))[-1]; }
    //: Access middle left data element from array 2
    
    Data2T &DataMM2() 
    { return this->cit.Data2(); }
    //: Access middle data element from array 2
    
    const Data2T &DataMM2() const
    { return this->cit.Data2(); }
    //: Access middle data element from array 2
    
    Data2T &Data2() 
    { return this->cit.Data2(); }
    //: Access middle data element from array 2
    
    const Data2T &Data2() const
    { return this->cit.Data2(); }
    //: Access middle data element from array 2
    
    Data2T &DataMR2() 
    { return (&(this->cit.Data2()))[1]; }
    //: Access middle right data element from array 2
    
    const Data2T &DataMR2() const
    { return (&(this->cit.Data2()))[1]; }
    //: Access middle right data element from array 2

    Data2T &DataTL2() 
    { return up2[-1]; }
    //: Access top left data element from array 2
    
    const Data2T &DataTL2() const
    { return up2[-1]; }
    //: Access top left data element from array 2

    Data2T &DataTM2() 
    { return *up2; }
    //: Access top middle element from array 2
    
    const Data2T &DataTM2() const
    { return *up2; }
    //: Access top middle element from array 2
    
    Data2T &DataTR2() 
    { return up2[1]; }
    //: Access top right data element from array 2
    
    const Data2T &DataTR2() const
    { return up2[1]; }
    //: Access top right data element from array 2
    
  protected:
    Array2dC<Data1T> array1;
    Array2dC<Data2T> array2;
    Data1T *up1;
    Data1T *dn1;
    Data2T *up2;
    Data2T *dn2;
  };
}



#endif
