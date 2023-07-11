# pull in some Python launch modules.
import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

# this function is needed


def generate_launch_description():

    ld = LaunchDescription()

    # Loading parameters from a file
    node_params = os.path.join(
        get_package_share_directory('rwa3'),
        'config',
        'params.yaml'
    )

    order_publisher = Node(
        package="rwa3",
        executable="order_publisher_exe",
        parameters=[node_params],   # parameter file
        name='order_publisher'            # node remapping
    )

    order_subscriber = Node(
        package="rwa3",
        executable="order_subscriber_exe",
        parameters=[node_params],   # parameter file
        name='order_subscriber'            # node remapping
    )

    ld.add_action(order_subscriber)
    ld.add_action(order_publisher)
    return ld

