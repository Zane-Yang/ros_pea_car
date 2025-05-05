#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>

class DifferentialDriveController {
public:
    DifferentialDriveController() {
        // 初始化节点
        ros::NodeHandle nh;
        
        // 发布左右轮子速度
        left_wheel_pub = nh.advertise<std_msgs::Float64>("left_wheel_speed", 10);
        right_wheel_pub = nh.advertise<std_msgs::Float64>("right_wheel_speed", 10);
        
        // 订阅 cmd_vel 话题
        cmd_vel_sub = nh.subscribe("cmd_vel", 10, &DifferentialDriveController::cmdVelCallback, this);
        
        // 小车参数
        wheel_radius = 0.0425; // 轮子半径，单位：米
        axle_length = 0.357;  // 轮子之间的距离，单位：米
    }
    
    void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& msg) {
        double linear_velocity = msg->linear.x;  // 线速度
        double angular_velocity = msg->angular.z; // 角速度
        
        // 计算左右轮子的速度
        double left_velocity = (linear_velocity - (axle_length / 2) * angular_velocity) / wheel_radius;
        double right_velocity = (linear_velocity + (axle_length / 2) * angular_velocity) / wheel_radius;
        
        // 发布速度命令
        std_msgs::Float64 left_msg;
        std_msgs::Float64 right_msg;
        left_msg.data = left_velocity;
        right_msg.data = right_velocity;
        
        left_wheel_pub.publish(left_msg);
        right_wheel_pub.publish(right_msg);
    }

private:
    ros::Publisher left_wheel_pub;
    ros::Publisher right_wheel_pub;
    ros::Subscriber cmd_vel_sub;
    
    double wheel_radius;
    double axle_length;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "differential_drive_controller");
    DifferentialDriveController controller;
    ros::spin();
    return 0;
}
