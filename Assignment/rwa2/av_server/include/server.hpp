/**
 * @file camera1.hpp
 * @author Yoseph Kebede (ykebede2)
 * @brief This header file shows an exercise on single publisher
 * @version 0.1
 * @date 2023-06-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/image.hpp>

// timer
class Server : public rclcpp::Node
{
public:
    Server(std::string node_name) : Node(node_name)
    {
        callback_group_subscriber1_ = this->create_callback_group(
            rclcpp::CallbackGroupType::MutuallyExclusive);
        callback_group_subscriber2_ = this->create_callback_group(
            rclcpp::CallbackGroupType::MutuallyExclusive);
        callback_group_subscriber3_ = this->create_callback_group(
            rclcpp::CallbackGroupType::MutuallyExclusive);
        callback_group_subscriber4_ = this->create_callback_group(
            rclcpp::CallbackGroupType::MutuallyExclusive);

        auto sub1_opt = rclcpp::SubscriptionOptions();
        sub1_opt.callback_group = callback_group_subscriber1_;
        auto sub2_opt = rclcpp::SubscriptionOptions();
        sub2_opt.callback_group = callback_group_subscriber2_;
        auto sub3_opt = rclcpp::SubscriptionOptions();
        sub3_opt.callback_group = callback_group_subscriber3_;
        auto sub4_opt = rclcpp::SubscriptionOptions();
        sub4_opt.callback_group = callback_group_subscriber4_;
        
        cam1_sub_ = this->create_subscription<sensor_msgs::msg::Image>("left", rclcpp::QoS(10), std::bind(&Server::cam1_callback, this, std::placeholders::_1), sub1_opt);
        cam2_sub_ = this->create_subscription<sensor_msgs::msg::Image>("right", rclcpp::QoS(10), std::bind(&Server::cam2_callback, this, std::placeholders::_1), sub2_opt);
        cam3_sub_ = this->create_subscription<sensor_msgs::msg::Image>("front", rclcpp::QoS(10), std::bind(&Server::cam3_callback, this, std::placeholders::_1), sub3_opt);
        cam4_sub_ = this->create_subscription<sensor_msgs::msg::Image>("rear", rclcpp::QoS(10), std::bind(&Server::cam4_callback, this, std::placeholders::_1), sub4_opt);
    
    }

private:
    // attributes
    sensor_msgs::msg::Image msg_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr cam1_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr cam2_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr cam3_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr cam4_sub_;

    // callback groups
    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber1_;
    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber2_;
    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber3_;
    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber4_;

    // methods
    void cam1_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void cam2_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void cam3_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void cam4_callback(const sensor_msgs::msg::Image::SharedPtr msg);

};