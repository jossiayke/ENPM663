#include <rclcpp/rclcpp.hpp>
#include <ariac_msgs/msg/kitting_task.hpp>
#include <ariac_msgs/msg/kitting_part.hpp>
#include <vector>
#include "order_publisher.hpp"

typedef unsigned char uint8;

void OrderPub::part_fill(int idx, uint8 color, uint8 part, uint8 quadrant){

    orderpub_msg_.kitting_task.parts[idx].part.color = color;
    orderpub_msg_.kitting_task.parts[idx].part.type = part;
    orderpub_msg_.kitting_task.parts[idx].quadrant = quadrant;

}

void OrderPub::timer_callback()
{
    RCLCPP_INFO_STREAM(this->get_logger(), "Published message entered callback" << '\n');

    orderpub_msg_.id = "KITTING01";
    orderpub_msg_.type = ariac_msgs::msg::Order::KITTING;
    orderpub_msg_.priority = false;

    orderpub_msg_.kitting_task.agv_number = 2;
    orderpub_msg_.kitting_task.tray_id = 4;
    orderpub_msg_.kitting_task.destination = ariac_msgs::msg::KittingTask::WAREHOUSE;

    RCLCPP_INFO_STREAM(this->get_logger(), "Published message was saved" << '\n');

    orderpub_msg_.kitting_task.parts = std::vector<ariac_msgs::msg::KittingPart>(4);

    this->part_fill(0, ariac_msgs::msg::Part::RED, ariac_msgs::msg::Part::BATTERY, ariac_msgs::msg::KittingPart::QUADRANT1);
    this->part_fill(1, ariac_msgs::msg::Part::ORANGE, ariac_msgs::msg::Part::REGULATOR, ariac_msgs::msg::KittingPart::QUADRANT2);
    this->part_fill(2, ariac_msgs::msg::Part::BLUE, ariac_msgs::msg::Part::SENSOR, ariac_msgs::msg::KittingPart::QUADRANT3);
    this->part_fill(3, ariac_msgs::msg::Part::PURPLE, ariac_msgs::msg::Part::PUMP, ariac_msgs::msg::KittingPart::QUADRANT4);

    //Publish ordered kit
    orderpub_->publish(orderpub_msg_);

    rclcpp::sleep_for(std::chrono::milliseconds(5000));
    
    RCLCPP_INFO_STREAM(this->get_logger(), "Published message ended" << '\n');

    rclcpp::shutdown();
    
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    
    auto orderpub_node = std::make_shared<OrderPub>("OrderPub");
    RCLCPP_INFO_STREAM(orderpub_node->get_logger(), "started node " << '\n');
    
    while (rclcpp::ok()){
        rclcpp::spin_some(orderpub_node);
        
    }
    rclcpp::shutdown();
}