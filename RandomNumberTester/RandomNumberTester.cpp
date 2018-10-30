#include<bits/stdc++.h>
#include "MyLibrary.h"
using namespace std;

vector<int> randomNumbers;
vector<double> randomNumbers0to1;
int n;
void input(){
	cout<<"No of Random Numbers: ";
	cin>>n;
	srand (time(NULL));
	
	for(int i = 0 ; i < n ; i++){
		int randNum = (rand() % n) + 1;
		double randNum0to1 = double(randNum)/n;
		randomNumbers.push_back(randNum);
		randomNumbers0to1.push_back(randNum0to1);
	}
	cout<<"\n";
}

int main(){
	input();

	cout<<"Random Numbers Generated:\n";
	int len = randomNumbers.size();
	for(int i = 0 ; i < len ; i++)
		cout<<randomNumbers[i]<<" ";
	cout<<"\n\n";

	cout<<"Random Numbers [0,1] Generated:\n";
	len = randomNumbers0to1.size();
	for(int i = 0 ; i < len ; i++)
		cout<<randomNumbers0to1[i]<<" ";
	cout<<"\n\n";
	frequencyTest(randomNumbers , 0.01);
	runsTest(randomNumbers , 0.01);
	chiSquareTest(randomNumbers0to1 , 0.1);
}