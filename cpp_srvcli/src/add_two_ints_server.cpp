#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/add_three_ints.hpp" // Include the service definition for AddTwoInts
#include <memory>

void add(const std::shared_ptr<custom_interfaces::srv::AddThreeInts::Request> request,
               std::shared_ptr<custom_interfaces::srv::AddThreeInts::Response> response)
{
    response->sum = request->a + request->b + request->c; 
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
    "Incoming request: a=%ld, b=%ld, c=%ld", 
    request->a, request->b, request->c);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
    "Sending response: [%ld]", 
    (long int)response->sum); // Log the response being sent
}

int main(int argc, char **argv) //Use to pass cmd line arguments to the node
{
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server"); 

    rclcpp::Service<custom_interfaces::srv::AddThreeInts>::SharedPtr service =
    node->create_service<custom_interfaces::srv::AddThreeInts>("add_three_ints", &add); // Create a service named "add_two_ints" and bind the add function to it
    // the &add is a pointer to the void add function

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");// Log that the service is ready
    rclcpp::spin(node); // Spin the node to keep it alive and process incoming requests
    rclcpp::shutdown();
    return 0;
}