
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <cstdlib>
#include "exercise3.hpp"

using namespace std::chrono_literals;

void exercise3::exe_callback(std_msgs::msg::Int64::SharedPtr msg_){

    if(msg_->data % 2 == 1){
        msg_div_.data = (float)msg_->data / 2;
        pub_div_->publish(msg_div_);

        RCLCPP_WARN_STREAM(this->get_logger(), "Got Odd number and Division by 2 is: " << msg_->data);

    }else if(msg_->data % 2 == 0){
        msg_mul_.data = msg_->data * 2;
        pub_mul_->publish(msg_mul_);

        RCLCPP_INFO_STREAM(this->get_logger(), "Got Even number and Multiplication by 2 is: " << msg_mul_.data);
    }

}

void exercise3::timer_callback()
{
    msg_.data = (std::rand() % 100);

    RCLCPP_ERROR_STREAM(this->get_logger(), "Publishing Random number from [0-100]: " << msg_.data);
    publisher_->publish(msg_);

    end_ = std::chrono::steady_clock::now();

    // Estimation completion time 40 minutes
    if((std::chrono::duration_cast<std::chrono::minutes>(end_ - start_).count()) > 40){
        rclcpp::shutdown();
    } else{
        RCLCPP_FATAL_STREAM(this->get_logger(), "Minute since node started: " << 
                    std::chrono::duration_cast<std::chrono::minutes>(end_ - start_).count());
    }

}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    // Publish exercise3 node
    auto publisher_node = std::make_shared<exercise3>("exercise3");
    
    rclcpp::spin(publisher_node);
    rclcpp::shutdown();
    
}
