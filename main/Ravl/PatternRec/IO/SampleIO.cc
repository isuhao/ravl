// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRecIO

#include "Ravl/Vector.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Types.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/SampleLabel.hh"

namespace RavlN {
  void InitRavlSampleIO()
  {}
  
  static TypeNameC type1(typeid(SampleC<UIntT>),"RavlN::SampleC<UIntT>");
  static TypeNameC type2(typeid(SampleC<VectorC>),"RavlN::SampleC<VectorC>");
  static TypeNameC type3(typeid(SampleVectorC),"RavlN::SampleVectorC");
  static TypeNameC type4(typeid(SampleLabelC),"RavlN::SampleLabelC");

  FileFormatStreamC<SampleC<UIntT> > FileFormatStream_SampelC_UIntT;
  FileFormatStreamC<SampleC<VectorC> > FileFormatStream_SampelC_VectorC;
  
  FileFormatBinStreamC<SampleC<UIntT> > FileFormatBinStream_SampelC_UIntT;
  FileFormatBinStreamC<SampleC<VectorC> > FileFormatBinStream_SampelC_VectorC;
  
  SampleC<VectorC> SampleVectorClassToTemplate(const SampleVectorC &sv)
  { return const_cast<SampleC<VectorC> &>((SampleC<VectorC> &)sv); }

  SampleVectorC SampleVectorTemplateToClass(const SampleC<VectorC> &sv)
  { return SampleVectorC(sv); }
  
  SampleC<UIntT> SampleLabelClassToTemplate(const SampleLabelC &sv)
  { return const_cast<SampleC<UIntT> &>((SampleC<UIntT> &)sv); }

  SampleLabelC SampleLabelTemplateToClass(const SampleC<UIntT> &sv)
  { return SampleLabelC(sv); }
  
  DP_REGISTER_CONVERSION_NAMED(SampleVectorClassToTemplate,1,"RavlN::SampleVectorClassToTemplate(const SampleVectorC &)");
  DP_REGISTER_CONVERSION_NAMED(SampleVectorTemplateToClass,1,"RavlN::SampleVectorTemplateToClass(const SampleC<VectorC> &)");
  
  DP_REGISTER_CONVERSION_NAMED(SampleLabelClassToTemplate,1,"RavlN::SampleLabelClassToTemplate(const SampleLabelC &)");
  DP_REGISTER_CONVERSION_NAMED(SampleLabelTemplateToClass,1,"RavlN::SampleLabelTemplateToClass(const SampleC<UIntT> &)");
  
}
