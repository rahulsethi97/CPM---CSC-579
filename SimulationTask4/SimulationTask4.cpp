/*
 * Author: Rahul Sethi
 * Lasts Modified: 12/05/2018
 * Subject: CSC 579
 */

#include<bits/stdc++.h>
using namespace std;

/*
 * Class that contain the data members for each output line.
 */
class SimulationEvent{
public:
	double mcl;
	int eventNo;
	char transSpeed;
	double clp;
	vector<pair<vector<double> , int > > inifinteQueuePackets;
	double clcq;
	int serviceQueueSize;
	vector<double> serviceQueue;
	int speedFlag; //1 for Up and 0 for down;

};

queue<pair<int , pair<double , double> > > packets;	//Packets which arrive from server
vector<SimulationEvent> events;			//It contains output of each line
SimulationEvent sharedObject;			
int lowerThreshold;						//Lower Threshold
int upperThreshold;						//Upper Threshold
int lastSpeedFlag;						//Speed for changing the speed of the server
double mcl;								//Master Clock
double clp;								//Clock time for next packet departure from server
double clcq;							//Clock time when next packet will be served at the service queue
double dh;								//Time after which packet departs from server at High Speed.
double dl;								//Time after which packet departs from server at Low Speed.
double stisq;							//Mean Service time in the infinite server queue.
double stcq;							//Mean Service time in the client queue.
int N;									//Number of packets

/*
 * Variables for Assigment 3
 */
int batchSize;
vector<double> totalTime;
vector<vector<double> > batches;
vector<double> batchMeans;
double meanOfAllBatches;
double standardDeviation;

/*
 * Variables for Assigment 4
 */
vector<pair<double , double> > idleTime;
vector<double> batchTotalTime;
vector<pair<double , vector<double> > > idleTimeBatches;
vector<double> probOfBatches;
double probOfAllBatches;
double standardDeviationIdleTime;



/*
 *	This funcion populates the packets with delays and service time according to
 *	given mean service time in both the queues.
 */
void populatepackets1(){
	totalTime.push_back(0);
	srand (time(NULL));
	double randNum0to1;
	double expRandNum;
	for(int i = 1 ; i <= N ; i++){
		totalTime.push_back(0);
		do{
			randNum0to1 = double((rand() % 100) + 1)/100;
			expRandNum = -log(1 - randNum0to1);
		} while(expRandNum == -log(0));
		packets.push(make_pair(i , make_pair (expRandNum * stisq , expRandNum * stcq) ) );
	}
}


/*
 *	This function is used to initiate the simulation with initial conditions.
 */
void initEvents(){
	sharedObject.mcl = 0;
	sharedObject.transSpeed = 'H';
	sharedObject.clp = dh;
	sharedObject.serviceQueueSize = 0;
	sharedObject.clcq = -1;
	sharedObject.speedFlag = -1;
	sharedObject.eventNo = -1;
}


/*
 *	This function updates the MCL value to the next MCL value where any of the
 *	3 events will occur.
 */
void nextMcl(){
	vector<pair<vector<double> ,int > > infiniteQueuePackets = sharedObject.inifinteQueuePackets;
	int len = infiniteQueuePackets.size();
	double minDep = INT_MAX;
	for(int i = 0; i < len ; i++){
		if(infiniteQueuePackets[i].first[0] >= mcl){
			minDep = min(minDep , infiniteQueuePackets[i].first[0]);
		}
	}

	if(clp == -1){
		if(clcq == -1)
			mcl = minDep;
		else
			mcl = min(minDep , clcq);
	}else{
		if(clcq == -1)
			mcl = min(clp , minDep);
		else
			mcl = min(clp , min(minDep , clcq));
	}
	if(sharedObject.serviceQueue.size() == 0){
		idleTime.push_back(make_pair(mcl , 0));
	}else{
		idleTime.push_back(make_pair(mcl , 1));
	}
}


/*
 *	This function initiates the global parameters.
 */
void init(){
	lastSpeedFlag = 1;
	nextMcl();
	clp = dh;
	clcq = -1;
	// populatepackets();
	initEvents();
}


/*
 *	This function takes the input from the input file.
 */
void input1(){
	// cin>>N;
	//cout<<"N: "<<N<<"\n";
	
	// cin>>dh;
	//cout<<"Dh: "<<dh<<"\n";
	
	// cin>>dl;
	//cout<<"Dl: "<<dl<<"\n";
	
	// cin>>stisq;
	//cout<<"Mean service time in the infinite server queue: "<<stisq<<"\n";
	
	// cin>>stcq;
	//cout<<"Mean service time in the client queue: "<<stcq<<"\n";

	/*cin>>lowerThreshold;
	cout<<"Tl: "<<lowerThreshold<<"\n";

	cin>>upperThreshold;
	cout<<"Th: "<<upperThreshold<<"\n";*/
	
	cin>>batchSize;
	//cout<<"BatchSize: "<<batchSize<<"\n";
	
}


/*
 *	This event checks if at given MCL event 2 will occur or not.
 */
bool checkEvent2(double mcl){
	vector<pair<vector<double> , int> > infiniteQueuePackets = sharedObject.inifinteQueuePackets;
	int len = infiniteQueuePackets.size();
	for(int i = 0; i < len ; i++){
		if(infiniteQueuePackets[i].first[0] == mcl)
			return true;
	}
	return false;
}


/*
 *	This function performs the event 1. Packet departs from the server queue.
 *	Find the next clock cycle for the next packet and change the speed accordingly.
 *	Push the packet into Infinite Server Queue.
 */
void performEvent1(){
	double packet = packets.front().second.first;
	int id = packets.front().first;
	double serviceTime = packets.front().second.second;
	packets.pop();
	sharedObject.mcl = mcl;
	sharedObject.eventNo = 1;
	if(lastSpeedFlag == 1){
		sharedObject.transSpeed = 'H';
		clp += dh;
	}
	else if(lastSpeedFlag == 0){
		sharedObject.transSpeed = 'L';
		clp += dl;
	}

	if(packets.empty())
		clp = -1;

	sharedObject.clp = clp;
	vector<double> temp;

	temp.push_back(mcl+packet);
	temp.push_back(packet);
	temp.push_back(serviceTime);
	sharedObject.inifinteQueuePackets.push_back(make_pair(temp , id));
	sort(sharedObject.inifinteQueuePackets.begin() , sharedObject.inifinteQueuePackets.end());
	sharedObject.speedFlag = -1;
	events.clear();
	events.push_back(sharedObject);

	/*if(sharedObject.serviceQueue.size() == 0)
		idleTime.push_back(make_pair(mcl , 0));
	else
		idleTime.push_back(make_pair(mcl , 1));*/
	
	totalTime[id] += serviceTime + packet;
	if(sharedObject.clp != -1)
		totalTime[id] += (sharedObject.clp - mcl);
}

/*
 *	This function performs the event 2. Packet departs from the inifinite server queue.
 *	Push the packet into Service Queue.
 *	Find the next clock cycle when the next packet in service queue will be serviced(If Necessary).
 */
void performEvent2(){
	sharedObject.eventNo = 2;
	sharedObject.mcl = mcl;
	int len = sharedObject.inifinteQueuePackets.size();
	vector<pair<vector<double> ,int > > newInfiniteQueuePackets;
	for(int i = 0 ; i < len ; i++){
		if(sharedObject.inifinteQueuePackets[i].first[0] == mcl){
			sharedObject.serviceQueue.push_back(sharedObject.inifinteQueuePackets[i].first[2]);	
		}else{
			newInfiniteQueuePackets.push_back(sharedObject.inifinteQueuePackets[i]);
		}
	}

	sort(sharedObject.serviceQueue.begin() , sharedObject.serviceQueue.end());

	sharedObject.inifinteQueuePackets  = newInfiniteQueuePackets;

	if(sharedObject.clcq == -1){
		sharedObject.clcq = mcl + sharedObject.serviceQueue[0];
		clcq = mcl + sharedObject.serviceQueue[0];
	}

	sharedObject.serviceQueueSize = sharedObject.serviceQueue.size();

	if(sharedObject.serviceQueueSize > upperThreshold){
		sharedObject.speedFlag = 0;
		lastSpeedFlag = 0;
	}
	else if(sharedObject.serviceQueueSize <= upperThreshold){	
		sharedObject.speedFlag = 1;
		lastSpeedFlag = 1;
	}
	else
		sharedObject.speedFlag = -1;

	events.clear();
	events.push_back(sharedObject);
	
	// if(sharedObject.serviceQueue.size() == 0)
	// 	idleTime.push_back(make_pair(mcl , 0));
	// else
	// 	idleTime.push_back(make_pair(mcl , 1));
	
}

/*
 *	This function performs the event 3. Packet in the service queue gets serviced.
 *	Packet is removed from the service queue.
 *	Find the next clock cycle when the next packet in service queue will be serviced.
 */
void performEvent3(){
	sharedObject.eventNo = 3;

	sharedObject.serviceQueue.erase(sharedObject.serviceQueue.begin());

	sharedObject.serviceQueueSize =  sharedObject.serviceQueue.size();
	sharedObject.mcl = mcl;

	if(sharedObject.serviceQueueSize > 0){
		sharedObject.clcq = mcl + sharedObject.serviceQueue[0];
		clcq = mcl + sharedObject.serviceQueue[0];
	}
	else{
		sharedObject.clcq = -1;
		clcq = -1;
	}
	sharedObject.speedFlag = -1;
	events.clear();
	events.push_back(sharedObject);
	
	// if(sharedObject.serviceQueue.size() == 0)
	// 	idleTime.push_back(make_pair(mcl , 0));
	// else
	// 	idleTime.push_back(make_pair(mcl , 1));
}

/*
 *	This function populates the events vector and check which event needs to be called
 *	and call the events accordingly. MCL is updated everytime a event occurs.
 */
void simulate(){
	bool event1Flag = false;
	bool event2Flag = false;
	bool event3Flag = false;

	bool flag;
	while(!packets.empty()){
		flag = false;
		if(mcl == clp){
			performEvent1();
			flag = true;
		}
		if(checkEvent2(mcl)){
			performEvent2();
			flag = true;
		}
		if(clcq == mcl){
			performEvent3();
			flag = true;		
		}

		if(!flag){
			sharedObject.mcl = mcl;
			sharedObject.eventNo = 0;
			events.clear();
			events.push_back(sharedObject);
		}
		nextMcl();
	}

	while(sharedObject.inifinteQueuePackets.size() > 0){
		flag = false;
		if(checkEvent2(mcl)){
			performEvent2();
			flag = true;
		}
		if(clcq == mcl){
			performEvent3();
			flag = true;
		}

		if(!flag){
			sharedObject.mcl = mcl;
			sharedObject.eventNo = 0;
			events.clear();
			events.push_back(sharedObject);
		}
		nextMcl();
	}

	while(sharedObject.serviceQueueSize > 0){
		flag = false;
		if(clcq == mcl){
			performEvent3();
			flag = true;
		}
		if(!flag){
			sharedObject.mcl = mcl;
			sharedObject.eventNo = 0;
			events.clear();
			events.push_back(sharedObject);
		}
		nextMcl();
	}

}
/*
 *	This function divides the Times into different batches
 */
void populateBatches(){

	vector<double> batch;
	int len = totalTime.size();
	for(int i = 1 ; i < len ; ){
		int ctr = batchSize;
		batch.clear();
		while(i< len && ctr--){
			batch.push_back(totalTime[i]);
			i++;
		}
		batches.push_back(batch);
	}

	/*
	 * Populating Batched for Idle Time
	 */

	vector<double> idleTimeBatch;
	len = idleTime.size();
	for(int i = 0 ; i < len ; ){
		int ctr = batchSize;
		double startTime = idleTime[i].first;
		idleTimeBatch.clear();
		while(i < len && ctr--){
			idleTimeBatch.push_back(idleTime[i].second);
			i++;
		}

		double endTime;
		if(i < len)
			endTime = idleTime[i].first;
		else
			endTime = idleTime[len].first;
		idleTimeBatches.push_back(make_pair(endTime - startTime , idleTimeBatch));
	}
	
}

void calculate95thPercentileForIdleTime(){
	// cout<<"\n--------------------Calculations for 95thPercentile For Idle Time-----------------------\n\n";
	int noOfBatches = idleTimeBatches.size();
	// cout<<"Number of Batches: "<<noOfBatches<<"\n";
	
	double prob;
	meanOfAllBatches = 0;
	for(int i = 0 ; i < noOfBatches ; i++){
		prob = 0;
		double a = 0;
		for(int j = 0 ; j < idleTimeBatches[i].second.size() ; j++){
			if(idleTimeBatches[i].second[j] == 0)
				prob++;
			else
				a++;
		}
		//cout<<i<<" "<<prob<<" "<<a<<"\n";
		// prob /= idleTimeBatches[i].first;
		prob /= idleTimeBatches[i].second.size();
		probOfAllBatches += prob;
		probOfBatches.push_back(prob);
	}
	probOfAllBatches /= noOfBatches;

	cout<<"Mean of probabilities of all batches: "<<probOfAllBatches<<"\n";

	// cout<<"----------------------------------------------------------------------------------------";
}

void calculate95thPercentile(){

	// cout<<"\n-------------------------Calculations for 95thPercentile--------------------------------\n\n";

	// cout<<"Number of Batches: "<<batches.size()<<"\n";
	int noOfBatches = batches.size();
	double mean;
	meanOfAllBatches = 0;
	for(int i = 0 ; i < noOfBatches ; i++){
		mean = 0;
		for(int j = 0 ; j < batches[i].size() ; j++){
			mean += batches[i][j];
		}
		mean /= batches[i].size();
		meanOfAllBatches += mean;
		batchMeans.push_back(mean);
	}
	meanOfAllBatches /= noOfBatches;

	cout<<"Mean of all batches: "<<meanOfAllBatches<<"\n";

	double temp = 0 ;
	for(int i = 0 ; i < batchMeans.size() ; i++){
		temp += ((batchMeans[i] - meanOfAllBatches) * (batchMeans[i] - meanOfAllBatches));
	}

	standardDeviation = sqrt(temp / noOfBatches);

	// cout<<"Standard Deviation: "<<standardDeviation<<"\n";

	double temp2 = standardDeviation / sqrt(noOfBatches - 1);
	temp2 *= 1.96;
	cout<<"The confidence interval at 95% confidence: ( "<<meanOfAllBatches - temp2<<" , "<<meanOfAllBatches + temp2<<" )\n";
	// cout<<"----------------------------------------------------------------------------------------";
}

/*
 *	This function displays all events that occurs.
 */
void display(){
	int len = events.size();
	cout<<"MCL\t\tEventNo\t\tSpeed\t\tCLp\t\tCLcq\t\tQueueSize\tFlag\t\tInfinite Server Queue\n";
	for(int i = 0 ; i < len ; i++){
		cout<<events[i].mcl<<"\t\t";
		if(events[i].eventNo == -1)
			cout<<"-\t\t";
		else
			cout<<events[i].eventNo<<"\t\t";
		cout<<events[i].transSpeed<<"\t\t";

		if(events[i].clp == -1)
			cout<<"-\t\t";
		else
			cout<<events[i].clp<<"\t\t";

		if(events[i].clcq == -1)
			cout<<"-\t\t";
		else
			cout<<events[i].clcq<<"\t\t";

		cout<<events[i].serviceQueueSize<<"\t\t";
		if(events[i].speedFlag == -1)
			cout<<"-\t\t";
		else
			cout<<events[i].speedFlag<<"\t\t";

		vector<pair<vector<double> , int> > q = events[i].inifinteQueuePackets;

		int len = q.size();

		for(int j = 0 ; j < len ; j++){
			cout<<q[j].first[0]<<"("<<q[j].first[1]<<")";
			if(j < (len-1))
				cout<<",";
		}
		cout<<"\n";
	}	
}

/*
 *	This function displays the initial packets their delays and service time which are generated
 *	randomly.
 */
void displayPackets(){
	cout<<"---------PacketNo -> (Delay , ServiceTime)---------\n";
	queue<pair<int , pair<double,double> > > tmp_q = packets; //copy the original queue to the temporary queue
	int ctr = 1;
	while (!tmp_q.empty())
	{
	    cout<<ctr++<<" -> ("<<tmp_q.front().second.first<<" , "<<tmp_q.front().second.second<<")\n";
	    tmp_q.pop();
	} 

	cout<<"----------------------------------------------------\n\n";
}

int simulateUtil(int l , int h , int n, int DH , int DL , int STISQ , int STCQ , queue<pair<int , pair<double , double> > > p , vector<double> tT , int bS){	
	batchSize = bS;
	lowerThreshold = l;
	upperThreshold = h;
	N = n;
	dh = DH;
	dl = DL;
	stisq = STISQ;
	stcq = STCQ;
	packets = p;
	totalTime = tT;
	cout<<"\n";
	cout<<"Calculating For LowerThreshold: "<<lowerThreshold<<" UpperThreshold: "<<upperThreshold<<"\n";
	init();
	// displayPackets();
	simulate();
	// cout<<"Here2";
	// display();
	populateBatches();
	// cout<<"here3";
	calculate95thPercentile();
	// cout<<"here4";
	calculate95thPercentileForIdleTime();
	// cout<<"here5";
}
