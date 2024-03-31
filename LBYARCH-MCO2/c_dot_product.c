#include<stdint.h>

extern float c_dot_product(uint64_t n, float* vectorA, float* vectorB) {
	float sdot = 0;
	for (uint64_t i = 0; i < n; i++) {
		sdot += vectorA[i] * vectorB[i];
	}

	return sdot;
}