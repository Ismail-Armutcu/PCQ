/*
 * WFQ.h
 *
 *  Created on: 18 Oca 2024
 *      Author: iharm
 */

#ifndef WFQ_H_
#define WFQ_H_

#include <queue>
#include <vector>

#include "Packet.h"
#include "PriorityQ.h"
class PacketVirtualTimeCompare {
public:
	bool operator()(const Packet* p1, const Packet* p2) const {
		return p1->virtualFinishTime < p2->virtualFinishTime;
	}
};


class WFQ {
public:
	WFQ();
	WFQ(int size);
	int qsize;
	int init;
	float virtualTime;
	float globalTime;
	int totalServicedPacketNumber;
	float totalServicedSize;
	float totalServiceDelay;
	Packet* currentPacket;
	priority_queue<Packet*,vector<Packet*>,PacketVirtualTimeCompare> qPrio;
	void enqueue(Packet& packet);
	void simulateTime(float duration);
	Packet* pop();
	void print();
	float getTime();
	~WFQ();
};

#endif /* WFQ_H_ */
