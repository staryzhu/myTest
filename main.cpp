#include <stdio.h>
#include <time.h>
#include <string>
#include <string.h>
#include <map>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define MAPCI map<char, int>

int lengthOfLongestSubstring(string s){
    const char *p = s.data();
    int len = s.length();
    char *pRslt = new char[len];
    map<char, int> char_pos;
    MAPCI::iterator it;
    pair<MAPCI::iterator, bool> rit;
    int max_fin = 0;
    int max_now = 0;
    int max_s = 0, max_e = 0;
    int now_s = 0;
    for(int i = 0; i < len; i++){
        //rit = char_pos.insert(MAPCI::value_type(*(p + i), i));
        it = char_pos.find(*(p + i));
        // if(char_pos.count(*(p+i)) > 0){
        //     cout << "key : " << *(p+i) << endl;
        // }
        if(it == char_pos.end()/*rit.second*/){
            char_pos.insert(MAPCI::value_type(*(p + i), i));
            //char_pos.insert(make_pair(*(p + i), i));
            max_now++;
            if(max_now > max_fin) {
                max_e = i;
                max_s = now_s;
                max_fin = max_now;
            }
        }
        else {
            if(max_now > max_fin) {
                max_e = i - 1;
                max_s = now_s;
                max_fin = max_now;
            }
            //now_s = rit.first->second + 1;
            now_s = it->second + 1;
            //rit.first->second = i;
            max_now = i - now_s + 1;
        #ifdef C11
            for(it = char_pos.begin(); it != char_pos.end(); ){
                if(now_s > it->second){
                    it = char_pos.erase(it);//c++11 support
                }
                else {
                    it++;
                }
            }
        #else
    //             for(it = char_pos.begin(); it != char_pos.end(); it++){
    //     cout << "key : " << it->first << " value : " << it->second << endl;
    // }
    // cout << endl ;
    // cout << endl ;
            char_pos.clear();
            cout << "now_s : " << now_s << endl;
            for(int j = now_s; j < i + 1; j++){
                char_pos.insert(MAPCI::value_type(*(p + j), j));
                //char_pos.insert(make_pair(*(p + i), i));
            }
        #endif
        }
    }
    // for(it = char_pos.begin(); it != char_pos.end(); it++){
    //     cout << "key : " << it->first << " value : " << it->second << endl;
    // }
    printf("max start : %d to %d\n", max_s, max_e);
    printf("max Length : %d \n", max_fin);
    memset(pRslt, 0, len);
    memcpy(pRslt, p + max_s, max_fin);
    cout << "max str :" << pRslt << endl;
#if 0
    for(int i = 0; i < len; i++){
        pair<map<char, int>::iterator, bool> iit = char_pos.insert(map<char, int>::value_type(*(p + i), i));
        if(iit.second){
            printf("%c,", *(p+i));
        }
        else{
            iit.first->second = i;
        }
    }
    printf("\n\n");
    map<char, int>::const_iterator it = char_pos.begin();
    for(;it != char_pos.end(); it++){
        printf("%c:%d,", it->first, it->second);
    }
#endif
    delete pRslt;
    return 0;
}

void ttt(){
    time_t val = time(NULL);
    printf("time_t : %d\n", sizeof(time_t));
    printf("time now: %ld\n", val);
}

int main(){
    ttt();
    srandom(time(NULL));
    int aa = 0x12345678;
    char * p = (char *)&aa;
    char s = 0x61;
    for(int i = 0; i < 4; i++){
        printf("%x,", p[i]);
    }
    printf("\n\n");
    // lengthOfLongestSubstring("abcdefgaiahijklmn");
    // lengthOfLongestSubstring("doyouhave");
    // lengthOfLongestSubstring("abcdefghijklmn");
    lengthOfLongestSubstring("wsuohkvcfpxsgutlft");
    lengthOfLongestSubstring("abcdefgaahijklmn");
    for(int i = 0; i < 10; i++){
        int cnt = random() % 118 + 10;
        char *str = new char[cnt];
        for(int j = 0; j < cnt ; j++){
            str[j] = s + random() % 26;
        }
        cout << "src str : " << str << endl;
        lengthOfLongestSubstring(str);
        cout << endl;
        delete str;
    }

    return 0;
}
