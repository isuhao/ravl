// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html


%include "Ravl/Swig2/Types.i"
%include "Ravl/Swig2/Index2d.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/IndexRange2d.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN {

  class IndexRange2dC {
  public:
    IndexRange2dC();
    IndexRange2dC(IntT rows, IntT cols);
    IndexC TRow() const;
    IndexC BRow() const;
    IndexC LCol() const;
    IndexC RCol() const;
    Index2dC TopLeft() const;
    Index2dC TopRight() const;
    Index2dC BottomLeft() const;
    Index2dC BottomRight() const;
    Index2dC Center() const;
    IntT Rows() const;
    IntT Cols() const;
    SizeT Area() const;
    bool Contains(Index2dC index) const;
    IndexRange2dC Expand(IntT n) const;
    void ClipBy(IndexRange2dC range);
  };
}
