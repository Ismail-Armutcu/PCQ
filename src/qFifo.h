/*
 * qFifo.h
 *
 *  Created on: 17 Oca 2024
 *      Author: iharm
 */

#ifndef QFIFO_H_
#define QFIFO_H_
#include <queue>

#include "Packet.h"
using namespace std;
class qFifo {
public:
	queue<Packet> Fifo;
	//priority_queue<Packet> qFifo
	int qsize;
	static float globalTimeqFifo;
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
	qFifo(int qsize);
	qFifo();
	virtual ~qFifo();
};

#endif /* QFIFO_H_ */
