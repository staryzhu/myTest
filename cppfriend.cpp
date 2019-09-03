#include <iostream>
#include <string>
#include <assert.h>

using namespace std;


class clsA
{
	friend clsA &operator+(clsA &a, clsA &b);
	friend void printSize(clsA &inst);
	friend class clsB;
private:
	int size;
	void showA(char * pinfo){ cout << "info: " << pinfo << endl; };

public:
	clsA(){ size = 0; };
	clsA(int nsize){ size = nsize; };
	~clsA(){};
	void print(){ cout << "Size : " << size << endl; };

};


clsA &operator+(clsA &a, clsA &b)
{
	clsA tmp(0);
	tmp.size = a.size + b.size;
	return tmp;
}

//
class clsB
{
public:
	void showA()
	{
		clsA a;
		a.showA("test class friend");
	};
};



void printSize(clsA &inst)
{
	cout << "Instance Size :" << inst.size << endl;
	inst.showA("just a test");
}

char *my_memcpy(char *dst, const char* src, int cnt)
{
	assert(dst != NULL && src != NULL);

	char *ret = dst;

	if (dst >= src && dst <= src + cnt - 1) //内存重叠，从高地址开始复制
	{
		dst = dst + cnt - 1;
		src = src + cnt - 1;
		while (cnt--)
			*dst-- = *src--;
	}
	else    //正常情况，从低地址开始复制
	{
		while (cnt--)
			*dst++ = *src++;
	}

	return ret;
}

char * my_strcpy(char *dst, const char *src)
{
	assert(dst != NULL && src != NULL);

	char *ret = dst;

	my_memcpy(dst, src, strlen(src) + 1);

	return ret;
}

void show_word(char * str)
{
	if (str == NULL)
		return;
	char *p = strtok(str, " ");
	while (p != NULL)
	{
		cout << "split word : " << p << endl;
		p = strtok(NULL, " ");
	}
}

#define MEMGUARD(type, name)\
class CMemGuard##name\
{\
private:\
	type * ptr; \
public:\
	CMemGuard##name(type * name)\
{\
	ptr = name; \
}\
	~CMemGuard##name()\
{\
	cout << "delete" << endl;\
		if(ptr) delete[] ptr; \
	}\
}; \
CMemGuard##name tmp##name(name);

union uncode{
	int i;
	char ch[2];
};

void show()
{
	uncode aa;
	aa.i = 0;
	aa.ch[0] = 0x01;
	aa.ch[1] = 0x01;
	cout << "aa.i : " << aa.i << endl;
}

void testSplitNum(int sample)
{
	int tmp = sample;
	while (tmp)
	{
		cout << "num : " << tmp % 10 << endl;
		tmp = tmp / 10;
	}
}

int main(void)
{
	clsA A(9999);
	printSize(A);
	clsB B;
	B.showA();
	clsA AA(12);
	A.print();
	AA.print();
	clsA AAA = A + AA;
	AAA.print();

	char str[] = "do you have money";
	char *ppp = NULL;
	cout << "ppp address: " << &ppp << endl;
	cout << "str address: " << &str << endl;
	ppp = new char[strlen(str) + 1];
	MEMGUARD(char, ppp)
	my_strcpy(ppp, str);
	cout << "copy str: " << ppp << endl;
	//clsC C;
	//C.showC(A);
	show_word(ppp);
	//delete[] ppp;
	show();

	testSplitNum(2345);
	return 0;
}