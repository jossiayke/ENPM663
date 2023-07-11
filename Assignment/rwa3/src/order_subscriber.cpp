#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "order_subscriber.hpp"
#include <vector>
#include <string>

void OrderSub::ordersub_callback(const ariac_msgs::msg::Order::SharedPtr msg_){

        
    order_id_ = msg_->id;

    if (msg_->type == ariac_msgs::msg::Order::KITTING){
        order_type_ = "KITTING";
    }else if(msg_->type == ariac_msgs::msg::Order::ASSEMBLY){
        order_type_ = "ASSEMBLY";
    }else if(msg_->type == ariac_msgs::msg::Order::COMBINED){
        order_type_ = "COMBINED";
    }
    
    RCLCPP_INFO_STREAM(this->get_logger(), "The Order ID is: " << order_id_ << '\n');

    RCLCPP_INFO_STREAM(this->get_logger(), "The Order Type is: " << order_type_ << '\n');

    std::vector<std::vector<int>> temp(4);

    for(int i=0; i < (int) msg_->kitting_task.parts.size(); i++)
    {
        temp[i] = {(int) msg_->kitting_task.parts[i].part.color,
                        (int) msg_->kitting_task.parts[i].part.type};
    
        if (temp[i][0] == ariac_msgs::msg::Part::RED){
            order_parts_[i] = "Red";
        } else if(temp[i][0] == ariac_msgs::msg::Part::GREEN){
            order_parts_[i] = "Green";
        }else if(temp[i][0] == ariac_msgs::msg::Part::BLUE){
            order_parts_[i] = "Blue";
        }else if(temp[i][0] == ariac_msgs::msg::Part::ORANGE){
            order_parts_[i] = "Orange";
        }else if(temp[i][0] == ariac_msgs::msg::Part::PURPLE){
            order_parts_[i] = "Purple";
        }

        if (temp[i][1] == ariac_msgs::msg::Part::BATTERY){
            order_parts_[i] = order_parts_[i] + " Battery";
        }else if (temp[i][1] == ariac_msgs::msg::Part::PUMP){
            order_parts_[i] = order_parts_[i] + " Pump";
        }else if (temp[i][1] == ariac_msgs::msg::Part::SENSOR){
            order_parts_[i] = order_parts_[i] + " Sensor";
        }else if (temp[i][1] == ariac_msgs::msg::Part::REGULATOR){
            order_parts_[i] = order_parts_[i] + " Regulator";
        }
    
    }

    for(long unsigned int i=0; i < order_parts_.size(); i++){
        RCLCPP_INFO_STREAM(this->get_logger(), "The Order parts are: " << order_parts_[i].c_str() << '\n');
    }
}

rcl_interfaces::msg::SetParametersResult OrderSub::parametersCallback(
    const std::vector<rclcpp::Parameter> &parameters){

    rcl_interfaces::msg::SetParametersResult result;
    result.successful = true;
    result.reason = "success";
    for (const auto &param : parameters)
    {
        if (param.get_name() == "order_id")
        {
            order_id_ = param.as_int();
        }
        else if(param.get_name() == "order_type")
        {
            order_type_ = param.as_string();
        }
        else if(param.get_name() == "order_parts")
        {
            order_parts_= param.as_string_array();
        }
        else
        {
            result.successful = false;
            result.reason = "parameter name not found";
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto ordersub = std::make_shared<OrderSub>("ordersub_node");
    rclcpp::spin(ordersub);
    rclcpp::shutdown();
}