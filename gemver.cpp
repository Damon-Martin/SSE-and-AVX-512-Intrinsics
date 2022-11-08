#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <time.h> 
#include <math.h>
#include <pmmintrin.h>
#include <process.h>
//#include <chrono>
#include <iostream>
#include <immintrin.h>

void initialization();
unsigned short int gemver_default();
unsigned short int gemver_vectorized();
unsigned short int Compare_Gemver();
inline unsigned short int equal(float const a, float const b);

#define P 1500 //input size
__declspec(align(64)) float A2[P][P], test4[P][P], u1[P], v1[P], u2[P], v2[P];

#define TIMES_TO_RUN 1
#define EPSILON 0.0001

int main() {

	
	clock_t start_1, end_1;

	initialization();

	start_1 = clock(); 

	for (int i = 0; i < TIMES_TO_RUN; i++)
		gemver_default();


	end_1 = clock(); 

	gemver_vectorized();

	printf(" clock() method: %ldms\n", (end_1 - start_1) / (CLOCKS_PER_SEC / 1000));

	if (Compare_Gemver() == 0)
		printf("\nCorrect Result\n");
	else
		printf("\nINcorrect Result\n");

	system("pause"); 

	return 0;
}



void initialization() {

	float e = 0.1234f, p = 0.7264f, r = 0.11f;

	
	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++) {
			A2[i][j] = 0.0f;
			test4[i][j] = 0.0f;
		}

	for (int j = 0; j < P; j++) {
		u1[j] = e + (j % 9);
		v1[j] = e - (j % 9) + 1.1f;
		u2[j] = p + (j % 9) - 1.2f;
		v2[j] = p - (j % 9) + 2.2f;
	}


}



unsigned short int gemver_default() {

	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++)
			A2[i][j] += u1[i] * v1[j] + u2[i] * v2[j];

	return 0;
}

unsigned short int gemver_vectorized() {
	//this code is working using SSE technology
	__m128 U1_128, V1_128, ans, num1, num2, num4;
	for (int y = 0; y < P; y++)
	{
		for (int x = 0; x < P; x++) {

			//OPERATIONS must FOLLOW BIDMAS
			
			//seting as 0 before usage
			num1 = _mm_setzero_ps();
			num2 = _mm_setzero_ps();
			ans = _mm_setzero_ps();

			//loading arrays to Multiply together and store in num 1 which is a temp value
			U1_128 = _mm_load_ps(&u1[y]);
			V1_128 = _mm_load_ps(&v1[x]);
			num1 = _mm_mul_ps(U1_128, V1_128);

			//loading arrays to Multiply together and store in num 1 which is a temp value
			U1_128 = _mm_load_ps(&u2[y]);
			V1_128 = _mm_load_ps(&v2[x]);
			num2 = _mm_mul_ps(U1_128, V1_128);

			//Add adding array section
			num4 = _mm_add_ps(num1, num2);
			ans = _mm_add_ps(ans, num4);
			_mm_store_ps(&A2[y][x], ans);
		}
	}
	return 0;
}

unsigned short int Compare_Gemver() {

	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++)
			test4[i][j] += u1[i] * v1[j] + u2[i] * v2[j];

	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++)
			if (equal(test4[i][j], A2[i][j]) == 1)
				return -1;

	return 0;
}






unsigned short int equal(float const a, float const b) {

	if (fabs(a - b) / fabs(a) < EPSILON)
		return 0; //success
	else
		return 1;
}


