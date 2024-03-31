#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>

extern float c_dot_product(uint64_t n, float* vectorA, float* vectorB);

extern float asm_dot_product(uint64_t n, float* vectorA, float* vectorB);

const int RUNS = 30;
const uint64_t VECTOR_SIZES[3] = { 1 << 20, 1 << 24, 1 << 30 };
const uint32_t SIZES[3] = { 20, 24, 30 };

void initVectors(uint64_t n, float* vectorA, float* vectorB) {
	for (int i = 0; i < n; i++) {
		vectorA[i] = 1.0;
		vectorB[i] = (float)i;
	}
}

int main() {
	/* Initializations */
	float* vectorA;
	float* vectorB;
	float sdot1, sdot2;
	clock_t c_start, c_end;
	clock_t x86_start, x86_end;
	double c_time, x86_time;
	double ave_c_time = 0, ave_x86_time = 0;
	FILE* c_data = NULL;
	FILE* asm_data = NULL;
	errno_t error;

	for (int runCount = 0; runCount < 3; runCount++) {
		vectorA = malloc(VECTOR_SIZES[runCount] * sizeof(float));
		vectorB = malloc(VECTOR_SIZES[runCount] * sizeof(float));
		initVectors(VECTOR_SIZES[runCount], vectorA, vectorB);

		/* Initial Execution */
		sdot1 = c_dot_product(VECTOR_SIZES[runCount], vectorA, vectorB);
		sdot2 = asm_dot_product(VECTOR_SIZES[runCount], vectorA, vectorB);

		/* Output of initial execution */
		printf("C   Output: %f\n", sdot1);
		printf("ASM Output: %f\n", sdot2);
		printf("Output values are equal: %s\n", (sdot1 == sdot2) ? "Yes" : "No");

		/* Setup for Automated Output */
		struct stat st = { 0 };

		if (stat("./Data", &st) == -1) {
			mkdir("./Data", 0700);
		}

		error = fopen_s(&c_data, "./Data/C_benchmark_data.csv", "a");
		if (error != 0) {
			free(vectorA);
			free(vectorB);
			return 1;
		}

		error = fopen_s(&asm_data, "./Data/ASM_benchmark_data.csv", "a");
		if (error != 0) {
			free(vectorA);
			free(vectorB);
			return 1;
		}

		if (c_data != NULL && asm_data != NULL) {
			fprintf(c_data, "C Benchmark Test Data for 2^%d\n", SIZES[runCount]);
			fprintf(asm_data, "Assembly Benchmark Test Data for 2^%d\n", SIZES[runCount]);
			fprintf(c_data, "Run#, Start Time, End Time, Clocks per Second, Time (seconds)\n");
			fprintf(asm_data, "Run#, Start Time, End Time, Clocks per Second, Time (seconds)\n");

			/* Benchmarking */
			for (int i = 1; i <= RUNS; i++) {
				// For C
				c_start = clock();
				sdot1 = c_dot_product(VECTOR_SIZES[runCount], vectorA, vectorB);
				c_end = clock();
				c_time = ((double)c_end - (double)c_start) / CLOCKS_PER_SEC;
				ave_c_time += c_time;
				fprintf(c_data, "%d, %ld, %ld, %ld, %lf\n", i, c_start, c_end, CLOCKS_PER_SEC, c_time);

				// For Assembly
				x86_start = clock();
				sdot2 = asm_dot_product(VECTOR_SIZES[runCount], vectorA, vectorB);
				x86_end = clock();
				x86_time = ((double)x86_end - (double)x86_start) / CLOCKS_PER_SEC;
				ave_x86_time += x86_time;
				fprintf(asm_data, "%d, %ld, %ld, %ld, %lf\n", i, x86_start, x86_end, CLOCKS_PER_SEC, x86_time);
			}
			ave_c_time = ave_c_time / RUNS;
			ave_x86_time = ave_x86_time / RUNS;
			fprintf(c_data, "Average, , , , %lf\n", ave_c_time);
			fprintf(asm_data, "Average, , , , %lf\n", ave_x86_time);

			/* Clean Up */
			fclose(c_data);
			fclose(asm_data);
		}

		free(vectorA);
		free(vectorB);
	}
	return 0;
}
