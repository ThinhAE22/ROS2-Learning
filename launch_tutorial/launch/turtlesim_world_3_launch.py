import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('launch_tutorial'),
        'config',
        'turtlesim.yaml'
    )

    return LaunchDescription([
        Node(
            package='turtlesim',
            executable='turtlesim_node',
            #Added again (no namespace config in launch_turtlesim_launch file)
            namespace = 'turtlesim3',
            name= 'sim',
            parameters=[config]
        )
    ])