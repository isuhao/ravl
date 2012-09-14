/*
 * Plot.cc
 *
 *  Created on: 10 Aug 2012
 *      Author: kieron
 */

#include "Ravl/Plot/Plot2d.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  
  /*
   * Construct
   */
  Plot2dC::Plot2dC(const StringC & title) :
      m_title(title)
  {
  }

  /*
   * Plot points on graph
   */
  bool Plot2dC::Plot(const SArray1dC<Point2dC> & data, const StringC & dataName)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Plot as separate plots on same graph
   */
  bool Plot2dC::Plot(const RCHashC<StringC, CollectionC<Point2dC> > & data)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Plot a straight line
   */
  bool Plot2dC::Plot(const LineABC2dC & line)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Plot a function
   */
  bool Plot2dC::Plot(const StringC & function)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Make a scatter plot of a data set
   */
  bool Plot2dC::Plot(const DataSetVectorLabelC & dataSet, UIntT feature1, UIntT feature2, UIntT samplesPerClass)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Plot vector samples
   */
  bool Plot2dC::Plot(const SampleVectorC & sample, UIntT feature1, UIntT feature2, UIntT samples)
  {
    DataSetVectorLabelC dset(sample.Size());
    dset.Append(sample, 0);
    return Plot(dset, feature1, feature2, samples);
  }

  /*
   * Plot right wrong decisions made by a trained classifier
   */
  bool Plot2dC::Plot(const ClassifierC & classifier, const DataSetVectorLabelC & dataSet, UIntT feature1, UIntT feature2)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Plot a function between min and max
   */
  bool Plot2dC::Plot(const FunctionC & function, const VectorC & min, const VectorC & max)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Set the X label
   */
  bool Plot2dC::SetXLabel(const StringC & xlabel)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Set the Y label
   */
  bool Plot2dC::SetYLabel(const StringC & ylabel)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   *  Set axis range of a plot
   */

  bool Plot2dC::SetXRange(const RealRangeC & xrange)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   *  Set axis range of a plot
   */

  bool Plot2dC::SetYRange(const RealRangeC & yrange)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   *  Set axis range of a plot
   */

  bool Plot2dC::SetAxisRange(const RealRangeC & xrange, const RealRangeC & yrange)
  {
    return SetXRange(xrange) && SetYRange(yrange);
  }
  //: Set axis range

  /*
   * Set the line style
   */

  bool Plot2dC::SetLineStyle(const StringC & lineStyle)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Set the output.  Either X11 or a filename.
   */

  bool Plot2dC::SetOutput(const StringC & output, const IndexRange2dC & rec)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }

  /*
   * Send the plotting device a generic command
   */

  bool Plot2dC::Command(const StringC & command)
  {
    //RavlAssertMsg(0, "Abstract method called!");
    RavlError("Abstract method called");
    return false;
  }
//: General method to send a command to the ploting library

  //! userlevel=Develop
  Plot2dC::RefT CreatePlot2d_default(const StringC & name)
  {
    RavlError("Abstract Create Plot called!");
    return new Plot2dC(name);
  }

  Plot2dC::RefT (*g_createPlot2d)(const StringC & title) = &CreatePlot2d_default;


} /* namespace RavlN */
