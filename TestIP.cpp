#include <iostream>

using namespace std;

#include <iostream>
#include <memory>
using namespace std;

class A{
public:
	A(int x = 0) :m_x(x){
		cout << "A����" << endl;
	}
	~A(){
		cout << "A����" << endl;
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
	/*pa����ᱻ�ͷ�,һ�ֻ���ʹ��pa���ͷŵ��¶��ڴ���ͷ�
	���Բ�����һ����ָͨ��������pa����һ���������� */
	//A * pa = new A(123);
	auto_ptr<A> pa(new A(123));
	pa->print();
	//delete pa;
	/*����ָ������⣬ȱ����������,��ָͨ��϶�û����*/
	auto_ptr<A> pb = pa;//��������
	pb->print();
	/*�δ���*/
	pa->print();
}

/*����ָ����������������*/
void test3(){
	auto_ptr<A> pa(new A[3]);//����ת�棬��ӳ�����
	/*Ϊʲô����ָ�벻�ܹ����������*/
}

void test4(){
	unique_ptr<A[]> pa(new A[3]);//����������
}

void test5(){
	unique_ptr<A> pa(new A);
	//unique_ptr<A> pb = pa;//�޷�����ֵ
	unique_ptr<A> pb = move(pa);
}

void test6(){
	shared_ptr<A> pa(new A[3], [](A *p) { delete[] p; });//lambda��������
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
	//���ݲ�ͬ����λ�����ӿ츳ֵ�ٶȣ���charתΪint��32bit�����е��θ�ֵ
	//int wordnum = num / 4;//�����ж��ٸ�32λ����4�ֽڿ���  
	//int slice = num % 4;//ʣ��İ��ֽڿ���  
	//int * pintsrc = (int *)src;
	//int * pintdst = (int *)dst;
	//while (wordnum--)*pintdst++ = *pintsrc++;
	//while (slice--)*((char *)pintdst++) = *((char *)pintsrc++);
	//return dst;
	void *ret = dst;

	if (dst <= src || (char *)dst >= (char *)src + len){
		//û���ڴ��ص����ӵ͵�ַ��ʼ����
		while (len--){
			*(char *)dst = *(char *)src;
			dst = (char *)dst + 1;
			src = (char *)src + 1;
		}
	}
	else{
		//���ڴ��ص����Ӹߵ�ַ��ʼ����
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
	CGUARDMEM(T * ptr, bool isArray = false/*�Ƿ�Ϊ����*/){ m_ptr = ptr; m_isArray = isArray; };
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
	cout << "1�ĸ�����" << NumberOf1Solution3(1000) << endl;
	cout << "main������ʼ��" << endl;
	test6();
	cout << "main��������" << endl;
	return 0;
}
