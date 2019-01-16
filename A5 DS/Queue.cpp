#include <iostream>
#include "Queue.h"
#include <sstream>

using namespace std;

Queue::Queue(int size){
	queueSize=size;
    queueHead=0;
    queueTail=0;
    queueCount=0;
    arrayQueue=new string[queueSize];
}
Queue::~Queue(){
	delete [] arrayQueue;
	arrayQueue = NULL;
}

bool Queue::queueIsFull(){
	if(queueCount==queueSize){
		return true;
	}
	else{
		return false;
	}
}
bool Queue::queueIsEmpty(){
	if(queueCount==0){
		return true;
	}
	else{
		return false;
	}
}

void Queue::enqueue(string newWord){
	if(queueIsFull()==true){
		cout<<"Queue is full."<<endl;
	}
	else if(queueHead==0 && queueTail==0){
		arrayQueue[queueTail]=newWord;
		queueTail++;
		queueCount++;
		cout<<"word: "<<newWord<<endl<<"H: "<<queueHead<<endl<<"T: "<<queueTail<<endl;
	}
	else if (queueTail == queueSize && queueHead != 0)
    {
        queueTail = 0;
        arrayQueue[queueTail] = newWord;
        queueTail++;
        queueCount++;
        cout<<"E: "<<newWord<<endl<<"H: "<<queueHead<<endl<<"T: "<<queueTail<<endl;
    }
	else{
		arrayQueue[queueTail]=newWord;
		queueTail++;
		queueCount++;
		if(queueTail==queueSize){
			queueTail=0;
		}
		cout<<"E: "<<newWord<<endl<<"H: "<<queueHead<<endl<<"T: "<<queueTail<<endl;
	}
}

void Queue::dequeue(){
	if(queueIsEmpty()==true){
		cout<<"Queue is empty."<<endl;
		queueHead=0;
		queueTail=0;
	}
	else if(queueCount==0){
		cout<<"Queue is empty"<<endl;
		queueHead=0;
		queueTail=0;
	}
	else if(queueHead==queueSize-1){
		cout<<"H: "<<0<<endl<<"T: "<<queueTail<<endl<<"word: "<<arrayQueue[queueHead]<<endl;
		queueHead=0;
		queueCount--;
	}
	else{
		cout<<"H: "<<queueHead+1<<endl<<"T: "<<queueTail<<endl<<"word: "<<arrayQueue[queueHead]<<endl;
		arrayQueue[queueHead]="";
		queueHead++;
		queueCount--;
	}
}

void Queue::printQueue(){
	if(queueIsEmpty()==true){
		cout<<"Empty"<<endl;
	}
	else{
		for(int i=queueHead; i<queueSize; i++){
			if(arrayQueue[i]!=""){
				cout<<i<<": "<<arrayQueue[i]<<endl;
			}
		}
		if(queueIsFull()==true){
			for(int j=0; j<queueHead; j++){
				if(arrayQueue[j]!=""){
					cout<<j<<": "<<arrayQueue[j]<<endl;
				}	
			}
		}
	}
}

void Queue::enqueueSentence(string x){
	istringstream ss(x);
	string token;
	while(getline(ss, token, ' ')){
		enqueue(token);
	}

}




