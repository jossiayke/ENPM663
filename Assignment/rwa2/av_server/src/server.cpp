#include <string>
#include "server.hpp"
#include <sensor_msgs/msg/image.hpp>

using namespace std::chrono_literals;

void Server::cam1_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    RCLCPP_INFO_STREAM(this->get_logger(), "Received data from left camera (/left): " << msg->header.frame_id);
}

void Server::cam2_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    RCLCPP_WARN_STREAM(this->get_logger(), "Received data from right camera (/right): " << msg->header.frame_id);
}

void Server::cam3_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    RCLCPP_ERROR_STREAM(this->get_logger(), "Received data from front camera (/front): " << msg->header.frame_id);
}

void Server::cam4_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    RCLCPP_FATAL_STREAM(this->get_logger(), "Received data from rear camera (/rear): " << msg->header.frame_id);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto server = std::make_shared<Server>("server");
    rclcpp::spin(server);
    rclcpp::shutdown();
}