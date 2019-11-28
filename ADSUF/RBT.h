/*
 * RBT.h
 *
 *  Created on: Nov 20, 2019
 *      Author: rio
 */

#ifndef RBT_H_
#define RBT_H_

#include<iostream>
#include"Node.h"
using namespace std;

class RBT
 {
	Node *root;
	int nodeCount;
	void leftRotate(Node *x);
	void rightRotate(Node *x);
	void swapColors(Node *x1, Node *x2);
	void swapValues(Node *u, Node *v);
	void fixRedRed(Node *x);
	Node* successor(Node *x);
	Node* BSTreplace(Node *x);
	void fixDoubleBlack(Node *x);
	void levelOrder(Node *x);
public:
	RBT();
	Node* getRoot();
	Node* search(int n);
	Node* insert(Building n);
	void deleteNode(Node *v);
	void deleteByVal(Building n);
	void printLevelOrder();
	bool checkEmpty();
	bool pSuccessor(Node* x);
};

#endif /* RBT_H_ */
