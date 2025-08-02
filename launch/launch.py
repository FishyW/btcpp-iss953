import os
from ament_index_python import get_package_share_directory, get_package_prefix
from launch import LaunchDescription
from launch.actions import ExecuteProcess, DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


from pathlib import Path

PACKAGE_NAME = 'dummy'
PACKAGE_PATH = os.path.join(get_package_share_directory(PACKAGE_NAME))

BEHAVIOR_TREE = 'Test'

def generate_launch_description():
    declare_bt_arg = DeclareLaunchArgument('bt', default_value=BEHAVIOR_TREE)
    bt = LaunchConfiguration('bt')

    executor_params = os.path.join(PACKAGE_PATH, 'config','bt_executor.yaml')

    bt_executor = Node(
        package=PACKAGE_NAME,
        executable='bt_executor',
        parameters=[executor_params],
    )
    

    start_bt_executor =  ExecuteProcess(
        cmd=['ros2', 'action', 'send_goal', '/bt_execution', 
        'btcpp_ros2_interfaces/action/ExecuteTree', 
        ['target_tree: ', bt]],
        output='screen',
        name='bt-starter'
    )
   
   
    return LaunchDescription([
        declare_bt_arg,
        start_bt_executor,
        bt_executor
    ])