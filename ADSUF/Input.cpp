#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<vector>
#include"MinHeap.h"

int global = 0;
MinHeap h(2000);
RBT r;

class Input {
public:
	void tokenized();
	void processSelect(vector<string> token);
	void callingInsert(int ins[]);
	void callingPrint(int pri[]);
	void checkCompletion(buildingHeap bh, int* counter);
};

void Input::tokenized() {
	ifstream fr("E:\\no_touching\\CS(Basic)\\Codes\\Practice\\ADS\\Input.txt");
	string line;
	// Vector of string to save tokens
	vector<string> tokens;
	if (fr.is_open()) {
		while (getline(fr, line)) {
			// stringstream class check1
			stringstream check1(line);
			string intermediate;

			// Tokenizing w.r.t. space ' '
			while (getline(check1, intermediate, ' ')) {
				tokens.push_back(intermediate);
			}
		}
		fr.close();
	}
	processSelect(tokens);
}

void Input::processSelect(vector<string> tokens) {
	unsigned int i = 0;
	int j, k;
	int count = 5;
	int insert[3];
	int print[2];
	buildingHeap toWork;
	node *rb = new node;
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
			} else {
				stringstream s1(s.substr(14, s.length()));
				while (getline(s1, s2, ',')) {
					j = 0;
					print[j] = atoi(s2.c_str());
					j++;
				}
				callingPrint(print);
			}
			global++;
			if (count == 5) {
				if (h.checkHeap())
					toWork = h.extractMin();
				toWork.rb->key.extime++;
				checkCompletion(toWork, &count);
			} else if (count == 0) {
				h.insertKey(toWork);
				count = 5;
				count++;
			} else {
				toWork.rb->key.extime++;
				checkCompletion(toWork, &count);
			}
			count--;
		} else {
			global++;
			if (count == 5) {
				if (h.checkHeap())
					toWork = h.extractMin();
				toWork.rb->key.extime++;
				checkCompletion(toWork, &count);
			} else if (count == 0) {
				h.insertKey(toWork);
				count = 5;
				count++;
			} else {
				toWork.rb->key.extime++;
				checkCompletion(toWork, &count);
			}
			count--;
			i = k - 2;
		}
	}
	while (r.checkEmpty()) {
		if (count == 5) {
			if (h.checkHeap())
				toWork = h.extractMin();
			toWork.rb->key.extime++;
			checkCompletion(toWork, &count);
		} else if (count == 0) {
			h.insertKey(toWork);
			count = 5;
			count++;
		} else {
			toWork.rb->key.extime++;
			checkCompletion(toWork, &count);
		}
		count--;
	}
}

void Input::callingInsert(int insert[3]) {
	building b;
	buildingHeap b1;
	b.id = insert[0];
	b.extime = insert[1];
	b.totalTime = insert[2];
	b1.rb = r.insertNode(b);
	h.insertKey(b1);
}

void Input::callingPrint(int print[2]) {
	building b;
	b.id = print[0];
	b.extime = print[1];
}

void Input::checkCompletion(buildingHeap build, int *counter) {
	if(build.rb->key.extime == build.rb->key.totalTime)
	{
		cout<<"("<<build.rb->key.extime<<")"<<endl;
		r.del(build.rb->key);
		*counter = 6;
	}
}
