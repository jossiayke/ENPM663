#include <rclcpp/rclcpp.hpp>
#include "exercise1.hpp"

void exercise1::timer_callback()
{
        
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: " << msg_.data);
    publisher_->publish(msg_);
    msg_.data = msg_.data + 1;

    end_ = std::chrono::steady_clock::now();
    
    // Estimation completion time 30 minutes
    if((std::chrono::duration_cast<std::chrono::minutes>(end_ - start_).count()) > 30){
        rclcpp::shutdown();
    } else{
        RCLCPP_FATAL_STREAM(this->get_logger(), "Minute since node started: " << 
                    std::chrono::duration_cast<std::chrono::minutes>(end_ - start_).count());
    }

}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    // Publish exercise1 node
    auto publisher_node = std::make_shared<exercise1>("exercise1");
    
    rclcpp::spin(publisher_node);
    rclcpp::shutdown();
    
}
