#include <chrono>
#include <memory>
#include <rclcpp/rclcpp.hpp> // ROS 2 C++ client library
#include "custom_interfaces/msg/num.hpp" // Message type for publishing

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node // Inherit from rclcpp::Node to create a ROS 2 node
{
    public:
    MinimalPublisher() : Node("minimal_publisher"), count_(0)
    {
        publisher_ =this->create_publisher<custom_interfaces::msg::Num> // Create a publisher on "topic" with queue size 10
        ("topic", 10); // short chat history, topic name is "topic", queue size is 10

        timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

    private:
        void timer_callback()
        {
            auto message = custom_interfaces::msg::Num(); // Create a message of type custom_interfaces::msg::Num
            message.num = this->count_++; // Increment the count and assign it to the message field
            RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.num << "'"); // Log the message being published
            publisher_->publish(message);
        }

        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<custom_interfaces::msg::Num>::SharedPtr publisher_;
        size_t count_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); // Initialize ROS 2
    rclcpp::spin(std::make_shared<MinimalPublisher>()); // Run the node (keeps it alive)
    rclcpp::shutdown(); // Shutdown ROS 2
    return 0;
}