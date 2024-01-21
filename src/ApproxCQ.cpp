/*
 * ApproxCQ.cpp
 *
 *  Created on: 14 Oca 2024
 *      Author: iharm
 */

#include "ApproxCQ.h"



ApproxCQ::~ApproxCQ() {
	delete []bytes;
	delete []bpr;
	delete []buckets;
}
ApproxCQ::ApproxCQ(int bucketNumber, int flowNumber,int bucketSize) {
	this->buckets = new Fifo[bucketNumber];
	for(int i=0; i<bucketNumber;i++){
		this->buckets[i] = Fifo(bucketSize);
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

ApproxCQ::ApproxCQ(const ApproxCQ &other) {
	this->buckets = other.buckets;
	this->bucketNumber =other. bucketNumber;
	this->flowNumber = other.flowNumber;
	this->bytes = other.bytes;
	this->bpr = other.bpr;
	this->currentRound =  other.currentRound;
	this->currentBucket = other.currentBucket;

}

int ApproxCQ::compute_rank(Packet &packet) {
	int flow = packet.flow;
	float weight = packet.priority;
	float size = packet.size;
	bytes[flow]= max(bytes[flow], currentRound*bpr[flow]*packet.priority);
	int n = (bytes[flow]+size)/(bpr[flow]*weight)-(this->currentRound);
	return n;


}

void ApproxCQ::enqueue(Packet &packet) {
	int n = compute_rank(packet);
	int bucketToPush = (n+bucketNumber)%bucketNumber;
	buckets[bucketToPush].push(packet);


}

void ApproxCQ::rotate() {
	currentBucket = (currentBucket+1)%bucketNumber;
	currentRound++;

}

void ApproxCQ::dequeue(float time) {

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

void ApproxCQ::printCQ() {
	for(int i=0;i<bucketNumber;i++){
		cout<<"Bucket["<<i<<"] ";
		buckets[i].print();
		cout<<endl;
	}
}

void ApproxCQ::simulateTime(float time) {
	float endTime = buckets[0].globalTime + time;
	dequeue(time);
	buckets[0].globalTime = endTime;
}


void simulateFifo(){
	Fifo q1(3);
	Fifo q2(3);
	Packet a1("A",3,5,1);
	Packet b1("B1",2,3,2);
	Packet c1("C1",1,3,3);
	Packet a2("A2",3,2,1);
	q1.push(a1);
	q1.simulateTime(1);
	q1.push(b1);
	q1.push(c1);
	q1.simulateTime(1);
	q1.simulateTime(1);
	q1.simulateTime(1);
	q1.simulateTime(1);
	q1.simulateTime(1);
	q1.simulateTime(1);
	q1.push(a2);
	q1.simulateTime(5);

	q2.push(a1);
	q2.simulateTime(1);
	q2.push(b1);
	q2.push(c1);
	q2.simulateTime(1);
	q2.simulateTime(1);
	q2.simulateTime(1);
	q2.simulateTime(1);
	q2.simulateTime(1);
	q2.simulateTime(1);
	q2.push(a2);
	q2.simulateTime(5);


}

void simulatepcq(){
	ApproxCQ pcq(5,3,4);
	Packet b1("B1",2,3.0,1);
	Packet c1("C1",1,3.0,2);
	Packet a1("A1",3,5.0,0);
	Packet a2("A2",3,2.0,0);
	pcq.enqueue(a1);
	pcq.enqueue(b1);
	pcq.enqueue(c1);
	pcq.enqueue(a2);
	pcq.printCQ();
	pcq.simulateTime(1);


	//pcq.printCQ();

	//pcq.printCQ();
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	//
	//pcq.printCQ();
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(1);
	pcq.simulateTime(5);
	for(int i=0;i<3;i++){
		cout<<"Bytes["<<i<<"]: "<<pcq.bytes[i]<<endl;

	}
	pcq.enqueue(a1);
	pcq.enqueue(b1);
	pcq.enqueue(c1);
	pcq.enqueue(a2);
	pcq.printCQ();
	pcq.simulateTime(30);
	for(int i=0;i<3;i++){
		cout<<"Bytes["<<i<<"]: "<<pcq.bytes[i]<<endl;

	}

}
