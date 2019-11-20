#include<iostream>

using namespace std;

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
      void insertNode();
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void del();
      node* successor(node *);
      void delfix(node *);
      void disp();
      void display( node *);
      void searchNode();
};
