#Added (launch)
import os
from glob import glob
#End Added (launch)
from setuptools import find_packages, setup

package_name = 'py_parameters'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        #Added (launch)
        (os.path.join('share', package_name), glob('launch/*.py')),
        #End Added (launch)
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
            #Added (console_scripts)
            'minimal_param_node = py_parameters.py_parameters_node:main',
            #End Added (console_scripts)
        ],
    },
)
