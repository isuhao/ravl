// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI3D_VIEW3D_HEADER
#define RAVLGUI3D_VIEW3D_HEADER 1
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/3D/View3D.hh"
//! lib=RavlGUI3D
//! docentry="Ravl.API.Graphics.3D"
//! author="James Smith"

#include "Ravl/GUI/Canvas3D.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/GUI/Table.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/MenuCheck.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/GUI/Manager.hh"

namespace RavlGUIN {

  class MouseEventC;
  class View3DC;

  //! userlevel=Develop
  //: Body for 3D Viewer widget.

  class View3DBodyC : public Canvas3DBodyC
  {
  public:
    View3DBodyC(int sx, int sy, bool enableLighting = true,
                bool enableTexture = true);
    //: Default constructor.

    bool GUIInitGL(void);
    //: Sets up GL context

    virtual bool Create(GtkWidget *Parent);
    //: Setup widget.

    bool GUIAdd(const DObject3DC &r, IntT id = 0);
    //: Add object to scene (call only from GUI thread)
    // If ID!=0, the object is assigned this id number, and
    // can be accessed using it.

    bool Add(const DObject3DC &r, IntT id = 0);
    //: Add object to scene
    // If ID!=0, the object is assigned this id number, and
    // can be accessed using it.
    
    void GUISceneComplete();
    //: Make the scene complete.
    // If more objects are Add()ed after this, a new scene will be started

    DObjectSet3DC &Scene()
      { return scene; }
    //: Access current scene. Not thread safe!

    bool GUIAdjustView();
    //:Automatically adjust view point

    bool GUIFit();
    //: Fit object to view

    bool GUICenter();
    //: Center output.

    bool GUIResetRotation();
    //: reset rotations.

    bool GUISetCamera(void);
    //: Rotates the camera

    bool GUIRefresh();
    //: Refresh display.

    bool Refresh();
    //: Refresh display. (Thread safe postponded refresh)

    Signal1C<Vector2dC> &SigRotationTx(void) {return m_sRotationTx;}
    //: Access to rotation send signal
  
    Signal1C<Vector2dC> &SigRotationRx(void) {return m_sRotationRx;}
    //: Access to rotation receive signal

    bool Master(bool& bMaster) {m_bMaster = bMaster; return true;}
    //: Enable or disable camera mastering

    bool Slave(bool& bSlave) {m_bSlave = bSlave; return true;}
    //: Enable or disable camera slaving

  protected:
    bool MousePress(MouseEventC &me);
    //: Handle button press.

    bool MouseRelease(MouseEventC &me);
    //: Handle button release.

    bool MouseMove(MouseEventC &me);
    //: Handle mouse move.

    bool MouseWheel(GdkEvent *event);
    //: Handle mouse wheel.

    //void GUIResetCamera();
    //: Resets the camera position.

    bool CBConfigureEvent(GdkEvent *event);
    //: Handle configure event

    bool SelectRenderMode(int& iOption);
    //: Selects the rendering mode for the backmenu
    // Reads value from the appropriate render mode menu item, and updates the other menu options appropriately.

    bool GUIFrontFaces(bool& bFront)
      { m_bFront = bFront; GUISetCullMode(); return true; }
    //: Enable or disable frontfaces

    bool GUIBackFaces(bool& bBack)
      { m_bBack = bBack; GUISetCullMode(); return true; }
    //: Enable or disable backfaces

    void GUISetCullMode();
    //: Sets the face culling mode based on member variables

    void CalcViewParams(bool AutoExtent);
    //: Calculate parameters of view on the scene
 
    bool m_bMaster;
    //: Are we controlling other cameras?
    bool m_bSlave;
    //: Are we slaved to other cameras?
    Signal1C<Vector2dC> m_sRotationTx; 
    //: Rotation sending signal
    Signal1C<Vector2dC> m_sRotationRx; 
    //: Rotation receiving signal
    bool SlaveRotation(Vector2dC& rotation);
    //: Rotation slaving function
    void SendSlaveSignal();
    //: Sends the updated rotation to slave views
    Vector2dC m_vRotation;
    //: View rotation parameters

    bool sceneComplete;
    DObjectSet3DC scene; // List of current render instructions.
    MenuC backMenu;
    //Vector3dC viewObject; // looking at point.
    //bool useRotate;
    //Vector3dC viewRotate;    // Rotation to apply.
    //RealT fov;
    //bool enablerefresh; // Are we allowed to refresh

    bool initDone; // Has initalization been completed ?

    //view settings (these are parameters of the camera)
    GLdouble m_sceneExtent;
    Vector3dC m_viewPoint;  // Where we are.
    Vector3dC m_sceneCenter; // looking at point.

    bool m_bTextureStatus;
    bool m_bLightingStatus;

    // Mouse position storage
    Index2dC m_lastMousePos;
    bool m_bIsDragging;

    // Render mode menu option handles
    MenuCheckItemC m_oRenderOpts[4];

    // Culling options
    bool m_bFront;
    bool m_bBack;

    RWLockC viewLock;
  };


  //! userlevel=Normal
  //: 3D Viewer widget.
  // <p>This class enables you to manipulate a 3D object as you view it, using the mouse.  </p>
  // <ul>
  // <li> Button 1 rotates about horizontal and vertical axes </li>
  // <li> Button 2 <i>should</i> translate in x and y directions, but the code needs fixing</li>
  // <li> Button 3 provides a menu of rendering options <li>
  // <li> The wheel <i>should</i> zoom in and out, but the code needs fixing</li>
  // </ul>

  class View3DC : public Canvas3DC
  {
  public:
    View3DC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
    View3DC(int width,int height,bool enableLighting = true,bool enableTexture = true)
      : Canvas3DC(*new View3DBodyC(width,height,enableLighting,enableTexture))
      {}
    //: Constructor.

    View3DC(View3DBodyC &bod)
      : Canvas3DC(bod)
      {}
    //: Body constructor.

    // *********************  GUI only intefrace  ******************************
    bool GUIInitGL()
      { return Body().GUIInitGL(); }
    //: Sets up GL context

    bool GUIAdd(const DObject3DC &r, IntT id = 0)
      { return Body().GUIAdd(r, id); }
    //: Add object to scene (only from gui thread)
    // If ID!=0, the object is assigned this id number, and
    // can be accessed using it.

    void GUISceneComplete()
      { Body().GUISceneComplete(); }
    //: Make the scene complete. GUI only
    // If more objects are Add() after this, a new scene will be started

    bool GUIAdjustView()
      { return Body().GUIAdjustView(); }
    //:Automatically adjust view point

    void GUIFit()
      { Body().GUIFit(); }
    //: Auto fit output.

    void GUICenter()
      { Body().GUICenter(); }
    //: Auto center output.

    void GUIResetRotation()
      { Body().GUIResetRotation(); }
    //: reset rotations.


    // ********************* General interface *********************************
    bool Add(const DObject3DC &r, IntT id = 0)
      { return Body().Add(r, id); }
    //: Add object to scene
    // If ID!=0, the object is assigned this id number, and
    // can be accessed using it.

    void SceneComplete()
      { Manager.Queue(Trigger(*this, &View3DC::GUISceneComplete)); }
    //: Make the scene complete.
    // If more objects are Add() after this, a new scene will be started



    // ****************  not checked unsorted functions  ***********************
    //bool GUINewFrame(void)
    //{ return Body().GUINewFrame(); }
    //: Sets up for a new frame

    bool GUISetCamera(void)
    { return Body().GUISetCamera(); }
    //: Rotates the camera

    //void GUIDoAuto()
    //  { return Body().GUIDoAuto(); }
    //: Fit and centre output if auto is enabled

    DObjectSet3DC &Scene()
      { return Body().Scene(); }
    //: Access current scene. (not thread safe!)

    void GUIRefresh()
    { Body().GUIRefresh(); }
    //: Auto center output.

    Signal1C<Vector2dC> &SigRotationTx(void) {return Body().SigRotationTx();}
    //: Access to rotation send signal
  
    Signal1C<Vector2dC> &SigRotationRx(void) {return Body().SigRotationRx();}
    //: Access to rotation receive signal

    bool Master(bool bMaster) {return Body().Master(bMaster);}
    //: Enable or disable camera mastering

    bool Slave(bool bSlave) {return Body().Slave(bSlave);}
    //: Enable or disable camera slaving

  protected:
    View3DBodyC &Body()
      { return static_cast<View3DBodyC &>(Canvas3DC::Body()); }
    //: Access body.

    const View3DBodyC &Body() const
      { return static_cast<const View3DBodyC &>(Canvas3DC::Body()); }
    //: Access body.

//    friend class View3DBodyC;
  };

}



#endif
