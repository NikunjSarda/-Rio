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
ofstream fw("output.txt", ios::out | ios::app | ios::binary);
class Input {
public:
	void tokenized(const char *f);
	void processSelect(vector<string> token);
	void callingInsert(int ins[]);
	void callingPrint(int pri[]);
	bool checkCompletion(buildingHeap bh);
};

void Input::tokenized(const char *f) {

	ifstream fr(f);
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
	int insert[2] = { 0, 0 };
	int print[2] = { 0, 0 };
	buildingHeap toWork;
	buildingHeap tempWork;
	Building b;
	Node *rb = new Node(b);
	Node *temp = new Node(b);
	tempWork.rb = temp;
	rb->key.buildingId = 0;
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
			if (count == 5) {
				if (h.checkHeap()) {
					toWork = h.extractMin();
					toWork.rb->key.executeTime++;
					if (checkCompletion(toWork)) {
						if (r.pSuccessor(toWork.rb)) {
							r.deleteNode(toWork.rb);
							h.extractMin();
							h.insertKey(toWork);
						} else {
							r.deleteNode(toWork.rb);
						}
						toWork = tempWork;
						count = 6;
					}
				}
			} else if (count == 0) {
				if (toWork.rb->key.executeTime != toWork.rb->key.totalTime
						&& toWork.rb->key.executeTime != 0) {
					h.insertKey(toWork);
				}
				if (h.checkHeap()) {
					toWork = h.extractMin();
					toWork.rb->key.executeTime++;
				}
				if (checkCompletion(toWork)) {
					if (r.pSuccessor(toWork.rb)) {
						r.deleteNode(toWork.rb);
						h.extractMin();
						h.insertKey(toWork);
					} else {
						r.deleteNode(toWork.rb);
					}
					toWork = tempWork;
					count = 6;
				}
				count = 5;
			} else {
				if (toWork.rb != NULL) {
					toWork.rb->key.executeTime++;
					if (checkCompletion(toWork)) {
						if (r.pSuccessor(toWork.rb)) {
							r.deleteNode(toWork.rb);
							h.extractMin();
							h.insertKey(toWork);
						} else {
							r.deleteNode(toWork.rb);
						}
						toWork = tempWork;
						count = 6;
					}
				} else {
					count = 6;
				}
			}
		} else {
			if (count == 5) {
				if (h.checkHeap()) {
					toWork = h.extractMin();
					toWork.rb->key.executeTime++;
					if (checkCompletion(toWork)) {
						if (r.pSuccessor(toWork.rb)) {
							r.deleteNode(toWork.rb);
							h.extractMin();
							h.insertKey(toWork);
						} else {
							r.deleteNode(toWork.rb);
						}
						toWork = tempWork;
						count = 6;
					}
				}
			} else if (count == 0) {
				if (toWork.rb->key.executeTime != toWork.rb->key.totalTime
						&& toWork.rb->key.executeTime != 0) {
					h.insertKey(toWork);
				}
				if (h.checkHeap()) {
					toWork = h.extractMin();
					toWork.rb->key.executeTime++;
				}
				if (checkCompletion(toWork)) {
					if (r.pSuccessor(toWork.rb)) {
						r.deleteNode(toWork.rb);
						h.extractMin();
						h.insertKey(toWork);
					} else {
						r.deleteNode(toWork.rb);
					}
					toWork = tempWork;
					count = 6;
				}
				count = 5;
			} else {
				if (toWork.rb != NULL) {
					toWork.rb->key.executeTime++;
					if (checkCompletion(toWork)) {
						if (r.pSuccessor(toWork.rb)) {
							r.deleteNode(toWork.rb);
							h.extractMin();
							h.insertKey(toWork);
						} else {
							r.deleteNode(toWork.rb);
						}
						toWork = tempWork;
						count = 6;
					}
				} else {
					count = 6;
				}
			}
			i = k - 2;
		}
		count--;
		global++;
	}

	while (r.checkEmpty()) {

		if (count == 5) {
			if (h.checkHeap()) {
				toWork = h.extractMin();
				toWork.rb->key.executeTime++;
				if (checkCompletion(toWork)) {
					if (r.pSuccessor(toWork.rb)) {
						r.deleteNode(toWork.rb);
						h.extractMin();
						h.insertKey(toWork);
					} else {
						r.deleteNode(toWork.rb);
					}
					toWork = tempWork;
					count = 6;
				}
			}
		} else if (count == 0) {
			if (toWork.rb != temp) {
				h.insertKey(toWork);
				toWork = tempWork;
			}
			if (h.checkHeap()) {
				toWork = h.extractMin();
				toWork.rb->key.executeTime++;
				if (checkCompletion(toWork)) {
					if (r.pSuccessor(toWork.rb)) {
						r.deleteNode(toWork.rb);
						h.extractMin();
						h.insertKey(toWork);
					} else {
						r.deleteNode(toWork.rb);
					}
					toWork = tempWork;
					count = 6;
				} else {
					count = 5;
				}
			}
		} else {
			if (toWork.rb != NULL) {
				toWork.rb->key.executeTime++;
				if (checkCompletion(toWork)) {
					if (r.pSuccessor(toWork.rb)) {
						r.deleteNode(toWork.rb);
						h.extractMin();
						h.insertKey(toWork);
					} else {
						r.deleteNode(toWork.rb);
					}
					toWork = tempWork;
					count = 6;
				}
			} else {
				count = 6;
			}
		}
		count--;
		global++;
	}
}

void Input::callingInsert(int insert[2]) {
	Building b;
	buildingHeap b1;
	b.buildingId = insert[0];
	b.executeTime = 0;
	b.totalTime = insert[1];
	b1.rb = r.insert(b);
	h.insertKey(b1);
}

void Input::callingPrint(int print[2]) {
	Building b;
	Node *toPrint;
	b.buildingId = print[0];
	b.executeTime = print[1];
	if (b.executeTime == 0) {
		toPrint = r.search(b.buildingId);
		if (toPrint == NULL) {
			fw << "(0,0,0)" << endl;
		} else {
			fw << "(" << toPrint->key.buildingId << ","
					<< toPrint->key.executeTime << "," << toPrint->key.totalTime
					<< ")" << endl;
		}
	} else {
		for (int i = print[0]; i < print[1]; i++) {
			toPrint = r.search(i);
			if (toPrint == NULL) {
				fw << "(0,0,0) ," << endl;
			} else {
				fw << "(" << toPrint->key.buildingId << ","
						<< toPrint->key.executeTime << ","
						<< toPrint->key.totalTime << "), ";
			}
		}
		toPrint = r.search(print[1]);
		if (toPrint == NULL) {
			fw << "(0,0,0)" << endl;
		} else {
			fw << "(" << toPrint->key.buildingId << ","
					<< toPrint->key.executeTime << "," << toPrint->key.totalTime
					<< ")" << endl;
		}
	}
}

bool Input::checkCompletion(buildingHeap build) {
	if (build.rb->key.executeTime == build.rb->key.totalTime) {
		fw << "(" << build.rb->key.buildingId << "," << global + 1 << ")"
				<< "\n";
		return true;
	}
	return false;
}
