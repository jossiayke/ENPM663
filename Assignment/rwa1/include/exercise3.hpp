/**
 * @file exercise3.hpp
 * @author Yoseph Kebede (ykebede2)
 * @brief This header file shows an exercise on multiple publishers and one subscriber
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
#include <std_msgs/msg/float64.hpp>

class exercise3 : public rclcpp::Node
{
public:
    exercise3(std::string node_name) : Node(node_name)
    {
        // initialize the message
        msg_ = std_msgs::msg::Int64();
        msg_.data = 100;

        msg_mul_ = std_msgs::msg::Int64();
        msg_mul_.data = 0;

        msg_div_ = std_msgs::msg::Float64();
        msg_div_.data = 0.0;

        // timer callback
        timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(333)),
                                         std::bind(&exercise3::timer_callback, this));

        // Display node that's running                     
        RCLCPP_INFO_STREAM(this->get_logger(), node_name << " is running");
        
        // publisher random
        publisher_ = this->create_publisher<std_msgs::msg::Int64>("number", 10);

        // publisher multiplication
        pub_mul_ = this->create_publisher<std_msgs::msg::Int64>("multiplication", 10);

        // publisher division
        pub_div_ = this->create_publisher<std_msgs::msg::Float64>("division", 10);

        // subscriber
        subscriber_ = this->create_subscription<std_msgs::msg::Int64>("number", 10, 
        std::bind(&exercise3::exe_callback, 
        this, 
        std::placeholders::_1));
        
        // record clock when node starts
        start_ = std::chrono::steady_clock::now();

    }

private:
    // attributes
    std_msgs::msg::Int64 msg_;
    std_msgs::msg::Int64 msg_mul_;
    std_msgs::msg::Float64 msg_div_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr pub_div_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr pub_mul_;
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscriber_;
    std::chrono::time_point<std::chrono::steady_clock> start_;
    std::chrono::time_point<std::chrono::steady_clock> end_;    

    // methods
    void timer_callback();
    void exe_callback(std_msgs::msg::Int64::SharedPtr msg_);
};