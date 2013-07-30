/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2012, Willow Garage, Inc.
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
*   * Neither the name of Willow Garage, Inc. nor the names of its
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

/* Author: Ioan Sucan */

#ifndef MOVEIT_PLANNING_INTERFACE_PLANNING_SCENE_INTERFACE_
#define MOVEIT_PLANNING_INTERFACE_PLANNING_SCENE_INTERFACE_

#include <moveit/robot_state/robot_state.h>

namespace moveit
{

namespace planning_interface
{

class PlanningSceneInterface
{
public:
  PlanningSceneInterface();
  ~PlanningSceneInterface();

  /**
   * \defgroup move_group_interface_world_management Manage the world
   */
  /**@{*/

  /** \brief Get the names of all known objects in the world. If \e with_type is set to true, only return objects that have a known type. */
  std::vector<std::string> getKnownObjectNames(bool with_type = false);
  
  /** \brief Get the names of known objects in the world that are located within a bounding region (specified in the frame reported by getPlanningFrame()).
      If \e with_type is set to true, only return objects that have a known type. */
  std::vector<std::string> getKnownObjectNamesInROI(double minx, double miny, double minz, double maxx, double maxy, double maxz, bool with_type, std::vector<std::string> &types);

  /** \brief Get the names of known objects in the world that are located within a bounding region (specified in the frame reported by getPlanningFrame()).
      If \e with_type is set to true, only return objects that have a known type. */
  std::vector<std::string> getKnownObjectNamesInROI(double minx, double miny, double minz, double maxx, double maxy, double maxz, bool with_type = false)
  {
    std::vector<std::string> empty_vector_string;    
    return getKnownObjectNamesInROI(minx, miny, minz, maxx, maxy, maxz, with_type, empty_vector_string);
  };  

  /**@}*/

private:

  class PlanningSceneInterfaceImpl;
  PlanningSceneInterfaceImpl *impl_;

};

}

}

#endif
