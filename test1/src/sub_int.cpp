#include <memory>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8.hpp"

class Subscriber:public rclcpp::Node
{
public:
    Subscriber():Node("int _sub")
    {
        sub_ =this->create_subscription<std_msgs::msg::Int8>("Topic",10,std::bind(&Subscriber::callback,this,std::placeholders::_1));
    }
private:
    void callback(std_msgs::msg::Int8 &msg)const 
    {
        RCLCPP_INFO(this->get_logger(),"%d",msg.data);
    }
rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr sub_;
};
int main (int argc,char* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Subscriber>());
    rclcpp::shutdown();
    return 0;
}