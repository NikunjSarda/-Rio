/*
 * MinHeap.cpp
 *
 *  Created on: Nov 19, 2019
 *      Author: rio
 */

// A C++ program to demonstrate common Binary Heap Operations
#include<iostream>
#include<climits>
using namespace std;

struct building {
    int id;
    int extime;
    int totalTime;
};

// Prototype of a utility function to swap two integers


bool compareitem(building a, building b);

// A class for Min Heap
class MinHeap
{
    building *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int capacity);

    // to heapify a subtree with the root at given index
    void MinHeapify(int i);

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i)+1; }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    building extractMin();

    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

    void increaseKey(int i, int new_val);

    // Returns the minimum key (key at root) from min heap
    building getMin();

    // Deletes a key stored at index i
    void deleteKey(int i);

    // Inserts a new key 'k'
    void insertKey(building k);

    void swap(int x, int y);

    void printHeap();
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new building[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(building k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Fix the min heap property if it is violated
    while (i != 0 && compareitem(harr[parent(i)], harr[i]))
    {
       swap(i, parent(i));
       i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i].extime = new_val;
    while (i != 0 && compareitem(harr[parent(i)],harr[i]))
    {
       swap(i, parent(i));
       i = parent(i);
    }
}

void MinHeap::increaseKey(int i, int new_val)
{
    if(harr[i].extime == harr[i].totalTime){
    	deleteKey(i);
    	increaseKey(0,1);
    }
    else {
		harr[i].extime = harr[i].extime + new_val;
		int smallest = i;
		while (left(i) < heap_size) {
			if (left(i) <= heap_size && compareitem(harr[i], harr[left(i)])) {
				smallest = left(i);
			}
			if (right(i) <= heap_size
					&& compareitem(harr[smallest], harr[right(i)])) {
				smallest = right(i);
			}
			if (smallest != i) {
				i = smallest;
				swap(smallest, i);
			} else {
				break;
			}
		}
    }
}

// Method to remove minimum element (or root) from min heap
building MinHeap::extractMin()
{
    if (heap_size <= 0) {
        building b;
        b.extime = INT_MAX;
        b.id = INT_MAX;
        b.totalTime = INT_MAX;
        return b;
    }
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    building root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    building completeb = extractMin();
    cout<< completeb.id<<endl;;
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && compareitem(harr[i], harr[l]))
        smallest = l;
    if (r < heap_size && compareitem(harr[smallest], harr[r]))
        smallest = r;
    if (smallest != i)
    {
        swap(i, smallest);
        MinHeapify(smallest);
    }
}

building MinHeap::getMin() {
	return harr[0];
}

void MinHeap::printHeap()
{
    cout << "Array representation of Heap is:\n";

    for (int i = 0; i < heap_size; ++i)
        cout << harr[i].id << " "<<harr[i].extime<<" "<<harr[i].totalTime;
    cout << "\n";
}

// A utility function to swap two elements
void MinHeap::swap(int x, int y)
{
    building temp = harr[x];
    harr[x] = harr[y];
    harr[y] = temp;
}

bool compareitem(building a, building b) {

    if(a.extime > b.extime) {
        return true;
    }
    else if(a.extime < b.extime) {
    	return false;
    }
    else {
		if (a.id > b.id) {
			return true;
		} else {
			return false;
		}
	}
}



