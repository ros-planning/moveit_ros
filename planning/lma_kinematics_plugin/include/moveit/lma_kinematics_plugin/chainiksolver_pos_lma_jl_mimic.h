// Copyright  (C)  2007-2008  Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// Copyright  (C)  2008  Mikael Mayer
// Copyright  (C)  2008  Julia Jesse

// Version: 1.0
// Author: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// Maintainer: Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
// URL: http://www.orocos.org/kdl

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

// Modified to account for "mimic" joints, i.e. joints whose motion has a
// linear relationship to that of another joint.
// Copyright  (C)  2013  Sachin Chitta, Willow Garage

#ifndef KDLCHAINIKSOLVERPOS_LMA_JL_MIMIC_H
#define KDLCHAINIKSOLVERPOS_LMA_JL_MIMIC_H

#include "kdl/chainiksolverpos_lma.hpp" // Solver for the inverse position kinematics that uses Levenberg-Marquardt.
#include "kdl/chainfksolver.hpp"

#include <moveit/lma_kinematics_plugin/joint_mimic.h>

namespace KDL
{

/**
 * Implementation of a general inverse position kinematics
 * algorithm based on Levenberg-Marquardt method to calculate the
 * position transformation from Cartesian to joint space of a general
 * KDL::Chain. Takes joint limits into account.
 *
 * @ingroup KinematicFamily
 */
class ChainIkSolverPos_LMA_JL_Mimic : public ChainIkSolverPos
{
public:
  /**
   * Constructor of the solver, it needs the chain, a forward
   * position kinematics solver and an inverse velocity
   * kinematics solver for that chain.
   *
   * @param chain the chain to calculate the inverse position for
   * @param q_max the maximum joint positions
   * @param q_min the minimum joint positions
   * @param fksolver a forward position kinematics solver
   * @param iksolver an inverse velocity kinematics solver
   * @param maxiter the maximum Levenberg-Marquardt iterations,
   * default: 100
   * @param eps the precision for the position, used to end the
   * iterations, default: epsilon (defined in kdl.hpp)
   *
   * @return
   */
  ChainIkSolverPos_LMA_JL_Mimic(const Chain& chain,const JntArray& q_min, const JntArray& q_max, ChainFkSolverPos& fksolver,ChainIkSolverPos_LMA& iksolver,unsigned int maxiter=100,double eps=1e-6, bool position_ik = false);

  ~ChainIkSolverPos_LMA_JL_Mimic();

  virtual int CartToJnt(const JntArray& q_init, const Frame& p_in, JntArray& q_out);

  virtual int CartToJntAdvanced(const JntArray& q_init, const Frame& p_in, JntArray& q_out, bool lock_redundant_joints);

  bool setMimicJoints(const std::vector<lma_kinematics_plugin::JointMimic>& mimic_joints);

private:
  const Chain chain;
  JntArray q_min;//These are the limits for the "reduced" state consisting of only active DOFs
  JntArray q_min_mimic;//These are the limits for the full state
  JntArray q_max;//These are the limits for the "reduced" state consisting of only active DOFs
  JntArray q_max_mimic;//These are the limits for the full state
  JntArray q_temp;
  ChainFkSolverPos& fksolver;
  ChainIkSolverPos_LMA& iksolver;
  JntArray delta_q;
  Frame f;
  Twist delta_twist;
  unsigned int maxiter;
  double eps;
  std::vector<lma_kinematics_plugin::JointMimic> mimic_joints;
  void qToqMimic(const JntArray& q, JntArray& q_result);  // Convert from the "reduced" state (only active DOFs) to the "full" state
  void qMimicToq(const JntArray& q, JntArray& q_result);  // Convert from the "full" state to the "reduced" state
  void harmonize(JntArray& q_out);                        // Puts the angles within [-2PI, 2PI]
  bool obeysLimits(const KDL::JntArray &q_out);           // Checks that a set of joint angles obey the urdf limits
  bool position_ik;

};

}

#endif
