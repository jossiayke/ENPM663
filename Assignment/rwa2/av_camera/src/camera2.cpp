#include <rclcpp/rclcpp.hpp>
#include "camera2.hpp"

void camera2::timer_callback()
{
    msg_.header.stamp = this->get_clock()->now();
    msg_.header.frame_id = camera_name_ + "_frame";
    msg_.height = 480;
    msg_.width = 640;
    msg_.encoding = "rgb8";
    msg_.is_bigendian = false;
    msg_.step = 640 * 3;
    msg_.data = std::vector<uint8_t>(msg_.height * msg_.step, 0);

    for(long unsigned int i=0; i < (msg_.height * msg_.step); i++){ 
            
            msg_.data[i] = std::rand() % 255;
        }  
    // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing Camera 2 Data: " << msg_.header.stamp);
    publisher_->publish(msg_);
    
        
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    // Publish camera2 node
    auto publisher_node = std::make_shared<camera2>("camera2");
    
    while(rclcpp::ok()){
        rclcpp::spin(publisher_node);
    }
    rclcpp::shutdown();
    
}
