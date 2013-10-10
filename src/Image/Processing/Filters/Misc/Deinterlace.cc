#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/DeinterlaceStream.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/Image/Font.hh"

using namespace RavlN;
using namespace RavlImageN;

int main (int argc, char* argv[])
{
  if (argc < 3) exit(-1);
  DPIPortC<ImageC<ByteRGBValueC> > in;
  if(!OpenISequence(in, argv[1])) exit(-2);
  DPOPortC<ImageC<ByteRGBValueC> > out;
  if(!OpenOSequence(out, argv[2])) exit (-3);

  DeinterlaceStreamC<ByteRGBValueC> di(in);
  ImageC<ByteRGBValueC> im;
  int i(0);
  while(di.Get(im)) {
    //Sleep(1);
    char x;
    DrawText<ByteRGBValueC>(im, ByteRGBValueC(255,255,255), Index2dC(15,15), StringC(i++));
    out.Put(im);
    cin >> x;
  }
}

