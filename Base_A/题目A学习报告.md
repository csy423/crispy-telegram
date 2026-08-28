# 题目A



## 第一问



我在大学前并没有学习过编程，在大一上的c语言课堂上，我第一次接触到编程。我发现了我喜欢在课后自己琢磨老师的课后习题，喜欢去写一段代码，实现自己的目标，这个过程很有趣。我在大一下曾自学c语言的数论和图论，备考蓝桥杯，可惜未能获得奖项。这个暑假，我转战c++，我是看的b站上的黑马程序员up主的那个视频，帮我一点点入门。

[黑马程序员](https://www.bilibili.com/read/cv7881295/)

这是我在自学后的第一段代码,按照自我的数学逻辑设计，先通分，再计算，再约分。然而这样会有许多问题，1.浪费大量的空间。2.

改变了计算初值。3.不能处理负数 4.封装功能差。

：

c++

```
#include<iostream>
using namespace std;
#include<string>
class calculater
{
public:
	//设置通分辅助函数
	void tongfen(calculater& a, calculater& b)
	{
		//保留其中一个分母的初值
		long MU;
		MU = a.m_mu;
		//最大化通分，因为后面可以约分
		a.m_mu = a.m_mu * b.m_mu;
		a.m_zi= a.m_zi * b.m_mu;
		b.m_mu = b.m_mu * MU;
		b.m_zi = b.m_zi * MU;

	}
	//设置约分辅助函数
	void yuefen(calculater& a)
	{
		//用辗转相除法，先求出最大公约数
		long m;
		long max = a.m_zi> a.m_mu ? a.m_zi : a.m_mu;
		long min = a.m_zi < a.m_mu ? a.m_zi : a.m_mu;
		while (min != 0)
		{
			m = max % min;
			max = min;
			min = m;
		}
		//再约分
		a.m_zi /= max;
		a.m_mu /= max;
	}
	//重载加法
	calculater operator+(calculater &a)
	{
		//先通分，再计算，最后约分
		calculater temp;
		calculater:: tongfen(*this,a);
		temp.m_zi = this->m_zi + a.m_zi;
		temp.m_mu = a.m_mu;
		calculater::yuefen(temp);
		return temp;
	}
	//重载减法
	calculater operator-(calculater& a)
	{
		//先通分，再计算，最后约分
		calculater temp;
		calculater::tongfen( *this,a);
		temp.m_zi = this->m_zi - a.m_zi;
		temp.m_mu = a.m_mu;
		calculater::yuefen(temp);
		return temp;
	}
	//重载乘法
	calculater operator*(calculater& a)
	{
		//直接相乘后约分
		calculater temp;
		temp.m_zi = this->m_zi * a.m_zi;
		temp.m_mu = this->m_mu * a.m_mu;
		calculater::yuefen(temp);
		return temp;
	}
	//重载除法
	calculater operator/(calculater& a)
	{
		//直接相除后约分
		calculater temp;
		temp.m_zi = this->m_zi * a.m_mu;
		temp.m_mu = this->m_mu * a.m_zi;
		calculater::yuefen(temp);
		return temp;
	}
	//获取数据
	void set(long a,long b)
	{
		m_zi = a;
		m_mu = b;
	}
	//打印数据
	void print()
	{
		if(m_mu==1)
			cout << m_zi << endl;
		else
		cout << m_zi << "/" << m_mu << endl;

	}


private:
	long m_zi;
	long m_mu;
};


int main(void)
{
	calculater num1,num2,result;
	long a, b;
	char c;
	//输入
	cout << "请输入第一个数的分子" << endl;
	cin >> a;
	cout << "请输入第一个数的分母" << endl;
	cin >> b;
	//分母为零，报错
	if (b == 0)
	{
		cout << "分母为零，请重新输入分母" << endl;
		return 0;
	}
	cout << "请输入符号" << endl;
	cin >> c;
	num1.set(a, b);
	cout << "请输入第二个数的分子" << endl;
	cin >> a;
	cout << "请输入第二个数的分母" << endl;
	cin >> b;
	//分母为零，报错
	if (b == 0)
	{
		cout << "分母为零，请重新输入分母" << endl;
		return 0;
	}
	num2.set(a, b);
	//判断运算符号，并计算
	switch (c)
	{
	case '+':
		{
		result = num1 + num2;
		break;
		}
	case '-':
	{
		result = num1 - num2;
		break;
	}case '*':
	{
		result = num1 * num2;
		break;
	}case '/':
	{
		result = num1 / num2;
		break;
	default:
		{
		cout << "请输入合法的计算符号" << endl;
		return;
		}
	}
	

	}
	//打印
	result.print();
}
```

在深入学习后，我学会了用const保护数据，用副本复制原值去代替原来数据计算，将求最大公约数分离出来额外做一个函数gcd，既更加简便，又可以处理负数，还有最重要的就是补上了有参构造函数。在改进中，我根据豆包的指点一点一点修改自己的错误，学习各种知识点，学习编程思维而不是数学思维去写代码。但是我仍然觉得我的代码有一点冗杂，希望以后可以设计出更好的程序。

```c++
#include<iostream>
#include<cstdlib>
using namespace std;

class Rational
{
public:
    // 构造函数重载
    // 无参构造，默认0/1
    Rational()
    {
        m_zi = 0;
        m_mu = 1;
    }

    // 带参构造函数，当分母为零时报错，且将约分
    Rational(long zi, long mu)
    {
        if (mu == 0)
        {
            cout << "错误：分母不能为0，已置为0/1" << endl;
            m_zi = 0;
            m_mu = 1;
            return;
        }
        m_zi = zi;
        m_mu = mu;
        yuefen(*this);
    }

    // 设置数据
    void set(long zi, long mu)
    {
        //保证数据安全
        if (mu == 0)
        {
            cout << "错误：分母不能为0，赋值失败" << endl;
            return;
        }
        m_zi = zi;
        m_mu = mu;
        yuefen(*this);
    }

    //获得数据 ，保证数据安全
    long getZi() const { return m_zi; }
    long getMu() const { return m_mu; }

    // 重载加法，const，不修改原对象
    Rational operator+(const Rational& a) const
    {
        Rational t1 = *this;
        Rational t2 = a;
        tongfen(t1, t2);
        return Rational(t1.m_zi + t2.m_zi, t1.m_mu);
    }

    // 重载减法
    Rational operator-(const Rational& a) const
    {
        Rational t1 = *this;
        Rational t2 = a;
        tongfen(t1, t2);
        return Rational(t1.m_zi - t2.m_zi, t1.m_mu);
    }

    // 重载乘法
    Rational operator*(const Rational& a) const
    {
        return Rational(m_zi * a.m_zi, m_mu * a.m_mu);
    }

    // 重载除法
    Rational operator/(const Rational& a) const
    {
        if (a.m_zi == 0)
        {
            cout << "错误：除数不能为0" << endl;
            return Rational(0, 1);
        }
        return Rational(m_zi * a.m_mu, m_mu * a.m_zi);
    }

    // 输出，当分子可以整除分母时候，输出分子
    void print() const
    {
        if (m_mu == 1)
            cout << m_zi << endl;
        else
            cout << m_zi << "/" << m_mu << endl;
    }

private:
    long m_zi;   //分子
    long m_mu;   //分母

    // 用辗转相除法找到最大公约数
    long gcd(long a, long b) const
    {
        a = abs(a);
        b = abs(b);
        while (b != 0)
        {
            long m = a % b;
            a = b;
            b = m;
        }
        return a;
    }

    //通分
    void tongfen(Rational& a, Rational& b) const
    {
        //保留原来的分母
        long oldMuA = a.m_mu;
        long oldMuB = b.m_mu;
        long gys = gcd(oldMuA, oldMuB);
        long gbs = oldMuA / gys * oldMuB;

        a.m_zi = a.m_zi * (gbs / oldMuA);
        a.m_mu = gbs;

        b.m_zi = b.m_zi * (gbs / oldMuB);
        b.m_mu = gbs;
    }

    //约分，分母恒正
    void yuefen(Rational& a)
    {
        long gys = gcd(a.m_zi, a.m_mu);
        a.m_zi /= gys;
        a.m_mu /= gys;
        if (a.m_mu < 0)
        {
            a.m_zi = -a.m_zi;
            a.m_mu = -a.m_mu;
        }
    }
};


int main(void)
{
    Rational num1, num2, result;
    long a, b;
    char c;
    //输入
    cout << "请输入第一个数的分子" << endl;
    cin >> a;
    cout << "请输入第一个数的分母" << endl;
    cin >> b;
    if (b == 0)
    {
        cout << "分母为零，程序退出" << endl;
        return 0;
    }
    num1.set(a, b);

    cout << "请输入符号" << endl;
    cin >> c;

    cout << "请输入第二个数的分子" << endl;
    cin >> a;
    cout << "请输入第二个数的分母" << endl;
    cin >> b;
    if (b == 0)
    {
        cout << "分母为零，程序退出" << endl;
        return 0;
    }
    num2.set(a, b);

    switch (c)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2.getZi() == 0)
        {
            cout << "除数不能为0，程序退出" << endl;
            return 0;
        }
        result = num1 / num2;
        break;
    default:
        cout << "请输入合法的计算符号" << endl;
        return 0;
    }

    result.print();
    return 0;
}
```

## 题目二



这个题目在我看的网课中，在第57节课中有相似的结构，我按照那个结构依葫芦画瓢，很快就写出了我的写了代码，运行效果还不错。这一次，我记住了要规范数据，如数据一定为正，三角形形成的要求。因此特地加了jianyan（）函数来检验，在这道题中，我遇到最大的问题就是将检验函数放在哪里，最后我决定用成员函数，一开始，我把检验函数放进setShut（）函数里面，但是这样不能让整个流程停下来，面积和周长将会变成乱码，最后，我想到可以把检验函数放进整个流程进去判断，这样就可以让整个程序在输入数据有误后停止。在注释的过程中，我对代码的注释还不大熟练，往往不知道要写什么上去，对一些专业术语还有待学习。



```c++
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
```



