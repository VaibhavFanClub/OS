#include<stdio.h>
#include<time.h>

int main(){
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	for(long i = 0; i < 10000000000; i++);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nStart = %f\nEnd = %f", ((double)start) / CLOCKS_PER_SEC, ((double)end) / CLOCKS_PER_SEC);
	printf("\nCPU time used: %f seconds\n", cpu_time_used);
	return 0;
}
