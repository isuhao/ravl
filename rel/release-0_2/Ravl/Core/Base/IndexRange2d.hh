// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLINDEXRANGE2D_HH
#define RAVLINDEXRANGE2D_HH
///////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/IndexRange2d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! docentry="Ravl.Core.Indexing"
//! rcsid="$Id$"
//! date="06/08/95"
//! userlevel=Default

#include "Ravl/Index.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/Index2d.hh"

namespace RavlN {

  class BinIStreamC;
  class BinOStreamC;
  
  //! userlevel=Normal
  //: An index range of a 2D array
  
  class IndexRange2dC {
  public:
    IndexRange2dC()
      {}
    //: Default constructor.
    
    IndexRange2dC(IndexC rowNumber, IndexC colNumber)
      : rows(0, rowNumber-1), 
      cols(0, colNumber-1)
      {}
    //: Constructor.
    
    IndexRange2dC(const IndexRangeC & rowRange,
		  const IndexRangeC & colRange);
    //: Constructor.
    
    IndexRange2dC(const IndexRange2dC & range);
    //: Constructor.

    IndexRange2dC(const Index2dC &org,const Index2dC &end)
      : rows(org.Row(), end.Row()), 
      cols(org.Col(),end.Col())
      {}
    //: Create an 2d range from corner points.

    IndexRange2dC(IndexC minRow, IndexC maxRow,
		    IndexC minCol, IndexC maxCol)
      : rows(minRow, maxRow), 
      cols(minCol,maxCol)
      {}
    //: Create rectangle from indvidual values.
    
    inline Index2dC Origin() const
      { return Index2dC(rows.Min(),cols.Min()); }
    // Returns the top-left index of the rectangle.
    
    inline Index2dC  End() const
      { return Index2dC(rows.Max(),cols.Max()); }
    // Returns the bottom-right index of the rectangle.
    
    inline Index2dC Center() const
      { return Index2dC(rows.Center(),cols.Center()); }
    // Returns the index which is in the middle of the rectangle
    
    inline IndexC TRow() const
      { return rows.Min(); }
    // Returns the top row index.
    
    inline IndexC LCol() const
      { return cols.Min(); }
    // Returns the left side column index.
    
    inline IndexC BRow() const
      { return rows.Max(); }
    // Returns the bottom row index.
    
    inline IndexC RCol() const
      { return cols.Max(); }
    // Returns the right side column index.

    inline IndexC &TRow()
      { return rows.Min(); }
    // Returns the top row index.
    
    inline IndexC &LCol()
      { return cols.Min(); }
    // Returns the left side column index.
    
    inline IndexC &BRow()
      { return rows.Max(); }
    // Returns the bottom row index.
    
    inline IndexC &RCol()
      { return cols.Max(); }
    // Returns the right side column index.
    
    inline SizeT Rows() const
      { return rows.Size(); }
    //: The number of rows in the rectangle.

    inline SizeT Cols() const
      { return cols.Size(); }
    //: The number of rows in the rectangle.

    inline SizeT Area() const
      { return (SizeT) Rows() * Cols(); }
    // Returns the area of the image rectangle expressed in number of indexs.
    
    inline IndexRange2dC Dilate() const 
      { return IndexRange2dC(rows.Expand(1),cols.Expand(1)); }
    //: Returns a new rectangle one index larger on each side.
    
    inline IndexRange2dC Erode() const
      { return IndexRange2dC(rows.Shrink(1),cols.Shrink(1)); }
    // Removes one index layer on each side.
    
    inline IndexRange2dC Expand(IndexC n) const
      { return IndexRange2dC(rows.Expand(n),cols.Expand(n)); }
    // Expands the rectangle by adding 'n' indexs on each side.
    
    inline IndexRange2dC Shrink(IndexC n) const
      { return IndexRange2dC(rows.Shrink(n),cols.Shrink(n)); }
    // Returns a new rectangle which has layer of the width of 'n' indexs
    // removed.
    
    inline const IndexRange2dC & operator+=(const Index2dC & offset);
    // Shifts the rectangle to the new position.
    
    inline const IndexRange2dC & operator-=(const Index2dC & offset);
    // Shifts the rectangle to the new position.
    
    inline const IndexRangeC & RowRange() const
      { return rows; }
    //: Access row range.
    
    inline const IndexRangeC & ColRange() const
      { return cols; }
    //: Access col range.

    inline IndexRangeC & RowRange()
      { return rows; }
    //: Access row range.
    
    inline IndexRangeC & ColRange()
      { return cols; }
    //: Access col range.
    
    inline const IndexRangeC & Range1() const
      { return rows; }
    //: Access row range.
    
    inline const IndexRangeC & Range2() const
      { return cols; }
    //: Access col range.
    
    inline IndexRangeC & Range1()
      { return rows; }
    //: Access row range.
    
    inline IndexRangeC & Range2()
      { return cols; }
    //: Access col range.
    
    inline void SetIn(const Index2dC & index);
    // Checks and changes, if necessary, the 2 dimensional range
    // to contain the 'index'.
    
    inline 
    bool IsValid() const 
      { return rows.IsValid() && cols.IsValid(); }
    // Returns TRUE if this rectangle contains at least one index.

    bool operator==(const IndexRange2dC &oth) const
      { return oth.Range1() == Range1() && oth.Range2() == Range2(); }
    //: Are two ranges equal ?

    bool operator!=(const IndexRange2dC &oth) const
      { return oth.Range1() != Range1() || oth.Range2() != Range2(); }
    //: Are two ranges unequal ?
    
  protected:
    inline const IndexRange2dC & Range() const
      { return(*this); }
    
  private:
    IndexRangeC rows;
    IndexRangeC cols;
  };

  inline
  ostream &operator<<(ostream &s,const IndexRange2dC &ir) {
    s << ir.Range1() << ' ' << ir.Range2();
    return s;
  }
  
  inline
  istream &operator>>(istream &s,IndexRange2dC &ir) {
    s >> ir.Range1() >> ir.Range2();
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const IndexRange2dC &ir);  
  BinIStreamC &operator>>(BinIStreamC &s,IndexRange2dC &ir);
  
  ///////////////////////////////////////////////////////
  
  inline 
  const IndexRange2dC &IndexRange2dC::operator+=(const Index2dC & offset) {
    rows += offset.Row();
    cols += offset.Col();
    return *this;
  }
  
  inline 
  const IndexRange2dC & IndexRange2dC::operator-=(const Index2dC & offset) {
    rows -= offset.Row();
    cols -= offset.Col();
    return *this;
  }
  
  inline 
  void 
  IndexRange2dC::SetIn(const Index2dC & index) {
    if (rows.Min() > index.Row()) rows.Min() = index.Row();
    if (rows.Max() < index.Row()) rows.Max() = index.Row();
    if (cols.Min() > index.Col()) cols.Min() = index.Col();
    if (cols.Max() < index.Col()) cols.Max() = index.Col();
  }
  
}
#endif
