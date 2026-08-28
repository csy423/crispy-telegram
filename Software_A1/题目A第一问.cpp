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