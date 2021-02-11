#include "Graph.h"
#include <cstdlib>
#include "TSPBruteForce.h"
#include "TSPDynamicProgramming.h"
#include "TSPBranchAndBound.h"
#include "TSPAlgorithm.h"
#include "TSPSimulatedAnnealing.h"
#include "TSPTabuSearch.h"
#include "TSPGeneticAlgorithm.h"

Graph::Graph(int cityNum)
{
	this->cityNum = cityNum;
	arrayGraph = new int* [cityNum];
	for(int i=0;i<cityNum;i++)
		arrayGraph[i] = new int[cityNum];
}

void Graph::LoadGraph(int i,int j, int value)
{
	try {
		if(i==j)
			this->arrayGraph[i][j] = -1;
		else
			this->arrayGraph[i][j] = value;
	}
	catch (const std::exception&) {
		printf("Error position out of range");
	}
}

void Graph::PrintGraph()
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

void Graph::DynamicPrograming()
{
	TSPDynamicProgramming* DynamicProgramming= new TSPDynamicProgramming(this->arrayGraph, this->cityNum);
	DynamicProgramming->CalculatePath();
	this->path = DynamicProgramming->GetPath();
	this->distance = DynamicProgramming->GetDistance();
}

void Graph::BranchAndBound()
{
	TSPBranchAndBound* branchAndBound = new TSPBranchAndBound(this->arrayGraph, this->cityNum);
	branchAndBound->CalculatePath();
	this->path = branchAndBound->GetPath();
	this->distance = branchAndBound->GetDistance();
}

void Graph::BruteForce()
{
	TSPBruteForce* BruteForce = new TSPBruteForce(this->arrayGraph, this->cityNum);
	BruteForce->CalculatePath();
	this->path = BruteForce->GetPath();
	this->distance = BruteForce->GetDistance();
}
void Graph::PrintPath() {

	try
	{

		printf("Path:\n");
		for (int i = 0; i < this->cityNum; i++)
			printf("%d -> ", this->path[i]);
		printf("%d \nDistance: %d \n", this->path.front(), this->distance);
	}
	catch (const std::exception&)
	{
		printf("Path is empty");
	}
}

void Graph::PrintPathAndTime()
{
	try 
	{
		printf("Path:\n");
		for (int i = 0; i < this->cityNum; i++)
			printf("%d -> ", this->path[i]);
		printf("%d \nDistance: %d \n", this->path.front(), this->distance);
		printf("Time: %f\n", this->time);
	}
	catch (const std::exception&)
	{
		printf("Path is empty");
	}
}

void Graph::SimulatedAnnealing(int time, double coolingValue)
{
	TSPSimulatedAnnealing* simulateAnnealing = new TSPSimulatedAnnealing(this->arrayGraph, this->cityNum,time, coolingValue);
	simulateAnnealing->Annealing();
	this->path = simulateAnnealing->GetPath();
	this->distance = simulateAnnealing->GetDistance();
	this->time = simulateAnnealing->GetFindTime();
}
void Graph::TabuSearch(int time,int type) {
	TSPTabuSearch* tabuSearch = new TSPTabuSearch(this->arrayGraph, this->cityNum, time, type);
	tabuSearch->TabuSearch();
	this->path = tabuSearch->GetPath();
	this->distance = tabuSearch->GetDistance();
	this->time = tabuSearch->GetFindTime();
}
void Graph::GeneticAlgorithm(int runningTime, int crossover, int mutation, int population, double crossOverChance, double mutationChance){
	TSPGeneticAlgorithm* genetic = new TSPGeneticAlgorithm(this->arrayGraph, this->cityNum, runningTime,crossover,mutation,population,crossOverChance,mutationChance);
	genetic->GeneticAlgorithm();
	this->path = genetic->GetPath();
	this->distance = genetic->GetDistance();
}