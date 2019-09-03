#include <stdio.h>
#include <vector>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define aaa "abcde"
#define bbb "bbbb"

#define cat(a,b) a##b

const unsigned char TTT = 0x61;


#define ABS(number) (number) > 0 ? (number) : (~(number) + 1)

//#define READYLEN(w, r) (w) > (r) ? (w - r) :
#include <iostream>
using namespace std;

class A{
public:
	virtual void g(){
		cout << "this is A::g" << endl;
	}
private:
	virtual void f(){
		cout << "this A::f" << endl;
	}
};

class B:public A{
public:
	virtual void g(){
		cout << "this is B::g" << endl;
	}
	virtual void h(){
		cout << "this is B::h" << endl;
	}
};
#define chen long long 
typedef void (*functype)(void);
void test_a(){
	B a;
	functype f;
	cout << "sizeof address : "<< sizeof(functype) << endl;
	cout << "sizeof int : "<< sizeof(int) << endl;
	cout << "sizeof longlong : "<< sizeof(long long) << endl;
	//f = (functype)a;
	//f();
	for(int i = 0; i < 3; i++){
		f = (functype)*((chen *)*(chen *)(&a) + i);

		f();
	}
}	

void this_test(){
    char b = '\0xab';
    int a = 0x0f;
    int c = ~a;
    printf("out : %x ~%x \n", a , c);
    printf("this test : %d\n",b);
	test_a();
}

void testTime()
{
    timeval _tv_end;
    timeval _tv_start;

    gettimeofday(&_tv_start, NULL);
    sleep(5);
    gettimeofday(&_tv_end, NULL);
    //int s = _tv_end.tv_sec - _tv_start.tv_sec;
    //while(s > 0){
    _tv_end.tv_usec += 1000*1000 * (_tv_end.tv_sec - _tv_start.tv_sec);
        //--s;
    //}

    printf("Distributed Wakeup Cost Time : %d ms  \n", (_tv_end.tv_usec - _tv_start.tv_usec) / 1000);
}

using namespace std;
void test1(){
	int a = 1;
	int b = 2;
	//__sync_synchronize();
	__asm__ __volatile__("mfence":::"memory");
	a++;
	b++;
	vector<int> vvv;
	for(int i = 0; i < 100000; i++){
		vvv.push_back(i);
		static unsigned int size = 0;
		if(size != vvv.capacity()){
			size = vvv.capacity();
			printf("change capacity : %u\n", vvv.capacity());
		}
	}
}
#if 0
void *memcpy(void *dest, const void *src, n_t n)
{
	unsigned int *d32, *s32, tmp1, tmp2;
	unsigned short *d16, *s16;
	unsigned char *d8, *s8;
	int cnt, align;

	d8 = (unsigned char *)dest;
	s8 = (unsigned char *)src;

	if(n < 4)
	{
		goto LAST_BYTES;
	}

	//判断dest地址是否对齐到四个字节
	align = (int)d8 & 0x03;
	if(align == 1)
	{
		*d8++ = *s8++;
		*d8++ = *s8++;
		*d8++ = *s8++；
		n -=3;
	}
	else if(align == 2)
	{
		*d8++ = *s8++;
		*d8++ = *s8++;
		n -=2;
	}
	else if(align == 3)
	{
		*d8++ = *s8++;
		n--;
	}

	if(n < 4)
	{
		goto LAST_BYTES;
	}

	//此处dest已经对齐到四个字节，再将src对齐到四个字节
	align = (int)s8 &0x03;
	d32 = (u32 *)d8;
	s32 = (u32 *)(s8 - align);

	if(align == 1)
	{
		tmp1 = *s32;
		while(n >=4)
		{
			tmp2 = tmp1 >> 8;
			tmp1 = *(++s32);
			*d32++ = tmp2 | (tmp1 << 24);
			n -=4;
		}
		d8 = (u8 *)d32;
		s8 = (u8 *)s32 +1;
	}
	else if(align == 2)
	{
		tmp1 = *s32;
		while(n >= 4)
		{
			tmp2 = tmp1 >> 16;
			tmp1 = *(++s32);
			*d32++ = tmp2 | (tmp1 << 16);
			n -=4;
		}
		d8 = (u8 *)d32;
		s8 = (u8 *)s32 +2;
	}
	else if(align == 3
	{
		tmp1 = *s32;
		while(n >= 4)
		{
			tmp2 = tmp1 >> 24
			tmp1 = *(++s32);
			*d32++ = tmp2 | (tmp1 << 8);
			n -=4;
		}
		d8 = (u8 *)d32;
		s8 = (u8 *)s32 +3
	}
	else
	{
		while(n >=4)
		{
			*d32++ = *s32++;
			n-=4;
		}
		d8 = (u8 *)d32;
		s8 = (u8 *)s32;
	}
LAST_BYTES:
	if(n == 3)
	{
		*d8++ = *s8++;
		*d8++ = *s8++;
		*d8 = *s8;
	}
	else if(n == 2)
	{
		*d8++ = *s8++;
	}
		*d8 = *s8;
	else
	{
		*d8 = *s8;
	}
	return dest;
}
#endif


#define TEST_RINGBUFFER

#ifdef TEST_RINGBUFFER
class CRingBuffer{
public:
    CRingBuffer(int len):capacity(len * 2),size(len),rPos(0),wPos(0),pBuffer(NULL),pOutBuff(NULL){

    }

    CRingBuffer():capacity(0),size(0),rPos(0),wPos(0),pBuffer(NULL),pOutBuff(NULL){

    }

    ~CRingBuffer(){
        if(!pBuffer){
            free(pBuffer);
        }
        if(!pOutBuff){
            free(pOutBuff);
        }
    }

    int init(unsigned int len = 0){
        if(len == 0){
            capacity = len * 2;
            size     = len;
        }
        if(capacity == 0){
            return 0;
        }
        printf("capacity : %d\n", capacity);
        printf("size     : %d\n", size);
        if(!pBuffer){
            pBuffer = (char *)malloc(capacity);
        }

        if(!pOutBuff){
            pOutBuff = (char *)malloc(size);
        }

        if(pBuffer && pOutBuff){
            memset(pBuffer, 0, capacity);
            memset(pBuffer, 0, size);
            return size;
        }
        return 0;
    }

    int push_back(char *buf, int len){
        //unsigned int len = 0;
        //__sync_synchronize
        if(len <= 0)return 0;
        // if((wPos + 1) % capacity == rPos){
        //  printf("Buffer is Full");
        //  return 0;
        // }
        if(wPos + len > capacity){
            int last = wPos + len - capacity;
            memmove(pBuffer + wPos, buf, capacity - wPos);//push last
            memmove(pBuffer, buf + capacity - wPos, last);
            wPos = last;
        }
        else{
            memmove(pBuffer + wPos, buf, len);
            wPos += len;//wPos always point to next byte == current length
        }

        return len;
    }

    char *pop_front(int len){
        //unsigned int  = 0;
        if(!pOutBuff){
            printf("NULL Buffer Pointer\n");
            if(init() == 0)
                return NULL;
        }
        memset(pOutBuff, 0, size);
        if(len < 0 || len > size){
            printf("wrong len while read\n");
            return pOutBuff;
        }
        int cur = wPos;
        if(len <= cur){
            memmove(pOutBuff, pBuffer + cur - len, len);
        }
        else
        {
            memmove(pOutBuff, pBuffer + capacity - len + cur, len - cur);
            memmove(pOutBuff + len - cur, pBuffer, cur);
        }
        return pOutBuff;
    }

private:
    int capacity;
    int rPos;
    int wPos;
    int size;
    char * pBuffer;
    char * pOutBuff;
};
#endif //TEST_RINGBUFFER
//A write consequence number to ringbuffer
void *threadA(void *arg){
	CRingBuffer *p = (CRingBuffer *)arg;
	char ch[11] = {0};
	int couter = 0;
	while(couter < 10000){
		usleep(1000);
		snprintf(ch, 11,"%d", couter++);
		p->push_back(ch, 3);
	}
}

//B each 1 second read from ringbuffer
void *threadB(void *arg){
	CRingBuffer *p = (CRingBuffer *)arg;
	char *chr;
	while(1){
		usleep(10000);
		chr = p->pop_front(50);
		printf("pop string : %s\n", chr);
	}
}

void testRB(){
	pthread_t ta;
	pthread_t tb;
	CRingBuffer flb(100);
	if(flb.init(100) == 0){
		printf("Free Lock Buffer Init Failed\n");
		return ;
	}
	char buf[100] = {'\xab','\x12','\x34','\x56','\x78'};
	printf("out before: %x %x", buf[0], buf[1]);
	printf("out : %08x %08x\n", ((int *)buf)[0], ((int *)buf)[1]);
	threadA(&flb);

#if 0
	if(!pthread_create(&ta, NULL, threadA, &flb)){
		printf("wrong threadA create\n");
	}

	if(!pthread_create(&tb, NULL, threadB, &flb)){
		printf("wrong threadB create\n");
	}
	printf("Start Working Now\n");
	pthread_join(ta, NULL);
	printf("writing thread exit\n");
	pthread_join(tb, NULL);
	printf("Exit All\n");
#endif

}

int main(){
	char *p = "abcd";
	char ppp[10];
    //testTime();
	//testRB();
	//test1();
    this_test();
#if 0
	ppp[0] = 0x61;
	printf("%c\n",TTT);
	printf("*p:%c\n",*p);
	if(*p == TTT){
		printf("equal\n");
	}
	__sync_synchronize();
	if(*ppp == TTT){
		printf("equal\n");
	}
	printf("concat : %s \n", cat(aa,a));
#endif
	return 0;
}
