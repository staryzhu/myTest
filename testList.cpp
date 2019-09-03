//linklist.h：定义链表结点和方法。
#include <string>
using namespace std;

struct Info
{
	string name;	//姓名
	int id;		//学号
};
//链表定义
struct Node
{
	Info val;
	Node *next;
	Node(Info x) :val(x), next(NULL) {}
};

class LinkList
{
public:
	//构造函数
	LinkList();
	//在链表头部插入结点
	void InsertHead(Info val);
	//插入结点
	void Insert(Info val, int pos);
	//删除结点
	void Remove(Info val);
	//得到链表长度
	int Length();
	//链表反序
	void Reverse();
	//查找结点位置
	int Find(Info val);
	//打印链表
	void Print();
	//析构函数
	~LinkList();
private:
	Node *head;
	int length;
};

//然后，定义一个linklist.cpp文件，是链表方法的实现。如下所示：
//linklist.cpp：链表方法的实现。
#include "stdafx.h"
#include <iostream>
//#include "linklist.h"
using namespace std;

//构造函数
LinkList::LinkList()
{
	head = NULL;
	length = 0;
}

//析构函数
LinkList::~LinkList()
{
	Node *temp;
	for (int i = 0; i<length; i++)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

//得到链表长度
int LinkList::Length()
{
	return length;
}

//在链表头部插入结点
void LinkList::InsertHead(Info val)
{
	Insert(val, 0);
}

//插入结点
void LinkList::Insert(Info val, int pos)
{
	if (pos<0)
	{
		cout << "pos must be greater than zero" << endl;
		return;
	}
	int index = 1;
	Node *temp = head;
	Node *node = new Node(val);
	if (pos == 0)
	{
		node->next = temp;
		head = node;
		length++;
		return;
	}
	while (temp != NULL && index<pos)
	{
		temp = temp->next;
		index++;
	}
	if (temp == NULL)
	{
		cout << "Insert failed" << endl;
		return;
	}
	node->next = temp->next;
	temp->next = node;
	length++;
}

//删除结点
void LinkList::Remove(Info val)
{
	int pos = Find(val);
	if (pos == -1)
	{
		cout << "Delete failed" << endl;
		return;
	}
	if (pos == 1)
	{
		head = head->next;
		length--;
		return;
	}
	int index = 2;
	Node *temp = head;
	while (index < pos)
		temp = temp->next;
	temp->next = temp->next->next;
	length--;
}

//查找结点位置
int LinkList::Find(Info val)
{
	Node *temp = head;
	int index = 1;
	while (temp != NULL)
	{
		if (temp->val.name == val.name && temp->val.id == val.id)
			return index;
		temp = temp->next;
		index++;
	}
	return -1; //不存在返回-1
}

//链表反序
void LinkList::Reverse()
{
	if (head == NULL)
		return;
#ifdef changed
	Node *curNode = head, *nextNode = head->next, *temp = NULL;
	while (nextNode != NULL)
	{
		temp = nextNode->next;
		nextNode->next = curNode;
		curNode = nextNode;
		nextNode = temp;
	}
	head->next = NULL;
#else
	Node *curNode = NULL, *nextNode = head, *temp = NULL;
	while (nextNode != NULL)
	{
		temp = nextNode->next;
		nextNode->next = curNode;
		curNode = nextNode;
		nextNode = temp;
	}
#endif
	head = curNode;
}

//打印链表
void LinkList::Print()
{
	if (head == NULL)
	{
		cout << "LinkList is empty" << endl;
		return;
	}
	Node *temp = head;
	while (temp != NULL)
	{
		cout << temp->val.name << "," << temp->val.id << endl;
		temp = temp->next;
	}
	cout << endl;
}
//最后，定义一个main.cpp，用来测试链表功能，如下所示：
// main.cpp : 测试链表功能。
#include "stdafx.h"
#include <iostream>
#include <string>
//#include "linklist.h"
using namespace std;

int _tmain00(int argc, _TCHAR* argv[])
{
	LinkList head;
	Info val1, val2, val3, val4;
	val1.id = 1, val1.name = "Kevin", val2.id = 2, val2.name = "Cathy", val3.id = 3, val3.name = "Lucy", val4.id = 4, val4.name = "Gravin";

	//测试插入功能
	cout << "Insert test:" << endl;
	head.InsertHead(val1);
	head.Print();
	head.Insert(val2, 1);
	head.Print();
	head.Insert(val3, 4);
	head.Print();
	head.InsertHead(val3);
	head.Insert(val4, 2);
	head.Print();

	//测试反序功能
	cout << "reverse test:" << endl;
	head.Reverse();
	cout << "reversed linklist is:" << endl;
	head.Print();

	//测试删除功能
	cout << "remove test:" << endl;
	cout << "the length of linklist is:" << endl;
	cout << head.Length() << endl;
	head.Remove(val4);
	head.Print();
	cout << "the length of linklist is:" << endl;
	cout << head.Length() << endl;
	head.Remove(val4);
	head.Print();
	return 0;
}