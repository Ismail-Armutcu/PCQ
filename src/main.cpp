#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

#include "ApproxCQ.h"
#include "Fifo.h"
#include "IdealCQ.h"
#include "Packet.h"
#include "PriorityQ.h"
#include "qFifo.h"
#include "WFQ.h"

using namespace std;

float generateInterarrivalTime(float lambda) {
	random_device rd;
	mt19937 gen(rd());
	exponential_distribution<float> distribution(lambda);

	return distribution(gen);
}

int generateRandomFlow(int n){
	// Generate a random integer between 0 and n (exclusive)
	return rand() % n;
}

float generatePacketSize(float lambda) {
	// Use C++11 random library to generate exponentially distributed float in [0, 1)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::exponential_distribution<float> distribution(lambda);  // lambda = 1.0

	return distribution(gen);
}


int main(){
	int numLoadLevels = 1000;

	float prioA = 3.0/6;
	float prioB = 1.5/6;
	float prioC = 1.6/6;
	float lambdaPacket = 1;

	vector<float> interarrivalTime ;
	vector<float> packetsize ;
	vector<int> flowno ;
	for(int i = 1; i<=9;i++){
		for (int loadLevel = 0; loadLevel < numLoadLevels; ++loadLevel) {
			float m = generateInterarrivalTime(0.1);
			interarrivalTime.push_back(m);
			packetsize.push_back(m*i/10.0+3.5);
			flowno.push_back(generateRandomFlow(3));
		}
	}
	cout<<interarrivalTime.size()<<endl;
	cout<<packetsize.size()<<endl;
	cout<<flowno.size()<<endl;
	for(int i = 0; i<10;i++){
		int id[3] = {0};
		float totaltime = 0.0;
		float totalpacketsize = 0.0;
		int packetperflow[3] = {0};
		ApproxCQ approxcq(15,3,10);
		IdealCQ idealcq(15,3,10);
		qFifo     newfifo(150);
		WFQ 	fairq(150);
		float temp = 0.0;
		for (int loadLevel = 0; loadLevel < numLoadLevels; ++loadLevel) {



			totaltime+=interarrivalTime.at(loadLevel);
			if(flowno.at(loadLevel) == 0){
				totalpacketsize+= 6;
				packetperflow[0]++;
				Packet packetAapproxCQ("AapproxCQ"+to_string(id[flowno.at(loadLevel)]),prioA,6,flowno.at(loadLevel));
				Packet packetAidealCQ("AidealCQ"+to_string(id[flowno.at(loadLevel)]),prioA,6,flowno.at(loadLevel));
				Packet packetAFIFO("AFIFO"+to_string(id[flowno.at(loadLevel)]),prioA,6,flowno.at(loadLevel));
				Packet packetAWFQ("AWFQ"+to_string(id[flowno.at(loadLevel)]++),prioA,6,flowno.at(loadLevel));
//				Packet packetAapproxCQ("AapproxCQ"+to_string(id[flowno.at(loadLevel)]),prioA,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
//				Packet packetAidealCQ("AidealCQ"+to_string(id[flowno.at(loadLevel)]),prioA,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
//				Packet packetAFIFO("AFIFO"+to_string(id[flowno.at(loadLevel)]),prioA,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
//				Packet packetAWFQ("AWFQ"+to_string(id[flowno.at(loadLevel)]++),prioA,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				approxcq.enqueue(packetAapproxCQ);
				idealcq.enqueue(packetAidealCQ);
				newfifo.push(packetAFIFO);
				fairq.enqueue(packetAWFQ);
			}
			else if(flowno[loadLevel] == 1){
				totalpacketsize+= packetsize.at(loadLevel+i*numLoadLevels);
				packetperflow[1]++;
				Packet packetBapproxCQ("BapproxCQ"+to_string(id[flowno.at(loadLevel)]),prioB,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				Packet packetBidealCQ("BidealCQ"+to_string(id[flowno.at(loadLevel)]),prioB,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				Packet packetBFIFO("BFIFO"+to_string(id[flowno.at(loadLevel)]),prioB,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				Packet packetBWFQ("BWFQ"+to_string(id[flowno.at(loadLevel)]++),prioB,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				approxcq.enqueue(packetBapproxCQ);
				idealcq.enqueue(packetBidealCQ);
				newfifo.push(packetBFIFO);
				fairq.enqueue(packetBWFQ);
			}
			else{
				totalpacketsize+= packetsize.at(loadLevel+i*numLoadLevels);
				packetperflow[2]++;
				Packet packetCapproxCQ("CapproxCQ"+to_string(id[flowno.at(loadLevel)]),prioC,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				Packet packetCidealCQ("CidealCQ"+to_string(id[flowno.at(loadLevel)]),prioC,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				Packet packetCFIFO("CFIFO"+to_string(id[flowno.at(loadLevel)]),prioC,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				Packet packetCWFQ("CWFQ"+to_string(id[flowno.at(loadLevel)]++),prioC,packetsize.at(loadLevel+i*numLoadLevels),flowno.at(loadLevel));
				approxcq.enqueue(packetCapproxCQ);
				idealcq.enqueue(packetCidealCQ);
				newfifo.push(packetCFIFO);
				fairq.enqueue(packetCWFQ);

			}


			//cout<<totaltime<<endl;
			newfifo.simulateTime(interarrivalTime.at(loadLevel),temp);//temp ekle diğer func kullan
			fairq.simulateTime(interarrivalTime.at(loadLevel));
			idealcq.simulateTime(interarrivalTime.at(loadLevel));
			approxcq.simulateTime(interarrivalTime.at(loadLevel));



		}
		cout<<"pcq time:"<<approxcq.buckets[0].getTime()<<"	-- fifo time: "<<newfifo.getTime()
																																	<<" -- idealcq time:"<<idealcq.buckets[0].getTime()<<"-- fairqueue time:"<<fairq.getTime()<<endl;
		cout<<"totaltime:"<<totaltime<<" total packet:"<<totalpacketsize<<endl;
		cout<<"Load: "<<totalpacketsize/totaltime<<endl;
		cout<<"			Fifo			"<<"ApproxCQ	"<<"IdealCQ			"<<"WFQ"<<endl;
		cout<<"Total Packets Serviced   "<<newfifo.totalServicedPacketNumber<<"			"<<approxcq.buckets->totalServicedPacketNumber<<" 		"
				<<idealcq.buckets->totalServicedPacketNumber<<"			"<<fairq.totalServicedPacketNumber<<endl;

		cout<<"Total Service Delay   	 "<<newfifo.totalServiceDelay<<"		"<<approxcq.buckets->totalServiceDelay<<" 	"
				<<idealcq.buckets->totalServiceDelay<<"			"<<fairq.totalServiceDelay<<endl;

		cout<<"Total Service Size   	 "<<newfifo.totalServicedSize<<"		"<<approxcq.buckets->totalServicedSize<<" 	"
				<<idealcq.buckets->totalServicedSize<<"			"<<fairq.totalServicedSize<<endl;
	}


	return 0;
}
