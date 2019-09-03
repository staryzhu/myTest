#include <list>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;


typedef struct Node {
	string name;
	list<struct Node *> neibors;
	Node(const string & strName){
		name = strName;
	};
} Node;

class CGraph{
public:
	CGraph(){};
	~CGraph();
	void addNode(const string & fatherName, const string & name);
	void recurveDFS(const string &startName);
	void recurveFuc(set<string> &visited, Node *node);
	void commonDFS(const string &startName);
	void BFS(const string &startName);

private:
	Node * getNode(const string & name);

private:
	list<Node *> nodeList;
};

CGraph::~CGraph()
{
	for (list<Node *>::iterator it = nodeList.begin(); it != nodeList.end(); it++)
	{
		Node *tmp = *it;
		it = nodeList.erase(it);
		delete tmp;
		if (it != nodeList.end())
			break;
	}
	cout << "~end testing" << endl;
}

Node *CGraph::getNode(const string & name)
{
	list<Node*>::iterator it = nodeList.begin();
	for (; it != nodeList.end(); it++)
	{
		if ((*it)->name == name)
		{
			break;
		}
	}
	if (it == nodeList.end())
	{
		return NULL;
	}
	return (*it);
}


void CGraph::addNode(const string & fatherName, const string & name)
{
	Node * childNode = getNode(name);
	Node * fatherNode = getNode(fatherName);

	if (childNode == NULL)
	{
		childNode = new Node(name);
		nodeList.push_back(childNode);
	}
	if (fatherNode == NULL)
	{
		cout << "Create a Father Father Node " << endl;
	}
	else
	{
		fatherNode->neibors.push_back(childNode);
	}
	
}

void CGraph::BFS(const string &startName)
{
	list<Node*>::iterator it = nodeList.begin();
	for (; it != nodeList.end(); it++)
	{
		if ((*it)->name == startName)
		{
			break;
		}
	}

	if (it == nodeList.end())
	{
		cout << "Can not find node" << startName << endl;
		return;
	}

	pair<set<string>::iterator, bool> ret;
	set<string> visited;
	queue<Node *> que;
	que.push(*it);
	while (!que.empty())
	{
		Node * fatherNode = que.front();
		que.pop();
		ret = visited.insert(fatherNode->name);
		if (!ret.second)
			continue;
		cout << "BFS Value: " << fatherNode->name << endl;
		list<Node *>::iterator it = fatherNode->neibors.begin();
		for (; it != fatherNode->neibors.end(); it++)
		{
			que.push(*it);
		}
	}

}

void CGraph::commonDFS(const string &startName)
{
	list<Node*>::iterator it = nodeList.begin();
	for (; it != nodeList.end(); it++)
	{
		if ((*it)->name == startName)
		{
			break;
		}
	}

	if (it == nodeList.end())
	{
		cout << "Can not find node" << startName << endl;
		return;
	}

	set<string> visited;
	stack<Node*> sta;

	visited.insert((*it)->name);
	sta.push((*it));
	Node * fatherall = *it;
	cout << "Get Value : " << fatherall->name << endl;
	it = fatherall->neibors.begin();
	if (it == fatherall->neibors.end())
		return;
	while (true)
	{
		pair<set<string>::iterator, bool> ret = visited.insert((*it)->name);
		if (ret.second)
		{
			cout << "Get Value : " << (*it)->name << endl;
			list<Node *> neib = (*it)->neibors;
			list<Node *>::iterator pbegin = neib.begin();
			if (pbegin != neib.end())
			{
				sta.push(*it);
				it = pbegin;
				continue;
			}
		}
		if (sta.empty())
			break;
		Node * fatherNode = sta.top();
		sta.pop();
		list<Node*>::iterator child_it = ++it;
		if (child_it != fatherNode->neibors.end())
		{
			it = child_it;
		}
	}
}

void CGraph::recurveFuc(set<string> &visited, Node *node)
{
	
	pair<set<string>::iterator, bool> ret = visited.insert(node->name);
	if (ret.second)
	{
		cout << "get value : " << node->name << endl;
	}
	else
		return;
	list<Node *>::iterator it = node->neibors.begin();
	for (; it != node->neibors.end(); it++)
	{
		recurveFuc(visited, *it);
	}
}

void CGraph::recurveDFS(const string &startName)
{
	list<Node*>::iterator it = nodeList.begin();
	for (; it != nodeList.end(); it++)
	{
		if ((*it)->name == startName)
		{
			break;
		}
	}

	if (it == nodeList.end())
	{
		cout << "Can not find node" << startName << endl;
	}

	set<string> visited;
	recurveFuc(visited, *it);

}


int main98()
{
	CGraph g;
	g.addNode("none", "1");
	g.addNode("1", "2");
	g.addNode("1", "3");
	g.addNode("1", "4");
	g.addNode("2", "5");
	g.addNode("2", "6");
	g.addNode("3", "7");
	g.addNode("4", "7");
	g.recurveDFS("1");
	//cout << "Common method to traversal graph" << endl;
	//g.commonDFS("1");
	cout << "BFS Traverse all Graph" << endl;
	g.BFS("1");
	return 0;
}