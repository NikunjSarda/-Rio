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
building toBuild;

void input();
void insertselect(vector <string> tokens);
void callingInsert(int insert[3]);
void callingPrint(int print[2]);

// Driver program to test above functions
int main()
{
	input();
	h.printHeap();
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
	int i = 0;
	int j, k;
	int count = 5;
	int insert[3];
	int print[2];
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
			if(count == 0) {
				h.MinHeapify(0);
				count = 5;
			}
			h.increaseKey(0, 1);
			count--;
		}
		else {
			global++;
			if(count == 0){
				h.MinHeapify(0);
				count = 5;
			}
			h.increaseKey(0, 1);
			count--;
			i = k-2;
		}
	}
	while(h.getMin().id != INT_MAX) {
		if(count == 0) {
			h.MinHeapify(0);
			count = 5;
		}
		h.increaseKey(0, 1);
		count--;
	}
}

void callingInsert(int insert[3]) {
	building b;
	b.id = insert[0];
	b.extime = insert[1];
	b.totalTime = insert[2];
	h.insertKey(b);
//	h.printHeap();
}

void callingPrint(int print[2]) {
	building b;
	b.id = print[0];
	b.extime = print[1];
}
