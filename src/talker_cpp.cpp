#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "cpp_pkg/msg/num.hpp"

using namespace std::chrono_literals;

rclcpp::Publisher<cpp_pkg::msg::Num>::SharedPtr helloworld_publisher;
size_t count = 0;

void publish_helloworld_msg()
{
  auto msg = cpp_pkg::msg::Num();
  msg.num = count++;
  RCLCPP_INFO(rclcpp::get_logger("talker"), "Published message: '%ld'", msg.num);
  helloworld_publisher->publish(msg);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("talker");

  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
  helloworld_publisher = node->create_publisher<cpp_pkg::msg::Num>("chatter", qos_profile);

  auto timer = node->create_wall_timer(1s, publish_helloworld_msg);

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}

