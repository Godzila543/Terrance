from setuptools import find_packages, setup

package_name = 'py_publisher'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools', 'inputs'],
    zip_safe=True,
    maintainer='Colin Brown',
    maintainer_email='colin2003az@gmail.com',
    description='package to publish controller commands to the stepper driver',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'talker = py_publisher.publisher_member_function:main',
            'listener = py_publisher.subscriber_member_function:main',
            'gamepad = py_publisher.gamepad:main'
        ],
    },
)
