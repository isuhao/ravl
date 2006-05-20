// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUIMANAGER_HEADER
#define RAVLGUIMANAGER_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$
//! file="Ravl/GUI/GTK/Manager.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/03/99"
//! example=exCanvas.cc
//! docentry="Ravl.GUI.Internal"


#include "Ravl/GUI/Widget.hh"
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/Threads/Semaphore.hh"
#include "Ravl/Trigger.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/Types.hh"
#include "Ravl/Hash.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/Threads/MessageQueue.hh"

namespace RavlGUIN {
  using namespace RavlN;
  
  class WindowC;
  
  //! userlevel=Normal
  //: GUI Manager class
  // As a user you should never need to creat an instance of this
  // class, instead you should use the global variable Manager
  // to access the relavent functions.
  
  class ManagerC  {
  public:
    ManagerC();
    //: Default constructor.
    
    ~ManagerC();
    //: Desructor.
    
    void Init(int &nargs,char *args[]);
    //: Initalise system.
    
    void Execute();
    //: Start manager on seperate thread.
    // Call only ONCE.
    
    void Start();
    //: Handle over control to manager.
    // This will only return when the GUI is exited by the
    // user.
    
    bool Notify(IntT id);
    //: Notify interface of event.
    
    void HandleNotify();
    //: Handle notify request.
    
    bool Shutdown();
    //: Finishup and exit.
    // This will not returns until the shutdown is complete.
    // It should NOT be used from withing the GUI interface.
    
    bool Wait();
    //: Wait for the GUI to be shutdown by the user.
    
    bool WaitForStartup();
    //: Wait for the GUI to be started.
    
    void Quit();
    //: Start shutdown, use if called from a button.
    
    WindowC &GetRootWindow();
    //: Access window.
    
    void SetRootWindow(WindowC &);
    //: Set root window.
    
    void Queue(const TriggerC &se);
    //: Queue an event for running in the GUI thread.
    // Thread safe.
    
    void Queue(RealT t,const TriggerC &se);
    //: Queue an event for running after delay 't'
    // NB. These events are NOT run on the GUI thread! <p>
    // Implemented with TimedEventQueue.
    // Thread safe.
    
    bool IsGUIThread() const;
    //: Test if we're in the GUI thread.
    
    bool IsManagerStarted() const
      { return managerStarted; }
    //: Test the GUI manger has been started.
    
    void UnrefPixmap(GdkPixmap *);
    //: Ensure that an unref takes place for pixmap on the GUIThread.
    
    void TidyUp();
    //: Tidy up before exiting..
    
  protected:
    
    IntT Register(WidgetBodyC &win);
    //: Register new window.
    
    void Deregister(WidgetBodyC &win);
    //: Deregister widget.
    
    void Deregister(IntT widgeID);
    //: Deregister widget.
    
    void SetupEvent(RealT &delay,TriggerC &se);
    //: Setup delayed event.
    // GUI thread only.
    
    static int timeout_callback(void *data);
    //: Timeout callback.
    
    bool &InitDone();
    //: Access init flag.
    
    MessageQueueC<TriggerC> events;
    HashC<IntT,TriggerC> delayEvents;
    int eCount;
    
    bool eventProcPending;
    
    MutexC access;
    HashC<IntT,WidgetC> wins; // Table of windows.
    IntT idc;                    // Window id counter.
    IntT ifp,ofp;  // File handle for event pipe.
    bool initCalled;
    bool managerStarted;
    bool shutdownFlag;
    ThreadEventC shutdownDone;
    ThreadEventC startupDone;
    UIntT guiThreadID;
    
    friend class WidgetBodyC;
    friend class WindowBodyC;
  };
  
  extern ManagerC Manager;
  
}
#endif