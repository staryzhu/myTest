#include <iostream>
using namespace std;

typedef int Keytype;
const int NULLKEY = 0;  //表示该位置无值

//链地址法中的节点结构体
struct Hash_List
{
	Keytype e;
	Hash_List *next;
};

class Hash_Table
{
private:
	Hash_List *hashlist;
	int  hash_length;
public:
	Hash_Table()
	{
		int i;
		//初始化hash表大小为11
		hash_length = 10;
		hashlist = new Hash_List[hash_length];
		if (!hashlist)
		{
			cout << "内存申请失败" << endl;
			exit(0);
		}
		for (i = 0; i<hash_length; i++)
		{
			hashlist[i].e = NULLKEY;
			hashlist[i].next = NULL;
		}
	}

	~Hash_Table()
	{
		delete[]hashlist;
		hashlist = NULL;
	}

	unsigned Hash(Keytype k)  //hash函数(取模法)
	{
		return (k%hash_length);
	}

	bool Search_hash(Keytype k, int &p)
	{
		p = Hash(k);
		Hash_List *t = &hashlist[p];
		while (t && t->e != k)
			t = t->next;
		if (t && t->e == k)
			return true;
		return false;
	}

	int Insert_hash(Keytype e)
	{
		int p = -1;
		Hash_List *l = NULL;
		if (Search_hash(e, p))
			return -1;
		else
		{
			l = new Hash_List;
			l->e = e;
			l->next = hashlist[p].next;
			hashlist[p].next = l;
			return 1;
		}
	}

	void Traverse_HashTable()
	{
		Hash_List *p;
		cout << "哈希表中所有元素为(按对10取余后的余数归表)：" << endl;
		for (int i = 0; i<hash_length; i++)
		{
			cout << i << ": ";
			p = &hashlist[i];
			while (p)
			{
				if (p->e != NULLKEY)
					cout << p->e << "  ";
				p = p->next;
			}
			cout << endl;
		}
		cout << endl;
	}

};

int main0()
{
	int n, i;
	Keytype *r, key;
	Hash_Table HT;
	cout << "输入你要输入多少个元素来初始化hash表：";
	cin >> n;
	if (n>0)
	{
		r = new Keytype[n];
		cout << "输入 " << n << "个整数：" << endl;
		for (i = 0; i<n; i++)
			cin >> r[i];
		for (int i = 0; i<n; i++)
		{
			if (HT.Insert_hash(r[i]) == -1)
				cout << "该元素 " << r[i] << " 已存在，不重复插入" << endl;
		}
		HT.Traverse_HashTable();
		cout << endl;

		cout << "输入你要查找的数(输入-1退出查找)：";
		while (cin >> key)
		{
			if (key == -1)
				break;
			if (HT.Search_hash(key, i))
				cout << "该元素存在hash表的第 " << i + 1 << " 个子表中" << endl;
			else
				cout << "该元素不存在表中" << endl;
		}

		cout << "输入你要插入的数(输入-1退出插入)：" << endl;
		while (cin >> key)
		{
			if (key == -1)
				break;
			if (HT.Insert_hash(key) == -1)
				cout << "该元素已存在表中" << endl;
			else
				cout << "元素 " << key << " 插入成功" << endl;
		}

		HT.Traverse_HashTable();

	}
	return 0;
}
