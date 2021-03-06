// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef _D_PINHOLE_CAMERA_0_
#define _D_PINHOLE_CAMERA_0_
///////////////////////////////////////////////////
//! docentry="Ravl.API.Graphics.3D"
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/DPointSet3D.hh"
//! lib=RavlGUI3D
//! author="Joel Mitchelson"
//! date="31/1/2002"

#include "Ravl/GUI/DObject3D.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/3D/PinholeCamera0.hh"

namespace RavlGUIN
{
  using namespace Ravl3DN;

  //: Use PinholeCamera0C class to set OpenGL viewpoint
  class DPinholeCamera03DBodyC : public DObject3DBodyC
  {
  public:
    DPinholeCamera03DBodyC(const PinholeCamera0C& _camera,
                           const IndexRange2dC& _canvas_region)
      : camera(_camera),
        canvas_region(_canvas_region)
     {}
    // Constructor.

    virtual bool GUIRender(Canvas3DC &c3d) const;
    //: Render object.

    virtual Vector3dC GUICenter() const
      { return Vector3dC(0, 0, 0); }
    //: Get center of object.
    // defaults to 0,0,0

    virtual RealT GUIExtent() const
      { return 1; }
    //: Get extent of object.
    // defaults to 1

  protected:
    PinholeCamera0C camera;
    IndexRange2dC canvas_region;
  };

  //: Use PinholeCamera0C class to set OpenGL viewpoint
  class DPinholeCamera03DC : public DObject3DC
  {
  public:
    DPinholeCamera03DC()
      {}
    //: Default constructor, creates an invalid handle.

    DPinholeCamera03DC(const PinholeCamera0C& camera,
                       const IndexRange2dC& canvas_region)
      : DObject3DC(*new DPinholeCamera03DBodyC(camera, canvas_region))
      {}
    //: Constructor.
  };

}

#endif
