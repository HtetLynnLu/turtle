#include <memory>
#include <functional>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class Publisher : public rclcpp::Node 
{
    public:
    Publisher():Node("turtle_pub")
    {
        pub_ = this -> create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
        timer_ =this -> create_wall_timer(100ms,std::bind(&Publisher::callback,this));
    }
private:
void callback()
{
auto msg = geometry_msgs::msg::Twist();
msg.linear.x=2.5;
RCLCPP_INFO(this->get_logger(),"%f",msg.linear.x);
pub_ -> publish(msg);
}
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
rclcpp::TimerBase::SharedPtr timer_;
};
int main (int argc,char* argv[])
{   rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}