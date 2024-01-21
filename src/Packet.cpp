/*
 * Packet.cpp
 *
 *  Created on: 14 Oca 2024
 *      Author: iharm
 */

#include "Packet.h"


Packet::Packet(string name,float priority, float size, int flow) {
	this->name = name;
	this->flow = flow;
	this->priority = priority;
	this->size = size;
	this->arrivalTime = 0.0;
	this->serviceTime = 0.0;
	this->waitingTime = 0.0;
	this->virtualFinishTime = 0.0;
	this->packet_size = size;

}


Packet::Packet(const Packet &rhs) {
	this->name = rhs.name;
	this->flow = rhs.flow;
	this->priority = rhs.priority;
	this->size = rhs.size;
	this->arrivalTime = rhs.arrivalTime;
	this->serviceTime = rhs.serviceTime;
	this->waitingTime = rhs.waitingTime;
	this->virtualFinishTime = rhs.virtualFinishTime;
	this->packet_size = rhs.size;
}

Packet::~Packet() {

}

void Packet::arrived(float time) {
	arrivalTime = time;
}

void Packet::serviced(float time) {
	serviceTime = time;
	waitingTime = serviceTime- arrivalTime;

}


void Packet::printpacket() {
	cout<<"Packet Name: "<<name<<
			"Arrival Time: "<<arrivalTime <<
			" Service Time: "<<serviceTime<<
			" Queueing Time: "<<waitingTime<<endl;
}





ostream& operator<<(std::ostream& os, const Packet& packet) {
        os << "Name: " << packet.name
           << " Service Time: " << packet.serviceTime<< endl;
        return os;
}

bool Packet::operator <(const Packet &packet) const {
	return this->priority < packet.priority;
}
