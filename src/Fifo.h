/*
 * Fifo.h
 *
 *  Created on: 14 Oca 2024
 *      Author: iharm
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <queue>

#include "Packet.h"

using namespace std;
class Fifo {
public:
	queue<Packet> qFifo;
	//priority_queue<Packet> qFifo
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
	Fifo(int qsize);
	Fifo();
	virtual ~Fifo();
};

#endif /* FIFO_H_ */
