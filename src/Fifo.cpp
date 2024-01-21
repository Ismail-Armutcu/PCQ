/*
 * Fifo.cpp
 *
 *  Created on: 14 Oca 2024
 *      Author: iharm
 */

#include "Fifo.h"

float Fifo::globalTime = 0.0;
int Fifo::totalServicedPacketNumber = 0;
float Fifo::totalServicedSize = 0.0;
float Fifo::totalServiceDelay = 0.0;

Fifo::Fifo(int qsize) {
	this->qsize = qsize;

}

Fifo::Fifo() {
	qsize =0;

}

bool Fifo::empty() {
	return qFifo.empty();
}

float Fifo::getTime() {
	return globalTime;
}

Packet* Fifo::front() {
	return &qFifo.front();
}

Fifo::~Fifo() {
	globalTime = 0.0;
	totalServicedPacketNumber = 0;
	totalServicedSize = 0.0;
	totalServiceDelay = 0.0;

}
void Fifo::push(Packet &packet) {
	if((int)qFifo.size() < qsize){
		packet.arrived(globalTime);
		if(packet.name.find(pack) != string::npos && packet.flow == 0){
			cout<<"Packet arrived: "<<packet<<endl;
		}
		qFifo.push(packet);
	}
	else{
		if(packet.name.find(pack) != string::npos && packet.flow == 0){
			cout<<"Packet Dropped: "<<packet<<endl;
		}
	}
}

Packet* Fifo::pop() {
	if(!qFifo.empty()){
		Packet* servicedPacket = &qFifo.front();
		globalTime += servicedPacket->size;
		servicedPacket->serviced(globalTime);
		totalServicedPacketNumber++;
		totalServicedSize += servicedPacket->packet_size;
		totalServiceDelay += servicedPacket->serviceTime - servicedPacket->arrivalTime;
		servicedPacket->size = 0.0;

		if(servicedPacket->name.find(pack) != string::npos && servicedPacket->flow == 0){
			cout<<"Packet Serviced: "<<*servicedPacket<<endl;
		}

		qFifo.pop();
		return servicedPacket;
	}
	else{
		return nullptr;
	}
}

void Fifo::print() {
	queue<Packet> tempq = qFifo;
	int i = 0;
	while(!tempq.empty()){
		cout<<i++<<": "<<tempq.front()<<endl;
		tempq.pop();
	}
}


void Fifo::simulateTime(float duration,float &bytes) {
	float endTime = globalTime + duration;
	while(globalTime < endTime){
		if(!qFifo.empty()){
			float size = qFifo.front().size;
			if(size < duration+0.0001){
				bytes+= qFifo.front().size;
				pop();
				duration-= size;
			}
			else{
				size -= duration-0.0001;
				qFifo.front().size -=duration-0.0001;
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

void Fifo::simulateTime(float duration) {
	float endTime = globalTime + duration;
	while(globalTime < endTime){
		if(!qFifo.empty()){
			if(qFifo.front().size < duration){
				pop();
			}
			else{
				qFifo.front().size -=duration+0.0001;
				globalTime += duration+0.00001;
			}
		}
		else{
			globalTime+=duration;
			break;
		}
	}
}
