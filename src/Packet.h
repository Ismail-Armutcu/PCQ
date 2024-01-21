/*
 * Packet.h
 *
 *  Created on: 14 Oca 2024
 *      Author: iharm
 */
#define pack "250"
#ifndef PACKET_H_
#define PACKET_H_
#include <iostream>
#include <string>
using namespace std;

class Packet {
public:
	string name;
	int flow;
	float priority;
	float size;
	float packet_size;
	float virtualFinishTime;
	float arrivalTime;
	float serviceTime;
	float waitingTime;
	Packet(string name, float priority,float size,int flow);
	Packet(const Packet& rhs);
	~Packet();
	void arrived(float time);
	void serviced(float time);
	void printpacket();
	void sleepMilliseconds(int milliseconds);
	void sleepPreciseMilliseconds(int milliseconds);
	friend std::ostream& operator<<(std::ostream& os, const Packet& packet);
	bool operator<(const Packet &packet) const ;

private:
};

#endif /* PACKET_H_ */

