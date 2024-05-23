#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class ControllerSubscriber : public rclcpp::Node {
  public:
    ControllerSubscriber() 
    : Node("ControllerSubscriber") {
      subscription_ = this->create_subscription<std_msgs::msg::String>(
      "gamepad", 10, std::bind(&ControllerSubscriber::topic_callback, this, _1));
       RCLCPP_INFO(this->get_logger(), "Hello from ControllerSubscriber Node");
    }
    float first;
    float second;
    float third;
    float fourth;

  private:
    void topic_callback(const std_msgs::msg::String& msg) const {
      RCLCPP_INFO(this->get_logger(), "Received: %s", msg.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};
