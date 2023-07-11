/**
 * @file camera1.hpp
 * @author Yoseph Kebede (ykebede2)
 * @brief This header file shows a node for single camera
 * @version 0.1
 * @date 2023-06-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

class camera4 : public rclcpp::Node
{
public:
    camera4(std::string node_name) : Node(node_name)
    {
        // initialize the message
        msg_ = sensor_msgs::msg::Image();
               
        // publisher
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("rear", 10);

        // parameters
        this->declare_parameter("frequency", 10.0);
        this->declare_parameter("name", "camera4");
        camera_frequency_ = this->get_parameter("frequency").as_double();
        camera_name_ = this->get_parameter("name").as_string();

        // display node that is running                      
        RCLCPP_INFO_STREAM(this->get_logger(),"Currently " << camera_name_ << " is running");

        // timer callback
        timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(1 / camera_frequency_) * 1000),
                                         std::bind(&camera4::timer_callback, this));
        

    }

private:
    // attributes
    sensor_msgs::msg::Image msg_;
    std::string camera_name_;
    double camera_frequency_;
    double camera_bandwidth_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;

    // methods
    void timer_callback();
};

