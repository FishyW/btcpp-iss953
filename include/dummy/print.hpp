#ifndef PRINT_PLUGIN_HPP_
#define PRINT_PLUGIN_HPP_

#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_ros2/ros_node_params.hpp"
#include "rclcpp/node.hpp"


class Print : public BT::SyncActionNode
{
public:
    Print(const std::string& name, const BT::NodeConfig& config)
    : BT::SyncActionNode(name, config)
  {}

  BT::NodeStatus tick() override;
  // It is mandatory to define this static method.
  static BT::PortsList providedPorts();
  
  private:
    std::shared_ptr<rclcpp::Node> node_;
};

#endif