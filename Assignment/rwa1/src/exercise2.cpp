#include <rclcpp/rclcpp.hpp>
#include "exercise2.hpp"

using namespace std::chrono_literals;

void exercise2::exe_callback(std_msgs::msg::Int64::SharedPtr msg_){

    msg_->data = 2 * msg_->data;
    RCLCPP_WARN_STREAM(this->get_logger(), "Received and doubled data: " << msg_->data);

}

void exercise2::timer_callback()
{
        
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: " << msg_.data);
    publisher_->publish(msg_);

    end_ = std::chrono::steady_clock::now();

    // Estimation completion time 30 minutes
    if((std::chrono::duration_cast<std::chrono::minutes>(end_ - start_).count()) > 30){
        rclcpp::shutdown();
    } else{
        RCLCPP_FATAL_STREAM(this->get_logger(), "Minute since node started: " << 
                    std::chrono::duration_cast<std::chrono::minutes>(end_ - start_).count());
    }

    msg_.data = msg_.data + 1;
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    // Publish exercise2 node
    auto publisher_node = std::make_shared<exercise2>("exercise2");
    
    rclcpp::spin(publisher_node);
    rclcpp::shutdown();
    
}
