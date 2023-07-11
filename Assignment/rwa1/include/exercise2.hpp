/**
 * @file exercise2.hpp
 * @author Yoseph Kebede (ykebede2)
 * @brief This header file shows an exercise on single publisher and subscriber
 * @version 0.1
 * @date 2023-06-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/int64.hpp>

class exercise2 : public rclcpp::Node
{
public:
    exercise2(std::string node_name) : Node(node_name)
    {
        // initialize the message
        msg_ = std_msgs::msg::Int64();
        msg_.data = 0;

        // timer callback
        timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(500.0)),
                                         std::bind(&exercise2::timer_callback, this));

        // Display node that is run                       
        RCLCPP_INFO_STREAM(this->get_logger(), node_name << " is running");
        
        // publisher
        publisher_ = this->create_publisher<std_msgs::msg::Int64>("counter", 10);

        // subscriber
        subscriber_ = this->create_subscription<std_msgs::msg::Int64>("counter", 10, 
        std::bind(&exercise2::exe_callback, 
        this, 
        std::placeholders::_1));
        
        // Record clock when node starts
        start_ = std::chrono::steady_clock::now();

    }

private:
    // attributes
    std_msgs::msg::Int64 msg_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscriber_;
    std::chrono::time_point<std::chrono::steady_clock> start_;
    std::chrono::time_point<std::chrono::steady_clock> end_;
    

    // methods
    void timer_callback();
    void exe_callback(std_msgs::msg::Int64::SharedPtr msg_);
};