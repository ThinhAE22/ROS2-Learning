#include <functional>
#include <memory>
#include <thread>
#include <action_tutorials_interfaces/action/fibonacci.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <action_server_client_cpp/visibility_control.h>

namespace action_server_client_cpp
{
    class FibonacciActionServer : public rclcpp::Node
    {
        public:
        using Fibonacci = action_tutorials_interfaces::action::Fibonacci;
        using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

        ACTION_SERVER_CLIENT_CPP_PUBLIC
        explicit FibonacciActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions()) : Node("fibonacci_action_server", options)
        {
            using namespace std::placeholders;
            this->action_server_ = rclcpp_action::create_server<Fibonacci>(
                this,
                "fibonacci",
                std::bind(&FibonacciActionServer::handle_goal, this, _1, _2),
                std::bind(&FibonacciActionServer::handle_cancel, this, _1),
                std::bind(&FibonacciActionServer::handle_accepted, this, _1));
        }


        private:
            rclcpp_action::Server<Fibonacci>::SharedPtr action_server_;

            rclcpp_action::GoalResponse handle_goal(
                const rclcpp_action::GoalUUID & uuid,
                std::shared_ptr<const Fibonacci::Goal> goal)
                {
                    RCLCPP_INFO(this->get_logger(), "Received goal request with order: %d", goal->order);
                    (void)uuid; // Suppress unused variable warning
                    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
                }

            rclcpp_action::CancelResponse handle_cancel(
                const std::shared_ptr<GoalHandleFibonacci> goal_handle)
                {
                    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
                    (void)goal_handle; // Suppress unused variable warning
                    return rclcpp_action::CancelResponse::ACCEPT;
                }

            void handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
            {
                using namespace std::placeholders;
                std::thread(std::bind(&FibonacciActionServer::execute, this, _1), goal_handle).detach();
            }

            void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
            {
                RCLCPP_INFO(this->get_logger(), "Executing goal");
                rclcpp::Rate loop_rate(1);
                const auto goal = goal_handle->get_goal();
                auto feedback = std::make_shared<Fibonacci::Feedback>();
                auto & sequence = feedback->partial_sequence;

                sequence.push_back(0);
                sequence.push_back(1);
                auto result = std::make_shared<Fibonacci::Result>();

                for (int i = 1; i < goal->order && rclcpp::ok(); ++i)
                {
                    if (goal_handle->is_canceling())
                    {
                        RCLCPP_INFO(this->get_logger(), "Goal canceled");
                        goal_handle->canceled(result);
                        return;
                    }

                    sequence.push_back(sequence[i] + sequence[i - 1]);
                    // Publish feedback
                    goal_handle->publish_feedback(feedback);
                    RCLCPP_INFO(this->get_logger(), "Published feedback:");
                    loop_rate.sleep();
                }

                if (rclcpp::ok())
                {
                    result->sequence = sequence;
                    RCLCPP_INFO(this->get_logger(), "Goal completed successfully");
                    goal_handle->succeed(result);
                }
            }
    };
}

RCLCPP_COMPONENTS_REGISTER_NODE
(action_server_client_cpp::FibonacciActionServer)