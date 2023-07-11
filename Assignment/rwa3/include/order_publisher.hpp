#pragma once

#include <rclcpp/rclcpp.hpp>
#include <cstdint>
#include <ariac_msgs/msg/order.hpp>
#include <ariac_msgs/msg/part.hpp>

typedef unsigned char uint8;

// timer
class OrderPub : public rclcpp::Node
{
public:
    OrderPub(std::string node_name) : Node(node_name)
    {
        // initialize the message
        orderpub_msg_ = ariac_msgs::msg::Order();
        
        // timer callback
        timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0)),
                                         std::bind(&OrderPub::timer_callback, this));

        // publisher
        orderpub_ = this->create_publisher<ariac_msgs::msg::Order>("order", 10);
    }

private:
    // attributes
    ariac_msgs::msg::Order orderpub_msg_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<ariac_msgs::msg::Order>::SharedPtr orderpub_;

    // methods
    void timer_callback();
    void part_fill(int idx, uint8 color, uint8 part, uint8 quadrant);
};
