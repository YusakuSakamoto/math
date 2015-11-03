#include <iostream>
#include <stdio.h>
#define dimention 4

using namespace std;

int matrix_show(double **mat){
  int i,j;
  
  for(i=0; i<dimention; i++){
	for(j=0; j<dimention; j++){
	  printf("  %.2f", *( *(mat+i)+j) );
	}
	printf("\n");
  }
  return 0;
}

int matrix_inverser(double **input,double **output){
  double buf; //一時的なデータを蓄える
  int i,j,k; //カウンタ

  //単位行列を作る
  for(i=0; i<dimention; i++){
	for(j=0; j<dimention; j++){
	  *( *(output+i)+j) = ((i==j)?1.0:0.0) ;
	}
  }
  //掃き出し法
  for(i=0;i<dimention;i++){
	buf=1/ *(*(input+i)+i);
	for(j=0;j<dimention;j++){
	  *(*(input+i)+j) *= buf;
	  *(*(output+i)+j) *= buf;
	}
	for(j=0;j<dimention;j++){
	  if(i!=j){
		buf=*(*(input+j)+i);
		for(k=0;k<dimention;k++){
		  *(*(input+j)+k) -= *(*(input+i)+k)*buf;
		  *(*(output+j)+k) -= *(*(output+i)+k)*buf;
		}
	  }
	}
  }
  matrix_show(output);
  return 0;
}

int main(void){
  int i;
  double *input_pointer[ dimention ];
  double input_entity[][ dimention ]={
	{ 1, 2, 0,-1},
	{-1, 1, 2, 0},
	{ 2, 0, 1, 1},
	{ 1,-2,-1, 1}};
  
  double *output_pointer[dimention];
  double output_entity[][dimention]={
	{ 0, 0, 0, 0},
	{ 0, 0, 0, 0},
	{ 0, 0, 0, 0},
	{ 0, 0, 0, 0}};

  for(i=0; i<dimention; i++){
	input_pointer[i] = input_entity[i];
	output_pointer[i] = output_entity[i];
  }
  matrix_inverser(input_pointer, output_pointer);
  return 0;
}
