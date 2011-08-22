// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2009, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlXMLFactory
//! author=Charles Galambos
//! docentry=Ravl.API.Core.IO.XMLFactory

#include "Ravl/IO.hh"
#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/StringList.hh"
#include "Ravl/HSet.hh"
#include "Ravl/XMLFactory.hh"
#include "Ravl/XMLFactoryAutoStart.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/OS/Filename.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  using RavlN::StringC;

  RavlN::HashC<StringC,XMLFactoryC::TypeFactoryT> &XMLFactoryC::Type2Factory() {
    static RavlN::HashC<StringC,TypeFactoryT> type2factory;
    return type2factory;
  }

  //! Destructor.
  XMLFactoryNodeC::~XMLFactoryNodeC()
  {
    //RavlSysLogf(SYSLOG_DEBUG,"XMLFactoryNodeC::~XMLFactoryNodeC, Called. %p Name:'%s' ",(void *)this,m_xmlNode.Name().chars());
  }
  
  //: Flag attribute as used.
  
  void XMLFactoryNodeC::UseAttribute(const StringC &name) const {
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    m_usedAttributes += name;
  }
  //: Check if all attributes have been used.
  
  bool XMLFactoryNodeC::CheckUsedAttributes() const {
    bool passed = true;
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_READONLY);
    for(RavlN::HashIterC<StringC,StringC> it(XMLNode().Attributes());it;it++) {
      if(it.Key() == "typename")
        continue;
      if(!m_usedAttributes[it.Key()]) {
        RavlSysLogf(SYSLOG_ERR,"Unknown attribute '%s' in '%s' ",it.Key().data(),Path().data());
        passed = false;
      }
    }
    return passed;
  }

  //! Follow path to child node.
  
  bool XMLFactoryNodeC::FollowPath(const StringC &path,XMLFactoryNodeC::RefT &node,bool verbose) const {
    RavlN::StringListC pathElements(path,":/.");
    return FollowPath(pathElements,node,verbose);
  }
  
  //! Follow path to child node.
  
  bool XMLFactoryNodeC::FollowPath(const RavlN::DListC<StringC> &path,RefT &node,bool verbose) const {
    XMLFactoryNodeC::RefT at = this;
    for(RavlN::DLIterC<StringC> it(path);it;it++) {
      RavlN::RWLockHoldC hold(at->m_access,RavlN::RWLOCK_READONLY);
      const RefT *child = at->m_children.Lookup(*it);
      if(child == 0) {
        hold.Unlock();
        // This failed, try parent.
        if(m_parent.IsValid())
          return m_parent->FollowPath(path,node,verbose);
        return false;
      }
      RavlAssert((*child).IsValid());
      at = &(**child);
      hold.Unlock();
    }
    node = at;
    return true;
  }
  
  //! Follow path to child node, create nodes where needed
  
  bool XMLFactoryNodeC::UsePath(const StringC &path,
                                RefT &node,
                                bool restrictToXMLTree,
                                bool verbose,
                                XMLFactorySearchScopeT searchScope)
  {
    RavlN::StringListC pathElements(path,":/.");
    return UsePath(pathElements,node,restrictToXMLTree,verbose,searchScope);
  }
  
  //! Follow path to child node, create nodes where needed
  
  bool XMLFactoryNodeC::UsePath(const RavlN::DListC<StringC> &path,
                                RefT &node,
                                bool restrictToXMLTree,
                                bool verbose,
                                XMLFactorySearchScopeT searchScope)
  {
    XMLFactoryNodeC::RefT at = this;
    for(RavlN::DLIterC<StringC> it(path);it;it++) {
      RefT child;
      if(!at->UseChild(*it,child,restrictToXMLTree,verbose)) {
        // This failed, try parent.

        if(searchScope == XMLFACTORY_SEARCH_PARENT_NODES && m_parent.IsValid()) {
          if(verbose)
            RavlSysLogf(SYSLOG_DEBUG,"Child '%s' not found in '%s', trying parent. ",it->chars(),at->Path().chars());
          return m_parent->UsePath(path,node,restrictToXMLTree,verbose);
        }
        return false;
      }
      RavlAssert(child.IsValid());
      at = child;
    }
    node = at;
    return true;
  }
  
  //! Find child and create one if it doesn't exist.
  
  bool XMLFactoryNodeC::UseChild(const StringC &name,
                                 RefT &child,
                                 bool restrictToXMLTree,
                                 bool verbose)
  {
    if(FindChild(name,child)) {
      RavlAssert(child.IsValid());
      return true;
    }
    XMLTreeC childNode;
    if(!m_xmlNode.IsValid() && restrictToXMLTree) {
      if(verbose)
        RavlSysLogf(SYSLOG_ERR,"Child '%s' of '%s' is out of tree.",name.chars(),Path().chars());
      return false;
    }
    if(m_xmlNode.IsValid() && !m_xmlNode.Child(name,childNode)) {
      if(restrictToXMLTree) {
        if(verbose)
          RavlSysLogf(SYSLOG_DEBUG,"Child '%s' not in tree from path '%s'. XMLNode:%s ",name.chars(),Path().chars(),m_xmlNode.Name().chars());
        return false;
      }
    }
    XMLFactoryNodeC::RefT newNode = new XMLFactoryNodeC(childNode,*this);
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    m_children[name] = newNode;
    child = newNode;
    return true;
  }
  
  //! Find named child.
  
  bool XMLFactoryNodeC::FindChild(const StringC &name,RefT &child) const {
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_READONLY);
    const RefT *childp = m_children.Lookup(name);
    if(childp == 0 || !childp->IsValid())
      return false;
    child = *childp;
    return true;
  }
  
  //! Create component in node.
  
  bool XMLFactoryNodeC::CreateComponent(XMLFactoryC &factory) {
    // Only one thread can create a node at a time. The lock
    // is recursive so we should still catch recursive create loops nicely.
    RavlN::MutexLockC lock(m_createLock);
    bool ret = true;
    if(!m_component.IsValid()) {
      if(m_createComponentCalled) {
        RavlSysLogf(SYSLOG_ERR,"XMLFactory detected a recursive create loop in %s ",Path().chars());
        RavlAssertMsg(0,"Recursive create loop found. ");
        return false;
      }
      m_createComponentCalled = true;
      ret = factory.CreateComponentInternal(*this,m_component);
      m_createComponentCalled = false;
    }
    return ret;
  }
  
  
  //! Get named component.

  bool XMLFactoryNodeC::GetComponentInternal(const RavlN::StringC &name,
                                             const std::type_info &to,
                                             RavlN::RCWrapAbstractC &handle,
                                             bool silentError) const
  {
    XMLFactoryNodeC::RefT child;
    if(!FollowPath(name,child) || !child.IsValid()) {
      RavlSysLogf(SYSLOG_DEBUG," follow path '%s' from '%s' children:",name.chars(),Path().chars());
      RavlSysLogf(SYSLOG_DEBUG," NOTE: This method will not create components, only reuse existing ones. (Try UseComponent)");
      for(HashIterC<StringC,RefT> it(m_children);it;it++) {
        RavlSysLogf(SYSLOG_DEBUG," Child '%s'",it.Key().chars());
      }
      
      return false;
    }
    
    if(!child->Component().IsValid()) {
      RavlSysLogf(SYSLOG_DEBUG,"No component at the leaf of path '%s' from '%s'",name.chars(),Path().chars());
      return false;
    }
    
    const std::type_info &from = child->Component().DataType();
    if(from == to) {
      handle = child->Component();
      return true;
    }
    
    handle = RavlN::SystemTypeConverter().DoConversion(child->Component().Abstract(),from,to);
    if(!handle.IsValid()) {
      if(!silentError)
        RavlSysLogf(SYSLOG_WARNING," convert data to requested type, from '%s' to '%s' ",RavlN::TypeName(from),RavlN::TypeName(to));
      return false;
    }
    return true;
    
  }

  //! Get named component.
  bool XMLFactoryNodeC::UseComponentInternal(XMLFactoryC &factory,
                                             const RavlN::StringC &rawname,
                                             const std::type_info &to,
                                             RavlN::RCWrapAbstractC &handle,
                                             bool silentError,
                                             const std::type_info &defaultType,
                                             XMLFactorySearchScopeT searchScope
                                             ) 
  {
    XMLFactoryNodeC::RefT child;

    RavlAssert(m_xmlNode.IsValid());
    
    // Look for redirection.
    StringC name = AttributeString(rawname);
    if(!name.IsEmpty()) {
      // If name has been redefined use extended search scope.
      searchScope = XMLFACTORY_SEARCH_PARENT_NODES;
    } else {
      name = rawname;
    }

    if(!UsePath(name,child,true,factory.VerboseMode(),searchScope) || !child.IsValid()) {
      if(!silentError) {
        RavlSysLogf(SYSLOG_DEBUG,"Failed to find path to requested type, '%s' from path '%s' ",name.chars(),Path().chars());
        //Dump(std::cerr);
        //XMLNode().Dump(std::cerr);
      }
      return false;
    }
    
    // FIXME:- Do we want to use the default type ?
    if(child->XMLNode().IsValid()) {
      if(!child->XMLNode().Data().IsElm("typename")) {
        // Do we know how to build the type?
        StringC reqType = RavlN::TypeName(defaultType);
        //std::cerr << "Setting default type for node=" <<reqType << "\n";
        if(XMLFactoryC::Type2Factory().IsElm(reqType))
          child->XMLNode().Data()["typename"] = reqType;
      }
    }
    if(!child->Component().IsValid()) {
      if(!child->CreateComponent(factory)) {
        if(!silentError)
          RavlSysLogf(SYSLOG_ERR," create component '%s' ",name.chars());
        return false;
      }
      RavlAssert(child->Component().IsValid());
    }
    
    const std::type_info &from = child->Component().DataType();
    if(from == to || to == typeid(void)) {
      ONDEBUG(RavlSysLogf(SYSLOG_DEBUG,"UseComponentInternal, no conversion needed at '%s' for type '%s'",name.chars(),RavlN::TypeName(from)));
      handle = child->Component();
      RavlAssert(handle.IsValid());
      return true;
    }
    
    handle = RavlN::SystemTypeConverter().DoConversion(child->Component().Abstract(),from,to);
    if(!handle.IsValid()) {
      if(!silentError)
        RavlSysLogf(SYSLOG_ERR," convert data to requested type, from '%s' to '%s' ",RavlN::TypeName(from),RavlN::TypeName(to));
      return false;
    }
    ONDEBUG(RavlSysLogf(SYSLOG_DEBUG,"UseComponentInternal, successfull @ '%s' ",name.chars()));
    return true;
  }
  
  //! Set named component.
  
  bool XMLFactoryNodeC::SetComponentInternal(const RavlN::StringC &name,const RavlN::RCWrapAbstractC &handle) {
    XMLFactoryNodeC::RefT child;
    RavlN::StringListC pathElements(name,":/");
    XMLFactoryNodeC::RefT at = this;
    for(RavlN::DLIterC<StringC> it(pathElements);it;it++) {
      XMLFactoryNodeC::RefT atNext;
      if(!at->UseChild(*it,atNext,false) || !atNext.IsValid()) {
        RavlSysLogf(SYSLOG_DEBUG," create path. '%s' at '%s'",name.chars(),it->chars());
        return false;
      }
      at = atNext;         
    }
    at->SetComponent(handle);
    ONDEBUG(RavlSysLogf(SYSLOG_DEBUG,"Component '%s' set ok. ",name.chars()));
    return true;
  }
  

  
  static StringC Ident(int n) {
    StringC ret;
    for(int k = 0;k < n;k++)
      ret += ' ';
    return ret;
  }
  
  bool XMLFactoryNodeC::Dump(std::ostream &strm,int level) {
    strm << Ident(level*2) << " " << Name() << " : " << XMLNode().AttributeString("typename","?") << "\n";
    for(RavlN::HashIterC<StringC,RefT> it(m_children);it;it++) {
      it.Data()->Dump(strm,level+1);
    }
    
    return true;
  }
  
  //! Get path to this node.
  
  StringC XMLFactoryNodeC::Path() const {
    StringC ret;
    const XMLFactoryNodeC *at = this;
    ret = at->Name();
    while(at->m_parent.IsValid()) {
      at = &(*at->m_parent);
      ret = at->Name() + ':' + ret;
    }
    return ret;
  }
  
  //: Called when owner handles drop to zero.
  
  void XMLFactoryNodeC::ZeroOwners() {
    //RavlSysLogf(SYSLOG_DEBUG,"XMLFactoryNodeC::ZeroOwners, Called. %p '%s' ",(void *)this,Name().chars());
    //RavlAssert(0);
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    m_children.Empty();
    m_parent.Invalidate();
    hold.Unlock();
    RavlN::RCLayerBodyC::ZeroOwners();
  }
  
  //! Add a child to this node.
  //! Note: This will overwrite any existing node of the name
  
  bool XMLFactoryNodeC::AddChild(const StringC &name,XMLFactoryNodeC &child) {
    StringC newName = name;
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    if(m_children.IsElm(newName)) {
      int count = 0;
      do {
        newName = name + '-' + StringC(count++);
      } while(m_children.IsElm(newName)) ;
      
      RavlSysLogf(SYSLOG_WARNING,"Child of name '%s' already exists in '%s', using name '%s' instead ",name.chars(),Path().chars(),newName.chars());
    }
    m_children[newName] = &child; 
    child.m_parent = this;
    return true;
  }
  
  //! Remove a child.
  
  bool XMLFactoryNodeC::DelChild(const StringC &name) {
    XMLFactoryNodeC::RefT child;
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    if(!m_children.Lookup(name,child))
      return false; // Child not known.
    if(&(*child->m_parent) == this)
      child->m_parent.Invalidate();
    m_children.Del(name);
    return true;
  }
  
  
  //------------------------------------------------------------

  extern void linkXMLFactoryRegister();
  
  //! Construct from Factory.
  
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryHC &factory)
    : m_iNode(&factory.IRoot()),
      m_factory(const_cast<XMLFactoryC &>(*factory.BodyPtr()))
  { 
    UseAttribute("verbose");
    UseAttribute("checkConfig");
  }
  
  //! Constructor.
  
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryC &factory,
                                         const XMLFactoryNodeC &iNode)
    : m_iNode(&iNode),
      m_factory(const_cast<XMLFactoryC &>(factory))
  { const_cast<XMLFactoryC &>(factory).PostReadConfig();  }

  //! Got a child node.
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryContextC &context,const StringC &childName)
    : m_factory(context.m_factory)
  {
    if(!context.m_iNode->FindChild(childName,m_iNode))
      RavlSysLogf(SYSLOG_WARNING,"Child '%s' not found. ",childName.chars());
  }
  
  //! Factory.
  
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryC &factory)
    : m_factory(const_cast<XMLFactoryC &>(factory))
    
  { 
    const_cast<XMLFactoryC &>(factory).PostReadConfig(); 
    m_iNode = &factory.IRoot();
    UseAttribute("verbose");
    UseAttribute("checkConfig");
  }
  
  //: Destructor
  
  XMLFactoryContextC::~XMLFactoryContextC()
  {
#if 0
    if(m_factory.IsValid() && m_iNode.IsValid()) {
      if(Factory().CheckConfig()) {
        if(!m_iNode->CheckUsedAttributes()) {
          throw RavlN::ExceptionBadConfigC("Unexpected attributes in file. ");
        }
      }
    }
#endif
  }
      
  //: lookup child in tree.
  // Returns true and updates parameter 'child' if child is found.
  bool XMLFactoryContextC::ChildContext(const StringC &key,XMLFactoryContextC &child) const {
    if(!m_iNode.IsValid())
      return false;
    XMLFactoryNodeC::RefT childNode;
    if(!m_iNode->UseChild(key,childNode)) {
      return false;
    }
    child = XMLFactoryContextC(Factory(),*childNode);
    return true;
  }

  //! Set factory to use.
  
  void XMLFactoryContextC::SetFactory(const XMLFactoryC &factory) { 
    m_factory = const_cast<XMLFactoryC &>(factory); 
    const_cast<XMLFactoryC &>(factory).PostReadConfig();
  }
  
  XMLFactoryC &XMLFactoryContextC::Factory() const { 
    RavlAssert(m_factory.IsValid());
    return const_cast<XMLFactoryC &>(static_cast<const XMLFactoryC &>(m_factory.Body())); 
  }
  
  //------------------------------------------------------------

  XMLFactoryC::XMLFactoryC()
    : m_configRoot(true),
      m_setupClean(true),
      m_verbose(false),
      m_checkConfig(false)
  {
    m_configTree = XMLTreeC(true);
    m_iRoot = new XMLFactoryNodeC(m_configTree);
  }
  
  //! Open a config file.
  
  XMLFactoryC::XMLFactoryC(const StringC &configFile,XMLTreeLoadC *loader)
    : m_configRoot(true),
      m_setupClean(true),
      m_donePostSetup(false),
      m_verbose(false),
      m_checkConfig(false)
  {
    RavlSysLogf(SYSLOG_DEBUG,"XMLFactoryC, Config file '%s' ",configFile.chars());
    if(!Read(configFile,loader)) {
      throw RavlN::ExceptionBadConfigC("Can't open config file. ");
    }
  }

  //! Recursive constructor.
  
  XMLFactoryC::XMLFactoryC(const XMLFactoryContextC &context)
    : m_configRoot(true),
      m_setupClean(true),
      m_donePostSetup(false),
      m_verbose(false),
      m_checkConfig(false)
  {
    RavlSysLogf(SYSLOG_DEBUG,"XMLFactoryC, Sub factory. ");
    
    StringC fileName = context.AttributeString("configfile","");
    if(!fileName.IsEmpty())
      Read(fileName);
  }
  
  //! Use an existing tree.
  
  XMLFactoryC::XMLFactoryC(const StringC &configFileName,const XMLTreeC &configTree)
    : m_masterConfigFilename(configFileName),
      m_configRoot(configTree),
      m_setupClean(true),
      m_donePostSetup(false),
      m_verbose(false),
      m_checkConfig(false)
  {
    RavlSysLogf(SYSLOG_DEBUG,"Constructing from preparsed tree %s. ",configFileName.chars());
    // Setup the root.
    if(!m_configRoot.Child("Config",m_configTree)) {
      RavlSysLogf(SYSLOG_ERR,"No config section in '%s' ",m_masterConfigFilename.chars());
      m_setupClean = false;
      
    } else {
      // Setup root node.
      m_iRoot = new XMLFactoryNodeC(m_configTree);
    }
    // In verbose mode ?
    m_verbose = m_configTree.AttributeBool("verbose",false);
    if(m_verbose) {
      std::cerr << "XMLFactory config tree: \n";
      m_configRoot.Dump(std::cerr);
    }
    m_checkConfig = m_configTree.AttributeBool("checkConfig",false);
    RavlSysLogf(SYSLOG_DEBUG,"Enabled check config:%d ",(int) m_checkConfig);
  }
  
  //! Read config file.
  
  bool XMLFactoryC::Read(const StringC &configFile,XMLTreeLoadC *loader) {
    m_masterConfigFilename = configFile;    
    m_configRoot = XMLTreeC(true);
    if(!m_configRoot.ReadFile(configFile,loader)) {
      RavlSysLogf(SYSLOG_ERR,"Failed to load config file. '%s' ",configFile.chars());
      m_setupClean = false;
      return false;
    }

    // Setup the root.
    //m_configRoot.Dump(std::cerr);
    if(!m_configRoot.Child("Config",m_configTree)) {
      RavlSysLogf(SYSLOG_ERR,"No config section in '%s' ",m_masterConfigFilename.chars());
      m_setupClean = false;
      return false;
    } else {
      // Setup root node.
      m_iRoot = new XMLFactoryNodeC(m_configTree);
    }
    
    // In verbose mode ?
    m_verbose = m_configTree.AttributeBool("verbose",false);
    m_checkConfig = m_configTree.AttributeBool("checkConfig",false);
    
    // Do post config if we can.
    
    if(References() > 0)
      PostReadConfig();
    return true;
  }
  
  //! Check config thats just been loaded.
  bool XMLFactoryC::PostReadConfig() {
    if(m_donePostSetup)
      return true;
    
    m_donePostSetup = true;    
    if(!m_configTree.IsValid()) {
      //std::cerr << "Config loaded:\n";
      //m_configRoot.Dump(std::cerr);
      
      if(!m_configRoot.Child("Config",m_configTree)) {
        RavlSysLogf(SYSLOG_ERR,"No config section in '%s' ",m_masterConfigFilename.chars());
        m_setupClean = false;
        return false;
      }
      
      // Setup root node.
      m_iRoot = new XMLFactoryNodeC(m_configTree);
    }
    
    if(m_verbose) {
      std::cerr << "XMLFactory config tree: \n";
      m_configRoot.Dump(std::cerr);
    }
    
    // Look for preload section.
    XMLTreeC preLoad;
    if(m_configTree.Child("Preload",preLoad)) {
      //UIntT count = 0;
      //RavlSysLogf(SYSLOG_DEBUG,"Found preload section. ");
      XMLFactoryNodeC::RefT preLoadNode;
      if(!m_iRoot->UseChild("Preload",preLoadNode)) {
        RavlAssertMsg(0," create preload section.");
        RavlSysLogf(SYSLOG_ERR,"Unexpected error creating preload section. ");
        return false;
      }
      for(RavlN::DLIterC<XMLTreeC> it(preLoad.Children());it;it++) {
        const StringC xmlName = it->Name();
        
        // Make sure name is unique within preload section.
        StringC finalName = it->Name();
        XMLFactoryNodeC::RefT childNode;        
        UIntT count = 1;
        while(preLoadNode->FindChild(finalName,childNode)) {
          finalName = xmlName + '-' + StringC(count++);
        }
        
        // Create the component here in the tree.
        childNode = new XMLFactoryNodeC(*it,*preLoadNode);
        if(!childNode->CreateComponent(*this)) {
          continue; // We  create the node, the reason should have already been reported.
        }
        
        // Is this component intended for elsewhere in the tree ?
        StringC componentName = childNode->AttributeString("component","");
        if(!componentName.IsEmpty()) {
          // FIXME :- Do we need to do this ?
          RavlSysLogf(SYSLOG_WARNING,"Preloading components into other parts of the tree not currently supported. ");
        }
        
        preLoadNode->AddChild(finalName,*childNode);
      }
    }
    
    return true;
  }
  
  //! Report failure in UseComponent
  
  void XMLFactoryC::ReportUseComponentFailed(const XMLFactoryContextC &currentNode,
                                             const RavlN::StringC &name,
                                             const std::type_info &type) const 
  {
    RavlSysLogf(SYSLOG_ERR," find component '%s', to create type '%s'. Path=%s ",name.chars(),RavlN::TypeName(type),currentNode.Path().chars());
  }

  //! Create a component
  bool XMLFactoryC::CreateComponentInternal(const XMLFactoryNodeC &node,RavlN::RCWrapAbstractC &rawHandle) {
    StringC loadFilename = node.AttributeString("load","");
    if(!loadFilename.IsEmpty()) {
      // ---- Load component from file ----
      StringC resourceModule = node.AttributeString("resourceModule","");
      RavlSysLogf(SYSLOG_DEBUG,"Loading component, Name='%s' file='%s' ",node.Name().chars(), loadFilename.data());
      StringC fullName = RavlN::FilenameC::Search(loadFilename,
                                                  RavlN::FilenameC(MasterConfigFilename()).PathComponent(),
                                                  resourceModule.data());
      if(fullName.IsEmpty()) {
        RavlSysLogf(SYSLOG_ERR," Failed to find file '%s'  in node '%s' resourceModule '%s'",
               loadFilename.chars(), node.Name().chars(),resourceModule.chars());
        return false;
      }
      RavlSysLogf(SYSLOG_DEBUG,"Loading file='%s' ", fullName.data());
      if(!RavlN::LoadAbstract(fullName, rawHandle, "", node.XMLNode().AttributeBool("loadVerbose", false))) {
        RavlSysLogf(SYSLOG_ERR," load node '%s' from '%s'",node.Name().chars(),fullName.chars());
        throw RavlN::ExceptionBadConfigC("Failed to load node from file. ");
        return false;
      }
      
    } else {
      // ---- Create component using factory ----
      
      StringC typeToMake = node.AttributeString("typename","");
      RavlSysLogf(SYSLOG_DEBUG,"Creating component, Path='%s' Type='%s' ",node.Path().chars(),typeToMake.chars());
      if(typeToMake.IsEmpty()) {
        RavlSysLogf(SYSLOG_ERR,"No type specified for node '%s'",node.Name().chars());
        throw RavlN::ExceptionBadConfigC("Type not specified. ");
        return false;
      }
      TypeFactoryT *tf = Type2Factory().Lookup(typeToMake);
      if(tf == 0) {
        RavlSysLogf(SYSLOG_ERR,"Node '%s', Type '%s' unknown.",node.Name().chars(),typeToMake.chars());
        throw RavlN::ExceptionBadConfigC("Type not known. ");
        return false;
      }
      XMLFactoryContextC createNode(*this,node);
      rawHandle = (*tf)(createNode);
      if(!rawHandle.IsValid())
        RavlSysLogf(SYSLOG_WARNING,"Factory  create node of type '%s' \n",typeToMake.chars());
      if(m_checkConfig) {
        if(!node.CheckUsedAttributes()) {
          throw RavlN::ExceptionBadConfigC("Unexpected attributes in file. ");
        }
      }
    }
    
    // Can we auto start this ?
    RavlN::RCWrapC<XMLFactoryAutoStartC::RefT> handle;
    if(node.GetComponentInternal("",typeid(XMLFactoryAutoStartC::RefT),handle,true)) {
      // Auto start...
      if(handle.IsValid())
        handle.Data()->Init();
    }
    
    return true;
  }
  
  //! Create a component
  
  bool XMLFactoryC::CreateComponentInternal(const XMLFactoryContextC &node,
                                            const std::type_info &to,
                                            RavlN::RCWrapAbstractC &handle) 
  {
    RavlN::RCWrapAbstractC rawHandle;
    if(!CreateComponentInternal(node.INode(),rawHandle)) {
      RavlSysLogf(SYSLOG_DEBUG,"CreateComponentInternal(node,handle) failed. ");
      return false;
    }
    
    // ---- Convert to requested type ----
    
    RavlAssert(rawHandle.IsValid());
    
    const std::type_info &from = rawHandle.DataType();
    if(from == to) {
      handle = rawHandle;
      return true;
    }
    
    handle = RavlN::SystemTypeConverter().DoConversion(rawHandle.Abstract(),from,to);
    if(!handle.IsValid()) {
      //RavlAssert(0);
      RavlSysLogf(SYSLOG_ERR,"Don't know how to convert from type %s to %s ",RavlN::TypeName(from),RavlN::TypeName(to));
      return false;
    }
    RavlAssert(handle.IsValid());
    return true;
  }
  
  void XMLFactoryC::RegisterTypeFactory(const std::type_info &typeInfo,TypeFactoryT typeFactoryFunc) {
    StringC typeName = RavlN::TypeName(typeInfo);
    if(Type2Factory().Lookup(typeName) != 0) {
      // As this is called before main() is executed and the program has had a chance
      // to redirect log messages we'll just send them to stderr.
      //RavlSysLogf(SYSLOG_WARNING,"Duplicate registration of type %s in factory.",);
      std::cerr << "WARNING: Duplicate registration of type " << typeName << " in factory. \n";
    }
    Type2Factory()[RavlN::TypeName(typeInfo)] = typeFactoryFunc;
  }
  
  //: Register an alias for a type. This must be done after the type is registered.
  //: Note: This is NOT thread safe.

  bool XMLFactoryC::RegisterTypeAlias(const char *originalName,const char *newName) {
    XMLFactoryC::TypeFactoryT factoryFunc = 0;
    if(!Type2Factory().Lookup(originalName,factoryFunc)) {
      RavlSysLogf(SYSLOG_ERR,"Can't alias unknown type '%s' ",originalName);
      return false;
    }
    if(Type2Factory().Lookup(newName) != 0) {
      RavlSysLogf(SYSLOG_WARNING,"Can't set alias '%s' as its already defined ",newName);
      return false;
    }
    Type2Factory()[originalName] = factoryFunc;
    return true;
  }

  //! Follow path to node.
  
  bool XMLFactoryC::FollowPath(const StringC &path,XMLFactoryNodeC::RefT &node) {
    if(!m_iRoot.IsValid())
      return false;
    return m_iRoot->FollowPath(path,node);
  }
  

  //static RavlN::TypeNameC type1(typeid(XMLFactoryC),"RavlN::XMLFactoryC");  
  static RavlN::TypeNameC type2(typeid(RavlN::SmartPtrC<XMLFactoryC>),"RavlN::SmartPtrC<RavlN::XMLFactoryC>");  
  
  
}
