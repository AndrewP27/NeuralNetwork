#pragma once
#include "Node.h"
#include "stdafx.h"

class Layer
{
private:
	int myNumNodes;
	Node* myNodes;
public:
	Layer();
	Layer(int numNodes, int sizeOfPrevLay);
	Layer(int numNodes, int sizeOfPrevLay, NodePtrVect prevNodes);
	int getNumNumbers();
	NodePtrVect getNodePtrs();
	VectorDouble getOutputs();
	VectorDouble calculateNodes(VectorDouble prevValues);
	void changeInitalWeights(VectorDouble prevOut);
	void assignInputToOutput(VectorDouble inputVals);
	~Layer();
};

