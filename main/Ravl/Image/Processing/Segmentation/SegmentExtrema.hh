// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SEGMENTEXTREMA_HEADER
#define RAVLIMAGE_SEGMENTEXTREMA_HEADER 1
//! rcsid="$Id$"
//! lib=RavlImageProc
//! author="Charles Galambos, based on code by Jiri Matas."
//! docentry="Ravl.Images.Segmentation"
//! userlevel=Normal
//! file="Ravl/Image/Processing/Segmentation/SegmentExtrema.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/FloodRegion.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/SArray1dIter.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  //! userlevel=Develop
  //: Extrema threshold information.
  
  class ExtremaThresholdC {
  public:
    int thresh;
    int pos;
    int margin;
  };
  
  //! userlevel=Develop
  //: Extremal region
  
  class ExtremaRegionC {
  public:
    ExtremaRegionC()
      : hist(0),
	thresh(0)
    {}
    //: Constructor.
    
    ~ExtremaRegionC() {
      if(hist != 0)
	delete [] hist;
      if(thresh != 0)
	delete [] thresh;
    }
    //: Destructor.
    
    ExtremaRegionC *merge;
    IntT *hist; // Histogram of levels.
    IntT total;
    
    ExtremaThresholdC *thresh; // Thresholds
    IntT nThresh; // Number of thresholds.
    
    IntT maxValue;
    IntT minValue;
    Index2dC minat;
    ExtremaRegionC *closed;
  };
  
  //! userlevel=Develop
  //: Extremal pixel list.
  
  class ExtremaChainPixelC {
  public:
    ExtremaRegionC *region;
    ExtremaChainPixelC *next;
  };

  //! userlevel=Advanced
  //: Common parts to segmenting extrema.
  
  class SegmentExtremaBaseC {
  public:
    SegmentExtremaBaseC(IntT nMinSize,RealT nMinMargin,IntT nlimitMaxValue = 255)
      : labelAlloc(1),
	minSize(nMinSize),
	minMargin(nMinMargin),
	limitMaxValue(nlimitMaxValue)
    {}
    //: Constructor.
    
    ~SegmentExtremaBaseC();
    //: Destructor.
    
    
    void SetupImage(const IndexRange2dC &rect);
    //: Setup structures for a given image size.
    
    bool SortPixels(const ImageC<ByteT> &img);
    //: Build a list from a byte image.
    
    void GenerateRegions();
    //: Generate regions.
    
    UIntT Levels() const 
    { return levels.Size(); }
    //: Get number of levels being considered.
    
    Array1dC<ExtremaChainPixelC *> &LevelSets()
    { return levels; }
    //: Access level set array.
    
  protected:
    void ReallocRegionMap(IntT size);
    //: Reallocate the current region set, free any memory used.
    
    static ExtremaRegionC *FindLabel(ExtremaChainPixelC *lab);
    //: Find matching label.
    
    int ConnectedLabels(ExtremaChainPixelC *pix,ExtremaRegionC **labelArray);
    //: Find the labels around the pixel 'pix'
    // put the results into 'labelArray' which must be at least 4 labels long.
    // The number of labels found is returned.
    
    void AddRegion(ExtremaChainPixelC *pix,IntT level);
    //: Add a new region.
    
    void AddPixel(ExtremaChainPixelC *pix,IntT level,ExtremaRegionC *reg);
    //: Add pixel to region.
    
    void MergeRegions(ExtremaChainPixelC *pix,IntT level,ExtremaRegionC **labels,IntT n);
    //: Add pixel to region.

    void Thresholds();
    //: Generate thresholds
    
    void Thresholds2();
    //: Generate thresholds
    
    void PeakDetection(Array1dC<RealT> &real);
    //: Peak detection.
    
    ImageC<ExtremaChainPixelC> pixs;
    Array1dC<ExtremaChainPixelC *> levels;
    SArray1dC<ExtremaRegionC> regionMap;
    UIntT stride; // Image stride.
    UIntT labelAlloc;
    IndexRangeC valueRange; // Range of pixel values.
    ExtremaChainPixelC *origin;
    
    // Paramiters.
    
    IntT minSize;
    IntT maxSize;
    RealT minMargin;
    IntT limitMaxValue; // Maximum image value that will be encountered.
    
  };
  
  
  //! userlevel=Normal
  //: Extremal region segmentation.
  // Refrence: J Matas. BMVC 2002

  template<class PixelT>
  class SegmentExtremaC 
    : public SegmentExtremaBaseC
  {
  public:
    SegmentExtremaC(IntT minRegionSize,RealT minMargin = 10,IntT nlimitMaxPixelValue = 255)
      : SegmentExtremaBaseC(minRegionSize,minMargin,nlimitMaxPixelValue)
    {}
    //: Constructor.
    //!param:minRegionSize - Minimum region size to detect.
    //!param:minMargin - Threshold for region stability.
    
    DListC<BoundaryC> Apply(const ImageC<PixelT> &img) {
      SortPixels(img);
      GenerateRegions();
      Thresholds();
      return GrowRegionBoundary(img);
    }
    //: Apply operation to img.
    // Note: The boundaries generated by this function are not ordered. If you require ordered
    // boundries you can use its 'Order()' method to sort them.
    
    DListC<ImageC<IntT> > ApplyMask(const ImageC<PixelT> &img) {
      SortPixels(img);
      GenerateRegions();
      Thresholds();
      return GrowRegionMask(img);
    }
    //: Apply operation to img.
    // Generates labeled images.
    
  protected:
    bool SortPixels(const ImageC<PixelT> &nimg);
    //: Do initial sorting of pixels.
    
    DListC<BoundaryC> GrowRegionBoundary(const ImageC<PixelT> &img);
    //: Grow regions.
    
    DListC<BoundaryC> GrowRegionBoundary(ExtremaRegionC &region,FloodRegionC<PixelT> &fr);
    //: Grow regions associated with a extrema.
    
    DListC<ImageC<IntT> > GrowRegionMask(const ImageC<PixelT> &img);
    //: Grow regions.
    
    DListC<ImageC<IntT> > GrowRegionMask(ExtremaRegionC &region,FloodRegionC<PixelT> &fr);
    //: Grow regions associated with a extrema.
    
  };

  
  template<class PixelT>
  bool SegmentExtremaC<PixelT>::SortPixels(const ImageC<PixelT> &img) {
    
    SetupImage(img.Frame());
    
    // Find range of values in image.
    {
      Array2dIterC<PixelT> it(img);
      PixelT lmin = *it;
      PixelT lmax = *it;
      for(;it;it++) {
	if(*it < lmin)
	  lmin = *it;
	if(*it > lmax)
	  lmax = *it;
      }
      valueRange.Min() = (IntT) lmin;
      valueRange.Max() = (IntT) lmax;
    }

    if(valueRange.Max() >= limitMaxValue)
      valueRange.Max() = limitMaxValue-1;
      
    // Check level list allocation.
    
    if(!levels.Range().Contains(valueRange))
      levels = Array1dC<ExtremaChainPixelC *>(valueRange.Expand(2));
    levels.Fill(0);
    
    // Sort pixels into appropriate lists.
    
    for(Array2dIter2C<PixelT,ExtremaChainPixelC> it(img,pixs,img.Frame());it;it++) {
      PixelT val = it.Data1();
      it.Data2().region = 0;
      if(val >= limitMaxValue) {
        it.Data2().next = 0;
	continue;
      }
      ExtremaChainPixelC * &tmp = levels[val]; 
      it.Data2().next = tmp;
      tmp = &it.Data2();
    }
    
    return true;
  }
  
  template<class PixelT>
  DListC<BoundaryC> SegmentExtremaC<PixelT>::GrowRegionBoundary(const ImageC<PixelT> &img) {
    //cerr << "SegmentExtremaBaseC::GrowRegions() \n";
    FloodRegionC<PixelT> flood(img);
    
    DListC<BoundaryC> bounds;
    if(labelAlloc == 0)
      return bounds;
    for(SArray1dIterC<ExtremaRegionC> it(regionMap,labelAlloc-1);it;it++) {
      if(it->nThresh > 0)
	bounds += GrowRegionBoundary(*it,flood);
      if(it->thresh != 0) {
	delete [] it->thresh;
	it->thresh = 0;
      }
    }
    
    return bounds;
  }
  
  template<class PixelT>
  DListC<BoundaryC> SegmentExtremaC<PixelT>::GrowRegionBoundary(ExtremaRegionC &region,FloodRegionC<PixelT> &flood) {
    DListC<BoundaryC> ret;
    //cerr << " Thresholds=" << region.nThresh << "\n";
    for(int i = 0;i < region.nThresh;i++) {
      BoundaryC boundary;
      if(flood.GrowRegion(region.minat,region.thresh[i].thresh,boundary))
	ret.InsLast(boundary);
    }
    return ret;
  }
  
  template<class PixelT>
  DListC<ImageC<IntT> > SegmentExtremaC<PixelT>::GrowRegionMask(const ImageC<PixelT> &img) {
    //cerr << "SegmentExtremaBaseC::GrowRegions() \n";
    FloodRegionC<PixelT> flood(img);
    
    DListC<ImageC<IntT> > masks;
    if(labelAlloc == 0)
      return masks;
    for(SArray1dIterC<ExtremaRegionC> it(regionMap,labelAlloc-1);it;it++) {
      if(it->nThresh > 0)
        masks += GrowRegionMask(*it,flood);
      if(it->thresh != 0) {
        delete [] it->thresh;
        it->thresh = 0;
      }
    }

    return masks;
  }
  
  template<class PixelT>
  DListC<ImageC<IntT> > SegmentExtremaC<PixelT>::GrowRegionMask(ExtremaRegionC &region,FloodRegionC<PixelT> &flood) {
    DListC<ImageC<IntT> > ret;
    //cerr << " Thresholds=" << region.nThresh << "\n";
    for(int i = 0;i < region.nThresh;i++) {
      ImageC<IntT> mask;
      if(flood.GrowRegion(region.minat,region.thresh[i].thresh,mask,1))
        ret.InsLast(mask);
    }
    return ret;
  }
  

}


#endif
