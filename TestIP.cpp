#include <iostream>

using namespace std;

#include <iostream>
#include <memory>
using namespace std;

class A{
public:
	A(int x = 0) :m_x(x){
		cout << "A构造" << endl;
	}
	~A(){
		cout << "A析构" << endl;
	}
	void print()const{
		cout << m_x << endl;
	}
private:
	int m_x;
};

void test1(){
	A * pa = new A(123);
	pa->print();
	delete pa;
}


void test2(){
	/*pa本身会被释放,一种机制使得pa的释放导致堆内存的释放
	所以不再让一个普通指针来保存pa，用一个类来保存 */
	//A * pa = new A(123);
	auto_ptr<A> pa(new A(123));
	pa->print();
	//delete pa;
	/*智能指针的问题，缺乏拷贝语义,普通指针肯定没问题*/
	auto_ptr<A> pb = pa;//拷贝构造
	pb->print();
	/*段错误*/
	pa->print();
}

/*智能指针管理多个对象的问题*/
void test3(){
	auto_ptr<A> pa(new A[3]);//核心转存，解映射出错
	/*为什么智能指针不能管理对象数组*/
}

void test4(){
	unique_ptr<A[]> pa(new A[3]);//传入数组标记
}

void test5(){
	unique_ptr<A> pa(new A);
	//unique_ptr<A> pb = pa;//无法被赋值
	unique_ptr<A> pb = move(pa);
}

void test6(){
	shared_ptr<A> pa(new A[3], [](A *p) { delete[] p; });//lambda析构过程
	//shared_ptr<A[]> pb = pa;

}

int NumberOf1Solution3(int n)
{
	int count = 0;

	while (n > 0)
	{
		count++;
		n = (n - 1) & n;
	}

	return count;
}

void *abc_memcpy(void *dst, const void *src, size_t len)
{
	if (NULL == dst || NULL == src){
		return NULL;
	}
	//根据不同总线位数，加快赋值速度，将char转为int（32bit）进行单次赋值
	//int wordnum = num / 4;//计算有多少个32位，按4字节拷贝  
	//int slice = num % 4;//剩余的按字节拷贝  
	//int * pintsrc = (int *)src;
	//int * pintdst = (int *)dst;
	//while (wordnum--)*pintdst++ = *pintsrc++;
	//while (slice--)*((char *)pintdst++) = *((char *)pintsrc++);
	//return dst;
	void *ret = dst;

	if (dst <= src || (char *)dst >= (char *)src + len){
		//没有内存重叠，从低地址开始复制
		while (len--){
			*(char *)dst = *(char *)src;
			dst = (char *)dst + 1;
			src = (char *)src + 1;
		}
	}
	else{
		//有内存重叠，从高地址开始复制
		src = (char *)src + len - 1;
		dst = (char *)dst + len - 1;
		while (len--){
			*(char *)dst = *(char *)src;
			dst = (char *)dst - 1;
			src = (char *)src - 1;
		}
	}
	return ret;
}
#include<vector>
int main12()
{
	vector<int> cv;

	for (int i = 1; i < 12; i++)
		cv.push_back(i * i);
	cout << "get cv[9]:" << cv[9] << endl;
	return 0;
}


template <class T> T max(T const& a, T const& b)
{
	return a > b ? a : b;
}

template <class T> class CGUARDMEM
{
public:
	CGUARDMEM(T * ptr, bool isArray = false/*是否为数组*/){ m_ptr = ptr; m_isArray = isArray; };
	~CGUARDMEM(){
		if (m_ptr != NULL)
		{
			if (!m_isArray){
				delete m_ptr;
			}
			else
			{
				delete []m_ptr;
			}
			m_ptr = NULL;
			cout << "Delete m_ptr" << endl;
		}
	}
private:
	bool m_isArray;
	T *m_ptr;
};

#define GUARDMEM(type,content) CGUARDMEM<type> mem##content(content)
#define GUARDARRAY(type,content) CGUARDMEM<type> mem##content(content, true)

class example
{
public:
	example(){ cout << "Default Construct " << endl; };
	example(char a)
	{
		cout << " got char : " << a << endl;
	};
	~example(){ cout << " Delete example " << endl; };
};


int mainss(){
	main12();
	example * p = new example('a');
	example * pp = new example[5];
	GUARDMEM(example, p);
	GUARDARRAY(example, pp);
	cout << "11 and 12 max : " << max(11, 12) << endl;
	cout << "11.0 and 12.0 max : " << max(11.0, 12.0) << endl;
	cout << "1的个数：" << NumberOf1Solution3(1000) << endl;
	cout << "main函数开始了" << endl;
	test6();
	cout << "main函数结束" << endl;
	return 0;
}
