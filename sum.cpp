#include <stdio.h>

int sum(int a, int b){
	if((a&b)<<1 == 0){
		return a^b;
	}	
	else{
		return sum(a^b, (a&b)<<1);
	}
}

int main(){
	int a = 99;
	int b = 199;

	printf("the rslt: %d\n", sum(a, b));
	return 0;
}
