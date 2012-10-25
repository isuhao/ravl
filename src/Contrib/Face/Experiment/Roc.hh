// This file is part of OmniSoft, Pattern recognition software 
// Copyright (C) 2003, Omniperception Ltd.
// file-header-ends-here
#ifndef RAVL_FACE_ROC_HH
#define RAVL_FACE_ROC_HH
////////////////////////////////////////////////////////////////////////////
//! author="Kieron J Messer"
//! date="11/10/2001"
//! lib=RavlFace
//! docentry="Ravl.Contrib.Face"
//! file="Ravl/Contrib/Face/Experiment/Roc.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/DList.hh"
#include "Ravl/String.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Tuple3.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/RealHistogram1d.hh"
#include "Ravl/Face/ScoreSession.hh"
#include "Ravl/Face/ResultsInfo.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/OS/Directory.hh"
#include "Ravl/Plot/GnuPlot.hh"

namespace RavlN {
  namespace FaceN {
    
    
    /////// RocBodyC ///////////////////////////////////////////
    //! userlevel=Develop
    //: A class for receiver operatign curves
    
    typedef Tuple2C<StringC, RealT> RankT;
    
    typedef Tuple2C<bool, RealT> ClaimT;
    
    class RocBodyC : public RCBodyC
    {
    public:
      //: Constructors, copies, assigment, and destructor
      //: -----------------------------------------------
      RocBodyC(bool highMatches);
      //: Construct empty

      RocBodyC(const DListC<RankT> & roc, UIntT nclients, UIntT nimpostors, bool highMatches);
      //: Construct "old style"

      RocBodyC(const ScoreSessionC & session, const StringC & metricType, bool highMatches);
      //: Construct from a score session

      RocBodyC(RealT min, RealT max, bool highMatches);
      //: Construct from a score session

      RocBodyC(istream &in);
      //: Stream constructor
      // This creates a new instance of the class from an input stream.

      RocBodyC(BinIStreamC &in);
      //: Stream constructor
      // This creates a new instance of the class from an input stream.

      bool Save(ostream &out) const;
      //: Save to ostream.

      bool Save(BinOStreamC &out) const;
      //: Save to ostream.

      void Sort();
      //: Sort scores

      void Insert(const RealT & score, bool client);
      //: Insert a score

      RealT EqualErrorRate() const;
      //: Select the threshold which gives an equal error rate

      RealT SmallestErrorRate() const;
      //: Select the threshold which would of given the smallest error rate

      RealT FAZero() const;
      //: Select the threshold which just gives the FA rate as zero

      RealT ErrorRateFA(RealT error) const;
      //: Select the threshold which just gives the FA rate of error

      RealT ErrorRateFR(RealT error) const;
      //: Select the threshold which just gives the FA rate of error

      ResultsInfoC Error(RealT threshold) const;
      //: Works out the error rates at a set threshold

      RealHistogram1dC Histogram(bool cl) const;
      //: Generate a histogram of the client and impostor distributions

      DListC<Tuple2C<RealT, RealT> > Graph(RealT maxFa, RealT maxFr) const;
      //: Generate a graph to plot

      SArray1dC<Tuple3C<RealT, RealT, RealT> > ThresholdInfo() const;
      //: Generate information about threshold

      RavlGUIN::GnuPlotC Plot(RealT maxFa, RealT maxFr) const;
      //: Generate a gnu plot

      RavlGUIN::GnuPlotC PlotHistogram(UIntT type) const;
      //: Generate a gnu plot of the score distributions
      //: 0 - client, 1 - impostor, 2 = both

      UIntT ClientClaims() const
      {
        return clients;
      }
      //: Number of true client claims

      UIntT ImpostorAttacks() const
      {
        return impostors;
      }
      //: Number of impostor attacks

      bool IsValid() const;
      //: Is ROC valid

      bool Report(const DirectoryC & outDir);
      //: Write some reports to the outDir

      friend ostream &operator<<(ostream &s, const RocBodyC &out);
      //: output stream operator

      friend istream &operator>>(istream &s, RocBodyC &in);
      //: input stream operator

      friend BinOStreamC &operator<<(BinOStreamC &s, const RocBodyC &out);
      //: output stream operator

      friend BinIStreamC &operator>>(BinIStreamC &s, RocBodyC &in);
      //: input stream operator

    protected:
      //: Put all your class members here
      DListC<ClaimT> claims;
      StringC metricType;
      bool highMatches;
      UIntT clients;
      UIntT impostors;
      bool sorted;
    };
    
    ostream &operator<<(ostream &s, const RocBodyC &out);
    //: output stream operator
    
    istream &operator>>(istream &s, RocBodyC &in);
    //: input stream operator

    BinOStreamC &operator<<(BinOStreamC &s, const RocBodyC &out);
    //: output stream operator
    
    BinIStreamC &operator>>(BinIStreamC &s, RocBodyC &in);
    //: input stream operator
    
    /////// RocC ///////////////////////////////////////////
    //! userlevel=Normal
    //: Receiver operator curves
    
    class RocC : public RCHandleC<RocBodyC>
    {
    public:
      //: Constructors, copies, assigment, and destructor
      //: -----------------------------------------------

      RocC()
      {
      }
      //: Default constructor
      // This creates an invalid handle.
      // You can remove this if you always want to create a full object.

      RocC(istream &in) :
          RCHandleC<RocBodyC>(*new RocBodyC(in))
      {
      }
      //: Stream constructor
      // This creates a new instance of the class from an input stream.

      RocC(BinIStreamC &in) :
          RCHandleC<RocBodyC>(*new RocBodyC(in))
      {
      }
      //: Stream constructor
      // This creates a new instance of the class from an input stream.

      RocC(bool highMatches) :
          RCHandleC<RocBodyC>(*new RocBodyC(highMatches))
      {
      }
      //: Constructor
      // This creates an invalid handle.
      // userArg should be changed to the real arguments.

      RocC(const DListC<RankT> & roc, UIntT nclients, UIntT nimpostors, bool highMatches = true) :
          RCHandleC<RocBodyC>(*new RocBodyC(roc, nclients, nimpostors, highMatches))
      {
      }
      //: Constructor
      // This creates an invalid handle.
      // userArg should be changed to the real arguments.

      RocC(const ScoreSessionC & session, const StringC & metricType, bool highMatches = true) :
          RCHandleC<RocBodyC>(*new RocBodyC(session, metricType, highMatches))
      {
      }
      //: Construct from a score session

      RocC(RealT min, RealT max, bool highMatches = true) :
          RCHandleC<RocBodyC>(*new RocBodyC(min, max, highMatches))
      {
      }
      //: Default constructor
      // This creates an invalid handle.
      // You can remove this if you always want to create a full object.

    protected:
      RocC(RocBodyC &bod) :
          RCHandleC<RocBodyC>(bod)
      {
      }
      //: Body Constructor
      // This creates a new handle to a body class, it can be usefull if
      // you wish to return handles to the class from within a body function.

      inline RocBodyC &Body()
      {
        return static_cast<RocBodyC &>(RCHandleC<RocBodyC>::Body());
      }
      //: Access body.
      // This isn't really needed, they're just to ensure
      // all derived classes work properly.

      inline const RocBodyC &Body() const
      {
        return static_cast<const RocBodyC &>(RCHandleC<RocBodyC>::Body());
      }
      //: Constant access body.
      // This isn't really needed, they're just to ensure
      // all derived classes work properly.

    public:
      bool Save(ostream &out) const
      {
        return Body().Save(out);
      }
      //: Save to ostream.

      bool Save(BinOStreamC &out) const
      {
        return Body().Save(out);
      }
      //: Save to stream

      void Sort()
      {
        return Body().Sort();
      }
      //: Sort roc

      void Insert(const RealT & score, bool client)
      {
        return Body().Insert(score, client);
      }
      //: Insert a new score

      inline RealT EqualErrorRate() const
      {
        return Body().EqualErrorRate();
      }
      //: Select the threshold which gives an equal error rate

      inline RealT SmallestErrorRate() const
      {
        return Body().SmallestErrorRate();
      }
      //: Select the threshold which gives the smallest error rate

      inline RealT FAZero() const
      {
        return Body().FAZero();
      }
      //: Select the threshold which gives a false acceptance rate of zero

      inline RealT ErrorRateFA(RealT error) const
      {
        return Body().ErrorRateFA(error);
      }
      //: Select the threshold which gives a false acceptance rate of error (0 to 1)

      inline RealT ErrorRateFR(RealT error) const
      {
        return Body().ErrorRateFR(error);
      }
      //: Select the threshold which gives a false acceptance rate of error (0 to 1)

      inline ResultsInfoC Error(RealT threshold) const
      {
        return Body().Error(threshold);
      }
      //: Works out the error rates at a set threshold

      RealHistogram1dC Histogram(bool cl) const
      {
        return Body().Histogram(cl);
      }
      //: Generate a histogram of the client and impostor distributions

      DListC<Tuple2C<RealT, RealT> > Graph(RealT maxFa = 1.0, RealT maxFr = 1.0) const
      {
        return Body().Graph(maxFa, maxFr);
      }
      //: Generate a graph to plot

      SArray1dC<Tuple3C<RealT, RealT, RealT> > ThresholdInfo() const
      {
        return Body().ThresholdInfo();
      }
      //: Generate information about threshold

      RavlGUIN::GnuPlotC Plot(RealT maxFa, RealT maxFr) const
      {
        return Body().Plot(maxFa, maxFr);
      }
      //: Generate a gnu plot

      RavlGUIN::GnuPlotC PlotHistogram(UIntT type) const
      {
        return Body().PlotHistogram(type);
      }
      //: Generate a gnu plot og histograms 0 = client, 1 = impostor, 2 = both in one

      UIntT ClientClaims() const
      {
        return Body().ClientClaims();
      }
      //: Number of true client claims

      UIntT ImpostorAttacks() const
      {
        return Body().ImpostorAttacks();
      }
      //: Number of impostor attacks

      bool IsValid() const
      {
        return Body().IsValid();
      }
      //: Is ROC valid

      bool Report(const DirectoryC & outDir) {
        return Body().Report(outDir);
      }
      //: Generate a report

      friend ostream &operator<<(ostream &s, const RocC &out);
      //: output stream operator

      friend istream &operator>>(istream &s, RocC &in);
      //: input stream operator

    };
    
    inline ostream &operator<<(ostream &s, const RocC &out)
    {
      out.Save(s);
      return s;
    }
    //: output stream operator
    
    inline istream &operator>>(istream &s, RocC &in)
    {
      in = RocC(s);
      return s;
    }
    //: input stream operator
    
    inline BinIStreamC &operator>>(BinIStreamC &strm, RocC &obj)
    {
      obj = RocC(strm);
      return strm;
    }
    //: Load from a binary stream.
    // Uses virtual constructor.

    inline BinOStreamC &operator<<(BinOStreamC &out, const RocC &obj)
    {
      obj.Save(out);
      return out;
    }
  //: Save to a stream.
  // Uses virtual constructor.
  
  }
}
#endif