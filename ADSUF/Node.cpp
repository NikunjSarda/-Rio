/*
 * Node.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: rio
 */
#include<iostream>

#include "Building.h"

enum COLOR { RED, BLACK };

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

  Node::Node(Building key) : key(key) {
    parent = left = right = NULL;

    // Node is created during insertion
    // Node is red at insertion
    color = RED;
  }

  // returns pointer to uncle
  Node *Node::uncle() {
    // If no parent or grandparent, then no uncle
    if (parent == NULL or parent->parent == NULL)
      return NULL;

    if (parent->isOnLeft())
      // uncle on right
      return parent->parent->right;
    else
      // uncle on left
      return parent->parent->left;
  }

  // check if node is left child of parent
  bool Node::isOnLeft() { return this == parent->left; }

  // returns pointer to sibling
  Node *Node::sibling() {
    // sibling null if no parent
    if (parent == NULL)
      return NULL;

    if (isOnLeft())
      return parent->right;

    return parent->left;
  }

  // moves node down and moves given node in its place
  void Node::moveDown(Node *nParent) {
    if (parent != NULL) {
      if (isOnLeft()) {
        parent->left = nParent;
      } else {
        parent->right = nParent;
      }
    }
    nParent->parent = parent;
    parent = nParent;
  }

  bool Node::hasRedChild() {
    return (left != NULL and left->color == RED) or
           (right != NULL and right->color == RED);
  }
