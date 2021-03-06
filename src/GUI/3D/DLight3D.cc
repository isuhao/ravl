// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D
//! file="Ravl/GUI/3D/DLight3D.cc"

#include "Ravl/GUI/DLight3D.hh"

namespace RavlGUIN {

  //: Render object.
  bool DLight3DBodyC::GUIRender(Canvas3DC &) const
  {
    const GLenum lightNo = LightNo(n);

    glClearColor(0,0,0,0);
    //glEnable(GL_AUTO_NORMAL);
    //glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);
    glEnable(lightNo);

    // Material defaults.
    float mat[4];

    mat[0] = 1;
    mat[1] = 1;
    mat[2] = 1;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 1;
    mat[1] = 1;
    mat[2] = 1;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0;
    mat[1] = 0;
    mat[2] = 0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

    // Set position...
    GLfloat fpos[4];
    fpos[0] = pos.X();
    fpos[1] = pos.Y();
    fpos[2] = pos.Z();
    fpos[3] = 1.;
    //cerr << "Light position:" << pos << std::endl;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glLightfv(lightNo, GL_POSITION, fpos);
    glPopMatrix();

    // Set colour....
    GLfloat col1[4],col2[4];
    col1[0] = colour.Red();
    col1[1] = colour.Green();
    col1[2] = colour.Blue();
    col1[3] = 1;
    for(IntT i = 0;i < 4;i++)
      col2[i] = col1[i] * 0.1;  // Ambient is 10% of full.

    glLightfv(lightNo, GL_AMBIENT,  col2);
    glLightfv(lightNo, GL_DIFFUSE,  col1);
    glLightfv(lightNo, GL_SPECULAR, col1);

    return true;
  }

  //: Convert Light number.
  GLenum DLight3DBodyC::LightNo(IntT no) const
  {
    switch(no)
    {
      case 0: return GL_LIGHT0;
      case 1: return GL_LIGHT1;
      case 2: return GL_LIGHT2;
      case 3: return GL_LIGHT3;
      case 4: return GL_LIGHT4;
      case 5: return GL_LIGHT5;
      case 6: return GL_LIGHT6;
      case 7: return GL_LIGHT7;
      default:
        RavlAssert(0);
        break;
    }
    return GL_LIGHT0;
  }
}
