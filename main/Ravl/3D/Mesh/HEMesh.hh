// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_HEMESH_HEADER
#define RAVL3D_HEMESH_HEADER 1
//! rcsid="$Id$"
//! lib=Ravl3D
//! author="Charles Galambos"
//! docentry="Ravl.3D.Half Edge Mesh"
//! date="24/4/2002"

#include "Ravl/3D/HEMeshFace.hh"
#include "Ravl/3D/HEMeshVertex.hh"
#include "Ravl/3D/HEMeshEdge.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/DList.hh"
#include "Ravl/InDList.hh"
#include "Ravl/SArray1d.hh"

namespace Ravl3DN {

  using namespace RavlN;
  
  class HEMeshC;
  class TriMeshC;
  
  //! userlevel=Develop
  //: Half Edge Mesh Body
  
  class HEMeshBodyC 
    : public RCBodyVC
  {
  public:
    HEMeshBodyC()
    {}
    //: Default constructor.
    // Creates an empty mesh.
    
    HEMeshBodyC(const TriMeshC &mesh);
    //: Construct from a TriMesh
    
    HEMeshVertexC InsertVertex(const Vector3dC &position,const Vector3dC &norm) {
      HEMeshVertexC vert(position,norm);
      vertices.InsLast(vert.Body());
      return vert;
    }
    //: Insert a new vertex into the mesh.

    HEMeshVertexC InsertVertex(const VertexC &vert) {
      HEMeshVertexC nvert(vert);
      vertices.InsLast(nvert.Body());
      return nvert;
    }
    //: Insert a new vertex into the mesh.
    
    HEMeshFaceC InsertFace(const SArray1dC<HEMeshVertexC> &vertices);
    //: Insert face defined by vertices.
    
    UIntT NoFaces() const
    { return faces.Size(); }
    //: Get the number of faces.
    
    UIntT NoVertices() const
    { return vertices.Size(); }
    //: Get the number of vertices.
    
    TriMeshC TriMesh() const;
    //: Build a TriMesh from this mesh.
    
  protected:
    IntrDListC<HEMeshFaceBodyC> faces;  // List of faces in the mesh.
    IntrDListC<HEMeshVertexBodyC> vertices; // List of vertices.
  };
  

  //! userlevel=Normal
  //: Half Edge Mesh
  // Refrence counted handle to mesh.
  
  class HEMeshC 
    : public RCHandleC<HEMeshBodyC>
  {
  public:
    HEMeshC()
    {}
    //: Default constructor.

    HEMeshC(bool)
      : RCHandleC<HEMeshBodyC>(*new HEMeshBodyC())
    {}
    //: Constructor.
    
    HEMeshC(const TriMeshC &mesh)
      : RCHandleC<HEMeshBodyC>(*new HEMeshBodyC(mesh))
    {}
    //: Construct from a TriMesh

    HEMeshVertexC InsertVertex(const Vector3dC &position,const Vector3dC &norm)
    { return Body().InsertVertex(position,norm); }
    //: Insert a new vertex into the mesh.

    HEMeshVertexC InsertVertex(const VertexC &vert)
    { return Body().InsertVertex(vert); }
    //: Insert a new vertex into the mesh.
    
    HEMeshFaceC InsertFace(const SArray1dC<HEMeshVertexC> &vertices)
    { return Body().InsertFace(vertices); }
    //: Insert face defined by vertices.

    UIntT NoFaces() const
    { return Body().NoFaces(); }
    //: Get the number of faces.
    
    UIntT NoVertices() const
    { return Body().NoVertices(); }
    //: Get the number of vertices.
    
    TriMeshC TriMesh() const;
    //: Build a TriMesh from this mesh.
    
  };

}

#endif
