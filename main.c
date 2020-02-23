#include <stdlib.h>
#include <stdio.h>

#include <complex.h>

#undef complex
typedef double _Complex complex;

typedef enum Eltype {INT, COMPLEX} Eltype;

typedef struct Matrix{
	Eltype eltype;
	int size;

	void **values;
} Matrix;



Matrix createMatrix(Eltype eltype, int size){
	Matrix matrix;

	matrix.eltype = eltype;
	matrix.size = size;

	int typesize;
	switch(eltype){
		case INT:
			typesize = sizeof(int);
			break;
		case COMPLEX:
			typesize = sizeof(complex);
			break;
		default:
			break;
	}
	matrix.values = calloc(size, sizeof(void*));

	for(int i = 0; i < size; i++) matrix.values[i] = calloc(size, typesize);

	return matrix;
}



Matrix add(Matrix m1, Matrix m2){
	if (m1.eltype != m2.eltype || m1.size != m2.size) return;

	int size = m1.size;
	Matrix result = createMatrix(m1.eltype, size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
		if(m1.eltype == INT)
			((int**)result.values)[i][j] = ((int**)m1.values)[i][j] + ((int**)m2.values)[i][j];
		else if(m1.eltype == COMPLEX){
			((complex**)result.values)[i][j] = ((complex**)m1.values)[i][j] + ((complex**)m2.values)[i][j];
		}
	}

	return result;
}


Matrix scalMultiply(Matrix m, float num){
	int size = m.size;
	Matrix result = createMatrix(m.eltype, size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
		if(m.eltype == INT)
			((int**)result.values)[i][j] = ((int**)m.values)[i][j] * num;
		if(m.eltype == COMPLEX)
			((complex**)result.values)[i][j] = ((complex**)m.values)[i][j] * num;
	}

	return result;
}



Matrix multiply(Matrix m1, Matrix m2){
	if (m1.size != m2.size) return;

	int size = m1.size;
	Matrix result = createMatrix(m1.eltype, size);

	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
		if(m1.eltype == INT){
			int sum = 0;
			for(int k = 0; k < size; k++){
				sum += ((int**)m1.values)[i][k] * ((int**)m2.values)[k][j];
			}

			((int**)result.values)[i][j] = sum;
		}
		else if(m1.eltype == COMPLEX){
			complex sum = 0;
			for(int k = 0; k < size; k++){
				sum += ((complex**)m1.values)[i][k] * ((complex**)m2.values)[k][j];
			}

			((complex**)result.values)[i][j] = sum;
		}
	}

	return result;
}



int main(int argc, char **argv){

	return 0;
}