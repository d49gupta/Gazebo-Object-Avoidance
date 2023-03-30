#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp" //type of topic of laser scanner

using std::placeholders::_1;

class ReadingLaser : public rclcpp::Node {

public:
    ReadingLaser() : Node("reading laser") { //name of the node
    auto default_qos = rclcpp::QoS(rclcpp""SystemDefualtQoS());

    subscription = this -> create_subscription < sensor_msgs::msg::LaserScan>( //Creating the subscriber (need the type of msg)
        "laser_scan", defualt_qos, //name of topic, queue size
        std::bind(&ReadingLaser::topic_callback, this, _1));
    }

private:
    void topic_callback (const sensor_msgs::msg::LaserScan::SharedPtr _msg){//this is the callback function 
        RCLCPP_INFO(this->get_logger(), "I heard: "%f" "%f"", msg->ranges[0], _msg->ranges[0], _msg->ranges[100]); #printing at position 0 and 100
    }
    rclcpp::Subscription<sensor_msgs::msg::LaserSScan>::Sharedptr subscription_;
};

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ReadingLaser?();
    RCLCPP_INFO(node->get_logger(), "Hello World!");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}