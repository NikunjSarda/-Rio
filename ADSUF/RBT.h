/*
 * RBT.h
 *
 *  Created on: Nov 20, 2019
 *      Author: rio
 */

#ifndef RBT_H_
#define RBT_H_

#include<iostream>
#include"Building.h"
using namespace std;

struct node
{
       building key;
       node *parent;
       char color;
       node *left;
       node *right;
};

class RBT
{
      node *root;
      node *q;
   public :
      RBT()
      {
              q=NULL;
              root=NULL;
      }
      node* insertNode(building z);
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void del(building x);
      node* successor(node *);
      void delfix(node *);
      void disp();
      void display( node *);
      void searchNode(building x);
      bool checkEmpty();
};

#endif /* RBT_H_ */
