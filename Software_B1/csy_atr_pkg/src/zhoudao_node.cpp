#include<ros/ros.h>//ros的头文件
#include<iostream>
#include<std_msgs/String.h>//信息类型对应的头文件
using namespace std;

void callback_01(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("%s",msg->data.c_str());//打印收到的信息（白色）
}

void callback_02(const std_msgs::String::ConstPtr& msg)
{
    ROS_WARN("%s",msg->data.c_str());//打印收到的信息（黄色）
}

int main(int argc,char *argv[])
{
   setlocale(LC_ALL,"");//用中文表示
    ros::init(argc,argv,"zhoudao_node");//初始化ROS节点，名称为“周导”
    ros::NodeHandle nh;//设置“大管家”
    ros::Subscriber sub1=nh.subscribe<std_msgs::String>("jiaowuxitong01",10,callback_01);//确定话题名称和消息形式，缓存长度为10
    ros::Subscriber sub2=nh.subscribe<std_msgs::String>("jiaowuxitong02",10,callback_02);//确定话题名称和消息形式，缓存长度为10
    cout << "====订阅节点已经启动，等待消息====" << endl; //在寻找自己代码问题的时候豆包给出的美化方法
    ros::spin();//比视频上的while死循环要简便一点
    return 0;
}

