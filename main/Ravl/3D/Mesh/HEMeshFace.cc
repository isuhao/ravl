// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D

#include "Ravl/3D/HEMeshFace.hh"

namespace Ravl3DN {

  //: Get number of edges on face.
  
  UIntT HEMeshFaceBodyC::Sides() const {
    if(edge == 0)
      return 0;
    UIntT count = 0;
    for(HEMeshFaceEdgeIterC it(const_cast<HEMeshFaceBodyC &>(*this));it;it++)
      count++;
    return count;
  }

  //: Check that the vertex is connected to this face.
  
  bool HEMeshFaceBodyC::HasVertex(HEMeshVertexC vert) const {
    for(HEMeshFaceEdgeIterC it(const_cast<HEMeshFaceBodyC &>(*this));it;it++)
      if(it.Data().Vertex() == vert) 
	return true;
    return false;
  }

  //: Find the edge linking to vertex a.
  // If edge is not found an invalid handle is returned.
  
  HEMeshEdgeC HEMeshFaceBodyC::FindEdge(HEMeshVertexC a) {
    for(HEMeshFaceEdgeIterC it(const_cast<HEMeshFaceBodyC &>(*this));it;it++)
      if(it.Data().Vertex() == a) 
	return it.Data();
    return HEMeshEdgeC();
  }
  
  
}
