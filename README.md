#ros_udp_bridge
----------------------------
The package has two nodes:
1) Receive data from an UDP port and publish it on a ROS topic.
2) Receive data from an ROS Topic and send it to an UDP port.

Run it !
------------------------------
Open the terminal on catkin environment and type:
```
source ./devel/setup.bash
```
After that, run the node udp_bridge_receive to publish data from an UDP port:
```
rosrun udp_bridge udp_bridge_receive
```
Or, run the node udp_bridge_send to subscribe a ROS topic and send the content to a UDP port.
```
rosrun udp_bridge udp_bridge_send
```

How to validate it
------------------------

You can send data through an UDP port using the command:
```
echo '<your message>' | socat - udp-sendto:<your_ip>:<udp_port>
```
You can listen to an UDP port using the command:

```
socat udp-listen:<port_number>, -
```
The data published using udp_bridge_receive node can be seem using the command above on catkin directory.
```
rostopic echo /udp_message
```
