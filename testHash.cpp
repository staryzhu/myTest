#include <iostream>
using namespace std;

typedef int Keytype;
const int NULLKEY = 0;  //��ʾ��λ����ֵ

//����ַ���еĽڵ�ṹ��
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
		//��ʼ��hash���СΪ11
		hash_length = 10;
		hashlist = new Hash_List[hash_length];
		if (!hashlist)
		{
			cout << "�ڴ�����ʧ��" << endl;
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

	unsigned Hash(Keytype k)  //hash����(ȡģ��)
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
		cout << "��ϣ��������Ԫ��Ϊ(����10ȡ�����������)��" << endl;
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
	cout << "������Ҫ������ٸ�Ԫ������ʼ��hash��";
	cin >> n;
	if (n>0)
	{
		r = new Keytype[n];
		cout << "���� " << n << "��������" << endl;
		for (i = 0; i<n; i++)
			cin >> r[i];
		for (int i = 0; i<n; i++)
		{
			if (HT.Insert_hash(r[i]) == -1)
				cout << "��Ԫ�� " << r[i] << " �Ѵ��ڣ����ظ�����" << endl;
		}
		HT.Traverse_HashTable();
		cout << endl;

		cout << "������Ҫ���ҵ���(����-1�˳�����)��";
		while (cin >> key)
		{
			if (key == -1)
				break;
			if (HT.Search_hash(key, i))
				cout << "��Ԫ�ش���hash��ĵ� " << i + 1 << " ���ӱ���" << endl;
			else
				cout << "��Ԫ�ز����ڱ���" << endl;
		}

		cout << "������Ҫ�������(����-1�˳�����)��" << endl;
		while (cin >> key)
		{
			if (key == -1)
				break;
			if (HT.Insert_hash(key) == -1)
				cout << "��Ԫ���Ѵ��ڱ���" << endl;
			else
				cout << "Ԫ�� " << key << " ����ɹ�" << endl;
		}

		HT.Traverse_HashTable();

	}
	return 0;
}
