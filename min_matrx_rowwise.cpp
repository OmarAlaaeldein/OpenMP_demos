#include <iostream>
#include <omp.h>
#include <vector>
#include "hpc_helpers.hpp"
using namespace std;


void init(vector<int> &A,int n,int m){
    for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
			A[i*n+j]= i==j?i+20:INT_MAX;
			//cout << A[i*n+j] <<' ';
			}
			//cout << '\n';
		}
}


void sequ(int B[],vector<int> &A,int n, int m)
{
for (int i=0;i<n;i++)
	{
	int x=INT_MAX;
	for (int j=0;j<m;j++){
		if (A[i*n+j]<x){
			x=A[i*n+j];
		}

	}
	B[i]=x;
	}    
}
void para(int B[],vector<int> &A,int n, int m){
int temp;
// USE TASKLOOP ???
#pragma omp parallel for 
for (int i=0;i<n;i++){
    for (int j=0;j<n;j++)
        if (A[i*n+j]<temp)
			temp=A[i*n+j];
    B[i]=temp;
    }
}
int main()
{
 const int m=1<<15;
 const int n=1<<15;
 vector<int> A(n*m);
 int B[n];
 init(A,n,m);
 TIMERSTART(Sequential)
 sequ(B,A,n,m);
 TIMERSTOP(Sequential)
 int C[n];
 TIMERSTART(Parallel)
 para(C,A,n,m);
 TIMERSTOP(Parallel)
 for (int i=0;i<n;i++){
	//cout<<"Sequential "<<B[i]<<" Parallel "<<C[i]<<'\n';
 }
 return 0;
}