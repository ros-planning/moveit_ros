/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2013, Willow Garage, Inc.
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

/* Author: Sachin Chitta */

#ifndef MOVEIT_SEMANTIC_WORLD_
#define MOVEIT_SEMANTIC_WORLD_

#include <ros/ros.h>
#include <moveit/transforms/transforms.h>
#include <object_recognition_msgs/TableArray.h>
#include <moveit_msgs/CollisionObject.h>
#include <geometric_shapes/shapes.h>

#include <boost/thread/mutex.hpp>

namespace moveit
{

namespace semantic_world
{

/**
 * @brief A (simple) semantic world representation for pick and place and other tasks.
 */
class SemanticWorld
{
public:

  /**
   * @brief A (simple) semantic world representation for pick and place and other tasks.
   * Currently this is used only to represent tables. 
   */
  SemanticWorld(const robot_state::Transforms &tf);  

  /**
   * @brief Get all the tables within a region of interest
   */
  object_recognition_msgs::TableArray getTablesInROI(double minx, double miny, double minz, 
                                                     double maxx, double maxy, double maxz);

  /**
   * @brief Get all the tables within a region of interest
   */
  std::vector<std::string> getTableNamesInROI(double minx, double miny, double minz, 
                                              double maxx, double maxy, double maxz);

  /**
   * @brief Generate possible place poses on the table for a given object. This chooses appropriate 
   * values for min_distance_from_edge and for height_above_table based on the object properties. 
   * The assumption is that the object is represented by a mesh. 
   */
  std::vector<geometry_msgs::PoseStamped> generatePlacePoses(const std::string &table_name,
                                                             const shapes::ShapeConstPtr& object_shape,
                                                             const geometry_msgs::Quaternion &object_orientation,
                                                             double resolution, 
                                                             double delta_height = 0.01,
                                                             unsigned int num_heights = 2);

  /**
   * @brief Generate possible place poses on the table for a given object. This chooses appropriate 
   * values for min_distance_from_edge and for height_above_table based on the object properties. 
   * The assumption is that the object is represented by a mesh.
   */
  std::vector<geometry_msgs::PoseStamped> generatePlacePoses(const object_recognition_msgs::Table &table,
                                                             const shapes::ShapeConstPtr& object_shape,
                                                             const geometry_msgs::Quaternion &object_orientation,
                                                             double resolution, 
                                                             double delta_height = 0.01,
                                                             unsigned int num_heights = 2) const;
  /**
   * @brief Generate possible place poses on the table. This samples locations in a grid on the table at 
   * the given resolution (in meters) in both X and Y directions. The locations are sampled at the 
   * specified height above the table (in meters) and then at subsequent additional heights (num_heights 
   * times) incremented by delta_height. Locations are only accepted if they are at least min_distance_from_edge
   * meters from the edge of the table. 
   */
  std::vector<geometry_msgs::PoseStamped> generatePlacePoses(const object_recognition_msgs::Table &table,
                                                             double resolution, 
                                                             double height_above_table,
                                                             double delta_height = 0.01,
                                                             unsigned int num_heights = 2,
                                                             double min_distance_from_edge = 0.10) const;


  void clear();

  bool addTablesToCollisionWorld();
  
private:

  void tableCallback(const object_recognition_msgs::TableArrayPtr &msg);
  
  void visualizePlaceLocations(const std::vector<geometry_msgs::PoseStamped> &poses) const;

  void transformTableArray(object_recognition_msgs::TableArray &table_array);

  const robot_state::Transforms &tf_;

  ros::NodeHandle node_handle_;

  object_recognition_msgs::TableArray table_array_;

  std::vector<geometry_msgs::PoseStamped> place_poses_;

  boost::mutex table_lock_;

  ros::Subscriber table_subscriber_;

  ros::Publisher visualization_publisher_, collision_object_publisher_;  

  std::vector<std::pair<std::string, object_recognition_msgs::Table> > current_tables_in_collision_world_;
  
  bool table_dirty_;

  std::string reference_frame_;  

  double place_resolution_;

};

}

}

#endif
