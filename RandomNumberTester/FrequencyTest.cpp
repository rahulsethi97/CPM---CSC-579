#include<bits/stdc++.h>
#include "MyLibrary.h"
using namespace std;

string decimalToBinary(int num){
	if(num == 0)
		return "0";
	string res = "";

	while(num > 0){
		res += ((num%2) == 0 ? "0" : "1" );
		num /= 2;
	}
	reverse(res.begin() , res.end());
	return res;
}

bool frequencyTest(vector<int> randomNumbers , double alpha){
	cout<<"--------------------Frequency Test--------------------\n\n";
	string binaryString = "";
	int len = randomNumbers.size();
	bool res;

	for(int i = 0 ; i < len ; i++){
		binaryString += decimalToBinary(randomNumbers[i]);
	}

	cout<<"Concatenated Binary String: "<<binaryString<<"\n";

	int Sn = 0;
	double Sobs;
	double Pval;

	len = binaryString.size();

	for(int i = 0 ; i < len ; i++){
		if(binaryString[i] == '0')
			Sn--;
		else
			Sn++;
	}

	cout<<"Sn: "<<Sn<<"\n";

	Sobs = (double)abs(Sn) / sqrt(len);

	cout<<"Sobs: "<<Sobs<<"\n";

	Pval = erfc(Sobs / sqrt(2));

	cout<<"Pval: "<<Pval<<"\n";

	cout<<"Alpha: "<<alpha<<"\n";

	if(Pval < alpha){
		cout<<"As "<<Pval<<" < "<<alpha<<" -> Null Hypothesis is rejected.\n\n";
		res = false;
	}else{
		cout<<"As "<<Pval<<" >= "<<alpha<<" -> Null Hypothesis is Accepted.\n\n";
		res = true;
	}

	cout<<"------------------------------------------------------\n\n";
	return res;
}