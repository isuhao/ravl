#include "Ravl/Image/OpenCVConvert.hh"

namespace RavlImageN{

  using namespace RavlN;

  template <>
  bool RavlImage2IplImage(const ImageC<ByteT> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    dest = cvCreateImage(size, IPL_DEPTH_8U, 1);
    char *dr = dest->imageData;
    for (IntT r=0; r<size.height; ++r) {
      const ByteT *sc = src.Row(r);
      char *dc = dr;
      for (IntT c=0; c<size.width; ++c)  *dc++ = *sc++;
      dr += dest->widthStep;
    }
    return true;
  }
  
  template <>
  bool RavlImage2IplImage(const ImageC<ByteRGBValueC> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    dest = cvCreateImage(size, IPL_DEPTH_8U, 3);
    char *dr = dest->imageData;
    for (IntT r=0; r<size.height; ++r) {
      const ByteT *sc = (ByteT*)src.Row(r);
      char *dc = dr;
      for (IntT c=0; c<size.width; ++c) {
        *(dc++ +2) = *sc++; // dodgy code to do RGB->BGR I think
        *dc++      = *sc++;
        *(dc++ -2) = *sc++;
      }
      dr += dest->widthStep;
    }
    return true;
  }
  
  template <>
  bool RavlImage2IplImage(const ImageC<RealT> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    dest = cvCreateImage(size, IPL_DEPTH_64F, 1);
    double *dr = (double *)dest->imageData;
    for (IntT r=0; r<size.height; ++r) {
      const RealT *sc = src.Row(r);
      double *dc = dr;
      for (IntT c=0; c<size.width; ++c)  *dc++ = *sc++;
      dr += dest->widthStep;
    }
    return true;
  }
  
  template <>
  bool RavlImage2IplImage(const ImageC<RealRGBValueC> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    dest = cvCreateImage(size, IPL_DEPTH_64F, 3);
    double *dr = (double *)dest->imageData;
    for (IntT r=0; r<size.height; ++r) {
      const RealT *sc = (RealT*)src.Row(r);
      double *dc = dr;
      for (IntT c=0; c<size.width; ++c) {
      *(dc++ +2) = *sc++;
      *dc++      = *sc++;
      *(dc++ -2) = *sc++;
      }
    dr += dest->widthStep;
    }
    return true;
  }
  
}
