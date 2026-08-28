
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>

// ============================================================
//  按键定义（ASCII 码）
// ============================================================
#define KEYCODE_W      0x77   // 前进
#define KEYCODE_S      0x73   // 后退
#define KEYCODE_A      0x61   // 左转
#define KEYCODE_D      0x64   // 右转
#define KEYCODE_X      0x78   // 停止
#define KEYCODE_Q      0x71   // 退出
#define KEYCODE_SPACE  0x20   // 空格=急停

// ============================================================
//  终端非阻塞键盘读取（不按回车也能读按键）
// ============================================================
class KeyboardReader
{
public:
    KeyboardReader()
    {
        // 获取当前终端属性
        tcgetattr(0, &original_settings_);
        // 复制一份用于修改
        new_settings_ = original_settings_;
        // 关闭规范模式（非阻塞）和回显
        new_settings_.c_lflag &= ~(ICANON | ECHO);
        // 设置最小读取字符数和超时
        new_settings_.c_cc[VMIN] = 0;
        new_settings_.c_cc[VTIME] = 0;
        // 应用新设置
        tcsetattr(0, TCSANOW, &new_settings_);
    }

    ~KeyboardReader()
    {
        // 恢复终端原始设置
        tcsetattr(0, TCSANOW, &original_settings_);
    }

    /**
     * @brief 读取一个按键（非阻塞）
     * @return 读到的字符，没读到返回 0
     */
    int readOneChar()
    {
        char ch = 0;
        int bytes_read = read(0, &ch, 1);
        if (bytes_read > 0)
            return ch;
        return 0;
    }

private:
    struct termios original_settings_;
    struct termios new_settings_;
};

// ============================================================
//  主函数
// ============================================================
int main(int argc, char** argv)
{
    // 初始化 ROS 节点
    ros::init(argc, argv, "keyboard_teleop");
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    // ============================================================
    //  从参数服务器读取速度参数（有默认值）
    // ============================================================
    double linear_speed  = 0.5;   // 线速度 m/s
    double angular_speed = 1.0;   // 角速度 rad/s
    private_nh.param("linear_speed",  linear_speed,  0.5);
    private_nh.param("angular_speed", angular_speed, 1.0);

    // ============================================================
    //  创建速度指令发布者
    // ============================================================
    ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // 打印使用说明
    printf("\n");
    printf("============================================\n");
    printf("    键盘控制小车运动 (csy_car_teleop)\n");
    printf("============================================\n");
    printf("  w : 前进        s : 后退\n");
    printf("  a : 左转        d : 右转\n");
    printf("  x / 空格 : 停止\n");
    printf("  q : 退出程序\n");
    printf("============================================\n");
    printf("  当前线速度: %.2f m/s\n", linear_speed);
    printf("  当前角速度: %.2f rad/s\n", angular_speed);
    printf("============================================\n");
    printf("  请确保此终端窗口为当前活动窗口！\n\n");

    // 创建键盘读取器
    KeyboardReader keyboard;

    // 速度指令消息
    geometry_msgs::Twist twist;
    bool running = true;

    // 主循环
    while (ros::ok() && running)
    {
        // 读取按键
        int c = keyboard.readOneChar();

        if (c > 0)
        {
            switch (c)
            {
                case KEYCODE_W:
                    twist.linear.x  = linear_speed;
                    twist.angular.z = 0.0;
                    printf("\r[前进] v=%.2f m/s, w=%.2f rad/s   ", twist.linear.x, twist.angular.z);
                    fflush(stdout);
                    break;

                case KEYCODE_S:
                    twist.linear.x  = -linear_speed;
                    twist.angular.z = 0.0;
                    printf("\r[后退] v=%.2f m/s, w=%.2f rad/s   ", twist.linear.x, twist.angular.z);
                    fflush(stdout);
                    break;

                case KEYCODE_A:
                    twist.linear.x  = 0.0;
                    twist.angular.z = angular_speed;
                    printf("\r[左转] v=%.2f m/s, w=%.2f rad/s   ", twist.linear.x, twist.angular.z);
                    fflush(stdout);
                    break;

                case KEYCODE_D:
                    twist.linear.x  = 0.0;
               twist.angular.z = -angular_speed;
                     printf("\r[右转] v=%.2f m/s, w=%.2f rad/s   ", twist.linear.x, twist.angular.z);
                     fflush(stdout);
                     break;
                 case KEYCODE_X:
                 case KEYCODE_SPACE:
                     twist.linear.x  = 0.0;
                     twist.angular.z = 0.0;
                     printf("\r[停止] v=0.00 m/s, w=0.00 rad/s   ");
                     fflush(stdout);
                     break;
                 case KEYCODE_Q:
                     running = false;
                     printf("\n\n[退出] 程序结束，小车停止\n");
                     break;
                 default:
                     // 其他按键忽略
                     break;
             }
         }
         // 发布速度指令
         twist_pub.publish(twist);
         // 短暂休眠，降低 CPU 占用
         ros::Duration(0.05).sleep();
     }
     // 退出前发一条停止指令，防止小车继续跑
     twist.linear.x  = 0.0;
     twist.angular.z = 0.0;
     twist_pub.publish(twist);
     return 0;
 }
