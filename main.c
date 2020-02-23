#include <stdlib.h>
#include <stdio.h>

#include <complex.h>

#undef complex
typedef float _Complex complex;

typedef enum {INT, COMPLEX} Eltype;

typedef struct {
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
	if (m1.eltype != m2.eltype || m1.size != m2.size) exit(1);

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
		else if(m.eltype == COMPLEX)
			((complex**)result.values)[i][j] = ((complex**)m.values)[i][j] * num;
	}

	return result;
}



Matrix multiply(Matrix m1, Matrix m2){
	if (m1.eltype != m2.eltype || m1.size != m2.size) exit(1);

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





void printAnsMatrix(Matrix m){
	printf("%s\n", "answer:");
	if(m.eltype == INT)
		for(int i = 0; i < m.size; i++){ for(int j = 0; j < m.size; j++){
			printf("%d ", ((int**)m.values)[i][j]);
		}
		printf("\n");
	}
	else if(m.eltype == COMPLEX)
		for(int i = 0; i < m.size; i++){ for(int j = 0; j < m.size; j++){
			printf("%g+%gi ", creal(((complex**)m.values)[i][j]), cimag(((complex**)m.values)[i][j]));
		}
		printf("\n");
	}
	printf("\n");
}


Matrix scanMatrix(){
	Matrix m;
	printf("%s\n", "type of matrix:\n1. int\n2. complex\n");

	int type;
	scanf("%d", &type); printf("\n");

	printf("%s\n", "size of matrix:");

	int size;
	scanf("%d", &size); printf("\n");

	Eltype eltype;
	if		(type == 1) eltype = INT;
	else if	(type == 2) eltype = COMPLEX;

	m = createMatrix(eltype, size);

	if(eltype == INT){
		printf("%s\n", "elements of matrix:");

		for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
			scanf("%d", &(((int**)m.values)[i][j]));
		}
		printf("\n");
	}

	else if(eltype == COMPLEX){
		printf("%s\n", "real parts of elements of matrix:");

		//real part
		for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
			float real;
			scanf("%f", &real);

			((complex**)m.values)[i][j] += real;
		}
		printf("\n");
		printf("%s\n", "imaginary parts of elements of matrix:");
		//imag part
		for(int i = 0; i < size; i++) for(int j = 0; j < size; j++){
			float imag;
			scanf("%f", &imag);

			((complex**)m.values)[i][j] += imag * I;
		}
		printf("\n");
	}
	return m;
}


void interface(){
	Matrix a;
	Matrix b;
	float n;

	Matrix r;
	while(1){
		printf("%s\n",
			"1. set matrix A\n"
			"2. set matrix B\n"
			"3. set number n\n"
			"4. get A+B\n"
			"5. get A*B\n"
			"6. get n*A\n"
			"7. exit\n"
		);

		int choice;
		scanf("%d", &choice); printf("\n");
		switch(choice){
			case 1:
				a = scanMatrix();
				break;
			case 2:
				b = scanMatrix();
				break;
			case 3:
				scanf("%f", &n); printf("\n");
				break;
			case 4:
				r = add(a, b);
				printAnsMatrix(r);
				break;
			case 5:
				r = multiply(a, b);
				printAnsMatrix(r);
				break;
			case 6:
				r = scalMultiply(a, n);
				printAnsMatrix(r);
				break;
			case 7:
				return;
			default:
				exit(1);
				break;
		}
	}
}


int main(int argc, char **argv){
	interface();

	return 0;
}