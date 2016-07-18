/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Kentaro Wada */

#ifndef MOVEIT_MOVE_GROUP_EXECUTE_ACTION_CAPABILITY_
#define MOVEIT_MOVE_GROUP_EXECUTE_ACTION_CAPABILITY_

#include <moveit/move_group/move_group_capability.h>
#include <actionlib/server/simple_action_server.h>
#include <moveit_msgs/ExecuteKnownTrajectoryAction.h>

namespace move_group
{

class MoveGroupExecuteAction : public MoveGroupCapability
{
public:

  MoveGroupExecuteAction();

  virtual void initialize();

private:

  void executeMoveCallback(const moveit_msgs::ExecuteKnownTrajectoryGoalConstPtr& goal);
  void executeMoveCallback_Execute(const moveit_msgs::ExecuteKnownTrajectoryGoalConstPtr& goal, moveit_msgs::ExecuteKnownTrajectoryResult &action_res);
  void startMoveExecutionCallback();
  void preemptMoveCallback();
  void setExecuteState(MoveGroupState state);

  boost::scoped_ptr<actionlib::SimpleActionServer<moveit_msgs::ExecuteKnownTrajectoryAction> > execute_action_server_;
  moveit_msgs::ExecuteKnownTrajectoryFeedback execute_feedback_;

  MoveGroupState execute_state_;
};

}  // namespace move_group

#endif  // MOVEIT_MOVE_GROUP_EXECUTE_ACTION_CAPABILITY_
