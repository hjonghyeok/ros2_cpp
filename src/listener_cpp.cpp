#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "cpp_pkg/msg/num.hpp"

rclcpp::Subscription<cpp_pkg::msg::Num>::SharedPtr sub;

void callback(const cpp_pkg::msg::Num::SharedPtr msg)
{
    RCLCPP_INFO(rclcpp::get_logger("listener"), "msg: %ld", msg->num);
}

int main(int ac, char **av)
{
    rclcpp::init(ac, av);

    auto node = rclcpp::Node::make_shared("listener");
    auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
    sub = node->create_subscription<cpp_pkg::msg::Num>(
        "chatter", qos, callback);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}