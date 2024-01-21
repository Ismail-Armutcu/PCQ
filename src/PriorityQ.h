/*
 * qPrio.h
 *
 *  Created on: 18 Oca 2024
 *      Author: iharm
 */

#ifndef PRIORITYQ_H_
#define PRIORITYQ_H_
#include "Packet.h"
#include <Queue>
#include <vector>
class PacketPointerCompare {
public:
	bool operator()(const Packet* p1, const Packet* p2) const {
		return p1->priority > p2->priority;
	}
};
class PriorityQ {
public:
	PriorityQ();
	PriorityQ(int size);
	~PriorityQ();
	priority_queue<Packet*,vector<Packet*>,PacketPointerCompare> qPrio;
	int qsize;
	static float globalTime;
	static int totalServicedPacketNumber;
	static float totalServicedSize;
	static float totalServiceDelay;
	void push(Packet &packet);
	Packet* pop();
	Packet* front();
	void print();
	void simulateTime(float duration, float &bytes);
	void simulateTime(float duration);
	bool empty();
	float getTime();

};

#endif /* PRIORITYQ_H_ */
