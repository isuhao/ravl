// This file is part of CxxDoc, The RAVL C++ Documentation tool 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU General 
// Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
///////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Lee Gregory"
//! docentry="Ravl.Source Tools"
//! lib=RavlSourceTools

#include "Ravl/Option.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Text/TextFile.hh"
#include "Ravl/Text/TextCursor.hh"
#include "Ravl/SourceTools/DefsFile.hh"
#include "Ravl/SourceTools/SourceCodeManager.hh"
#include "Ravl/SourceTools/SourceFile.hh"
#include "Ravl/CallMethods.hh"
//#include "Ravl/Calls.hh"
#include "Ravl/OS/Filename.hh"
#include   "Ravl/Text/ConfigFile.hh"

using namespace RavlN;


//: Simple class to handle moving html and eht doc entries.
//: ------------------------------------------------------------------------------
class DocRepC 
{
public:

  
  inline DocRepC(const StringC &o,const StringC &n,bool v,bool dr)
    : original(o), newun(n), verbose(v), dryRun(dr) {}
  //: Constructor.

  bool Process(StringC &dir,DefsMkFileC &where);
  //: Process a directory.
  
  inline bool IsVerbose() const { return verbose; }
  //: In verbose mode ?
  
protected:

  StringC original; 		// pattern to replace
  StringC newun;		// pattern to replace with
  bool verbose;			// verbose ?
  bool dryRun;			// dry run ?
};


//: ------------------------------------------------------------------------------
// MAIN
//: ------------------------------------------------------------------------------
int renameDocs(int nargs,char **argv) {
 StringC usage ;
usage += "\n\n This program is designed to move html and eht files in the qmake system. " ; 
usage += "\nAs well as moving the files, the references to these files are updated in the corresponding defs.mk \n" ;
  OptionC option(nargs,argv,true);
  FilenameC fn = option.CharArr("i",".","Input filename. ");
  //bool rec = option.Boolean("r",true,"recurse into subdirectories. ");
  bool all = option.Boolean("a",false,"Go into inactive directories as well. ");
  bool verb = option.Boolean("v",false,"Verbose mode.");
  bool dryRun = option.Boolean("d",false,"Do a dry run.");
  StringC oValue = option.CharArr("s","","Search pattern");
  StringC nValue = option.CharArr("r","","Replace with");
  option.Comment(usage) ; 
  option.Compulsory("s") ; 
  option.Compulsory("r") ;   
  option.Check();
  
  SourceCodeManagerC chkit(fn);
  //TriggerC trig = Trigger( &ProccessDir, StringC(""), DefsMkFileC("")  ) ; 
DocRepC rep ( oValue, nValue, verb, dryRun ) ; 
TriggerC trig = Trigger ( rep, &DocRepC::Process, StringC(""), DefsMkFileC("") ) ;
 chkit.ForAllDirs(trig,all); 
  return 0;
}



//: ------------------------------------------------------------------------------
//: Process a directory.
//: ------------------------------------------------------------------------------
bool DocRepC::Process(StringC &dir,DefsMkFileC &where) 
{
  if(IsVerbose())
    cerr << "\nProcessing:\t" << dir ;

// load this defs file as text so we can edit it
TextFileC text ; 
if ( ! text.Load( where.Name() ) ) 
{ cerr << "\nCould not load defs file " ;  } 

// get a list of doc files that need processing
  StringListC hdrs ; 
	hdrs += (where.Value("EHT"));
	hdrs += (where.Value("HTML") ) ; 

cerr << "\n abou to process files " << hdrs ; 

// check length of filename is reasonable  
  for(DLIterC<StringC> it(hdrs);it.IsElm();it.Next()) {
    if(it.Data().length() <= 3) {
      cerr << "WARNING: Short file name detected :'" << it.Data() << "'\n";
      continue; // Far too short !
    }

//: get absolute path to filename 
    FilenameC oldFile(dir + '/' + it.Data());

//: check file exists. 
    if(!oldFile.Exists()) {
      cerr <<"\nWARNING: No access to file:" << oldFile << "\n";
      continue; // No access to file.
    }

//: Apply substition to get new file name. 
FilenameC newFile (oldFile.Copy() ) ; 
newFile.gsub(original, newun) ; 

cerr << "\n\nDEBUG \t" << oldFile ; 
cerr << "\nDEBUG \t" << newFile ; 
//: do we have a new name for this doc file, if so, rename it and update the defs.mk
if ( oldFile != newFile ) {
	cerr  << "\nUpdating:\t" << oldFile.NameComponent() << " -> " << newFile.NameComponent() ; 
	//: rename file.
	if ( ! dryRun ) {
		if ( ! oldFile.CopyTo(newFile)  ) { cerr << "\nWARNING: Could not copy file: " << oldFile << " to " << newFile ; }
		else if ( ! oldFile.Remove() ) { cerr << "\nWARNING: Could not remove old file: " << oldFile ; }
	} 
	else cerr << "\t(dryRun)" ;
	//: update defs.mk 
	text.GlobalSubst( oldFile.NameComponent(), newFile.NameComponent() ) ; 
	}
} // end of loop for all html and eht files. 

//: Update the defs file, if we have modified it.
    if(text.IsModified()) {
	cerr << "\nUpdating:\t" << where.Name() ; 
      if(!dryRun) {
	if(!text.Save())
	  cerr << "\nWARNING Failed to save file '" << where.Name()<< "' \n";  
	} else cerr << "\t(dryRun ) " ; }

  return true;
}



RAVL_ENTRY_POINT(renameDocs);
