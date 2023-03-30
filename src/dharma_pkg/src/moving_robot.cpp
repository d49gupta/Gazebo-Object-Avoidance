#include <chrono>
#include <functional>
#include <memory>

#include<"geometry_msgs/msg/twist.hpp" //topic type of cmd_vel topic which controls the movements of the robot 
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MovingRobot : public rclcpp::Node{
public: 
    MovingRobot() : Node("moving_robot", count_(0)) //constructor of the class
    {
        publisher = this-> create_publisher<geometry_msgs::msg::Twist>("/dolly/cmd_vel", 10); //publishing movements to the topic 
        timer_ = this -> create_wall_timer(
            500ms, std::bind(&MovingRobot::timer_callback, this)); //creating timer for callback function
    }
private:
    void timer_callback(){ //callback function 
        auto message = geomtery_msgs::msg::Twist(); //creating message of type geometry twist
        message.linear.x = 0.5; //this actually moves the robot. Set the different objects of message to the change in position 
        message.angular.z = 0.3; //there is linear xyx and angular xyz
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f.2' and '%.2'", message.linear.x, message.angular.z); //outputting updated movements
        publisher -> publish(message); //publishing the message
    }
    //declaring the timer and publisher in private
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MovingRobot>());
    rclcpp::shutdown();
    return 0;
}