///////////////////////////////////////////////////
//! author="Charles Galambos"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinImgIO.hh"
#include "amma/BinIORGBValue.hh"
#include "amma/RGBImage.hh"

void InitImgIOU16RGB()
{}


namespace RavlN
{
  static TypeNameC type2(typeid(ImageC<RGBValueU16C>),"ImageC<RGBValueU16C>");

  static FileFormatStreamC<ImageC<RGBValueU16C> > FileFormatStream_ImageC_RGBValueU16C;
  static FileFormatBinStreamC<ImageC<RGBValueU16C> > FileFormatBinStream_ImageC_RGBValueU16C;
}


