
#define TEST_3

#ifdef TEST_1

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define inf 0x7fffffff
using namespace std;

void* operator new(size_t sz)
{
    printf("operator new: %d Bytes\n",sz);
    void* m = malloc(sz);
    if (!m) puts("out of memory");
    return m;
}

void operator delete(void* m)
{
    puts("operator delete");
    free(m);
}

class S
{
public:
    S() {
        for(int i = 0; i < 10; i++) {
            an[i] = i + 1;
        }
        printf("array addr : %x\n", an);
        printf("array size : %d\n", *(long long *)((long long *)an - 1));
        printf("byte size  : %d\n", *(long long *)((long long *)an - 2));
        puts("S::S()");
    }
    ~S() {puts("S::~S()"); }
private:
    int an[10];
    int b;
};


int main()
{
    puts("creating & destroying an int");
    int* q = new int(23);
    delete q;
    puts("creating & destroying an int[]");
    int* p = new int[10]();
    delete []p;
    puts("creating & destroying an s");
    S* s = new S;
    delete s;
    puts("creating & destroying S[3]");
    S* sa = new S[5];
    delete []sa;
    return 0;
}



////////////
#elif defined(TEST_2)
#include <iostream>
#include <cstddef>
#include <fstream>
#include <new>
#include <string.h>
using namespace std;
#define out cout
//ofstream out("Framis.out");

class Base {
public:
    int abc[10];
};

class Framis : public Base
{
public:
    enum{psize = 100 };
    Framis() {out<< "create Framis()" <<endl; }
    ~Framis() {out<< "~Framis() ... " <<endl; }
    void* operator new(size_t);// throw (bad_alloc);
    void operator delete(void*);
    void show(char *str);
private:
    enum{sz = 10 };
    char c[sz];
    static unsigned char pool[];
    static bool alloc_map[];
};
unsigned char Framis::pool[psize*sizeof(Framis)];
bool Framis::alloc_map[psize]={false};
#if 0
void* Framis::operator new(size_t sz) throw(bad_alloc)
{
    for (int i=0; i<psize; ++i) {
        if (!alloc_map[i]) {
            out<< "using block " << i << " ... ";
            alloc_map[i]=true;
            return pool+(i*sizeof(Framis));
        }
    }
    out<< "out of memory" <<endl;
    throw bad_alloc();
}

void Framis::operator delete(void* m)
{
    if (!m) return;
    unsigned long block = (unsigned long)m-(unsigned long)pool;
    block /= sizeof(Framis);
    out<< "freeing block " << block <<endl;
    alloc_map[block]=false;
}
#else
void Framis::show(char *str) {
    strncpy(c, str, 9);
    printf("Framis :: c : %x \n", c);
    printf("str: %s\n", c);
}

void *Framis::operator new(size_t sz) {
    cout << "new **** :" << sz << endl;
    printf("pool : %x\n", pool);
    return ::operator new(sz);
    //return pool;
    //::new ;
}

void Framis::operator delete(void *m) {
    cout << "delete ****" << endl;
    printf("m : %x\n", m);
    if (!m) ::operator delete(m);
}
#endif
int main()
{
#if 0
    Framis* f[Framis::psize];
    try {
        for (int i=0; i<Framis::psize; i++) {
            f[i]=new Framis;
        }
        //new Framis;
    } catch(bad_alloc) {
        cerr<< "Out of memory!" <<endl;
    }
    delete f[10];
    f[10]=0;
    Framis* X=new Framis;
    delete X;
    for (int j=0; j<Framis::psize; j++) {
        delete f[j];
    }
#else
    cout << "sizeof Framis : " << sizeof(Framis) << endl;
    Framis *p = new Framis();
    p->show("1234567890");
    delete p;

    //int *ppp = ::operator new(sizeof(int));
#endif
    return 0;
}


////////////////////////////////
#else
#include<iostream>
#include<fstream>
#include<new>
using namespace std;
//ofstream trace("ArrayOperatorNew.out");
#define trace cout

class Widget
{
public:
    Widget() {trace<< "Widget()" <<endl; }
    ~Widget() {trace<< "~Widget()" <<endl; }
    void* operator new(size_t sz) {
        trace<< "Widget::new: " << sz << " byte" <<endl;
        return ::new char[sz];
    }
    void operator delete(void* p) {
        trace<< "Widget::delete" <<endl;
        ::delete []p;
    }
    void* operator new[](size_t sz) {
        trace<< "Widget::new[]: " << sz << " bytes" <<endl;
        return ::new char[sz];
    }
    void operator delete[](void* p) {
        trace<< "Widget::delete[]" <<endl;
        ::delete []p;
    }
private:
    //enum{sz=10 };
    int an[10];
};

struct home {
    union {
        int aa;
        char ab;
    };
    union {
        int ba;
        char bb;
        struct {
            int bca;
            char bcb;
        };
    };
    char abc;
};

int main()
{
    struct home aaa;
    aaa.aa = 0x61;
    aaa.abc = 'c';
    aaa.bca = 0x62;
    printf("c1: %c  c2:%c c3:%c\n", aaa.ab, aaa.bca, aaa.abc);
    printf("c1: %c  c2:%c c3:%c\n", aaa.aa, aaa.bb, aaa.abc);
    trace<< "******************new Widget" <<endl;
    Widget* w=new Widget;
    trace<< "******************delete Widget" <<endl;
    delete w;
    trace<<endl<< "ARRAY new Widget[25]" <<endl;
    Widget* wa=new Widget[25];
    trace<<endl<< "ARRAY delete []Widget" <<endl;
    delete []wa;
    return 0;
}
#endif
