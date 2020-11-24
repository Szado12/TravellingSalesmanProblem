#include "Graph.h"
#include <cstdlib>
#include "TSPBruteForce.h"
#include "TSPDynamicProgramming.h"
#include "TSPBranchAndBound.h"
#include "TSPAlgorithm.h"

Graph::Graph(int cityNum)
{
	this->cityNum = cityNum;
	arrayGraph = new int* [cityNum];
	for(int i=0;i<cityNum;i++)
		arrayGraph[i] = new int[cityNum];
}

void Graph::generateGraph()
{
	for (int i = 0; i < this->cityNum; i++)
		for (int j = 0; j < this->cityNum; j++)
			if (i == j)
				arrayGraph[i][j] = -1;
			else
				arrayGraph[i][j] = rand()%100 + 1;
}

void Graph::loadGraph(int i,int j, int value)
{
	try {
		this->arrayGraph[i][j] = value;
	}
	catch (const std::exception&) {
		printf("Error position out of range");
	}
}

void Graph::printGraph()
{
	for (int i = -2; i < this->cityNum; i++) {
		if (i > -1)
			printf("\n %4d|", i);
		else
			printf("\n      ");
		for (int j = 0; j < this->cityNum; j++) {
			if (i == -2)
				printf("% 4d ", j);
			else if (i == -1)
				printf("_____");
			else
				printf("% 4d ", this->arrayGraph[i][j]);
		}
	}
	printf("\n");
}

void Graph::dynamicPrograming()
{
	TSPDynamicProgramming* DynamicProgramming= new TSPDynamicProgramming(this->arrayGraph, this->cityNum);
	DynamicProgramming->calculatePath();
	this->path = DynamicProgramming->getPath();
	this->distance = DynamicProgramming->getDistance();
}

void Graph::branchAndBound()
{
	TSPBranchAndBound* branchAndBound = new TSPBranchAndBound(this->arrayGraph, this->cityNum);
	branchAndBound->calculatePath();
	this->path = branchAndBound->getPath();
	this->distance = branchAndBound->getDistance();
}

void Graph::bruteForce()
{
	TSPBruteForce* BruteForce = new TSPBruteForce(this->arrayGraph, this->cityNum);
	BruteForce->calculatePath();
	this->path = BruteForce->getPath();
	this->distance = BruteForce->getDistance();
}
void Graph::printPath() {
	printf("Path:\n");
	for (int i = 0; i < this->cityNum; i++)
		printf("%d -> ", this->path[i]);
	printf("0 \nDistance: %d \n", this->distance);
}