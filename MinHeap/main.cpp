
// A C++ program to demonstrate common Binary Heap Operations
#include<iostream>
#include<climits>
#include"MinHeap.h"

using namespace std;
struct building {
    int id;
    int extime;
    int totalTime;
};
// Driver program to test above functions
int main()
{
    building b1, b2, b3;
    b1.id = 50;
    b1.extime = 0;
    b1.totalTime = 100;
    b2.id = 15;
    b2.extime = 0;
    b2.totalTime = 200;
    b3.id = 30;
    b3.extime = 0;
    b3.totalTime = 50;
    MinHeap h(2000);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    cout << h.extractMin() << " ";
    cout << h.getMin() << " ";
    h.increaseKey(1, 50);
    h.increaseKey(0,40);
    cout << h.getMin();
    return 0;
}
