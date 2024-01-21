/*
 * qPrio.cpp
 *
 *  Created on: 18 Oca 2024
 *      Author: iharm
 */

#include "PriorityQ.h"
float PriorityQ::globalTime = 0.0;
int PriorityQ::totalServicedPacketNumber = 0;
float PriorityQ::totalServicedSize = 0.0;
float PriorityQ::totalServiceDelay = 0.0;

PriorityQ::PriorityQ() {
	this->qsize = 0;

}

PriorityQ::PriorityQ(int size) {
	this->qsize = size;

}

PriorityQ::~PriorityQ() {
	this->globalTime = 0.0;
	this->totalServicedPacketNumber = 0;
	this->totalServicedSize = 0.0;
	this->totalServiceDelay = 0.0;
}

void PriorityQ::push(Packet &packet) {
	if((int)qPrio.size() < qsize){
		packet.arrived(globalTime);
		if(packet.name.find(pack) != string::npos && packet.flow == 0){

			cout<<"Packet arrived: "<<packet<<endl;
		}
		qPrio.push(new Packet(packet));
	}
	else{
		if(packet.name.find(pack) != string::npos && packet.flow == 0){
			cout<<"Packet Dropped: "<<packet<<endl;
		}
	}

}

Packet* PriorityQ::pop() {
	if(!qPrio.empty()){
		Packet* servicedPacket = qPrio.top();
		globalTime += servicedPacket->size;
		servicedPacket->serviced(globalTime);
		totalServicedPacketNumber++;
		totalServicedSize += servicedPacket->packet_size;
		totalServiceDelay += servicedPacket->serviceTime - servicedPacket->arrivalTime;
		servicedPacket->size = 0.0;
		if(servicedPacket->name.find(pack) != string::npos && servicedPacket->flow == 0){
			cout<<"Packet Serviced: "<<*servicedPacket<<endl;
		}
		qPrio.pop();

		return servicedPacket;
	}
	else{
		return nullptr;
	}
}

Packet* PriorityQ::front() {
	if(!qPrio.empty()){

		return qPrio.top();

	}
	else{
		return nullptr;
	}

}

void PriorityQ::print() {
	if(qPrio.empty()){
		cout<<"Priority Queue is empty"<<endl;
	}
	else{
		priority_queue<Packet*,vector<Packet*>,PacketPointerCompare> tempq=qPrio;
		while(!tempq.empty()){
			cout<<*(tempq.top())<<" ";
			tempq.pop();
		}
		cout<<endl;
	}
}

void PriorityQ::simulateTime(float duration, float &bytes) {
	float endTime = globalTime + duration;
	while(globalTime < endTime){
		if(!qPrio.empty()){
			float size = qPrio.top()->size;
			if(size < duration+0.05){
				bytes+= qPrio.top()->size;
				this->pop();
				duration-= size;
			}
			else{
				size -= duration-0.0001;
				qPrio.top()->size -=duration-0.0001;
				bytes+=duration;
				globalTime += duration+0.0001;
				break;
			}
		}
		else{
			globalTime+=duration;
			break;
		}
	}

}

void PriorityQ::simulateTime(float duration) {
	float endTime = globalTime + duration;
	while(globalTime < endTime){
		if(!qPrio.empty()){
			if(qPrio.top()->size < duration){
				pop();
			}
			else{
				qPrio.top()->size -=duration+0.0001;
				globalTime += duration+0.00001;
			}
		}
		else{
			globalTime+=duration;
			break;
		}
	}
}

bool PriorityQ::empty() {
	return qPrio.empty();
}

float PriorityQ::getTime() {
	return globalTime;
}
