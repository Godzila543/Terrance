#include <memory>
#include "json.hpp"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "Gamepad.hpp"

using std::placeholders::_1;

class ControllerSubscriber : public rclcpp::Node
{
public:
	ControllerSubscriber()
		: Node("ControllerSubscriber")
	{
		subscription_ = this->create_subscription<std_msgs::msg::String>(
			"gamepad", 10, std::bind(&ControllerSubscriber::gamepad_callback, this, _1));
		RCLCPP_INFO(this->get_logger(), "Hello from ControllerSubscriber Node");
	}

	const Gamepad &getGamepad() const
	{
		return gamepad;
	}

	float first;
	float second;
	float third;
	float fourth;

private:
	void gamepad_callback(const std_msgs::msg::String &msg)
	{
		// RCLCPP_INFO(this->get_logger(), "Received: %s", msg.data.c_str());
		gamepad = parseGamepad(msg.data);
	}

	Gamepad parseGamepad(const std::string &json_str)
	{
		nlohmann::json json_data = nlohmann::json::parse(json_str);

		Gamepad gp;

		gp.left_stick.x = json_data["left_stick"]["x"];
		gp.left_stick.y = json_data["left_stick"]["y"];

		gp.right_stick.x = json_data["right_stick"]["x"];
		gp.right_stick.y = json_data["right_stick"]["y"];

		gp.d_pad.x = json_data["d_pad"]["x"];
		gp.d_pad.y = json_data["d_pad"]["y"];

		gp.triggers.left = json_data["triggers"]["left"];
		gp.triggers.right = json_data["triggers"]["right"];

		gp.buttons.a = json_data["buttons"]["a"];
		gp.buttons.b = json_data["buttons"]["b"];
		gp.buttons.x = json_data["buttons"]["x"];
		gp.buttons.y = json_data["buttons"]["y"];
		gp.buttons.l1 = json_data["buttons"]["l1"];
		gp.buttons.r1 = json_data["buttons"]["r1"];
		gp.buttons.select = json_data["buttons"]["select"];
		gp.buttons.start = json_data["buttons"]["start"];
		gp.buttons.l_stick = json_data["buttons"]["l_stick"];
		gp.buttons.r_stick = json_data["buttons"]["r_stick"];

		return gp;
	}

	Gamepad gamepad;
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};
