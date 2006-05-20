// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/System/StreamParse.cc"

#include "Ravl/Stream.hh"
#include "Ravl/StreamType.hh"
#include "Ravl/FixedQueue.hh"

#include <ctype.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  char IStreamC::GetChar() {
    char c;
    read(&c,1);
    if(is().gcount() != 1)
      throw ExceptionEndOfStreamC("End of stream found in 'XMLIStreamC::GetChar()' ");
    return c;
  }

  //: Skip white space charactors.
  // returns the first non-white space charactor found.
  
  char IStreamC::SkipWhiteSpace() {
    char c;
    for(c = GetChar();*this && isspace(c);c = GetChar()) 
      ;
    return c;
  }
  
  //: Skip through stream until endStr is found.
  
  bool IStreamC::SkipTo(const StringC &endStr) {
    char c;
    RavlAssert(endStr.length() != 0);
    if(endStr.length() == 1)
      return SkipTo(endStr.firstchar());
    FixedQueueC<char> fq(endStr.Size());
    // Fill queue, can't match until the queue is filled.
    while(fq.Size() != endStr.Size()) {
      read(&c,1);
      if(is().gcount() != 1)
	break;
      fq.ForceInsLast(c);
    }
    FixedQueueIterC<char> it;
    const char *at;
    while(1) {
      at = &endStr[0];
      for(it = fq;it;it++,at++) {
	//ONDEBUG(cerr << "Str cmp '" << *it << "' == '" << *at << "'\n");
	if(*it != *at)
	  break;
      }
      if(!it.IsElm())
	return true; // Found!
      read(&c,1);
      if(is().gcount() != 1)
	break;
      //ONDEBUG(cerr << "Nope! got '" << c <<"'\n");
      fq.ForceInsLast(c);
    }
    return false;
  }

  //: Skip through stream until 'let' is found.
  
  bool IStreamC::SkipTo(char let) {
    char c;
    while(*this) {
      read(&c,1);
      if(is().gcount() != 1)
	break;
      if(let == c)
	return true;
    }
    return false;
  }

  //: Return all charactors before let.
  
  StringC IStreamC::ClipTo(char let) {
    StringC ret;
    char c;
    while(*this) {
      read(&c,1);
      if(is().gcount() != 1)
	break;
      if(let == c)
	return ret;
      ret += c;
    }
    return ret;
  }

  //: Return all charactors before 'endStr'.
  // this leaves the stream positioned at the
  // first charactor after the string. 

  StringC IStreamC::ClipTo(const StringC &endStr) {
    StringC ret;
    char c;
    RavlAssert(endStr.length() != 0);
    if(endStr.length() == 1)
      return SkipTo(endStr.firstchar());
    FixedQueueC<char> fq(endStr.Size());
    // Fill queue, can't match until the queue is filled.
    while(fq.Size() != endStr.Size()) {
      read(&c,1);
      if(is().gcount() != 1)
	break;
      fq.ForceInsLast(c);
      ret += c;
    }
    FixedQueueIterC<char> it;
    const char *at;
    while(1) {
      at = &endStr[0];
      for(it = fq;it;it++,at++) {
	//ONDEBUG(cerr << "Str cmp '" << *it << "' == '" << *at << "'\n");
	if(*it != *at)
	  break;
      }
      if(!it.IsElm()) {
	ret = ret.before(- ((int) endStr.length())); // Clip out 'endStr'.
	return ret; // Found!
      }
      read(&c,1);
      if(is().gcount() != 1)
	break;
      //ONDEBUG(cerr << "Nope! got '" << c <<"'\n");
      fq.ForceInsLast(c);
      ret += c;
    }
    return ret;    
  }

}