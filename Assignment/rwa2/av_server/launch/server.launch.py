# pull in some Python launch modules.
from launch import LaunchDescription
from launch_ros.actions import Node


# this function is needed
def generate_launch_description():
    serv = LaunchDescription()                # instantiate a Launchdescription object
    
    server_node = Node(                  # declare your Node
        package="av_server",            # package name
        executable="server_exe"  # executable as set in setup.py
    )

    # add each Node to the LaunchDescription object
    serv.add_action(server_node)  # add each Node to the LaunchDescription object
    return serv        