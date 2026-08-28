#include<iostream>
#include<cmath>
using namespace std;
#define pi 3.14159
class shape
{
public:
	//创立纯虚函数
	virtual void getSHu() = 0;
	virtual void getZhouC() = 0;
	virtual void getMianJ() = 0;
	virtual bool jianyan() = 0;
	//创立执行函数
	void work()
	{
		getSHu();
		if (!jianyan())  // 校验失败直接结束，不计算周长面积
		{
			return;
		}
		getZhouC();
		getMianJ();
	}
	//析构函数
	virtual ~shape() {}

};
class rectangle :public shape
{
public:
	//要求输入规范，只能输入正数
	bool jianyan()
	{
		if (m_Bian1 <= 0 || m_Bian2 <= 0)
		{
			cout << "请输入正数" << endl;
			return 0;
		}
		else return 1;
	}
	//得到矩形数据
	void getSHu()
	{
		cout << "请输入矩形的宽" << endl;
		cin >> m_Bian1;
		cout << "请输入矩形的长" << endl;
		cin >> m_Bian2;
	}
	//计算周长
	void getZhouC()
	{
		m_ZhouC = 2 * (m_Bian1 + m_Bian2);
		cout << "矩形的周长为" << m_ZhouC << endl;
	}
	//计算面积
	void getMianJ()
	{
		m_MianJ = m_Bian1 * m_Bian2;
		cout << "矩形的面积为" << m_MianJ << endl;
	}
private:
	double m_Bian1, m_Bian2,m_ZhouC,m_MianJ;
};
class circle: public shape
{
public:
	//要求输入规范，只能输入正数
	bool jianyan()
	{
		if (m_R <= 0)
		{
			cout << "请输入正数" << endl;
			return 0;
		}
		else return 1;
	}
	//获取圆形数据
	void getSHu()
	{
		cout << "请输入圆的半径" << endl;
		cin >> m_R;
	}
	//计算周长
	void getZhouC()
	{
		m_ZhouC = 2 * pi * m_R;
		cout << "圆形的周长为" << m_ZhouC << endl;
	}
	//计算面积
	void getMianJ()
	{
		m_MianJ = m_R * m_R * pi;
		cout << "圆形的面积为" << m_MianJ << endl;
	}
private:
	double m_R,m_ZhouC,m_MianJ;
};
class triangle : public shape
{
public:
	//要求输入规范，只能输入正数，且要能够形成三角形
	bool jianyan()
	{
		if (m_Bian1 <= 0 || m_Bian2 <= 0 || m_Bian3 <= 0)
		{
			cout << "请输入正数" << endl;
			return 0;
		}
		if (m_Bian1 + m_Bian2 <= m_Bian3 || m_Bian1 + m_Bian3 <= m_Bian2 || m_Bian2 + m_Bian3 <= m_Bian1)
		{
			cout << "无法形成三角形，请重新输入" << endl;
			return 0;
		}
		else return 1;
	}
	//获取三角形三边数据
	void getSHu()
	{
		cout << "请输入第一条边的边长" << endl;
		cin >> m_Bian1;
		cout << "请输入第二条边的边长" << endl;
		cin >> m_Bian2;
		cout << "请输入第三条边的边长" << endl;
		cin >> m_Bian3;
	}
	//计算周长
	void getZhouC()
	{
		m_ZhouC = m_Bian1 + m_Bian2 + m_Bian3;
		cout << "三角形的周长为" << m_ZhouC << endl;
	}
	//计算面积
	void getMianJ()
	{
		m_MianJ = sqrt((m_ZhouC / 2) * (m_ZhouC / 2 - m_Bian1) * (m_ZhouC / 2 - m_Bian2) * (m_ZhouC / 2 - m_Bian3));
		cout << "三角形的面积为" << m_MianJ << endl;
	}
private:
	double m_Bian1, m_Bian2,m_Bian3,m_ZhouC, m_MianJ;
};
void dowork(shape* a)//创立父类指针指向子类
{
	a->shape::work();
	delete a;//消除空间
}
int main(void)
{
	//选择图形
	char Xuanze;
	cout << "请选择你要计算的图形\n" << "A.矩形\n" << "B.圆形\n" << "C.三角形" << endl;
	cin >> Xuanze;
	switch(Xuanze)
	{
	case 'A':
	{
		dowork(new rectangle);
		break;
	}
	case 'B':
	{
		dowork(new circle);
		break;
	}
	case 'C':
	{
		dowork(new triangle);
		break;
	}
	default:
	{
		cout << "请输入合法的选项" << endl;
		break;
	}
	}
	return 0;
}   
