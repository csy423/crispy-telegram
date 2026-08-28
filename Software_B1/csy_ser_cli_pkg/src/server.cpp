//包含头文件
#include<ros/ros.h>
#include<iostream>
#include<csy_ser_cli_pkg/jidian.h>
using namespace std;
bool doNums(csy_ser_cli_pkg::jidian::Request &request,csy_ser_cli_pkg::jidian::Response &response)
{
    int num=request.num;
    double jidian=0;
    ROS_INFO("成绩为%d",num) ;

        //处理请求
    if(num>=90&&num<=100)  jidian=5.0;
        else if(num>=85&&num<90) jidian=4.5;
        else if(num>=80&&num<85) jidian=4.0;
        else if(num>=75&&num<80) jidian=3.5;
        else if(num>=70&&num<75) jidian=3.0;
        else if(num>=65&&num<70) jidian=2.5;
        else if(num>=60&&num<65) jidian=2.0;
        else if(num<60)   jidian=0;
        else {cout<<"输入错误"<<endl;
             return false;
            }
            response.jidian=jidian;
       //响应
            ROS_INFO("在河海大学绩点为%f",jidian) ;

    return true;
}
int main(int argc,char **argv)
{
    setlocale(LC_ALL,"");//可以输出中文
    ros::init(argc,argv,"jiaowuchu");//初始化ROS节点
    ros::NodeHandle nh;//创建节点句柄
    ros::ServiceServer server=nh.advertiseService("huansuan",doNums);// 创建服务对象
    ROS_INFO("服务器端启动");
    //处理请求并响应
    //处理回调事件
    ros::spin();
    return 0;
}