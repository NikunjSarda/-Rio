#include <iostream>

using namespace std;

struct node {
	node* p;
	int v;
};

int main () {
   int  var;
   node* ptr;
   node** pptr;

   var = 3000;

   // take the address of var
   ptr->v = var;

   // take the address of ptr using address of operator &
   pptr = &ptr;

   // take the value using pptr
   cout << "Value of var :" << var << endl;
   cout << "Value available at *ptr :" << ptr->v << endl;
//   cout << "Value available at **pptr :" << pptr-> << endl;

   return 0;
}
