// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_OBSERVATIONEXPLICIT_HEADER
#define RAVLMATH_OBSERVATIONEXPLICIT_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"

#include "Ravl/Observation.hh"
#include "Ravl/MatrixRS.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Explicit observation body.
  
  class ObservationExplicitBodyC
    : public ObservationBodyC
  {
  public:
    ObservationExplicitBodyC();
    //: Default constructor.
    
    ObservationExplicitBodyC(const ObsVectorC &nobs_vec);
    //: Constructor.
    
    RealT Residual(const StateVectorC &state_vec);
    //: Compute the residual (negative log-likelihood) of the observation

    RealT NonRobustResidual(const StateVectorC &state_vec);
    //: Compute the non-robust residual (negative log-likelihood)

    bool IncrementLS(const StateVectorC &state_vec,
		     MatrixRSC &A,
		     VectorC &a);
    //: Increment the linear system

    UIntT GetNumConstraints() const;
    //: Returns the number of constraints imposed on the state
    
    virtual VectorC EvaluateFunctionH(const StateVectorC &state_vec);
    //: Evaluate the observation function h(x) given x

    virtual MatrixC EvaluateJacobianHx(const StateVectorC &state_vec);
    //: Evaluate the Jacobian dh/dx given x
  };

  //! userlevel=Normal
  //! autoLink=on
  //: Explicit observation class
  // This class represents a single observation on a state vector x, where
  // the observation vector z is related to x through the explicit form of
  // observation equation
  // <blockquote>
  //    z = h(x) + w
  // </blockquote>
  // where the noise vector w has covariance N. To see how such observations
  // can be used in optimisation see the
  // <a href="../../../LevenbergMarquardt/levmarq.html#measure_equation">mathematical description</a>.
  // This class implements the
  // Residual() and IncrementLS() methods which are virtual in the
  // ObservationC base class, by applying the
  // <a href="../../../LevenbergMarquardt/levmarq.html#chi2-def">error function</a>
  // and
  // <a href="../../../LevenbergMarquardt/levmarq.html#LM_update">state update</a>
  // formulae. The specific form of h(.)
  // should be provided by a sub-class, which implements at least the virtual
  // function EvaluateFunctionH(). If a formula for the Jacobian dh/dx of h(.)
  // is known then it can be implemented in the virtual function
  // EvaluateJacobianHx(); otherwise the Jacobian is computed numerically.
  class ObservationExplicitC
    : public ObservationC
  {
  public:
    ObservationExplicitC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ObservationExplicitC(const ObsVectorC &nobs_vec)
      : ObservationC(*new ObservationExplicitBodyC(nobs_vec))
    {}
    //: Constructor
    
    ObservationExplicitC(const ObservationC &obs)
      : ObservationC(obs)
    {
      if(dynamic_cast<ObservationExplicitBodyC *>(&ObservationC::Body()) == 0)
	Invalidate();
    }
    //: Base class constructor.
    
  public:
    ObservationExplicitC(ObservationExplicitBodyC &bod)
      : ObservationC(bod)
    {}
    //: Body constructor.
    
    ObservationExplicitBodyC &Body()
    { return static_cast<ObservationExplicitBodyC &>(ObservationC::Body()); }
    //: Access body.

    const ObservationExplicitBodyC &Body() const
    { return static_cast<const ObservationExplicitBodyC &>(ObservationC::Body()); }
    //: Access body.
    
  public:

    VectorC EvaluateFunctionH(const StateVectorC &state_vec)
    { return Body().EvaluateFunctionH(state_vec); }
    //: Evaluate the observation function h(x) given x

    MatrixC EvaluateJacobianHx(const StateVectorC &state_vec)
    { return Body().EvaluateJacobianHx(state_vec); }
    //: Evaluate the Jacobian dh/dx given x

  };
}  


#endif
