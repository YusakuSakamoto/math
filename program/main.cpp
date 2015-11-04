#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define dimention 3

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
  //matrix_show(input);

  //単位行列を作る
  for(i=0; i<dimention; i++){
	for(j=0; j<dimention; j++){
	  *( *(output+i)+j) = ((i==j)?1.0:0.0) ;
	}
  }
  //matrix_show(input);
  //掃き出し法
  for(i=0;i<dimention;i++){
	//printf("%d\n",i);
	//matrix_show(input);
	buf = 1.0/ (*(*(input+i)+i));
	for(j=0;j<dimention;j++){
	  *(*(input+i)+j) *= buf;
	  *(*(output+i)+j) *= buf;
	}
	for(j=0;j<dimention;j++){
	  if(i!=j){
		buf = *(*(input+j)+i);
		for(k=0;k<dimention;k++){
		  *(*(input+j)+k) -= *(*(input+i)+k)*buf;
		  *(*(output+j)+k) -= *(*(output+i)+k)*buf;
		}
	  }
	}
  }
  //matrix_show(output);
  return 0;
}

int input_entity_creator(double **mat, double *x){
  int i=0;
  int j=0;
  
  for(i=0;i<dimention; i++){
	for(j=0;j<dimention; j++){
	  *(*(mat+i)+j) = exp( -1 * pow((*(x+i) - *(x+j)),2));
	}
  }
  
  return 0;
}

int main(void){
  int s=0;
  // file input get.
  //=======================================
  {
	ifstream ifs("../data/test.dat");
	std::string line;
	while (getline(ifs, line, '\t')) {
	  s++;
	}
  }
  //======================================

  double file[s];
  //=======================================
  {
	ifstream ifs("../data/test2.dat");
	std::string line;
	//cout << s << endl;
	s=0;
	while (std::getline(ifs, line, '\t')) {
	  //cout << line << endl;
	  file[s++] = atof( line.c_str() );
	  //cout << file[s-1] << endl;
	}
  }
  //=====================================


  const int num = s;
  double x[num/2];
  double y[num/2];
  // data spliter
  //=======================================
  {
	int q=0;
	int e=0;
	for(q=0;q<num;){
	  x[e] = file[q++];
	  y[e++] = file[q++];
	}

	for(q=0;q<num/2;q++){
	  //cout << "x = " << x[q] << " , y = " << y[q] << endl;
	}
  }
  //=============================================

  
  
  int i;
  double *input_pointer[ dimention ];
  double input_entity[ dimention ][ dimention ] = {};  
  double *output_pointer[dimention];
  double output_entity[ dimention ][dimention] = {};
  for(i=0; i<dimention; i++){
	input_pointer[i]  = input_entity[i];
	output_pointer[i] = output_entity[i];
  }
  
  input_entity_creator( input_pointer , x);
  matrix_show(input_pointer);
  
  matrix_inverser(input_pointer, output_pointer);
  matrix_show(output_pointer);

  double alpha[ dimention ];
  double value = 0;
  int j;
  for(i=0;i<dimention;i++){
	value = 0.0;
	for(j=0;j<dimention;j++){
	  value += (*(output_pointer[i] + j)) * (y[j]);
	}
	alpha[i] = value;
	printf("%f\n",alpha[i]);
  }

  ofstream ofs("../data/out.dat");
  int r;
  for(r=-20;r<20;r++){
	double t=0;
	for(j=0;j<dimention;j++){
	  t += alpha[j] * exp( -1 * pow((r*0.1-x[j]),2) );
	}
	ofs << r*0.1 << "\t" <<  t << endl;
  }
  
  return 0;
}
