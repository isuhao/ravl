// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D
//! file="Ravl/GUI/3D/DTriMesh3D.cc"

#include "Ravl/GUI/DTriMesh3D.hh"
#include "Ravl/GUI/Canvas3D.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter.hh"
#include "GL/gl.h"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#define USEMESHCOLOUR 1

namespace RavlGUIN {

  //: Constructor.
  DTriMesh3DBodyC::DTriMesh3DBodyC(const TriMeshC &oTriMesh)
    : model(oTriMesh),
      doneInfo(false),
      extent(0)
  {}

  //: Compute center and extent of mesh.
  void DTriMesh3DBodyC::ComputeInfo() const
  {
    center = model.Centroid();
    extent = 0;
    for(SArray1dIterC<VertexC> it(model.Vertices());it;it++) {
      RealT dist = it->Position().SqrEuclidDistance(center);
      if(dist > extent)
	extent = dist;
    }
    extent = Sqrt(extent);
    doneInfo = true;
    ONDEBUG(std::cerr << "Center=" << center << " Extent=" << extent << "\n");
  }


  //: Get center of object.
  // defaults to 0,0,0
  Vector3dC DTriMesh3DBodyC::GUICenter() const
  {
    if(!doneInfo)
      ComputeInfo();
    //cerr << "DTriMesh3DBodyC::GUICenter(): " << center << std::endl;
    return center;
  }

  //: Get extent of object.
  // defaults to 1
  RealT DTriMesh3DBodyC::GUIExtent() const
  {
    if(!doneInfo)
      ComputeInfo();
    //cerr << "DTriMesh3DBodyC::GUIExtent(): " << extent << std::endl;
    return extent;
  }

  //: Render object.
  bool DTriMesh3DBodyC::GUIRender(Canvas3DC &canvas) const
  {
    if (!model.IsValid())
      return true; // Don't do anything.

    // Setup materials and colours as appropriate
    if (canvas.GetLightingMode()) {
      GLfloat ambient[]  = {0.2,0.2,0.2,1.0};
      GLfloat diffuse[]  = {0.9,0.9,0.9,1.0};
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    } else {
      glColor3f(1.0,1.0,1.0);
    }
    // Render
    Canvas3DRenderMode eMode = canvas.GetRenderMode();
    SArray1dC<VertexC> verts = model.Vertices();

#if USEMESHCOLOUR
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
#endif

    switch(eMode) {
    case C3D_SMOOTH:
    case C3D_POINT:
    case C3D_WIRE:
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_DOUBLE,sizeof(VertexC),(void *)&(verts[0].Normal()));
    case C3D_FLAT:
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3,GL_DOUBLE,sizeof(VertexC),(void *)&(verts[0].Position()));
      break;
    }

    switch(eMode)
      {
      case C3D_POINT: {
	// Draw individual points
	glDrawArrays(GL_POINTS,0,verts.Size());
      } break;
      case C3D_WIRE: {
	for(SArray1dIterC<TriC> it(model.Faces());it;it++) {
	  glBegin(GL_LINE);
	  glArrayElement(model.Index(*it,0));
	  glArrayElement(model.Index(*it,1));
	  glArrayElement(model.Index(*it,2));
	  glEnd();
	}
      } break;
      case C3D_FLAT: {
	ONDEBUG(std::cerr << "flat render. \n");
	IntT eGLShadeModel;
	glGetIntegerv(GL_SHADE_MODEL,&eGLShadeModel);
	glShadeModel(GL_FLAT); // Flat shading
	// Draw filled polygon
	for(SArray1dIterC<TriC> it(model.Faces());it;it++) {
#if USEMESHCOLOUR
	  glColor3ubv(&(it->Colour()[0]));
#endif
	  GLNormal(it->FaceNormal());
	  glBegin(GL_POLYGON);
	  glArrayElement(model.Index(*it,0));
	  glArrayElement(model.Index(*it,1));
	  glArrayElement(model.Index(*it,2));
	  glEnd();
	}
	glShadeModel((GLenum)eGLShadeModel); // Restore old shade model
      } break;
      case C3D_SMOOTH: {
	ONDEBUG(std::cerr << "Smooth render. \n");
	IntT eGLShadeModel;
	glGetIntegerv(GL_SHADE_MODEL,&eGLShadeModel);
	glShadeModel(GL_SMOOTH); // Flat shading
	// Draw filled polygon
	for(SArray1dIterC<TriC> it(model.Faces());it;it++) {
#if USEMESHCOLOUR
	  glColor3ubv(&(it->Colour()[0]));
#endif
	  glBegin(GL_POLYGON);
	  glArrayElement(model.Index(*it,0));
	  glArrayElement(model.Index(*it,1));
	  glArrayElement(model.Index(*it,2));
	  glEnd();
	}
	glShadeModel((GLenum)eGLShadeModel); // Restore old shade model
      } break;
      };

    switch(eMode) {
    case C3D_SMOOTH:
    case C3D_POINT:
    case C3D_WIRE:
      glDisableClientState(GL_NORMAL_ARRAY);
    case C3D_FLAT:
      glDisableClientState(GL_VERTEX_ARRAY);
      break;
    }
#if USEMESHCOLOUR
    glDisable(GL_COLOR_MATERIAL);
#endif
    return true;
  }

  std::ostream &operator<<(std::ostream &strm,const DTriMesh3DC &) {
    RavlAssert(0);
    return strm;
  }

  std::istream &operator>>(std::istream &strm,DTriMesh3DC &) {
    RavlAssert(0);
    return strm;
  }
}

