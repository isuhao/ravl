// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// Python is used under the terms of the Python License
// Copyright (C) 2001, 2002, 2003, 2004 Python Software Foundation; All Rights Reserved
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! file = "Ravl/Contrib/Python/Python.hh"
//! lib = RavlPython
//! author = "Warren Moore"
//! docentry = "Ravl.API.Python"
//! example = "exPython.cc;exPythonThreaded.cc"

#ifndef RAVL_PYTHON_HEADER
#define RAVL_PYTHON_HEADER 1

#include <Python.h>
#include "Ravl/RefCounter.hh"
#include "Ravl/Hash.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlN
{
  
  class PythonC;
  class PythonObjectC;
  
  //! userlevel=Develop
  //: Class managing a Python interpreter
  
  class PythonBodyC : 
    public RCBodyVC
  {
  public:
    PythonBodyC();
    //: Constructor.
    //!throw: PythonExceptionC - If a Python exception is set
    
    virtual ~PythonBodyC();
    //: Destructor.
    
    const bool Initialised() const
    { return m_threadState != NULL; }
    //: Is the interpreter ready?
    //!return: False on failure
    
    bool AppendSystemPath(const StringC &path);
    //: Append a string to 'sys.path'.
    //!param: path - A file system path to search for Python modules
    //!return: false on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    bool Import(const StringC &module);
    //: Load a module using Python 'import' notation.
    //!param: module - The name of a Python module
    //!return: false on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    PythonObjectC NewObject();
    //: Create a new Python object.
    //!return: A new Python object
    
    PythonObjectC Call(const StringC &module, const StringC &function);
    //: Call a function.
    //!param: module - The name of the module containing the function to call
    //!param: function - The name of the function to call
    //!return: Invalid object on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    PythonObjectC Call(const StringC &module,
            const StringC &function,
            const PythonObjectC &args);
    //: Call a function with arguments.
    //!param: module - The name of the module containing the function to call
    //!param: function - The name of the function to call
    //!param: args - Must represent a tuple containing all the required arguments
    //!return: Invalid object on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    bool Run(const StringC &script, const StringC &traceName);
    //: Load a Python script into the main environment and execute immediately.
    //!param: script - Script to execute
    //!param: traceName - Name to be used in the Python exception traceback if the script fails
    //!return: False on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    PythonObjectC GetGlobal(const StringC &name);
    //: Get a result object called 'name' from the globals.
    //!return: Invalid object on failure
    
    PyThreadState *GetThreadState() const
    { return m_threadState; }
    //: Return the Python interpreter thread state.
    //!return: NULL on failure
    
  private:
    void InitialiseEnvironment();
    //: Initialise the Python thread state environment.
    //!throw: PythonExceptionC - If a Python exception is set
    
    PyObject *GetModuleDictionary(const StringC &name);
    //: Get a dictionary from the named module.
    //!return: A new reference to the dictionary or NULL on failure
    
  private:
    static MutexC m_initLock;
    static PythonC m_mainInterpreter;
    bool m_subInterpreter;
    PyThreadState *m_mainThreadState;
    PyThreadState *m_threadState;
    HashC<StringC, PyObject*> m_modules;
    MutexC m_lock;
  };
  
  //! userlevel = Normal
  //: Class managing a Python interpreter
  // BIG OBJECT
  
  class PythonC :
    public RCHandleC<PythonBodyC>
  {
  public:
    PythonC()
    {}
    //: Default constructor.
    // Creates an invalid handle
    
    PythonC(bool) :
      RCHandleC<PythonBodyC>(*new PythonBodyC())
    {}
    //: Constructor.
    //!throw: PythonExceptionC - If a Python exception is set
    
    const bool Initialised() const
    { return Body().Initialised(); }
    //: Is the interpreter ready?
    //!return: False on failure

    bool AppendSystemPath(const StringC &path)
    { return Body().AppendSystemPath(path); }
    //: Append a string to 'sys.path'.
    //!param: path - A file system path to search for Python modules
    //!return: false on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    bool Import(const StringC &module)
    { return Body().Import(module); }
    //: Load a module using Python 'import' notation.
    //!param: module - The name of a Python module
    //!return: false on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    PythonObjectC NewObject();
    //: Create a new Python object.
    //!return: A new Python object
    
    PythonObjectC Call(const StringC &module, const StringC &name);
    //: Call a function.
    //!param: module - The name of the module containing the function to call
    //!param: function - The name of the function to call
    //!return: Invalid object on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    PythonObjectC Call(const StringC &module, const StringC &name, const PythonObjectC &args);
    //: Call a function with arguments.
    //!param: module - The name of the module containing the function to call
    //!param: function - The name of the function to call
    //!param: args - Must represent a tuple containing all the required arguments
    //!return: Invalid object on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    bool Run(const StringC &script, const StringC &traceName = "<string>")
    { return Body().Run(script,traceName); }
    //: Load a Python script into the main environment and execute immediately.
    //!param: script - Script to execute
    //!param: traceName - Name to be used in the Python exception traceback if the script fails
    //!return: False on failure
    //!throw: PythonExceptionC - If a Python exception is set
    
    PythonObjectC GetGlobal(const StringC &name);
    //: Get a result object called 'name' from the globals.
    //!return: Invalid object on failure
    
    PyThreadState *GetThreadState() const
    { return Body().GetThreadState(); }
    //: Return the Python interpreter thread state.
    //!return: NULL on failure
    
  private:
    PythonC(PythonBodyC &body) : 
      RCHandleC<PythonBodyC>(body)
    {}
    //: Body constructor. 
    
    PythonBodyC& Body()
    { return static_cast<PythonBodyC &>(RCHandleC<PythonBodyC>::Body()); }
    //: Body Access. 
    
    const PythonBodyC& Body() const
    { return static_cast<const PythonBodyC &>(RCHandleC<PythonBodyC>::Body()); }
    //: Body Access. 
    
    friend class PythonBodyC;
  };

}

#endif

