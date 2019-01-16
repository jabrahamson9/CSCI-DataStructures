#include<iostream>
#include<time.h>
#include <vector>
#include "heap.h"

using namespace std;

bool detPrior(patient J, patient Z){ //This is my compare function, I had to add this to account for the two different types of priority values
	if(J.timeLabor < Z.timeLabor){
		return true;
	}
	else if(J.timeLabor == Z.timeLabor && J.t_rec < Z.t_rec){ //move over to second priority
		return true;
	}
	else return false;
}

MinHeap::MinHeap(){
    currentSize = 0;
    capacity = 881;//this is the max number of patients in our data set. I should have maybe made this dynamic but oh well 
    heap = new patient[capacity];
}

MinHeap::~MinHeap(){
    delete [] heap;
}
 
void MinHeap::push(patient k){
    if (currentSize == capacity)
    {
        cout << "At capacity, cannot insert key." << endl;
    }
 
    else {
        currentSize++;
        int i = currentSize ;
        heap[i] = k; // we can insert at currentSize b/c we ignore 0
     
        // Fix the min heap property if it is violated
        while (i > 1 && detPrior(heap[i], heap[parent(i)])){
        	swap(heap[i], heap[parent(i)]);
           //swap(&heap[i], &heap[parent(i)]);
           i = parent(i);
        }
    }
}
 
// for now, just return -1 if there's nothing to pop
void MinHeap::pop(){
    if (currentSize <= 0)
    {
        cout<<"Heap is Empty"<<endl;
        return;
    }
    if (currentSize == 1)
    {
        currentSize--;
        cout<<heap[1].name<<endl;
        return;

    }
 
    patient poppedVal = heap[1];
    heap[1] = heap[currentSize];
    currentSize--;
    MinHeapify(1);
    cout<<poppedVal.name<<"	"<<poppedVal.timeLabor<<"	"<<poppedVal.t_rec<<endl;

}

void MinHeap::popAll(){
	int count=1;
	for(int i=0;i<881;i++){
	    if (currentSize <= 0)
	    {
	        cout<<"Heap is Empty"<<endl;
	        return;
	    }
	    if (currentSize == 1)
	    {
	        currentSize--;
	        cout<<count<<":	"<<heap[1].name<<"	"<<heap[1].timeLabor<<"	  "<<heap[1].t_rec<<endl;
	        count++;
	        return;

	    }
	 
	    patient poppedVal = heap[1];
	    heap[1] = heap[currentSize];
	    currentSize--;
	    MinHeapify(1);
	    cout<<count<<":	"<<poppedVal.name<<"	"<<poppedVal.timeLabor<<"	"<<poppedVal.t_rec<<endl;
	    count++;
	}
}


 
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i){
    int leftChild = left(i);
    int rightChild = right(i);
    int smallest = i;
    if (leftChild <= currentSize && detPrior(heap[leftChild], heap[i]))
        smallest = leftChild;
    if (rightChild <= currentSize && detPrior(heap[rightChild], heap[smallest]))
        smallest = rightChild;

    if (smallest != i)
    {
    	swap(heap[i], heap[smallest]);
        //swap(&heap[i], &heap[smallest]);
        MinHeapify(smallest);
    }
}

void MinHeap::printHeap() {
    cout << "The heap array is currently {";
    for (int i = 0; i < currentSize; i++) 
    {
        cout << heap[i].name;
        if (i < currentSize-1) {
            cout << ", ";
        }
    }
    cout << "}" << endl;
}
