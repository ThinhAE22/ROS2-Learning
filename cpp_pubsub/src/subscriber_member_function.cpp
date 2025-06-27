#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_interfaces/msg/num.hpp" // Include the message type for subscriber
using std::placeholders::_1; //number of arguments to bind eg int a, int b

class MinimalSubscriber : public rclcpp::Node
{
    public:
        MinimalSubscriber() : Node("minimal_subscriber")
        {
            subscription_ = 
            this->create_subscription<custom_interfaces::msg::Num>(
            "topic", 10, std::bind(&MinimalSubscriber::topic_callback, 
            this, _1));
        }

    private:
        void topic_callback(const custom_interfaces::msg::Num & msg) const
        {
            RCLCPP_INFO(this->get_logger(), "I heard: '%ld'", msg.num);
        }
        rclcpp::Subscription<custom_interfaces::msg::Num>::SharedPtr 
        subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}