// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! docentry="Algorithms.Data Processing.IO" 
//! lib=RavlIO
//! author="Charles Galambos"
//! date="13/08/98"
//! rcsid="$Id$"
//! file="Ravl/Core/IO/FileFormDesc.cc"

#include "Ravl/DP/FileFormDesc.hh"
#include "Ravl/CDLIter.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/DP/SPort.hh"

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  //: Create an input from the descriptor.
  
  DPIPortBaseC FileFormatDescC::CreateInput(StringC filename) const {
    RavlAssert(isInput);
    DPIPortBaseC inp = form.CreateInput(filename,SourceType());
    if(!inp.IsValid()) {
      cerr << "Internal error: Failed to open input file '" << filename << "' in format '" << form.Name() << "' \n" ;
      RavlAssert(0);
      return DPIPortBaseC();
    }
    return BuildInputConv(inp);
  }
  
  
  //: Create an ouput from the descriptor.
  
  DPOPortBaseC FileFormatDescC::CreateOutput(StringC filename) const {
    RavlAssert(!isInput);
    DPOPortBaseC outp = form.CreateOutput(filename,SourceType());
    if(!outp.IsValid()) {
      cerr << "Internal error: Failed to open output file '" << filename << "' in format '" << form.Name() << "' \n" ;
      RavlAssert(0);
      return DPOPortBaseC();
    }
    return BuildOutputConv(outp);
  }
  

  //: Create an input from the descriptor.
  
  DPIPortBaseC FileFormatDescC::CreateInput(StringC filename,DPSeekCtrlC &sc) const {
    RavlAssert(isInput);
    DPIPortBaseC inp = form.CreateInput(filename,SourceType());
    sc = DPSeekCtrlC(inp); // This may or maynot work...
    if(!inp.IsValid()) {
      cerr << "Internal error: Failed to open input file '" << filename << "' in format '" << form.Name() << "' \n" ;
      RavlAssert(0);
      return DPIPortBaseC();
    }
    return BuildInputConv(inp);    
  }
  
  //: Create an input from the descriptor.
  
  DPOPortBaseC FileFormatDescC::CreateOutput(StringC filename,DPSeekCtrlC &sc) const {
    RavlAssert(!isInput);
    DPOPortBaseC outp = form.CreateOutput(filename,SourceType());
    sc = DPSeekCtrlC(outp); // This may or maynot work...
    if(!outp.IsValid()) {
      cerr << "Internal error: Failed to open output file '" << filename << "' in format '" << form.Name() << "' \n" ;
      RavlAssert(0);
      return DPOPortBaseC();
    }
    return BuildOutputConv(outp);    
  }
  

  //: Build input conversion.
  
  DPIPortBaseC FileFormatDescC::BuildInputConv(const DPIPortBaseC &ip) const {
    DPIPortBaseC inp(ip);
    for(ConstDLIterC<DPConverterBaseC> it(conv);it.IsElm();it.Next()) {
      inp = it.Data().CreateIStream(inp);
      ONDEBUG(cerr << "inp:" << TypeName(inp.InputType()) << endl);
      RavlAssert(inp.IsValid());
    }  
    return inp;
  }
  
  //: Build output conversion.

  DPOPortBaseC FileFormatDescC::BuildOutputConv(const DPOPortBaseC &op) const {
    DPOPortBaseC outp(op);
    ONDEBUG(cerr << "Start from:" << TypeName(outp.OutputType()) << " Steps:" << conv.Size() << endl);
    ConstDLIterC<DPConverterBaseC> it(conv);
    for(it.Last();it.IsElm();it.Prev()) {
      ONDEBUG(cerr << "Conv: " << it.Data().ProcType().name() << endl);
      outp = it.Data().CreateOStream(outp);
      ONDEBUG(cerr << "to:" << TypeName(outp.OutputType()) << endl);
      RavlAssert(outp.IsValid());
    }
    return outp;
  }
  
  //: Dump conversion to out.
  
  void FileFormatDescC::DumpConv(ostream &out) const {
    if(conv.IsEmpty())
      return ;
    ConstDLIterC<DPConverterBaseC> it(conv);
    if(isInput) {
      StringC arrow = " -> ";
      out << TypeName(it.Data().ArgType(0));
      for(;it.IsElm();it.Next()) 
	out << arrow << TypeName(it.Data().Output());
      out << "\n";
    } else {
      StringC arrow = " <- ";
      it.Last();
      out << TypeName(it.Data().Output());
      for(;it.IsElm();it.Prev())
	out << arrow << TypeName(it.Data().ArgType(0));
      out << "\n";
    }
  }
}