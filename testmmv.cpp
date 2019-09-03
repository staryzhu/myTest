#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

	char str[15] = "abcdefghi";
	char *dest = &(str[3]);
	char *p = (char *)malloc(sizeof(char) * 1024);
	memcpy(p, str, 10);
	printf("p addr : %x\n", p);
	p = (char *)realloc(p, sizeof(char) *2048);
	printf("p raddr: %x\n", p);
	printf("src : %s\n", str);
	//memmove(dest, str, 12);
	memcpy(dest, str, 12);
	memcpy(dest, str, 12);
	printf("out: %s\n", str);
	printf("p val : %s \n", p);
	char *q = p + 3;
	memcpy(q, p, 20);
	printf("p val : %s \n", p);
	free(p);
	return 0;
}
