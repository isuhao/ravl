// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_HEMESHFACEITER_HEADER
#define RAVL3D_HEMESHFACEITER_HEADER 1
//! rcsid="$Id$"
//! lib=Ravl3D
//! author="Charles Galambos"
//! docentry="Ravl.3D.Half Edge Mesh"
//! date="22/5/2002"

#include "Ravl/3D/HEMeshFace.hh"
#include "Ravl/InDLIter.hh"

namespace Ravl3DN {
  
  class HEMeshC;

  //! userlevel=Normal
  //: Mesh face iterator.
  
  class HEMeshFaceIterC 
    : public IntrDLIterC<HEMeshFaceBodyC>
  {
  public:
    HEMeshFaceIterC()
    {}
    //: Default constructor.

    HEMeshFaceIterC(IntrDListC<HEMeshFaceBodyC> &iter)
      : IntrDLIterC<HEMeshFaceBodyC>(iter)
    {}
    //: Constructor.

    HEMeshFaceC Data()
    { return HEMeshFaceC(IntrDLIterC<HEMeshFaceBodyC>::Data()); }
    //: Access Face.

    const HEMeshFaceC Data() const
    { return HEMeshFaceC(const_cast<HEMeshFaceBodyC &>(IntrDLIterC<HEMeshFaceBodyC>::Data())); }
    //: Access Face.

    HEMeshFaceC operator*()
    { return HEMeshFaceC(IntrDLIterC<HEMeshFaceBodyC>::Data()); }
    //: Access Face.
    
    const HEMeshFaceC operator*() const
    { return HEMeshFaceC(const_cast<HEMeshFaceBodyC &>(IntrDLIterC<HEMeshFaceBodyC>::Data())); }
    //: Access Face.
    
  protected:
    
    friend class HEMeshC;
  };
  
}


#endif
