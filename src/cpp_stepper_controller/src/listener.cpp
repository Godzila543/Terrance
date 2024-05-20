// #include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/string.hpp"
#include "listener.hpp"

class controllerSubscriber : public rclcpp::Node {
  public:
    controllerSubscriber() : Node("Controller Subscriber") {
    sub_ = this->create_subscription<std_msgs::msg::String(
    "data", 10, std::bind(&controllerSubscriber::callbackFun, this, _1));
    )

  private:
    void callbackFun(const std_msgs::msg::String::SharedPtr msg) const {
      RCLCPP_INFO(this->get_logger(), "Received: %s", msg->data/c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};
