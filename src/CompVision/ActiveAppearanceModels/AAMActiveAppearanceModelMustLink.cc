// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelMustLink.cc"

namespace RavlImageN {

  extern void InitScaleRotationShapeModel();
  extern void ActiveAppearanceModelsIO();
  
  void MustLinkActiveAppearanceModelsIO() {
    ActiveAppearanceModelsIO();
    InitScaleRotationShapeModel();
  }
  

}
