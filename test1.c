#include <stdio.h>
int num[4] = {1,2,3,4};
char num3[4] = {1,2,3,4};
char num2[10];
int number;
int number2;
int number3;
int number4;
int number5;

void print(char p[]){
	printf("out : %s\n", p);
}
int main(){
	const char *fff = "123456";
	const char eee = 'p';
	const char eee2 = 'z';
	char * abc = "abc";
	char * abcd = "abcd";
	char def[] = "abc";
	print(abc);
	return 0;
}

