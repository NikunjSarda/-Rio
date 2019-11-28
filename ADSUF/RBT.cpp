/*
 * RBT.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: rio
 */
#include <iostream>
#include <queue>
#include"Node.h"
using namespace std;

class RBT
 {
	Node *root;
	int nodeCount = 0;
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

  // left rotates the given node
  void RBT::leftRotate(Node *x) {
    // new parent will be node's right child
    Node *nParent = x->right;

    // update root if current node is root
    if (x == root)
      root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's left element
    x->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != NULL)
      nParent->left->parent = x;

    // connect new parent with x
    nParent->left = x;
  }

  void RBT::rightRotate(Node *x) {
    // new parent will be node's left child
    Node *nParent = x->left;

    // update root if current node is root
    if (x == root)
      root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's right element
    x->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != NULL)
      nParent->right->parent = x;

    // connect new parent with x
    nParent->right = x;
  }

  void RBT::swapColors(Node *x1, Node *x2) {
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }

  void RBT::swapValues(Node *u, Node *v) {
    Building temp;
    temp = u->key;
    u->key = v->key;
    v->key = temp;
  }

  // fix red red at given node
  void RBT::fixRedRed(Node *x) {
    // if x is root color it black and return
    if (x == root) {
      x->color = BLACK;
      return;
    }

    // initialize parent, grandparent, uncle
    Node *parent = x->parent, *grandparent = parent->parent,
         *uncle = x->uncle();

    if (parent->color != BLACK) {
      if (uncle != NULL && uncle->color == RED) {
        // uncle red, perform re-coloring and recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixRedRed(grandparent);
      } else {
        // Else perform LR, LL, RL, RR
        if (parent->isOnLeft()) {
          if (x->isOnLeft()) {
            // for left right
            swapColors(parent, grandparent);
          } else {
            leftRotate(parent);
            swapColors(x, grandparent);
          }
          // for left left and left right
          rightRotate(grandparent);
        } else {
          if (x->isOnLeft()) {
            // for right left
            rightRotate(parent);
            swapColors(x, grandparent);
          } else {
            swapColors(parent, grandparent);
          }

          // for right right and right left
          leftRotate(grandparent);
        }
      }
    }
  }

  // find node that do not have a left child
  // in the subtree of the given node
  Node *RBT::successor(Node *x) {
    Node *temp = x;

    while (temp->left != NULL)
      temp = temp->left;

    return temp;
  }

  // find node that replaces a deleted node in BST
  Node *RBT::BSTreplace(Node *x) {
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
      return successor(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
      return NULL;

    // when single child
    if (x->left != NULL)
      return x->left;
    else
      return x->right;
  }

  // deletes the given node
  void RBT::deleteNode(Node *v) {
	  nodeCount--;
    Node *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
    Node *parent = v->parent;

    if (u == NULL) {
      // u is NULL therefore v is leaf
      if (v == root) {
        // v is root, making root null
        root = NULL;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          fixDoubleBlack(v);
        } else {
          // u or v is red
          if (v->sibling() != NULL)
            // sibling is not null, make it red"
            v->sibling()->color = RED;
        }

        // delete v from the tree
        if (v->isOnLeft()) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      }
      delete v;
      return;
    }

    if (v->left == NULL or v->right == NULL) {
      // v has 1 child
      if (v == root) {
        // v is root, assign the value of u to v, and delete u
        v->key = u->key;
        v->left = v->right = NULL;
        delete u;
      } else {
        // Detach v from tree and move u up
        if (v->isOnLeft()) {
          parent->left = u;
        } else {
          parent->right = u;
        }
        delete v;
        u->parent = parent;
        if (uvBlack) {
          // u and v both black, fix double black at u
          fixDoubleBlack(u);
        } else {
          // u or v red, color u black
          u->color = BLACK;
        }
      }
      return;
    }

    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
  }

  void RBT::fixDoubleBlack(Node *x) {
    if (x == root)
      // Reached root
      return;

    Node *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      fixDoubleBlack(parent);
    } else {
      if (sibling->color == RED) {
        // Sibling red
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        // Sibling black
        if (sibling->hasRedChild()) {
          // at least 1 red children
          if (sibling->left != NULL and sibling->left->color == RED) {
            if (sibling->isOnLeft()) {
              // left left
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rightRotate(parent);
            } else {
              // right left
              sibling->left->color = parent->color;
              rightRotate(sibling);
              leftRotate(parent);
            }
          } else {
            if (sibling->isOnLeft()) {
              // left right
              sibling->right->color = parent->color;
              leftRotate(sibling);
              rightRotate(parent);
            } else {
              // right right
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              leftRotate(parent);
            }
          }
          parent->color = BLACK;
        } else {
          // 2 black children
          sibling->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }

  // prints level order for given node
  void RBT::levelOrder(Node *x) {
    if (x == NULL)
      // return if node is null
      return;

    // queue for level order
    queue<Node *> q;
    Node *curr;

    // push x
    q.push(x); // @suppress("Invalid arguments")

    while (!q.empty()) {
      // while q is not empty
      // dequeue
      curr = q.front();
      q.pop();

      // print node value
      cout << curr->key.buildingId << " ";

      // push children to queue
      if (curr->left != NULL)
        q.push(curr->left); // @suppress("Invalid arguments")
      if (curr->right != NULL)
        q.push(curr->right); // @suppress("Invalid arguments")
    }
  }

  // constructor
  // initialize root
  RBT::RBT() { root = NULL; }

  Node *RBT::getRoot() { return root; }

  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)
  Node *RBT::search(int n) {
    Node *temp = root;
    while (temp != NULL) {
      if (n < temp->key.buildingId) {
        if (temp->left == NULL)
          break;
        else
          temp = temp->left;
      } else if (n == temp->key.buildingId) {
        break;
      } else {
        if (temp->right == NULL)
          break;
        else
          temp = temp->right;
      }
    }

    return temp;
  }

  // inserts the given value to tree
  Node *RBT::insert(Building n) {
	  nodeCount++;
    Node *newNode = new Node(n);
    if (root == NULL) {
      // when root is null
      // simply insert value at root
      newNode->color = BLACK;
      root = newNode;
    } else {
      Node *temp = search(n.buildingId);

      if (temp->key.buildingId == n.buildingId) {
        // return if value already exists
    	  cout<<"Building already there"<<endl;
        return NULL;
      }

      // if value is not found, search returns the node
      // where the value is to be inserted

      // connect new node to correct node
      newNode->parent = temp;

      if (n.buildingId < temp->key.buildingId)
        temp->left = newNode;
      else
        temp->right = newNode;

      // fix red red voilaton if exists
      fixRedRed(newNode);
    }
    return newNode;
  }

  // utility function that deletes the node with given value
  void RBT::deleteByVal(Building n) {
    if (root == NULL)
      // Tree is empty
      return;

    Node *v = search(n.buildingId);

    if (v->key.buildingId != n.buildingId) {
      cout << "No node found to delete with value:" << n.buildingId << endl;
      return;
    }

    deleteNode(v);
  }

  // prints level order of the tree
  void RBT::printLevelOrder() {
    cout << "Level order: " << endl;
    if (root == NULL)
      cout << "Tree is empty" << endl;
    else
      levelOrder(root);
    cout << endl;
  }

  bool RBT::checkEmpty(){
	  if(getRoot() == NULL) {
		  return false;
	  }
	  return true;
  }

  bool RBT::pSuccessor(Node* x) {
	  if (x->left != NULL && x->right != NULL) {
		  return true;
	  }
	  return false;
  }





