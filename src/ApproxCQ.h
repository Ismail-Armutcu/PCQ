/*
 * ApproxCQ.h
 *
 *  Created on: 14 Oca 2024
 *      Author: iharm
 */

#ifndef APPROXCQ_H_
#define APPROXCQ_H_
#include "Fifo.h"
#include <algorithm>

using namespace std;
class Fifo;

class Packet;

class ApproxCQ {
public:
	ApproxCQ(int bucketNumber, int flowNumber, int bucketSize);
	~ApproxCQ();
	ApproxCQ(const ApproxCQ &other);
	int currentBucket;
	int bucketNumber;
	int flowNumber;
	int currentRound;
	float* bytes;//Number of bytes sent by flow f
	float* bpr; //Bytes sent per round for each flow
	Fifo* buckets;

	int compute_rank(Packet &packet);
	void enqueue(Packet &packet);
	void rotate();
	void dequeue(float time);
	void printCQ();
	void simulateTime(float time);
};

#endif /* APPROXCQ_H_ */
