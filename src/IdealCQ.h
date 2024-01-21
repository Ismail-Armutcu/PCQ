/*
 * IdealCQ.h
 *
 *  Created on: 18 Oca 2024
 *      Author: iharm
 */

#ifndef IDEALCQ_H_
#define IDEALCQ_H_
#include "PriorityQ.h"
class IdealCQ {
public:
	IdealCQ(int bucketNumber, int flowNumber, int bucketSize);
	~IdealCQ();
	int currentBucket;
	int bucketNumber;
	int flowNumber;
	int currentRound;
	float* bytes;//Number of bytes sent by flow f
	float* bpr; //Bytes sent per round for each flow
	PriorityQ* buckets;
	int compute_rank(Packet &packet);
	void enqueue(Packet &packet);
	void rotate();
	void dequeue(float time);
	void printCQ();
	void simulateTime(float time);
};

#endif /* IDEALCQ_H_ */

