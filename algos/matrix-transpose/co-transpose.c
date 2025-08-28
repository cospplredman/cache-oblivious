#include<stdio.h>
#include<stdlib.h>

void sub_transpose(int r, int c, int *in, int *out, int sx, int sy, int sw, int sh){
	for(int i = 0; i < sw; i++){
		for(int j = 0; j < sh; j++){
			out[(sx + i) + (sy + j)*r] = in[(sy + j) + (sx + i)*r];
		}
	}
}

void co_transpose(int r, int c, int *in, int *out, int sx, int sy, int w, int h){
	if(w * h < 256){
		sub_transpose(r, c, in, out, sx, sy, w, h);
		return;
	}


	if(h > w){
		co_transpose(r, c, in, out, sx, sy, w, h/2);
		co_transpose(r, c, in, out, sx, sy + h/2, w, h - h/2);
	}else{
		co_transpose(r, c, in, out, sx, sy, w/2, h);
		co_transpose(r, c, in, out, sx+w/2, sy, w - w/2, h);
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


	co_transpose(R, C, mat, mat_t, 0, 0, C, R);

	print_mat(R, C, mat, 10);
	printf("\n");
	print_mat(C, R, mat_t, 10);

	return 0;
}


