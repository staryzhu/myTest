// STLExample.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <hash_map>
#include <algorithm>

using namespace std;


void testSizeOf()
{
	char *p;
	char a[10];
	char (*pa)[10];
	char *pb[10];
	printf("sizeof p:%d\n", sizeof(p));
	printf("sizeof a:%d\n", sizeof(a));
	printf("sizeof pa:%d\n", sizeof(pa));
	printf("sizeof pb:%d\n", sizeof(pb));
}

void testArgStack(int a, int b)
{
	char c = 0x12;
	char * p;
	void * pa;
	pa = (void *)&pa;
	p = (char *)&p;
	printf("First Argument a : %d, sizeof p:%d", *((int *)p),sizeof(p));
	//testArgStack(0x22, 0x33);
}

void printStr(string str)
{
	printf("out:%s\n", str.c_str());
}

int _tmain99(int argc, _TCHAR* argv[])
{
	std::map<int, vector<string>> mapvector;
	vector<string> vectorstring1;
	vectorstring1.push_back("abc");
	vectorstring1.push_back("def");
	vectorstring1.push_back("ghi");
	
	mapvector.insert(make_pair(1, vectorstring1));

	vector<string> vectorstring2;
	vectorstring2.push_back("jkl");
	vectorstring2.push_back("mon");
	vectorstring2.push_back("xyz");
	mapvector.insert(pair< int, vector<string>>(2, vectorstring2));
	//¶ÁÈ¡Êý¾Ý

	map<int, vector<string>>::iterator it = mapvector.find(22);
	if (it == mapvector.end())
	{
		printf("Can not find the target\n");
	}
	it = mapvector.find(2);
	if (it == mapvector.end())
	{
		printf("Can not find the target\n");
	}
	vector<string> pvs = it->second;
	vector<string>::iterator vit = pvs.begin();
	for (; vit != pvs.end(); vit++)
	{
		printf("the result: %s\n", (*vit).c_str());
		//cout << "Result :: " << *vit << endl;
		*vit = "zzz";
	}

	vector<string>* ppvs = &(it->second);
	vector<string>::iterator pvit = ppvs->begin();
	for (; pvit != ppvs->end(); pvit++)
	{
		printf("the result: %s\n", (*pvit).c_str());
		//cout << "Result :: " << *vit << endl;
		*pvit = "zzz";
	}
	for_each(ppvs->begin(), ppvs->end(), printStr);

	printf("Start Testing sizeof\n");
	testSizeOf();
	printf("Start Testing Push Stack\n");
	testArgStack(199, 100);
	return 0;
}

