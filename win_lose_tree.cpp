#include <iostream>
#include <vector>
#include <time.h>
#include <random>

using namespace std;

class wlTree
{
public:
	wlTree(int size);
	~wlTree();
	void createlsTree();
private:
	void adjust();
private:
	//int * m_node;
	int m_size;
	vector<int> m_ls;
	vector<int> m_data;
};

wlTree::wlTree(int size)
{
//	if (size > 0)
//		m_node = new int[size];
//	else
//		m_node = new int[100];
}

wlTree::~wlTree()
{
	//delete[] m_node;
}

void wlTree::adjust()
{

}

void wlTree::createlsTree()
{

}