#include<iostream>
#include<climits>
#include<fstream>
#include<iomanip>
#include<string>
#include<sstream>
#include<cstdlib>
#include<vector>
#include"MinHeap.h"

using namespace std;

int global = 0;

MinHeap h(2000);
RBT r;

void input();
void insertselect(vector <string> tokens);
void callingInsert(int insert[3]);
void callingPrint(int print[2]);
buildingHeap checkCompletion(buildingHeap build, int* counter);

// Driver program to test above functions
int main()
{
//	buildingHeap bh1, bh2, bh3, bh4;
//	building b1, b2, b3;
//	    b1.id = 50;
//	    b1.extime = 0;
//	    b1.totalTime = 100;
//	    b2.id = 15;
//	    b2.extime = 0;
//	    b2.totalTime = 200;
//	    b3.id = 30;
//	    b3.extime = 0;
//	    b3.totalTime = 50;
//	    bh1.rb = r.insertNode(b1);
//	    h.insertKey(bh1);
//	    bh2.rb = r.insertNode(b2);
//	    h.insertKey(bh2);
//	    bh3.rb = r.insertNode(b3);
//	    h.insertKey(bh3);
//	    bh4 = h.extractMin();
//	    bh4.rb->key.extime++;
//	    h.insertKey(bh4);

	input();
	h.printHeap();
	r.disp();
    return 0;
}

void input() {
ifstream fr("E:\\no_touching\\CS(Basic)\\Codes\\Practice\\ADS\\Input.txt");
	string line;
	vector <string> tokens;
	  if (fr.is_open())
	  {
	    while ( getline(fr,line) )
	    {
	    	// Vector of string to save tokens

	    	    // stringstream class check1
	    	    stringstream check1(line);
	    	    string intermediate;

	    	    // Tokenizing w.r.t. space ' '
	    	    while(getline(check1, intermediate, ' '))
	    	    {
	    	        tokens.push_back(intermediate);
	    	    }
	    }
	    fr.close();
	  }
	  insertselect(tokens);
}

void insertselect(vector <string> tokens) {
	unsigned int i = 0;
	int j, k;
	int count = 5;
	int insert[3];
	int print[2];
	buildingHeap toWork;
	node* rb = new node;
	rb->key.id = 0;
	toWork.rb = rb;
	for (i = 0; i < tokens.size(); i = i + 2) {
		k = i;
		if (atoi(tokens[i].c_str()) == global) {
			string s = tokens[i + 1];
			string s2;
			if (s[0] == 'I') {
				j = 0;
				stringstream s1(s.substr(7, s.length()));
				while (getline(s1, s2, ',')) {
					insert[j] = atoi(s2.c_str());
					j++;
				}
				callingInsert(insert);
			}
			else {
				stringstream s1(s.substr(14, s.length()));
				while (getline(s1, s2, ',')) {
					j = 0;
					print[j] = atoi(s2.c_str());
					j++;
				}
				callingPrint(print);
			}
			global++;
			if(count == 5){
				if(h.checkHeap())
					toWork = h.extractMin();
			toWork.rb->key.extime++;
			toWork  = checkCompletion(toWork, &count);
			}
			else if(count == 0) {
				h.insertKey(toWork);
				count = 5;
				count++;
			}
			else {
				toWork.rb->key.extime++;
				toWork  = checkCompletion(toWork, &count);
			}
			count--;
		}
		else {
			global++;
			if (count == 5) {
				if (h.checkHeap())
					toWork = h.extractMin();
				toWork.rb->key.extime++;
				toWork  = checkCompletion(toWork, &count);
			}
			else if (count == 0) {
				h.insertKey(toWork);
				count = 5;
				count++;
			}
			else {
				toWork.rb->key.extime++;
				toWork  = checkCompletion(toWork, &count);
			}
			count--;
			i = k-2;
		}
	}
	h.printHeap();
	r.disp();
	while (r.checkEmpty()) {
		if (count != 0) {
			if (h.checkHeap())
				toWork = h.extractMin();
			toWork.rb->key.extime++;
			toWork  = checkCompletion(toWork, &count);
		}
		if (count == 0) {
			h.insertKey(toWork);
			count = 5;
			count++;
		}
		count--;

//		checkCompletion();
	}
}

void callingInsert(int insert[3]) {
	building b;
	buildingHeap b1;
	b.id = insert[0];
	b.extime = insert[1];
	b.totalTime = insert[2];
	b1.rb = r.insertNode(b);
	h.insertKey(b1);
}

void callingPrint(int print[2]) {
	building b;
	b.id = print[0];
	b.extime = print[1];
}

buildingHeap checkCompletion(buildingHeap build, int *counter) {
	if(build.rb->key.extime == build.rb->key.totalTime) {
		cout<<"("<<build.rb->key.extime<<")"<<endl;
		r.del(build.rb->key);
		*counter = 6;
		return h.extractMin();
	}
	else {
		return build;
	}
}
