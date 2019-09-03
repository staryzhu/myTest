#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class CSingle{
private:
	CSingle(){cout << "Construct this CSingle" << endl;};
	~CSingle(){cout << "DeConstruct this CSingle" << endl;};
public:
	static CSingle* instance(){
		cout << "Create the CSingle instance" << endl;
		_instance = new CSingle;
		return _instance;
	}
	static void destory(){
			if(_instance){
				cout << "free the CSingle" << endl;
				delete _instance;
			}
	}
	void show(){cout << "this is CSingle" << endl;}
private:
	static CSingle *_instance;
};

CSingle *CSingle::_instance = NULL;

template<class cls>
cls sum(cls a, cls b){
	return a + b;
}

template<typename type>
type testswap(type &a, type &b){
	type tmp;
	tmp = a;
	a = b;
	b = tmp;
	return tmp;
}

template<typename type>
class pointer_guard{
public:
	pointer_guard(type *name){
		_name = name;
	}
	~pointer_guard(){
		if(_name)
			delete _name;
	}
private:
	type *_name;
};

template<typename type>
class array_guard{
public:
	array_guard(type *name){
		_name = name;
	}
	~array_guard(){
		if(_name)
			delete[] _name;
	}
private:
	type *_name;
};

#define MEMGUARD(type, name) pointer_guard<type> pointer_##name(name)
#define ARRGUARD(type, name) array_guard<type> array_##name(name)

template<typename type>
class A{
public:
	A(){};
	~A(){};
	type sum(type a, type b){return a + b;}
};

template<unsigned NUM>
int lenlen(){
	int len = NUM;
	return len;
}

/*
int :4
long:8
long long :8
float : 4
double: 8
long double : 16
void * : 8
p heap address : 13b1050
q freestore address : 13b1090
pq freestore address : 13b10c0
p heap address : 13b1088 size : 49
p heap address : 13b10b8 size : 49
p heap address : 13b1048 size : 65
p heap address : 13b1050 size : 9
p heap address : 13b1058 size : 0
p heap address : 13b1060 size : 0
p heap address : 13b1068 size : 0
p heap address : 13b1070 size : 0
p heap address : 13b1078 size : 0
p heap address : 13b1080 size : 0
p heap address : 13b1088 size : 49
p heap address : 13b1090 size : 1
p heap address : 13b1098 size : 0
p heap address : 13b10a0 size : 0
p heap address : 13b10a8 size : 0
p heap address : 13b10b0 size : 0
p heap address : 13b10b8 size : 49
p heap address : 13b10c0 size : 0
p heap address : 13b10c8 size : 0
p heap address : 13b10d0 size : 0
p heap address : 13b10d8 size : 0
p heap address : 13b10e0 size : 0
p heap address : 13b10e8 size : 130849
p heap address : 13b10f0 size : 0
*/

void test_heep_and_freestore(){
	char *p = (char *)malloc(41);//64byte
	char *q = new char[30];
	char *pq = new char[25];
	long long * intp = (long long *)q;
	printf("p heap address : %x \n", p);
	printf("q freestore address : %x \n", q);
	printf("pq freestore address : %x \n", pq);
	p[0] = 9;
	q[0] = 1;
	printf("p heap address : %x size : %d\n", (char *)((long long *)q - 1), *(long long *)((long long *)q - 1));
	printf("p heap address : %x size : %d\n", (char *)((long long *)q + 5), *(long long *)((long long *)q + 5));
	for(int i = 0; i < (64 + 48 + 48) / 8 + 2; i++){
		printf("p heap address : %x size : %d\n", (char *)((long long *)p - 1 + i), *(long long *)((long long *)p - 1 + i));
	}

	delete[] q;
	q = new char[41];
	printf("q freestore address : %x \n", q);
	for(int i = 0; i < (64 + 48 + 48 + 64) / 8 + 2; i++){
		printf("p heap address : %x size : %d\n", (char *)((long long *)p - 1 + i), *(long long *)((long long *)p - 1 + i));
	}
	free(p);
	delete[] q;
	delete[] pq;
}


void test(){
	int arr[10];

	for(int i = 0; i < 10; i++){
		arr[i] = i * 10;
	}
	for(int i = 0; i < 10; i++){
		cout << "get arr : " << i << " value: " << arr[i] << endl;
	}
	cout << "out : " << 2[arr] << endl;
}
#define FILE_SIZE 3

#define MAXLENGTH 100

void doFileTest(){
	char buffer[100] = {1,2,3,4};
    do{
        static FILE *fp = NULL;
        static int fcount = 0;
        char filebuf[128] = {0};

        if(!fp){
            sprintf(filebuf, "./Audio_%d.pcm", fcount);
            fp = fopen(filebuf, "ab+");
        }
        if (fp) {
            // fseek(fp, 0, SEEK_END);

            fwrite(buffer, 1, 100, fp);

            const long lFileSize = ftell(fp);
            fflush(fp);
            if(lFileSize < MAXLENGTH)
            {
                break;
            }

            fclose(fp);
            fp = NULL;
            if(FILE_SIZE > 0)
            {
                char fileold[128] = {0};
                sprintf(filebuf, "./Audio_%d.pcm", FILE_SIZE);
                int nRet = remove(filebuf);

                for(int i = FILE_SIZE; i > 0; i--)
                {
                    sprintf(filebuf, "./Audio_%d.pcm", i);
                    sprintf(fileold, "./Audio_%d.pcm", i - 1);
                    cout << "old name : " << fileold << endl;
                    cout << "new name : " << filebuf << endl;
                    nRet = rename(fileold, filebuf);
                    cout << "rename : " << nRet << endl;

                }
            }

        }
    }while(0);
}

void concatfile(char * filename, char * readfilename){
	FILE * outp = NULL;
	FILE * readp = NULL;
	char buf[1024] = {0};
	outp = fopen(filename, "ab+");
	readp = fopen(readfilename, "rb");
	while(!feof(readp)){
		int len = fread(buf, 1, 1024, readp);
		if(len <= 0){
			break;
			cout << "read out" << endl;
		}
		fwrite(buf, 1, len, outp);
	}
	cout << "exit concat file" << endl;
	fclose(outp);
	fclose(readp);
}

void test_size(){
	cout << "int :" << sizeof(int) << endl;
	cout << "long:" << sizeof(long) << endl;
	cout << "long long :" << sizeof(long long) << endl;
	cout << "float : " << sizeof(float) << endl;
	cout << "double: " << sizeof(double) << endl;
	cout << "long double : " << sizeof(long double) << endl;
	cout << "void * : " << sizeof(void *) << endl;
}

void test_template(){
	int a = 10;
	int b = 9;
	A<int> aa;
	cout << "a : " << a << endl;
	cout << "b : " << b << endl;
	cout << "test sum : " << sum(a, b) << endl;
	cout << "test A::sum : " << aa.sum(a, b) << endl;
	testswap(a, b);
	cout << "a : " << a << endl;
	cout << "b : " << b << endl;
	cout << "lenlen : " << lenlen<10>() << endl;

	char *p = new char;
	char *ppp = new char[100];
	MEMGUARD(char, p);
	ARRGUARD(char, ppp);
}

int main(int argc, char *argv[]){
	CSingle *pb = CSingle::instance();
	pb->show();
	pb->destory();
	test_template();
	test_size();
	if(argc > 2){
		cout << "concat the file" << endl;
		concatfile(argv[1], argv[2]);
	}
		//test();
	// while(1){
	// 	doFileTest();
	// }
	test_heep_and_freestore();
    char *p = (char *)malloc(10);
    free(++p);
    // free(p);
	return 0;
}
