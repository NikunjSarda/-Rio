#include<iostream>
#include"RBT.h"

using namespace std;

int main()
{
    RBT obj;
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
        obj.insertNode(b1);
        obj.insertNode(b2);
        obj.insertNode(b3);
        obj.disp();

    return 0;
}
