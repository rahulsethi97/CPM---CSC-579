#include<bits/stdc++.h>
#include "MyLibrary.h"
using namespace std;

int findInterval(int k , double num){
	double start = 0.0;
	double size = (double)1.0/k;
	int ans = 0;
	for(double i = start ; i < 1; i += size){
		if( num >= i && num <= (i+size))
			break;
		ans++;
	}
	return ans;
}

bool chiSquareTest(vector<double> randomNumbers , double alpha){
	bool res = false;
	cout<<"--------------------Chi Sqaure Test------------------\n\n";
	
	int k = 15;
	cout<<"K: "<<k<<"\n";

	int len = randomNumbers.size();
	
	int ctr[k];

	for(int i = 0 ; i < 15 ; i++)
		ctr[i] = 0;

	for(int i = 0 ; i < len ; i++){
		ctr[findInterval(k , randomNumbers[i])]++;
	}
	cout<<"Interval Values: ";
	for(int i = 0 ; i < k ; i++)
		cout<<ctr[i]<<" ";
	cout<<"\n";

	double X2 = 0;

	for(int i = 0 ; i < k ; i++){
		X2 += pow( double((double)ctr[i] - (double)len/k) , 2);
	}
	
	X2 = (double)(X2 * (double)k) / (double)len;

	cout<<"X2: "<<X2<<"\n";
	double sigVal = 21.064;
	cout<<"Alpha: "<<alpha<<"\n";
	cout<<"Chi Sqaure Value for DF = 14 and Alpha = 0.1: "<<sigVal<<"\n";

	if(X2 > sigVal){
		cout<<"As "<<X2<<" > "<<sigVal<<" -> Null Hypothesis is rejected.\n\n";
		res = false;
	}else{
		cout<<"As "<<X2<<" <= "<<sigVal<<" -> Null Hypothesis is Accepted.\n\n";
		res = true;
	}

	cout<<"------------------------------------------------------\n\n";
	return res;
}