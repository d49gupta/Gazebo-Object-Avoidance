from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    reading laser = Node(
        package = 'dharma_pkg',
        executable = 'reading_laser',
        output = 'screen'
        remapping = [
            ('laser_scan', '/dolly/laser_scan')
        ]
    )
    return LaunchDescription([
        reading_laser
    ])