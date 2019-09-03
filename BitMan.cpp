#include<iostream>
#include<cstdlib>
using namespace std;

//递归版本的加法实现
int Add(int a, int b)
{
	return b ? Add(a^b, (a&b) << 1) : a;
	/*
	if(b)
	return plus_rec(a^b, (a&b)<<1);
	else
	return a;
	*/
}

//该为迭代版本
int Add_iter(int a, int b)
{
	int ans;
	while (b)
	{
		ans = a^b;
		b = (a&b) << 1;
		a = ans;
	}
	return ans;
}

//求a的相反数：将各位取反加一
int negative(int a)     //get -a
{
	return Add(~a, 1);
}

int Minus(int a, int b)
{
	return Add(a, negative(b));
}

//正数乘法
int Multi(int a, int b)
{
	int ans = 0;
	while (b)
	{
		if (b & 1)
			ans = Add(ans, a);
		a = a << 1;
		b = b >> 1;
	}
	return ans;
}

//正数除法
int Divide(int a, int b)
{
	int coun = 0;
	while (a >= b)
	{
		a = Minus(a, b);
		coun = Add(coun, 1);
	}
	return coun;
}

//判断是否是负数，0，正数
int isneg(int a)
{
	return a & 0x8000;
}
int iszero(int a)
{
	return !(a & 0xFFFF);
}
int ispos(int a)
{
	return (a & 0xFFFF) && !(a & 0x8000);
}

//处理负数的乘法和除法
int My_Multi(int a, int b)
{
	if (iszero(a) || iszero(b))
		return 0;
	if (isneg(a))
	{
		if (isneg(b))
			return Multi(negative(a), negative(b));
		else
			return negative(Multi(negative(a), b));
	}
	else if (isneg(b))
		return negative(Multi(a, negative(b)));
	else
		return Multi(a, b);
}

int My_Divide(int a, int b)
{
	if (iszero(b))
	{
		cout << "Error!" << endl;
		exit(1);
	}
	if (iszero(a))
		return 0;
	if (isneg(a))
	{
		if (isneg(b))
			return Divide(negative(a), negative(b));
		else
			return negative(Divide(negative(a), b));
	}
	else if (isneg(b))
		return negative(Divide(a, negative(b)));
	else
		return Divide(a, b);

}

int mainbb(int argc, char **argv)
{
	int a = 5;
	int aa = -5;
	int b = 3;
	int bb = -3;
	int c = 15;
	cout << Add(a, b) << endl;
	cout << Add(a, bb) << endl;
	cout << Minus(a, b) << endl;
	cout << Minus(b, a) << endl;
	cout << Multi(a, b) << endl;
	cout << My_Multi(aa, b) << endl;
	cout << Divide(c, a) << endl;

	return 0;
}