#include<bits/stdc++.h>
#include "MyLibrary.h"
using namespace std;

vector<int> runs;

double mat[6][6] =
    {
        {4529.4,9044.9,13568,18091,22615,27892},
		{9044.9,18097,27139,36187,45234,55789},
		{13568,27139,40721,54281,67852,83685},
		{18091,36187,54281,72414,90470,111580},
		{22615,45234,67852,90470,113262,139476},
		{27892,55789,83685,111580,139476,172860}
    };

double b[6] = {1/6,5/24 ,11/120 ,19/720 ,29/5040 ,1/840};

void init(){
	runs.push_back(0);
	runs.push_back(0);
	runs.push_back(0);
	runs.push_back(0);
	runs.push_back(0);
	runs.push_back(0);
}

bool runsTest(vector<int> randomNumbers , double alpha){
	bool res = false;
	init();
	cout<<"--------------------Runs Test--------------------\n\n";
	
	int len = randomNumbers.size();
	
	int ctr = 0;
	for(int i = 1 ; i < len ; i++){
		if(randomNumbers[i] >= randomNumbers[i-1]){
			ctr++;
		}else{
			runs[min( 5 , ctr )]++;
			ctr = 0;
		}
	}
	runs[min( 5 , ctr )]++;

	double R = 0;
	double sum = 0;

	for(int i = 0 ; i < 6 ;i++){
		for(int j = 0 ; j < 6 ; j++){
			sum += ( (runs[i] - len*b[i]) * (runs[j] - len*b[j]) * mat[i][j] ); 
		}
	}
	R = (double)sum / (double)len;
	cout<<"R: "<<R<<"\n";

	cout<<"Alpha: "<<alpha<<"\n\n";

	/*if(R < alpha){
		cout<<"As "<<R<<" < "<<alpha<<" -> Null Hypothesis is rejected.\n\n";
		res = false;
	}else{
		cout<<"As "<<R<<" >= "<<alpha<<" -> Null Hypothesis is Accepted.\n\n";
		res = true;
	}*/

	cout<<"------------------------------------------------------\n\n";
	return res;
}