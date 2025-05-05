// 用于rviz中控制小车移动的程序
// 键盘输入w,s,a,d控制小车移动
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "pea_car_control");
    ros::NodeHandle nh;

    ros::Publisher cmd_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    geometry_msgs::Twist cmd;
    ros::Rate loop_rate(10);
    while (ros::ok()) {
        char key = getch();

        switch (key) {
            case 'w':  // 向左平移
                cmd.linear.x = 0.3;
                cmd.linear.y = 0; // 调整为合适的平移速度
                cmd.angular.z = 0;
                break;
            case 's':  // 向右平移
                cmd.linear.x = -0.3;
                cmd.linear.y = 0; // 调整为合适的平移速度
                cmd.angular.z = 0;
                break;
            case 'a':  // 向左后方旋转
                cmd.linear.x = 0;
                cmd.linear.y = 0; // 直线速度为0
                cmd.angular.z = 0.5; // 调整为合适的旋转速度
                break;
            case 'd':  // 向右后方旋转
                cmd.linear.x = 0;
                cmd.linear.y = 0; // 直线速度为0
                cmd.angular.z = -0.5; // 调整为合适的旋转速度
                break;
            default:
                cmd.linear.x = 0;
                cmd.linear.y = 0;
                cmd.angular.z = 0;
                break;
        }

        cmd_pub.publish(cmd);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
