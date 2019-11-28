#ifndef INPUT_H_
#define INPUT_H_

#include<vector>
#include"MinHeap.h"
class Input {
public:
	void tokenized(const char* f);
	void processSelect(vector<string> token);
	void callingInsert(int ins[]);
	void callingPrint(int pri[]);
	void checkCompletion(buildingHeap bh, int* counter);
};

#endif
