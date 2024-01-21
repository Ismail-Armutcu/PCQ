/*
 * WFQ.cpp
 *
 *  Created on: 18 Oca 2024
 *      Author: iharm
 */

#include "WFQ.h"

#include <algorithm>
#include <iostream>

WFQ::WFQ() {
	qsize = 0;
	virtualTime = 0.0;
	globalTime = 0.0;
	totalServicedPacketNumber = 0;
	totalServicedSize = 0.0;
	totalServiceDelay = 0.0;
	currentPacket = nullptr;
	init = 1;
}

WFQ::WFQ(int size) {
	qsize = size;
	virtualTime = 0.0;
	globalTime = 0.0;
	totalServicedPacketNumber = 0;
	totalServicedSize = 0.0;
	totalServiceDelay = 0.0;
	currentPacket = nullptr;
	init = 1;

}

void WFQ::enqueue(Packet &packet) {

	if((int)qPrio.size() < qsize){
		packet.virtualFinishTime = virtualTime + packet.size/packet.priority;

		packet.arrived(globalTime);
		qPrio.push(new Packet(packet));
		if(init == 1){
			currentPacket = qPrio.top();
			init = 0;
		}
		if(packet.name.find(pack) != string::npos && packet.flow == 0){
			cout<<"Packet arrived: "<<packet<<endl;
		}
	}
	else{
		if(packet.name.find(pack) != string::npos && packet.flow == 0){
			cout<<"Packet Dropped: "<<packet<<endl;
		}
	}
}



/*
void WFQ::simulateTime(float duration) {
	float endTime = globalTime + duration;
	if(qPrio.empty()){
		globalTime += duration;
		return;
	}

	while(globalTime < endTime){
		if(!qPrio.empty()){
			Packet * servicedPacket = qPrio.top();
			if(servicedPacket->size < duration+0.0001){
				virtualTime += servicedPacket->size/servicedPacket->priority;
				duration -= servicedPacket->size;
				pop();
			}
			else{
				virtualTime += duration/servicedPacket->priority;
				globalTime += duration + 0.00001;
				servicedPacket->size -= duration +0.00001;
				//currentPacket->virtualFinishTime = virtualTime + currentPacket->size/currentPacket->priority;
			}
		}
		else{
			globalTime += duration + 0.000001;
			break;
		}
	}
}*/

void WFQ::simulateTime(float duration) {
	float endTime = globalTime + duration;
	if(qPrio.empty()){
		globalTime += duration;
		return;
	}
	while(globalTime < endTime){
		if(!qPrio.empty()){
//			if(currentPacket->size < 0.001){
//				currentPacket = qPrio.top();
//
//			}

			if(currentPacket->size < duration+0.0001 /*&& currentPacket->size > 0.001*/){
				virtualTime += currentPacket->size/currentPacket->priority;
				duration -= currentPacket->size;
				pop();
			}
			else{
				virtualTime += duration/currentPacket->priority;
				globalTime += duration + 0.00001;
				currentPacket->size -= duration +0.00001;
				//currentPacket->virtualFinishTime = virtualTime + currentPacket->size/currentPacket->priority;
			}
		}
		else{
			globalTime += duration + 0.000001;
			break;
		}
	}
}


void WFQ::print() {
	if(qPrio.empty()){
		cout<<"Priority Queue is empty"<<endl;
	}
	else{
		priority_queue<Packet*,vector<Packet*>,PacketVirtualTimeCompare> tempq=qPrio;
		while(!tempq.empty()){
			cout<<*(tempq.top())<<" ";
			tempq.pop();
		}
		cout<<endl;
	}

}

float WFQ::getTime() {
	return globalTime;
}

WFQ::~WFQ() {

}

Packet* WFQ::pop() {
	if(!qPrio.empty()){
		Packet* servicedPacket = qPrio.top();
		globalTime += currentPacket->size;
		currentPacket->serviced(globalTime);

		totalServicedPacketNumber++;
		totalServicedSize += currentPacket->packet_size;
		totalServiceDelay += currentPacket->serviceTime - currentPacket->arrivalTime;
		currentPacket->size = 0.0;
		if(currentPacket->name.find(pack) != string::npos && currentPacket->flow == 0){
			cout<<"Packet Serviced: "<<*currentPacket<<endl;
		}
		qPrio.pop();
		if(!qPrio.empty()){
			currentPacket = qPrio.top();
		}
		else{
			init = 1;
		}

		return servicedPacket;
	}
	else{
		return nullptr;
	}

}
/*
Packet* WFQ::pop() {
	if(!qPrio.empty()){
		Packet* servicedPacket = qPrio.top();
		servicedPacket->serviced(globalTime);
		globalTime += servicedPacket->size;
		totalServicedPacketNumber++;
		totalServicedSize += servicedPacket->packet_size;
		totalServiceDelay += servicedPacket->serviceTime - servicedPacket->arrivalTime;
		servicedPacket->size = 0.0;
		if(servicedPacket->name.find(pack) != string::npos && servicedPacket->flow == 0){
			cout<<"Packet Serviced: "<<*servicedPacket<<endl;
		}
		qPrio.pop();
		if(!qPrio.empty()){
			currentPacket = qPrio.top();
		}

		return servicedPacket;
	}
	else{
		return nullptr;
	}

}*/
