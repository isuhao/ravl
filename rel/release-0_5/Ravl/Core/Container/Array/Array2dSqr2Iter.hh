// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLARRAY2dSQR2ITER_HEADER
#define RAVLARRAY2dSQR2ITER_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.2D"
//! author="Charles Galambos"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/Array2dSqr2Iter.hh"

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterator which slides a 2x2 window over an array.
  // The square can be accessed with DataBL,DataBR,DataUL and DataUR
  // which access the following array elements. <p>
  //  TL TR <br>
  //  BL BR <br>
  
  template<class DataT>
  class Array2dSqr2IterC 
    : protected BufferAccess2dIterC<DataT>
  {
  public:
    Array2dSqr2IterC()
      {}
    //: Default constructor.
    
    Array2dSqr2IterC(const Array2dC<DataT> &narray) 
    : array(narray)
    { 
      First(); 
    }
    //: Constructor.
    
    bool First() {
      IndexRangeC nrng(array.Range2().Min()+1,array.Range2().Max());
      RavlAssert(nrng.Min() <= nrng.Max());
      if(!BufferAccess2dIterC<DataT>::First(array,nrng))
	return false;
      up = &(*cit);
      if(!NextRow()) {
	cit.Invalidate();
	return false;
      }
      return true;
    }
    //: Goto first element in the array.
    
    bool Next() { 
      up++;
      cit++;
      if(cit)
	return true;
      up = &((*rit)[rng.Min()]);
      rit++;
      if(!rit)
	return false;
      cit.First(rit.Data(),rng);
      return false;
    }
    //: Goto next element.
    // Returns true if its on the same row.
    
    bool IsElm() const
      { return cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
      { return cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() 
      { Next(); }
    //: Goto next element.

    void operator++(int) 
      { Next(); }
    //: Goto next element.
    
    DataT &operator*() 
      { return *cit; }
    //: Access bottom right data element 
    
    const DataT &operator*() const
      { return *cit; }
    //: Access bottom right data element 
    
    DataT &DataBR() 
      { return *cit; }
    //: Access bottom right data element 

    const DataT &DataBR() const
      { return *cit; }
    //: Access bottom right data element 

    DataT &DataBL() 
      { return (&(*cit))[-1]; }
    //: Access bottom left data element 

    const DataT &DataBL() const
      { return (&(*cit))[-1]; }
    //: Access bottom left data element 
    
    DataT &DataTR() 
      { return *up; }
    //: Access upper right data element 
    
    const DataT &DataTR() const
      { return *up; }
    //: Access upper right data element
    
    DataT &DataTL() 
      { return up[-1]; }
    //: Access upper left data element.
    
    const DataT &DataTL() const
      { return up[-1]; }
    //: Access upper left data element

    Index2dC Index() const { 
      assert(array.IsValid());
      return BufferAccess2dIterC<DataT>::Index(array.ReferenceElm());
    }
    //: Get index of current location.
    // Has to be calculate, and so is slightly slow.
    
  protected:
    Array2dC<DataT> array;
    DataT *up;
  };
}



#endif