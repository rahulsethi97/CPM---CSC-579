#include<bits/stdc++.h>
#include "MyLibrary.h"
using namespace std;

queue<pair<int , pair<double , double> > > packets1;	//packets1 which arrive from server
vector<double> totalTime1;
int N1;
double dh1 , dl1 , stisq1 , stcq1 , batchSize1;
void populatepackets(){
	totalTime1.push_back(0);
	srand (time(NULL));
	double randN1um0to1;
	double expRandN1um;
	for(int i = 1 ; i <= N1 ; i++){
		// cout<<i<<"\n";
		totalTime1.push_back(0);
		do{
			randN1um0to1 = double((rand() % 100) + 1)/100;
			expRandN1um = -log(1 - randN1um0to1);
		} while(expRandN1um == -log(0));
		packets1.push(make_pair(i , make_pair (expRandN1um * stisq1 , expRandN1um * stcq1) ) );
	}
}



void input(){
	cin>>N1;
	cout<<"N1: "<<N1<<"\n";
	
	cin>>dh1;
	cout<<"Dh: "<<dh1<<"\n";
	
	cin>>dl1;
	cout<<"Dl: "<<dl1<<"\n";
	
	cin>>stisq1;
	cout<<"Mean service time in the infinite server queue: "<<stisq1<<"\n";
	
	cin>>stcq1;
	cout<<"Mean service time in the client queue: "<<stcq1<<"\n";

	cin>>batchSize1;
	cout<<"batchSize1: "<<batchSize1<<"\n";
}

int main(){
	// freopen ("SimulationTask4Output.txt","w",stdout);	//Output is given to this file.
	freopen ("SimulationTask4Input.txt","r",stdin);		//Input is taken from this file.
	input();
	populatepackets();

	for(int i = 1 ; i < 20 ; i+=3){
		for(int j = i+1 ; j < 20 ; j+=3){
			simulateUtil(i,j,N1,dh1,dl1,stisq1,stcq1 , packets1 , totalTime1 , batchSize1);	
		}
		
	}
}