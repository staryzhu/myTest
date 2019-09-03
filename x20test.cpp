#include <stdlib.h>
#include <unistd.h>

#define aaa "abcde"
#define bbb "bbbb"

#define cat(a,b) a##b

const unsigned char TTT = 0x61;


#define ABS(number) (number) > 0 ? (number) : (~(number) + 1)




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


}

int main(){
    char *p = "abcd";
    char ppp[10];
    testRB();
    //test1();

    return 0;
}
