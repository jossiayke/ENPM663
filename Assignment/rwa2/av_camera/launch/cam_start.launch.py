# pull in some Python launch modules.
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os
from ament_index_python import get_package_share_directory


# this function is needed
def generate_launch_description():
    cam = LaunchDescription()                # instantiate a Launchdescription object
    
    camera1_node = Node(                  # declare your Node
        package="av_camera",            # package name
        executable="camera1_exe"  # executable as set in setup.py
    )
    camera2_node = Node(                  # declare your Node
        package="av_camera",            # package name
        executable="camera2_exe"  # executable as set in setup.py
        
    )
    camera3_node = Node(                  # declare your Node
        package="av_camera",            # package name
        executable="camera3_exe"  # executable as set in setup.py
        
    )
    camera4_node = Node(                  # declare your Node
        package="av_camera",            # package name
        executable="camera4_exe"  # executable as set in setup.py
        
    )

    av_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory('av_server'),
                         'launch/server.launch.py')
        )
    )

    cam.add_action(camera1_node)
    cam.add_action(camera2_node)
    cam.add_action(camera3_node)
    cam.add_action(camera4_node)   # add each Node to the LaunchDescription object
    cam.add_action(av_server_launch)  # add each Node to the LaunchDescription object
    return cam        