from setuptools import find_packages, setup

package_name = 'final_project'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name, ['launch/rob_arm_launch.py'])
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Ben Molnar',
    maintainer_email='molnarb@oregonstate.edu',
    description='Image detection for a robot arm.',
    license='BSD-3-Clause',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "camera = final_project.camera:main",
            "velocity = final_project.velocity:main",
        ],
    },
)
