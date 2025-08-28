#include<stdio.h>
#include<stdlib.h>

void transpose(int r, int c, int *in, int *out){
	for(int i = 0; i < c; i++){
		for(int j = 0; j < r; j++){
			out[i + j*r] = in[j + i*r];
		}
	}
}


void print_mat(int r, int c, int *mat, int lim){
	for(int i = 0; i < c && i < lim; i++){
		for(int j = 0; j < r && j < lim; j++){
			printf("%d ", mat[j + i*r]);
		}

		if(lim < r){
			printf("...");
		}

		printf("\n");
	}

	if(lim<c){
		for(int i = 0; i < lim; i++){
			printf("| ");
		}

		printf("\\\n");
	}
}


int main(){
	int *mat = malloc(sizeof(int) * R * C);
	int *mat_t = malloc(sizeof(int) * R * C);

	srand(3);
	for(int i = 0; i < R * C; i++)
		mat[i] = rand() % 10;


	transpose(R, C, mat, mat_t);

	print_mat(R, C, mat, 10);
	printf("\n");
	print_mat(C, R, mat_t, 10);

	return 0;
}


