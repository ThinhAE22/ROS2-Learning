#include <chrono>
#include <functional>
#include <string>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalPram : public rclcpp::Node
{
    public:
        MinimalPram() : Node("minimal_param_node")
        {
            this->declare_parameter("my_parameter", "world"); // Declare a parameter with a default value "world"
            timer_ = this->create_wall_timer(
            500ms, std::bind(&MinimalPram::timer_callback, this));
        }

        void timer_callback()
        {
            std::string my_parameter = this->get_parameter("my_parameter").as_string(); // Get the parameter value "world"
            RCLCPP_INFO(this->get_logger(), "Hello: %s !", my_parameter.c_str());
            std::vector<rclcpp::Parameter> all_new_parameters {
                rclcpp::Parameter("my_parameter", "world again")
            };
            this->set_parameters(all_new_parameters);
        }

    private:
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPram>());
    rclcpp::shutdown();
    return 0;
}