/*
 * IdealCQ.cpp
 *
 *  Created on: 18 Oca 2024
 *      Author: iharm
 */

#include "IdealCQ.h"

#include "Packet.h"
#include "PriorityQ.h"



IdealCQ::IdealCQ(int bucketNumber, int flowNumber, int bucketSize) {
	this->buckets = new PriorityQ[bucketNumber];
	for(int i=0; i<bucketNumber;i++){
		this->buckets[i] = PriorityQ(bucketSize);
	}

	this->bucketNumber = bucketNumber;
	this->flowNumber = flowNumber;
	this->bytes = new float[flowNumber];
	this->bpr = new float[flowNumber];
	for(int i=0; i<flowNumber;i++){
		bytes[i] = 0.0;
		bpr[i] = 2.5; //set as Maximum segment size in paper
	}
	this->currentRound =0;
	this->currentBucket = 0;
}

IdealCQ::~IdealCQ() {
	delete []bytes;
	delete []bpr;
	delete []buckets;
}

int IdealCQ::compute_rank(Packet &packet) {
	int flow = packet.flow;
	float weight = packet.priority;
	float size = packet.size;
	bytes[flow]= max(bytes[flow], currentRound*bpr[flow]*packet.priority);
	int n = (bytes[flow]+size)/(bpr[flow]*weight)-(this->currentRound);
	return n;
}

void IdealCQ::enqueue(Packet &packet) {
	int n = compute_rank(packet);
	int bucketToPush = (n+bucketNumber)%bucketNumber;
	buckets[bucketToPush].push(packet);
}

void IdealCQ::rotate() {
	currentBucket = (currentBucket+1)%bucketNumber;
	currentRound++;
}

void IdealCQ::dequeue(float time) {
	int rotator_limit = 0;
	while(buckets[currentBucket].empty() && rotator_limit++ < bucketNumber){
		rotate();
		time -= 0.01;

	}

	while(!buckets[currentBucket].empty() && time > 0.1){
		Packet* servicedPacket =buckets[currentBucket].front();
		int flow = servicedPacket->flow;
		float size = servicedPacket->size;
		if(time >= size-0.01 ){
			buckets[currentBucket].simulateTime(size,bytes[flow]);
			time -= size;
		}
		else{
			buckets[currentBucket].simulateTime(time,bytes[flow]);
			return;
		}

		if(time > 0.01){
			dequeue(time);
		}

	}
}


void IdealCQ::printCQ() {
	for(int i=0;i<bucketNumber;i++){
		cout<<"Bucket["<<i<<"] ";
		buckets[i].print();
		cout<<endl;
	}
}

void IdealCQ::simulateTime(float time) {
	float endTime = buckets[0].globalTime + time;
	dequeue(time);
	buckets[0].globalTime = endTime;
}
