#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <ariac_msgs/msg/order.hpp>
#include <ariac_msgs/msg/kitting_task.hpp>
#include <ariac_msgs/msg/part.hpp>
#include <string>
#include <vector>

class OrderSub : public rclcpp::Node
{
public:
    OrderSub(std::string node_name) : Node(node_name)
    {

    // Display node that is run                       
    RCLCPP_INFO_STREAM(this->get_logger(), node_name << " is running");

    // subscriber
    subscriber_ = this->create_subscription<ariac_msgs::msg::Order>("order", 10, 
    std::bind(&OrderSub::ordersub_callback, 
    this, 
    std::placeholders::_1));
    
    // parameter

    this->declare_parameter("order_id", "");
    this->declare_parameter("order_type", "");
    this->declare_parameter("order_parts", param_);//rclcpp::PARAMETER_STRING_ARRAY);//["","","",""]);

    order_id_ = this->get_parameter("order_id").as_string();
    order_type_ = this->get_parameter("order_type").as_string();
    order_parts_ = this->get_parameter("order_parts").as_string_array();

    
    // callback for parameter change
    callback_handle_ = this->add_on_set_parameters_callback(
        std::bind(&OrderSub::parametersCallback, this, std::placeholders::_1));

    }

private:
    // attributes
    std::string order_id_;
    std::string order_type_;
    std::vector<std::string> order_parts_{"","","",""};
    std::vector<std::string> param_{"","","",""};
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<ariac_msgs::msg::Order>::SharedPtr subscriber_;
    OnSetParametersCallbackHandle::SharedPtr callback_handle_;

    void ordersub_callback(const ariac_msgs::msg::Order::SharedPtr msg_);
    rcl_interfaces::msg::SetParametersResult parametersCallback(const std::vector<rclcpp::Parameter> &parameters);
};