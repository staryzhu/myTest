#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

static const int allal = 100;
const static int allab = 99;

class CString{
public:
	CString(){
		cout << "init with default" << endl;
		_buf = new char[64];
		_size = 64;
	}

	CString(int size){
		_buf = new char[64];
		_size = size;
	}

	CString(char *str){
		cout << "str init : " << str << endl;
		_size = strlen(str) + 1;
		_buf = new char[_size];
		memcpy(_buf, str, _size);
		_buf[_size - 1] = '\0';
	}

	CString(const CString &str){
		cout << "instance init : " << str.to_char() << endl;
		_size = str._size;
		_buf = new char[_size];
		memset(_buf, 0, _size);
		memcpy(_buf, str._buf, _size);
	}

	CString(CString &&str){
		cout << "right value init" << endl;
	}


	~CString(){
		if(_buf){
			cout << "deConstruct with : " << _buf << endl;
			delete[] _buf;
		}
	}

	CString& operator=(const CString &str){
		cout << "====" << endl;
		if(this == &str){
			return *this;
		}

		if(_buf) delete[] _buf;
		_buf = new char[str._size];
		_size = str._size;
		memcpy(_buf, str._buf, _size);
		return *(this);
	}

	CString& operator=(CString &&str){
		cout << "right value ====" << endl;
	}

	friend CString operator+(const CString &a, const CString &b);
	friend CString operator+(const char *str, const CString &b);

	CString operator+(const CString &str) {//priviliage to use
		cout << "++++" << endl;
		int size = str._size + _size - 1;
		char *buf = new char[size];
		memset(buf, 0, size);
		memcpy(buf, _buf, _size - 1);
		memcpy(buf + _size - 1, str._buf, str._size);
		CString tmp(buf);
		printf("tmp address : %x\n ", &tmp);
		delete[] buf;
		return tmp;
	}

	char * to_char() const{
		return _buf;
	}

	int len() const{
		return _size;
	}

private:
	char *_buf;
	int _size;
};

CString operator+(const CString &a, const CString &b){
	cout << "Out ++++" << endl;
	int size = a._size + b._size - 1;
	char * buf = new char[size];
	memset(buf, 0, size);
	memcpy(buf, a.to_char(), a.len());
	memcpy(buf + a.len() - 1, b.to_char(), b.len());
	CString tmp(buf);
	delete[] buf;
	return tmp;
}

CString operator+(const char *str, const CString &b){
	cout << "char++++" << endl;
	int strl = strlen(str);
	int size = strl + b._size;
	char * buf = new char[size];
	memset(buf, 0, size);
	memcpy(buf, str, strl);
	memcpy(buf + strl, b.to_char(), b.len());
	CString tmp(buf);
	delete[] buf;
	return tmp;
}

int main(){
	CString h("hello");
	CString w(" world!");
	char *my = "this is";
	char *test = "operator test";
	CString ww = w;//instance init :  world!
	CString wh = w + h;
	CString hh(w+h);
	cout << "wh : " << wh.to_char() << endl;
	printf("wh address : %x\n ", &wh);
	// CString hw;
	// hw = h + w;
	// CString tsot;
	// tsot = hw + " " + my + " " + test;
	// cout << h.to_char() << endl;
	// cout << w.to_char() << endl;
	// cout << hw.to_char() << endl;
	// cout << tsot.to_char() << endl;
	return 0;
}
