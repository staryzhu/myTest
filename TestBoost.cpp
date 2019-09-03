#include <boost\bimap.hpp>
#include <string>
#include <iostream>
using namespace std;


int foo()
{
	int s = 9;
	return s;
}

void bar(const int &s)
{
	//s = 8;
}


void TestArrayPoint()
{
	char * aaa[1];
	char b = 'a';
	for (int i = 0; i < 10; i++)
	{
		aaa[i] = &(b);
	}

}
#if 0
int main()
{
	string str;
	TestArrayPoint();
	bar(foo());//
	typedef boost::bimap<std::string, int> bimap;
	bimap persons;
	persons.insert(bimap::value_type("zhuzhiguang", 12));
	persons.insert(bimap::value_type("zhuzhiguang2", 15));
	persons.insert(bimap::value_type("zhuzhiguang3", 119));
	cout << persons.left.at("zhuzhiguang3") << endl;
	cout << persons.right.count(119) << endl;
	return 0;
}
#endif