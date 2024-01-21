/*
 * Fifo.cpp
 *
 *  Created on: 14 Oca 2024
 *      Author: iharm
 */

#include "qFifo.h"

float qFifo::globalTimeqFifo = 0.0;
int qFifo::totalServicedPacketNumber = 0;
float qFifo::totalServicedSize = 0.0;
float qFifo::totalServiceDelay = 0.0;

qFifo::qFifo(int qsize) {
	this->qsize = qsize;

}

qFifo::qFifo() {
	qsize =0;

}

bool qFifo::empty() {
	return Fifo.empty();
}

float qFifo::getTime() {
	return globalTimeqFifo;
}

Packet* qFifo::front() {
	return &Fifo.front();
}

qFifo::~qFifo() {
	globalTimeqFifo = 0.0;
	totalServicedPacketNumber = 0;
	totalServicedSize = 0.0;
	totalServiceDelay = 0.0;

}
void qFifo::push(Packet &packet) {
	if((int)Fifo.size() < qsize){
		packet.arrived(globalTimeqFifo);
		if(packet.name.find(pack) != string::npos && packet.flow == 0){
			cout<<"Packet arrived: "<<packet<<endl;
		}
		Fifo.push(packet);
	}
	else{
		if(packet.name.find(pack) != string::npos && packet.flow == 0){
			cout<<"Packet Dropped: "<<packet<<endl;
		}
	}
}

Packet* qFifo::pop() {
	if(!Fifo.empty()){
		Packet* servicedPacket = &Fifo.front();
		globalTimeqFifo += servicedPacket->size;
		servicedPacket->serviced(globalTimeqFifo);
		totalServicedPacketNumber++;
		totalServicedSize += servicedPacket->packet_size;
		totalServiceDelay += servicedPacket->serviceTime - servicedPacket->arrivalTime;
		servicedPacket->size = 0.0;

		if(servicedPacket->name.find(pack) != string::npos && servicedPacket->flow == 0){
			cout<<"Packet Serviced: "<<*servicedPacket<<endl;
		}
		Fifo.pop();
		return servicedPacket;
	}
	else{
		return nullptr;
	}
}

void qFifo::print() {
	queue<Packet> tempq = Fifo;
	int i = 0;
	while(!tempq.empty()){
		cout<<i++<<": "<<tempq.front()<<endl;
		tempq.pop();
	}
}


void qFifo::simulateTime(float duration,float &bytes) {
	float endTime = globalTimeqFifo + duration;
	while(globalTimeqFifo < endTime){
		if(!Fifo.empty()){
			float size = Fifo.front().size;
			if(size < duration+0.01){
				bytes+= Fifo.front().size;
				pop();
				duration-= size;
			}
			else{
				size -= duration-0.0001;
				Fifo.front().size -=duration-0.0001;
				bytes+=duration;
				globalTimeqFifo += duration+0.0001;
				break;
			}
		}
		else{
			globalTimeqFifo+=duration;
			break;
		}
	}
	//globalTimeqFifo = endTime;
}

void qFifo::simulateTime(float duration) {
	float endTime = globalTimeqFifo + duration;
	while(globalTimeqFifo < endTime){
		if(!Fifo.empty()){
			if(Fifo.front().size < duration+0.1){

				duration -=Fifo.front().size;
				pop();
			}
			else{
				Fifo.front().size -=duration-0.0001;
				globalTimeqFifo += duration+0.00001;
			}
		}
		else{
			globalTimeqFifo+=duration;
			break;
		}
	}
	globalTimeqFifo = endTime;
}
