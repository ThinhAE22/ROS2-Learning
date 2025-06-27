#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/add_three_ints.hpp"
#include <memory>
#include <chrono>
#include <cstdlib>
using namespace std::chrono_literals; //for using time manipulators like 1s, 2s, etc.

//argc is the number of command line arguments
//argv is an array of command line arguments
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    if (argc != 4) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Usage: add_three_ints_client X Y Z");
        return 1;
    }
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_client"); // Create a node named "add_two_ints_client"
    rclcpp::Client<custom_interfaces::srv::AddThreeInts>::SharedPtr client =
    node->create_client<custom_interfaces::srv::AddThreeInts>("add_three_ints"); // Create a client for the "add_two_ints" service
    auto request = std::make_shared<custom_interfaces::srv::AddThreeInts::Request>();
    request->a = std::atol(argv[1]); // Convert the first command line argument to long and assign it to request->a
    request->b = std::atol(argv[2]); // Convert the second command line argument to long and assign it to request->b
    request->c = std::atol(argv[3]); // Convert the third command line argument to long and assign it to request->c

    while (!client->wait_for_service(1s)) { // Wait for the service to be available
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service not available, waiting again...");
    }

    auto result = client->async_send_request(request); // Send the request asynchronously
    if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS) { // Wait for the result
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum); // Log the result
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_three_ints");
    }
    rclcpp::shutdown(); // Shutdown the ROS 2 system
    return 0; // Return success
}