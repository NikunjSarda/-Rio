/*
 * Node.h
 *
 *  Created on: Nov 23, 2019
 *      Author: rio
 */

#ifndef NODE_H_
#define NODE_H_
#include "Building.h"

enum COLOR { RED, BLACK };
/*
 *
 */
class Node {
public:
	Building key;
	  COLOR color;
	  Node *left, *right, *parent;

	Node(Building key);
	Node *uncle();
	bool isOnLeft();
	Node *sibling();
	void moveDown(Node *nParent);
	bool hasRedChild();
};

#endif /* NODE_H_ */
