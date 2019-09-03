#include <pthread.h>
#include <stdio.h>

int g_counter = 0;


void *threadfuc(void *){
	int i = 0;
	for(;i < 10000; i++){
		g_counter++;
		printf("swape\n");
	}
}

int main(){
	pthread_t ta;
	pthread_t tb;
	pthread_create(&ta, NULL, threadfuc, NULL);
	pthread_create(&tb, NULL, threadfuc, NULL);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);
	printf("last num : %d\n", g_counter);
	return 0;
}

	
