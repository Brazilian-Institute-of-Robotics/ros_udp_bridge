#ros_udp_bridge
Receive data from an UDP port and publish it on a ROS topic.

Run it !
------------------------------
Open the terminal and type:

```
rosrun udp_comm udp_bridge_node
```
Open other terminal window and send a data through a UDP port

```
echo 'Hello World' | socat - udp-sendto:<your_ip>:<udp_port>
```
Open other terminal port to see your message being published on a ROS Topic
```
rostopic echo /udp_message
```