#pragma once
#include "Layer.h"
class NeuralNetwork
{
private:
	int myNumLayers;
	Layer* myLayers;
	
public:
	NeuralNetwork();
	NeuralNetwork(int numLayers, int numFeatures, int hiddenLayerNodes, int numOutput);
	VectorDouble calculateOutput(VectorDouble input);
	double trainOnce(VectorDouble input, VectorDouble expectedOutput);
    double trainSet(double* input1, double* input2, double* output, int length);
    void updateWeights(VectorDouble yVals);
	~NeuralNetwork();
};

