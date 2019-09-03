#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <queue>

using namespace std;

#define LINK_BASED_HEAP 

#ifdef LINK_BASED_HEAP

typedef struct Node{
	int data;
	Node *left;
	Node *right;
}Node;

#endif

class HeapSort
{
public:
	HeapSort(int size);
	~HeapSort();
	void sort();
private:
	void adjustHeap(int top, int heapLength);
private:
	int m_size;
	vector<int> m_vector_heap;

};

HeapSort::HeapSort(int size)
{
	m_size = size;
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		m_vector_heap.push_back(rand());
	}
	cout << "traverse the vector : " << endl;
	vector<int>::iterator it = m_vector_heap.begin();
	for (; it != m_vector_heap.end(); it++)
	{
		cout << *it << ",";
	}
}

HeapSort::~HeapSort()
{

}

void HeapSort::adjustHeap(int top, int heapLength)
{//big top heap
	int top_value = m_vector_heap[top];
	for (int i = top * 2 + 1; i < heapLength; i = i*2 + 1)
	{
		if ((i + 1 < heapLength) && (m_vector_heap[i] < m_vector_heap[i + 1]))
		{
			i++;
		}
		if (top_value < m_vector_heap[i])
		{
			m_vector_heap[top] = m_vector_heap[i];
			top = i;
		}
		else
		{
			break;
		}
	}
	m_vector_heap[top] = top_value;

}

void HeapSort::sort()
{
	for (int i = m_size / 2 - 1; i >= 0; i--)
	{
		adjustHeap(i, m_size);
	}

	for (int i = m_size - 1; i > 0; i--)
	{
		int tmp = m_vector_heap[i];
		m_vector_heap[i] = m_vector_heap[0];
		m_vector_heap[0] = tmp;
		adjustHeap(0, i);
	}
	//adjustHeap(0, m_size);
	vector<int>::iterator it = m_vector_heap.begin();
	cout << endl;
	cout << "Adjust Data : " << endl;
	for (; it != m_vector_heap.end(); it++)
	{
		cout << *it << ",";
	}
}


void testPriority_queue()
{
	srand(time(NULL));
	priority_queue<int> pq;
	for (int i = 0; i < 100; i++)
	{
		pq.push(rand() % 1000);
	}
	cout << endl;
	cout << "Priority Queue" << endl;
	while (!pq.empty())
	{
		int tmp = pq.top();
		pq.pop();
		cout << "," << tmp;
	}
}

#include <list>
#include <stack>

void testMinStack()
{
	list<int> ll;
	stack<list<int>::iterator> ms;
	srand(time(NULL));

	int val = rand() % 1000;
	list<int>::iterator it, top;
	it = ll.insert(ll.end(), val);
	ms.push(it);
	for (int i = 0; i < 50; i++)
	{
		//ll.push_back(rand() % 1000);
		val = rand() % 1000;
		it = ll.insert(ll.end(), val);
		top = ms.top();
		if (*top > *it)
		{
			ms.push(it);
		}
	}
	cout << endl;
	cout << "Welcome to test MinStack " << endl;
	list<int>::iterator ite = ll.begin();
	for (; ite != ll.end(); ite++)
	{
		cout << "," << *ite;
	}
	cout << endl;
	cout << "Find the min number in the stack" << endl;
	while (!ms.empty())
	{
		list<int>::iterator it = ms.top();
		ms.pop();
		cout << "," << *it;
	}

}

int main099()
{
	HeapSort hs(70);
	hs.sort();
	//testPriority_queue();
	testMinStack();
	return 0;
}