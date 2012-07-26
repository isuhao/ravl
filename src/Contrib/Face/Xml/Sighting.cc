// This file is part of OmniSoft, Pattern recognition software 
// Copyright (C) 2003, Omniperception Ltd.
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlFace
//! file="Ravl.Contrib.Face/Sighting.cc"

#include "Ravl/Face/Sighting.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/DP/FileFormatXMLStream.hh"

namespace RavlN {
  namespace FaceN {

    using namespace RavlN;

    SightingBodyC::SightingBodyC(const StringC & id) :
        actualId(id)
    {
    }

    SightingBodyC::SightingBodyC(XMLIStreamC& xml)
    {
      StringC strType("");
      // Read tags until we get a Sighting
      while (xml && xml.ReadTag(strType) != XMLBeginTag && strType != "Sighting")
        ;
      if (!xml)
        return;

      xml.GetAttrib("id", actualId);

      //: The next tag is the actual id
      while (xml && xml.PeekTag(strType) != XMLEndTag) {
        if (strType == "faceid") {
          StringC fc;
          xml.ReadTag(strType);
          xml >> fc;
          fc = fc.TopAndTail();
          AddFaceId(fc);
          xml.ReadTag(strType);
        } else {
          xml.ReadTag(strType);
          xml.ReadTag(strType);
        }
      }
      //: read the end tag of Sighting
      xml.ReadTag(strType);
      return;
    }

    bool SightingBodyC::AddFaceId(const StringC & faceid)
    {
      list.InsLast(faceid);
      return true;
    }

    XMLOStreamC &SightingBodyC::SaveXML(XMLOStreamC &xml) const
    {

      // Set auto-indent mode
      xml.AutoIndent();

      // Start tag
      xml.StartTag("Sighting");

      xml.SetAttrib("id", actualId);

      // Write child tags
      xml.StartContents();

      //: All the paths to the images
      for (DLIterC < StringC > it(list); it; it++) {
        xml.StartTag("faceid");
        xml << *it;
        xml.EndTag();
      }

      //: End Tag
      xml.EndTag();

      return xml;
    }

    XMLIStreamC &operator>>(XMLIStreamC &xml, SightingC &data)
    {
      data = SightingC(xml);
      return xml;
    }

    XMLOStreamC &operator<<(XMLOStreamC &xml, const SightingC& data)
    {
      return data.SaveXML(xml);
    }

    void InitSightingFormat()
    {
    }

    static TypeNameC typeNameSightingC(typeid(SightingC), "OmniSoft::SightingC");

    FileFormatXMLStreamC<SightingC> FileFormatXMLStream_SightingC;
  }
}

