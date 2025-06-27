from setuptools import find_packages, setup

package_name = 'action_server_client_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='administrator',
    maintainer_email='thinh.tran@seamk.fi',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # Added to console_scripts for action server and client
            'fibonacci_action_server = action_server_client_py.fibonacci_action_server:main',
            'fibonacci_action_client = action_server_client_py.fibonacci_action_client:main',
            # End Added
        ],
    },
)
