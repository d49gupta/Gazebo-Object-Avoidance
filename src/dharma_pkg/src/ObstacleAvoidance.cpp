#include "geometry_msgs/msg/twist.hpp" //to read the movement topic messages
#include "rclcpp/rclcpp.hpp" //main c++ library
#include "sensor_msgs/msg/laser_scan.hpp" //in order to read laser scanner

using std::placeholders::_1;

class ObstacleAvoidance : public rclcpp::Node {
public: 
    ObstacleAvoidance() : Node("ObstacleAvoidance")
    {
        auto default_qos = rclcpp::QoS(rclcpp::SystemDefualtQoS());
        subscription = this -> create_subscription<sensor_msgs::msg::LaserScan>(
            "laser_scan", defualt_qos, std::bind(&ObstacleAvoidance::topic_callback, this, _1)); //this listens the to laser_scan publisher

    publisher_ this -> create_publisher<geometry_msgs::msg::Twist>("cmd_vel, 10"); //publishing on the cmd_vel topic
    }

private:
    void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr _msg) { //reading in the laser scanner through the topic 
        float min = 10;
        for (int a = 0; a < 200; a++)
        {
            float current = _msg-> ranges[a]; //how to get the current laser scanner value 
            if (current < min){
                min = current;
            }
        }
        auto message = this -> calculateVelmsg(min);
        publisher_ -> publish(message)
    }
    geometry_msgs::msg::Twist calculateVelMsg(float distance) {
        auto msg = geometry_msgs::msg::Twist();
        //logic
        RCLCPP_INFO(this->get_logger(), "Distance is: '%f'", distance);
        if (distance < 1) {
            //turn around
            msg.linear.x = 0; 
            msg.angular.z = 0.3; //robot rotates about its own axis at 0.3 speed
        }
        else {
            //go straing ahead
            msg.linear.x = 0.3; //0.3 is the speed 
            msg.angular.z = 0;
        }
        return msg;
    }
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<sensor msgs::msg::LaserScan>::SharedPtr subscription_;
    
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ObstacleAvoidance>());
    rclcpp::shutdown();
    return 0;
}