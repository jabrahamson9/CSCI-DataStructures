#include<iostream>
#include<time.h>
#include "LinkedListPriority.h"
//MANIUPLATED FROM MR ZAGRODSKI HELPER CODE SHARED ON GOOGLE DOCS
using namespace std;


 
class MinHeap
{
    public:
        MinHeap();
        ~MinHeap();
        void push(patient k);
        void pop();
        patient peek() { return heap[1]; }
        void printHeap();
        void popAll();
    private:
        patient *heap; // pointer to array of elements in heap
        int capacity; // maximum possible size of min heap
        int currentSize; // Current number of elements in min heap      
        void MinHeapify(int index);
        int parent(int i) { return (i)/2; }
        int left(int i) { return (2*i); }
        int right(int i) { return (2*i + 1); }
};
