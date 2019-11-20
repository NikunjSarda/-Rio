#include<iostream>

using namespace std;

struct building {
    int id;
    int extime;
    int totalTime;
};

struct node
{
       int key;
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
      void insertNode(building z);
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void del(building x);
      node* successor(node *);
      void delfix(node *);
      void disp();
      void display( node *);
      void searchNode(building x);
};
