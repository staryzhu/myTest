//linklist.h������������ͷ�����
#include <string>
using namespace std;

struct Info
{
	string name;	//����
	int id;		//ѧ��
};
//������
struct Node
{
	Info val;
	Node *next;
	Node(Info x) :val(x), next(NULL) {}
};

class LinkList
{
public:
	//���캯��
	LinkList();
	//������ͷ��������
	void InsertHead(Info val);
	//������
	void Insert(Info val, int pos);
	//ɾ�����
	void Remove(Info val);
	//�õ�������
	int Length();
	//������
	void Reverse();
	//���ҽ��λ��
	int Find(Info val);
	//��ӡ����
	void Print();
	//��������
	~LinkList();
private:
	Node *head;
	int length;
};

//Ȼ�󣬶���һ��linklist.cpp�ļ�������������ʵ�֡�������ʾ��
//linklist.cpp����������ʵ�֡�
#include "stdafx.h"
#include <iostream>
//#include "linklist.h"
using namespace std;

//���캯��
LinkList::LinkList()
{
	head = NULL;
	length = 0;
}

//��������
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

//�õ�������
int LinkList::Length()
{
	return length;
}

//������ͷ��������
void LinkList::InsertHead(Info val)
{
	Insert(val, 0);
}

//������
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

//ɾ�����
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

//���ҽ��λ��
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
	return -1; //�����ڷ���-1
}

//������
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

//��ӡ����
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
//��󣬶���һ��main.cpp���������������ܣ�������ʾ��
// main.cpp : ���������ܡ�
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

	//���Բ��빦��
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

	//���Է�����
	cout << "reverse test:" << endl;
	head.Reverse();
	cout << "reversed linklist is:" << endl;
	head.Print();

	//����ɾ������
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