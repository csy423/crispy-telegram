#include<ros/ros.h>
#include<iostream>
#include<std_msgs/String.h>//信息类型对应的头文件
using namespace std;


int main(int argc,char  *argv[])
{
   ros::init(argc,argv,"stu1_node");//初始化ROS节点
   cout<<"老师您好"<<endl;//方便观察是否正常启动

   ros::NodeHandle nh;//设置“大管家”
   ros::Publisher pub=nh.advertise<std_msgs::String>("jiaowuxitong01",10);//确定话题名称和缓存长度
   ros::Rate loop_rate(10);//控制发射频率
   while(ros::ok)
   {
      cout<<"我要请假"<<endl;
      std_msgs::String msg;//创建字符串类型信息对象
      msg.data="我想要请假";//赋值
      pub.publish(msg);//调用发布者将信息发布到话题
      loop_rate.sleep();//放缓速度
      ros::spinOnce();//处理回调事件
   }
   return 0;

}