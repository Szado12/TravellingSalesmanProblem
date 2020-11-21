#include "Graph.h"
#include <cstdlib>
#include "TSPBruteForce.h"

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

void Graph::loadGraph()
{
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
}

void Graph::branchAndBound()
{
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
	printf("0 \n Distance: %d", this->distance);
}