/*
 * RBT.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: rio
 */
#include<iostream>

using namespace std;

struct building {
    int id;
    int extime;
    int totalTime;
};

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
node* RBT::insertNode(building z)
{
     node *p,*q;
     node *t=new node;
     t->key=z;
     t->left=NULL;
     t->right=NULL;
     t->parent=NULL;
     t->color='r';
     p=root;
     q=NULL;
     if(root==NULL)
     {
           root=t;
           t->parent=NULL;
     }
     else
     {
         while(p!=NULL)
         {
              q=p;
              if(p->key.id<t->key.id)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=q;
         if(q->key.id<t->key.id)
              q->right=t;
         else
              q->left=t;
     }
     insertfix(t);
     return t;
}
void RBT::insertfix(node *t)
{
     node *u;
     if(root==t)
     {
         t->color='b';
         return;
     }
     while(t->parent!=NULL&&t->parent->color=='r')
     {
           node *g=t->parent->parent;
           if(g->left==t->parent)
           {
                        if(g->right!=NULL)
                        {
                              u=g->right;
                              if(u->color=='r')
                              {
                                   t->parent->color='b';
                                   u->color='b';
                                   g->color='r';
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->parent->right==t)
                            {
                                 t=t->parent;
                                 leftrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            rightrotate(g);
                        }
           }
           else
           {
                        if(g->left!=NULL)
                        {
                             u=g->left;
                             if(u->color=='r')
                             {
                                  t->parent->color='b';
                                  u->color='b';
                                  g->color='r';
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->parent->left==t)
                            {
                                   t=t->parent;
                                   rightrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            leftrotate(g);
                        }
           }
           root->color='b';
     }
}

void RBT::del(building x)
{
     if(root==NULL)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }
     node *p;
     p=root;
     node *y=NULL;
     node *q=NULL;
     int found=0;
     while(p!=NULL&&found==0)
     {
           if(p->key.id==x.id)
               found=1;
           if(found==0)
           {
                 if(p->key.id<x.id)
                    p=p->right;
                 else
                    p=p->left;
           }
     }
     if(found==0)
     {
            cout<<"\nElement Not Found.";
            return ;
     }
     else
     {
         cout<<"\nDeleted Element: "<<p->key.id;
         cout<<"\nColour: ";
         if(p->color=='b')
     cout<<"Black\n";
    else
     cout<<"Red\n";

         if(p->parent!=NULL)
               cout<<"\nParent: "<<p->parent->key.id;
         else
               cout<<"\nThere is no parent of the node.  ";
         if(p->right!=NULL)
               cout<<"\nRight Child: "<<p->right->key.id;
         else
               cout<<"\nThere is no right child of the node.  ";
         if(p->left!=NULL)
               cout<<"\nLeft Child: "<<p->left->key.id;
         else
               cout<<"\nThere is no left child of the node.  ";
         cout<<"\nNode Deleted.";
         if(p->left==NULL||p->right==NULL)
              y=p;
         else
              y=successor(p);
         if(y->left!=NULL)
              q=y->left;
         else
         {
              if(y->right!=NULL)
                   q=y->right;
              else
                   q=NULL;
         }
         if(q!=NULL)
              q->parent=y->parent;
         if(y->parent==NULL)
              root=q;
         else
         {
             if(y==y->parent->left)
                y->parent->left=q;
             else
                y->parent->right=q;
         }
         if(y!=p)
         {
             p->color=y->color;
             p->key=y->key;
         }
         if(y->color=='b')
             delfix(q);
     }
}

void RBT::delfix(node *p)
{
    node *s;
    while(p!=root&&p->color=='b')
    {
          if(p->parent->left==p)
          {
                  s=p->parent->right;
                  if(s->color=='r')
                  {
                         s->color='b';
                         p->parent->color='r';
                         leftrotate(p->parent);
                         s=p->parent->right;
                  }
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         p=p->parent;
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->left->color='b';
                             s->color='r';
                             rightrotate(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color='b';
                      s->right->color='b';
                      leftrotate(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        p->parent->color='r';
                        rightrotate(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              leftrotate(s);
                              s=p->parent->left;
                        }
                        s->color=p->parent->color;
                        p->parent->color='b';
                        s->left->color='b';
                        rightrotate(p->parent);
                        p=root;
                  }
          }
       p->color='b';
       root->color='b';
    }
}

void RBT::leftrotate(node *p)
{
     if(p->right==NULL)
           return ;
     else
     {
           node *y=p->right;
           if(y->left!=NULL)
           {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else
           {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}
void RBT::rightrotate(node *p)
{
     if(p->left==NULL)
          return ;
     else
     {
         node *y=p->left;
         if(y->right!=NULL)
         {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else
         {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

node* RBT::successor(node *p)
{
      node *y=NULL;
     if(p == NULL) {
    	 return y;
     }
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}

void RBT::disp()
{
     display(root);
}
void RBT::display(node *p)
{
     if(root==NULL)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(p!=NULL)
     {
                cout<<"\n\t NODE: ";
                cout<<"\n Key: "<<p->key.id<<" "<<p->key.extime<<" "<<p->key.totalTime;
                cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key.id;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key.id;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key.id;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;
    if(p->left)
    {
                 cout<<"\n\nLeft:\n";
     display(p->left);
    }
    if(p->right)
    {
     cout<<"\n\nRight:\n";
                 display(p->right);
    }
     }
}
void RBT::searchNode(building x)
{
     if(root==NULL)
     {
           cout<<"\nEmpty Tree\n" ;
           return  ;
     }
     node *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->key.id==x.id)
                found=1;
            if(found==0)
            {
                 if(p->key.id<x.id)
                      p=p->right;
                 else
                      p=p->left;
            }
     }
     if(found==0)
          cout<<"\nElement Not Found.";
     else
     {
                cout<<"\n\t FOUND NODE: ";
                cout<<"\n Key: "<<p->key.id;
                cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key.id;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key.id;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key.id;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;

     }
}

bool RBT::checkEmpty() {
	node * p = successor(root);
	if(p == NULL){
		return false;
	}
	else {
		return true;
	}
}




