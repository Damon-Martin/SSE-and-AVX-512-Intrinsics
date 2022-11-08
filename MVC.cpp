#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h>
#include <time.h> 
#include <math.h>


void init();
void MVM();


#define N 500 //input size
float Y[N], X[N], A[N * N], test[N];

#define TIMES_TO_RUN 3000//how many times the function will run

int main() {

	//define the timers measuring execution time
	clock_t start_1, end_1; //ignore this for  now

	init();

	//starts the clock
	//the clock function returns how many clocks have been executed since the start of the program
	start_1 = clock(); 

	for (int i = 0; i < TIMES_TO_RUN; i++)
		MVM();

	//ends the clock
	end_1 = clock();

	int executionTimeCalculationInMS = (end_1 - start_1) / (CLOCKS_PER_SEC / 1000);
	executionTimeCalculationInMS = executionTimeCalculationInMS / TIMES_TO_RUN;
	long double FLOP_In_Ms = ((long double)(2 * N * N) / executionTimeCalculationInMS);
	long double FLOPS = FLOP_In_Ms * 1000;

	printf(" clock() method: %lfms\n", (long double)executionTimeCalculationInMS);
	printf(" Outputing the FLOPS calculation: %Lf FLOPS\n", FLOPS);


	system("pause");

	return 0;
}


void init() {

	float e = 0.1234f, p = 0.7264f, r = 0.11f;

	//MVM
	for (unsigned int i = 0; i < N; i++)
		for (unsigned int j = 0; j < N; j++)
			A[N * i + j] = ((i - j) % 9) + p;

	for (unsigned int j = 0; j < N; j++) {
		Y[j] = 0.0f;
		test[j] = 0.0f;
		X[j] = (j % 7) + r;
	}
}



void MVM() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Y[i] += A[N * i + j] * X[j];
		}
	}

}