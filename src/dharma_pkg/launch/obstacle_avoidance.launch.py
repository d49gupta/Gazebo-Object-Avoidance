from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    reading laser = Node(
        package = 'dharma_pkg',
        executable = 'obstacleAvoidance',
        output = 'screen'
        remapping = [
            ('laser_scan', '/dolly/laser_scan'),
            ('cmd_vel', '/dolly/cmd_vel')
        ]
    )
    return LaunchDescription([
        obstacleAvoidance
    ])