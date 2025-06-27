#include <memory>
#include "rclcpp/rclcpp.hpp"

class SmapleNodeWithParameter : public rclcpp::Node
{
    public:
        SmapleNodeWithParameter()
        : Node("sample_node_with_parameter")
        {
            // Declare a parameter
            this->declare_parameter("an_int_param", 0);
            // this parameter subcriber can be use to monitor changes to the parameter
            param_subcriber_ = std::make_shared<rclcpp::ParameterEventHandler>(this);
            //Set a callback for parameter changes
            auto cb = [this](const rclcpp::Parameter & p)
            {
                RCLCPP_INFO(
                    this->get_logger(),
                    "callback: Receive an update to parameter \"%s\" of type %s: \"%ld\"",
                    p.get_name().c_str(),
                    p.get_type_name().c_str(),
                    p.as_int());
            };

            cb_handle_ = param_subcriber_->add_parameter_callback(
                "an_int_param", cb);

//Monitor remote node from start
            auto cb2 = [this](const rclcpp::Parameter & p) {
                RCLCPP_INFO(
                    this->get_logger(),
                    "callback2: Receive an update to parameter \"%s\" of type %s: \"%.02lf\"",
                    p.get_name().c_str(),
                    p.get_type_name().c_str(),
                    p.as_double());
            };
            auto remove_node_name = std::string("parameter_blackboard");
            auto remote_param_name = std::string("a_double_param");

            cb_handle_2_ = param_subcriber_->add_parameter_callback(
                remote_param_name, cb2, remove_node_name);

        }

    private:
        std::shared_ptr<rclcpp::ParameterEventHandler> param_subcriber_;
        std::shared_ptr<rclcpp::ParameterCallbackHandle> cb_handle_;
        std::shared_ptr<rclcpp::ParameterCallbackHandle> cb_handle_2_;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmapleNodeWithParameter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}