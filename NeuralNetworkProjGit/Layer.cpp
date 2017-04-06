#pragma once
#include "stdafx.h"
#include "Layer.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

Layer::Layer()
{
}

Layer::Layer(int numNodes, int sizeOfPrevLay)
{
	NodePtrVect nullVal;
	nullVal.length = -1;
	myNumNodes = numNodes;
	if (numNodes > 1)
	{
		myNodes = new Node[numNodes];
		for (int i = 0; i < numNodes; i++)
		{
			myNodes[i] = Node(sizeOfPrevLay, nullVal);
		}
	}
	else
	{
		myNodes = new Node[1];
		myNodes[0] = Node(sizeOfPrevLay, nullVal);
	}
	
}

Layer::Layer(int numNodes, int sizeOfPrevLay, NodePtrVect prevNodes)
{
	myNumNodes = numNodes;
	if (numNodes > 1)
	{
		myNodes = new Node[numNodes];
		for (int i = 0; i < numNodes; i++)
		{
			myNodes[i] = Node(sizeOfPrevLay, prevNodes);
		}
	}
	else
	{
		myNodes = new Node[1];
		myNodes[0] = Node(sizeOfPrevLay, prevNodes);
	}
}

NodePtrVect Layer::getNodePtrs()
{
	NodePtrVect outputVal;
	outputVal.length = myNumNodes;
	outputVal.ptrs = myNodes;
	return outputVal;
}

int Layer::getNumNumbers()
{
	return myNumNodes;
}

VectorDouble Layer::calculateNodes(VectorDouble prevValues)
{
	for (int i = 0; i < myNumNodes; i++)
	{
		myNodes[i].calculateOutput(prevValues);
	}

	double* myOutput = new double[myNumNodes];
	for (int i = 0; i < myNumNodes; i++)
	{
		myOutput[i] = myNodes[i].getOutput();
	}

	VectorDouble returnVal;
	returnVal.nums = myOutput;
	returnVal.length = myNumNodes;
	return returnVal;
}

void Layer::assignInputToOutput(VectorDouble inputVals)
{
	for (int i = 0; i < inputVals.length; i++)
	{
		myNodes[i].assignInputToOutput(inputVals.nums[i]);
	}
}

VectorDouble Layer::getOutputs()
{
	double* outputNums = new double[myNumNodes];
	for (int i = 0; i < myNumNodes; i++)
	{
		outputNums[i] = myNodes[i].getOutput();
	}
	VectorDouble outputVec;
	outputVec.nums = outputNums;
	outputVec.length = myNumNodes;
	return outputVec;
}

void Layer::changeInitalWeights(VectorDouble prevOut)
{
	for (int i = 0; i < myNumNodes; i++)
	{
		myNodes[i].updateWeights(prevOut.nums[i], 1);
	}
}

Layer::~Layer()
{
}
