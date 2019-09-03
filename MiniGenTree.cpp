#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INFINITE 0xFFFFFFFF   
#define VertexData unsigned int  //��������
#define UINT  unsigned int
#define vexCounts 6  //��������
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
struct node
{
	VertexData data;
	unsigned int lowestcost;
}closedge[vexCounts]; //Prim�㷨�еĸ�����Ϣ
typedef struct
{
	VertexData u;
	VertexData v;
	unsigned int cost;  //�ߵĴ���
}Arc;  //ԭʼͼ�ı���Ϣ

void AdjMatrix(unsigned int adjMat[][vexCounts])  //�ڽӾ����ʾ��
{
	for (int i = 0; i < vexCounts; i++)   //��ʼ���ڽӾ���
	for (int j = 0; j < vexCounts; j++)
	{
		adjMat[i][j] = INFINITE;
	}
	adjMat[0][1] = 6; adjMat[0][2] = 1; adjMat[0][3] = 5;
	adjMat[1][0] = 6; adjMat[1][2] = 5; adjMat[1][4] = 3;
	adjMat[2][0] = 1; adjMat[2][1] = 5; adjMat[2][3] = 5; adjMat[2][4] = 6; adjMat[2][5] = 4;
	adjMat[3][0] = 5; adjMat[3][2] = 5; adjMat[3][5] = 2;
	adjMat[4][1] = 3; adjMat[4][2] = 6; adjMat[4][5] = 6;
	adjMat[5][2] = 4; adjMat[5][3] = 2; adjMat[5][4] = 6;
}

int Minmum(struct node * closedge)  //������С���۱�
{
	unsigned int min = INFINITE;
	int index = -1;
	for (int i = 0; i < vexCounts; i++)
	{
		if (closedge[i].lowestcost < min && closedge[i].lowestcost != 0)
		{
			min = closedge[i].lowestcost;
			index = i;
		}
	}
	return index;
}
void MiniSpanTree_Prim(unsigned int adjMat[][vexCounts], VertexData s)
{
	for (int i = 0; i < vexCounts; i++)
	{
		closedge[i].lowestcost = INFINITE;
	}
	closedge[s].data = s;      //�Ӷ���s��ʼ
	closedge[s].lowestcost = 0;
	for (int i = 0; i < vexCounts; i++)  //��ʼ����������
	{
		if (i != s)
		{
			closedge[i].data = s;
			closedge[i].lowestcost = adjMat[s][i];
		}
	}
	for (int e = 1; e <= vexCounts - 1; e++)  //n-1����ʱ�˳�
	{
		int k = Minmum(closedge);  //ѡ����С���۱�
		cout << vextex[closedge[k].data] << "--" << vextex[k] << endl;//���뵽��С������
		closedge[k].lowestcost = 0; //������Ϊ0��������һ������
		for (int i = 0; i < vexCounts; i++)  //����v�ж�����С���۱���Ϣ
		{
			if (adjMat[k][i] < closedge[i].lowestcost)
			{
				closedge[i].data = k;
				closedge[i].lowestcost = adjMat[k][i];
			}
		}
	}
}
void ReadArc(unsigned int  adjMat[][vexCounts], vector<Arc> &vertexArc) //����ͼ�ıߴ�����Ϣ
{
	Arc * temp = NULL;
	for (unsigned int i = 0; i < vexCounts; i++)
	{
		for (unsigned int j = 0; j < i; j++)
		{
			if (adjMat[i][j] != INFINITE)
			{
				temp = new Arc;
				temp->u = i;
				temp->v = j;
				temp->cost = adjMat[i][j];
				vertexArc.push_back(*temp);
			}
		}
	}
}

bool compare(Arc  A, Arc  B)
{
	return A.cost < B.cost ? true : false;
}

bool FindTree(VertexData u, VertexData v, vector<vector<VertexData> > &Tree)
{
	unsigned int index_u = INFINITE;
	unsigned int index_v = INFINITE;
	for (unsigned int i = 0; i < Tree.size(); i++)  //���u,v�ֱ������Ŀ���
	{
		if (find(Tree[i].begin(), Tree[i].end(), u) != Tree[i].end())
			index_u = i;
		if (find(Tree[i].begin(), Tree[i].end(), v) != Tree[i].end())
			index_v = i;
	}
	if (index_u != index_v)   //u,v����һ�����ϣ��ϲ�������
	{
		for (unsigned int i = 0; i < Tree[index_v].size(); i++)
		{
			Tree[index_u].push_back(Tree[index_v][i]);
		}
		Tree[index_v].clear();
		return true;
	}
	return false;
}

void MiniSpanTree_Kruskal(unsigned int adjMat[][vexCounts])
{
	vector<Arc> vertexArc;
	ReadArc(adjMat, vertexArc);//��ȡ����Ϣ
	sort(vertexArc.begin(), vertexArc.end(), compare);//�߰���С��������
	vector<vector<VertexData> > Tree(vexCounts); //6�ö�����
	for (unsigned int i = 0; i < vexCounts; i++)
	{
		Tree[i].push_back(i);  //��ʼ��6�ö���������Ϣ
	}
	for (unsigned int i = 0; i < vertexArc.size(); i++)//���δ�С����ȡ��С���۱�
	{
		VertexData u = vertexArc[i].u;
		VertexData v = vertexArc[i].v;
		if (FindTree(u, v, Tree))//���˱ߵ����������Ƿ���һ������
		{
			cout << vextex[u] << "---" << vextex[v] << endl;//�Ѵ˱߼��뵽��С��������
		}
	}
}

class base
{
public:
	//virtual void funcA(){ cout << "base::funcA" << endl; };
	//virtual void funcB(){ cout << "base::funcB" << endl; };
	int a;
};

class son : public base
{
public:
	void funcB(){ cout << "son::funcB" << endl; };
};

void test()
{
	base * p = new son;
	cout << "sizeof(base) : " << sizeof(base) << endl;
	cout << "sizeof(son) : " << sizeof(son) << endl;
	//p->funcB();
}


class CMyString
{
public:
	CMyString()
	{
		str = NULL;
		length = 0;
		cout << "this CMyString Construction" << endl;
	}

	CMyString(const char * tstr)
	{
		if (!tstr)
		{
			length = 1;
			str = new char[1];
			str[0] = '\0';
		}
		else
		{
			length = strlen(tstr);
			str = new char[length + 1];
			strcpy(str, tstr);
		}
	}

	~CMyString()
	{
		if (str != NULL)
		{
			delete[] str;
			str = NULL;
		}
	}

	int size() const;
	const char* c_str() const;

	CMyString(const CMyString & ms)
	{
		length = ms.size();
		str = new char[length + 1];
		strcpy(str, ms.c_str());
	}

	void show()
	{
		cout << "string: " << str << endl;
	}

	CMyString operator+(const CMyString &ms) const
	{
		CMyString ns;
		ns.length = length + ms.size();
		ns.str = new char[ns.length + 1];
		strcpy(ns.str, str);
		strcat(ns.str, ms.c_str());
		return ns;
	}

	CMyString& operator=(const CMyString &ms)
	{
		if (this == &ms) return *this;
		delete[] str;
		length = ms.size();
		str = new char(length + 1);
		strcpy(str, ms.c_str());
		return *this;
	}

	CMyString& operator+=(const CMyString &ms)
	{
		length += length + ms.size();
		char * tmp = new char[length + 1];
		strcpy(tmp, str);
		strcat(tmp, ms.c_str());
		delete[] str;
		str = tmp;
		return *this;
	}

	CMyString operator++(int)
	{

	}

private:
	char * str;
	int length;
};

inline const char* CMyString::c_str() const
{
	return str;
}

inline int CMyString::size() const
{
	return length;
}

class CInt
{
public:
	CInt operator++(int i)
	{

		return *this;
	}
private:
	int num;
};

int main_test()
{
#if 0
	unsigned int  adjMat[vexCounts][vexCounts] = { 0 };
	AdjMatrix(adjMat);   //�ڽӾ���
	cout << "Prim :" << endl;
	MiniSpanTree_Prim(adjMat, 0); //Prim�㷨���Ӷ���0��ʼ.
	cout << "-------------" << endl << "Kruskal:" << endl;
	MiniSpanTree_Kruskal(adjMat);//Kruskal�㷨
	test();
#else
	CMyString ms("this is a testing mystring");
	ms.show();
	cout << endl;
	CMyString m2s(ms);
	m2s.show();
	cout << endl;
	CMyString m3s = ms + m2s;
	m3s.show();
	m3s += ms;
	m3s.show();
	cout << endl;
	CMyString m4s = ms;
	m4s.show();
#endif
	return 0;
}
