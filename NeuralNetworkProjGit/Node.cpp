#pragma once
#include "stdafx.h"
#include "Node.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>  

Node::Node()
{
}

Node::Node(int sizeOfPrevLay, NodePtrVect parentNodes)
{
	numWeights = sizeOfPrevLay;
	if (sizeOfPrevLay != -1)
		myWeights = new double[sizeOfPrevLay];
	for (int i = 0; i < sizeOfPrevLay; i++)
	{
		myWeights[i] = ((double)(rand() % 1000))/1000;
	}

	myParentNodes = parentNodes;
}

double Node::getOutput()
{
	return myOutput;
}

void Node::calculateOutput(VectorDouble prevValues)
{
	mySum = 0;
	for (int i = 0; i < prevValues.length; i++)
	{
		mySum = prevValues.nums[i] * myWeights[i] + mySum;
	}
	myOutput = sigmoidFun(mySum);
}

void Node::assignInputToOutput(double inputVals)
{
	myOutput = inputVals;
    mySum = inputVals;
}

double Node::sigmoidFun(double val)
{
	return (1 / (1 + exp(val)));
}

double Node::sigmoidPrimeFun(double val)
{
	return (sigmoidFun(val) * (1 - sigmoidFun(val)));
}

void Node::updateWeights(double prevOut, double forwardWeight)
{
	double myOut = prevOut*sigmoidPrimeFun(mySum);
	for (int i = 0; i < numWeights; i++)
	{
		myWeights[i] = myWeights[i] - myOut*forwardWeight*(myParentNodes.ptrs[i]).getOutput()*alphaVal;
	}

	for (int i = 0; i < myParentNodes.length; i++)
	{
		(myParentNodes.ptrs[i]).updateWeights(myOut, myWeights[i]);
	}
}

Node::~Node()
{
}
