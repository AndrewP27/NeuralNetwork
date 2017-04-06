#pragma once
#include "stdafx.h"
#include "NeuralNetwork.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(int numLayers, int numFeatures, int hiddenLayerNodes, int numOutput)
{
	myNumLayers = numLayers;
    
	if(myNumLayers > 3)
		myLayers = new Layer[myNumLayers];
	else
		myLayers = new Layer[3];
    
	myLayers[0] = Layer(numFeatures,-1);

	for (int i = 1; i < myNumLayers -1; i++)
	{
		NodePtrVect prevNodes = myLayers[i - 1].getNodePtrs();
		myLayers[i] = Layer(hiddenLayerNodes, myLayers[i-1].getNumNumbers(), prevNodes);
	}

	myLayers[myNumLayers -1] = Layer(numOutput, myLayers[myNumLayers - 2].getNumNumbers(), myLayers[myNumLayers - 2].getNodePtrs());
}

VectorDouble NeuralNetwork::calculateOutput(VectorDouble input)
{
	VectorDouble prevNums;
	prevNums = input;
	myLayers[0].assignInputToOutput(input);
	for (int i = 1; i < myNumLayers; i++)
	{
		prevNums = myLayers[i].calculateNodes(prevNums);
	}
	return prevNums;
}

double NeuralNetwork::trainOnce(VectorDouble input, VectorDouble expectedOutput)
{
    calculateOutput(input);
	updateWeights(expectedOutput);
    VectorDouble results = calculateOutput(input);
    double sum = 0;
    
	for (int i = 0; i < expectedOutput.length; i++)
	{
		sum += (expectedOutput.nums[i] - results.nums[i]) * (expectedOutput.nums[i] - results.nums[i]);
	}
    
	return sum;
}

void NeuralNetwork::updateWeights(VectorDouble yVals)
{
	VectorDouble differenceVals;
	differenceVals.nums = new double[yVals.length];
	differenceVals.length = yVals.length;
	VectorDouble calculated = myLayers[myNumLayers-1].getOutputs();

	for (int i = 0; i < yVals.length; i++)
	{
		differenceVals.nums[i] = yVals.nums[i] - calculated.nums[i];
	}
	myLayers[myNumLayers-1].changeInitalWeights(differenceVals);
}

double NeuralNetwork::trainSet(double* input1, double* input2, double* output, int length)
{
    VectorDouble theNums;
    VectorDouble out;
    int numIn = myLayers[0].getNumNumbers();
    int numOut = myLayers[myNumLayers - 1].getNumNumbers();
    double* ptrIn = new double[numIn];
    double* ptrOut = new double[numOut];
    double sumError = 0;

    for (int i = 0; i < length; i++)
    {
        ptrIn[0] = input1[i];
        ptrIn[1] = input2[i];
        ptrOut[0] = output[i];
        theNums.nums = ptrIn;
        theNums.length = numIn;
        out.nums = ptrOut;
        out.length = numOut;
        sumError = trainOnce(theNums, out);
    }

    return sumError / length;
}

NeuralNetwork::~NeuralNetwork()
{
}
