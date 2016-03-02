#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
//#include <../../roboteq/roboteq_driver/include/roboteq_driver/channel.h>
#include "roboteq_msgs/Command.h"



class Twist2Roboteq
{
public:
  Twist2Roboteq();

private:
  void twistCallback(const geometry_msgs::Twist::ConstPtr& twist);
  
  ros::NodeHandle nh_;
  ros::Publisher throttle_pub_;
  ros::Publisher steer_pub_;
  ros::Subscriber twist_sub_;
  
};


Twist2Roboteq::Twist2Roboteq()
{

  throttle_pub_ = nh_.advertise<roboteq_msgs::Command>("throttle/cmd", 1);
  steer_pub_ = nh_.advertise<roboteq_msgs::Command>("steer/cmd", 1);
  twist_sub_ = nh_.subscribe<geometry_msgs::Twist>("cmd_vel", 1, &Twist2Roboteq::twistCallback, this);

}

void Twist2Roboteq::twistCallback(const geometry_msgs::Twist::ConstPtr& twist)
{
 roboteq_msgs::Command cmd_throttle;
 roboteq_msgs::Command cmd_steer;
 
 
  // cmd_throttle.mode = 0;
  // cmd_throttle.setpoint = twist->linear.x;

  // cmd_steer.mode = 0;
  // cmd_steer.setpoint = twist->angular.z;
 
if (twist->linear.x == 0.0 || twist->linear.x == -0.0){
  cmd_throttle.mode = -1;
  cmd_throttle.setpoint = 0.0;
}
else{
  cmd_throttle.mode = 0;
  cmd_throttle.setpoint = twist->linear.x;
}


if(twist->angular.z == 0.0 || twist->angular.z == -0.0){
  cmd_steer.mode = -1;
  cmd_steer.setpoint = 0.0;
}
else{
  cmd_steer.mode = 0;
  cmd_steer.setpoint = twist->angular.z;
}
 
  
 throttle_pub_.publish(cmd_throttle);
 steer_pub_.publish(cmd_steer);

 
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "twist2roboteq");
  Twist2Roboteq twist2roboteq;

  ros::spin();
}

