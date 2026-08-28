//包含头文件
#include<ros/ros.h>
#include<csy_ser_cli_pkg/jidian.h>



int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");//可以输出中文
    ros::init(argc,argv,"stu");//初始化ROS节点
    ros::NodeHandle nh;//创建节点句柄
    ros::ServiceClient client=nh.serviceClient <csy_ser_cli_pkg::jidian>("huansuan");//创建一个客户端对象
    //提交请求并处理响应
    csy_ser_cli_pkg::jidian ai;
    //组织请求
    ai.request.num=83;
    //处理响应
    bool flag=client.call(ai);
    if(flag)
    {
        ROS_INFO("响应成功！");
        //获取结果
        ROS_WARN("响应结果=%f",ai.response.jidian);
    }
    return 0;

}