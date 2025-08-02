#include <behaviortree_ros2/tree_execution_server.hpp>
#include <behaviortree_cpp/xml_parsing.h>
#include <rclcpp/logger.hpp>
class MyActionServer : public BT::TreeExecutionServer
{
public:
MyActionServer(const rclcpp::NodeOptions& options) : TreeExecutionServer(options) {}



  void onTreeCreated(BT::Tree& tree) {
    (void) tree;
    // std::string xml_models = BT::writeTreeNodesModelXML(factory());

    // saves to a file
    // RCLCPP_WARN_STREAM(node()->get_logger(), xml_models);
  }

};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  auto action_server = std::make_shared<MyActionServer>(options);

  // TODO: This workaround is for a bug in MultiThreadedExecutor where it can deadlock when spinning without a timeout.
  // Deadlock is caused when Publishers or Subscribers are dynamically removed as the node is spinning.
  rclcpp::executors::MultiThreadedExecutor exec(rclcpp::ExecutorOptions(), 0, false,
                                                std::chrono::milliseconds(250));
  exec.add_node(action_server->node());
  exec.spin();
  exec.remove_node(action_server->node());

  rclcpp::shutdown();
}