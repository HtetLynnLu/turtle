#include <functional>
#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8.hpp" 
using namespace std::chrono_literals;
class Publisher : public rclcpp :: Node
{
public:
    Publisher():Node("int_pub")
    {
        pub_ = this -> create_publisher<std_msgs::msg::Int8>("Topic",10);
        timer_= this -> create_wall_timer(500ms,std::bind(&Publisher::callback,this));

    }
private:
void callback()
{
auto msg= std_msgs::msg::Int8();
msg.data= 10 ;
pub_ -> publish(msg);}
rclcpp::TimerBase::SharedPtr timer_;
rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr pub_;
};
int main(int argc,char* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}