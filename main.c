#include <stdlib.h>
#include <stdio.h>

#include <complex.h>


typedef struct MatrixI{
	int size;

	int **values;
} MatrixI;

typedef struct MatrixC{
	int size;

	float complex **values;
} MatrixC;



MatrixI createMatrixI(int size){
	MatrixI matrix;

	matrix.size = size;
	matrix.values = calloc(size, sizeof(typeof(*matrix.values)));

	for(int i = 0; i < size; i++) matrix.values[i] = calloc(size, sizeof(typeof(**matrix.values)));

	return matrix;
}

MatrixC createMatrixC(int size){
	MatrixC matrix;

	matrix.size = size;
	matrix.values = calloc(size, sizeof(typeof(*matrix.values)));

	for(int i = 0; i < size; i++) matrix.values[i] = calloc(size, sizeof(typeof(**matrix.values)));

	return matrix;
}



MatrixI addI(MatrixI m1, MatrixI m2){
	if (m1.size != m2.size) return;

	int size = m1.size;
	MatrixI result = createMatrixI(size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
		result.values[i][j] = m1.values[i][j] + m2.values[i][j];
	}

	return result;
}

MatrixC addC(MatrixC m1, MatrixC m2){
	if (m1.size != m2.size) return;

	int size = m1.size;
	MatrixC result = createMatrixC(size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
		result.values[i][j] = m1.values[i][j] + m2.values[i][j];
	}

	return result;
}



MatrixI scalMultiplyI(MatrixI m, float num){
	int size = m.size;
	MatrixI result = createMatrixI(size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
		result.values[i][j] = m.values[i][j] * num;
	}

	return result;
}

MatrixC scalMultiplyC(MatrixC m, float num){
	int size = m.size;
	MatrixC result = createMatrixC(size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
		result.values[i][j] = m.values[i][j] * num;
	}

	return result;
}



MatrixI multiplyI(MatrixI m1, MatrixI m2){
	if (m1.size != m2.size) return;

	int size = m1.size;
	MatrixI result = createMatrixI(size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){

		int sum = 0;
		for(int k = 0; k < size; k++){
			sum += m1.values[i][k] * m2.values[k][j];
		}

		result.values[i][j] = sum;
	}

	return result;
}

MatrixC multiplyC(MatrixC m1, MatrixC m2){
	if (m1.size != m2.size) return;

	int size = m1.size;
	MatrixC result = createMatrixC(size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){

		float complex sum = 0;
		for(int k = 0; k < size; k++){
			sum += m1.values[i][k] * m2.values[k][j];
		}

		result.values[i][j] = sum;
	}

	return result;
}



int main(int argc, char **argv){

	return 0;
}