// This file is part of OmniSoft, Pattern recognition software 
// Copyright (C) 2003, Omniperception Ltd.
// file-header-ends-here
// This file is part of OmniSoft, Pattern recognition software 
// Copyright (C) 2002, Omniperception Ltd.
//! rcsid="$Id$"
//! docentry="Ravl.Applications.Image.Face"
//! lib=RavlFace
//! file="Ravl/Contrib/Face/Xml/readFaceXml.cc"

#include "Ravl/Option.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Stream.hh"
#include "Ravl/IO.hh"
#include "Ravl/Face/FaceInfoDb.hh"
#include "Ravl/RLog.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

using namespace RavlN;
using namespace RavlN::FaceN;
using namespace RavlImageN;

//! userlevel=User
//: Read a face XML

int main(int argc, char **argv)
{
  OptionC opt(argc, argv);
  FilenameC db = opt.String("db", "", "input FaceInfoDb file");

  // RLog options
  bool verbose = opt.Boolean("v", false, "Verbose mode. ");
  StringC logFile = opt.String("l", "stderr", "Checkpoint log file. ");
  StringC logLevel = opt.String("ll", "debug", "Logging level (debug, info, warning, error)");

  //: check options selection
  opt.Compulsory("db");
  opt.Check();

  // Set up logging
  RavlN::RLogInit(argc, argv, logFile, verbose);
  RavlN::RLogSubscribeL(logLevel.chars());

  // Load in all the XML files into one master one!
  FaceInfoDbC faceInfoDb(db);
  rInfo("Loaded Face XML file '%s' with '%d' subjects and '%d' faces", db.data(), faceInfoDb.NoClients(), faceInfoDb.NoFaces());

  for (HashIterC<StringC, FaceInfoC> it(faceInfoDb); it; it++) {
    FilenameC filename(it.Data().OrigImage());
    if (!filename.Exists()) {
      rError("Image file '%s' does not exist!", it.Data().OrigImage().data());
      continue;
    }
    if (it.Data().FeatureSet().Position("LeftEyeCentre") == Point2dC()) {
      rError("Trouble with left-eye centre with face %s", it.Data().FaceId().data());
      continue;
    }
    if (it.Data().FeatureSet().Position("RightEyeCentre") == Point2dC()) {
      rError("Trouble with left-eye centre with face %s", it.Data().FaceId().data());
      continue;
    }
  }

  rInfo("All checked out OK!");
  return 0;
}

