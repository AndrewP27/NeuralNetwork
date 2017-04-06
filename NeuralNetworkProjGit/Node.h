#pragma once
#include "stdafx.h"

struct NodePtrVect {
	class Node* ptrs;
	int length;
};

class Node
{
private:
	int numWeights;
	double alphaVal = 10;
	double* myWeights;
	double myOutput;
	double mySum;
	double sigmoidFun(double val);
	double sigmoidPrimeFun(double val);
	NodePtrVect myParentNodes;
public:
	Node();
	Node(int sizeOfPrevLay, NodePtrVect parentNodes);
	double getOutput();
	void calculateOutput(VectorDouble prevValues);
	void updateWeights(double prevOut, double forwardWeight);
	void assignInputToOutput(double inputVals);
	~Node();
};


