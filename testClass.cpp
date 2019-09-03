#include <iostream>

using namespace std;

class B;
class A;



class B
{
public:
	B(){ nb = 100; cout << "Construct B" << endl; };
	~B(){ cout << "DeConstruct B" << endl; };
	void showb(){ cout << "show B" << endl; };
	friend class A;
private:
	int nb;
};
class A
{
public:
	A(){ cout << "Construct A" << endl; };
	~A(){ cout << "DeConstruct A" << endl; };
	void show(B &binstance, int n){ cout << " A show :" << n << endl; cout << "show B:" << binstance.nb << endl; };
};
int maintt_T(int argc, char * argv[])
{
	B b;
	b.showb();
	A a;
	a.show(b, 99);
	return 0;
}