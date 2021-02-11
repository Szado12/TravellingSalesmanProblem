#include <iostream>
#include "Graph.h"
#include <fstream>
#include <string>

#include <time.h>
#include <string>
using namespace std;
int main()
{

	
	srand(time(NULL));
	int menu, menuAlg, menuGA, menuTS, menuSA, time = 120, mutation = 0, population = 200, type = 0;
	double mutationChance = 0.01, crossoverChance = 0.8, coolingValue = 0.99;
	Graph* graph;
fileMenu:
	printf("1. Read graph from file\n");
	printf("2. End\n");
	cin >> menu;
	switch (menu) {
	case 1:
	{
		std::string filename;
		printf("File path:\n");
		cin >> filename;
		std::ifstream myfile;
		myfile.open(filename);
		if (!myfile) {
			printf("Couldn't read file\n");
			goto fileMenu;
		}
		else {
			int n, data;
			string info;
			for (int i=0; i < 3; i++) {
				getline(myfile, info);
			}
			myfile >> info;
			myfile >> n;
			for (int i = 0; i < 4; i++) {
				getline(myfile, info);
			}
			graph = new Graph(n);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					myfile >> data;
					graph->LoadGraph(i, j, data);
				}
			goto menuAlgorithm;
		}
	}
	
	case 2:
		return 0;
	default:
		goto fileMenu;
	}
menuAlgorithm:
	printf("1. Brute Force\n");
	printf("2. Dynamic Programming\n");
	printf("3. Branch and Bound\n");
	printf("4. Simulated Annealing\n");
	printf("5. Tabu Search\n");
	printf("6. Genetic Algorithm\n");
	printf("7. Back\n");
	printf("8. End\n");
	cin >> menuAlg;
	switch (menuAlg) {
	case 1:
	{
		graph->BruteForce();
		graph->PrintPath();
		goto menuAlgorithm;

	}
	case 2:
	{
		graph->DynamicPrograming();
		graph->PrintPath();
		goto menuAlgorithm;
	}
	case 3:
	{
		graph->BranchAndBound();
		graph->PrintPath();
		goto menuAlgorithm;
	}
	case 4:
	{
		goto menuAnnealing;
	}
	case 5:
	{
		goto menuTabu;
	}
	case 6:
	{
		goto menuGenetic;
	}
	case 7:
	{
		goto fileMenu;
	}
	case 8:
	{
		return 0;
	}
	default:
	{
		goto menuAlgorithm;
	}
	}
menuAnnealing:
	printf("1. Print graph\n");
	printf("2. Print path\n");
	printf("3. Change time of searching\n");
	printf("4. Change cooling value\n");
	printf("5. Run algorithm\n");
	printf("6. Back\n");
	printf("7. End\n");
	scanf_s("%d", &menuSA);
	switch (menuSA) {
	case 1:
	{
		graph->PrintGraph();
		goto menuAnnealing;
	}
	case 2:
	{
		graph->PrintPathAndTime();
		goto menuAnnealing;
	}
	case 3:
	{
		printf("New time of searching:\n");
		cin >> time;
		goto menuAnnealing;
	}
	case 4:
	{
		printf("Cooling value:\n");
		cin >> coolingValue;
		goto menuAnnealing;
	}
	case 5:
	{
		graph->SimulatedAnnealing(time, coolingValue);
		graph->PrintPathAndTime();
	}
	case 6:
	{
		goto menuAlgorithm;
	}
	case 7:
	{
		return 0;
	}
	}
menuTabu:
	printf("1. Print graph\n");
	printf("2. Print path\n");
	printf("3. Change time of searching\n");
	printf("4. Change neighbourhood type\n");
	printf("5. Run algorithm\n");
	printf("6. Back\n");
	printf("7. End\n");
	scanf_s("%d", &menuTS);
	switch (menuTS) {
	case 1:
	{
		graph->PrintGraph();
		goto menuTabu;
	}
	case 2:
	{
		graph->PrintPathAndTime();
		goto menuTabu;
	}
	case 3:
	{
		printf("New time of searching:\n");
		cin >> time;
		goto menuTabu;
	}
	case 4:
	{
		printf("Type of neighbour:\n");
		printf("1. Swap:\n");
		printf("2. Invert:\n");
		printf("3. Insert:\n");
		cin >> type;
		type--;
		goto menuTabu;
	}
	case 5:
	{
		graph->TabuSearch(time, type);
		graph->PrintPathAndTime();
	}
	case 6:
	{
		goto menuAlgorithm;
	}
	case 7:
	{
		return 0;
	}
	}
menuGenetic:
	printf("1. Print graph\n");
	printf("2. Print path\n");
	printf("3. Change time of searching\n");
	printf("4. Change crossover chance\n");
	printf("5. Change mutation chance\n");
	printf("6. Change type of mutation\n");
	printf("7. Change population size\n");
	printf("8. Run algorithm\n");
	printf("9. Back\n");
	printf("10. End\n");
	scanf_s("%d", &menuGA);
	switch (menuGA) {
	case 1:
	{
		graph->PrintGraph();
		goto menuGenetic;
	}
	case 2:
	{
		graph->PrintPathAndTime();
		goto menuGenetic;
	}
	case 3:
	{
		printf("New time of searching:\n");
		cin >> time;
		goto menuGenetic;
	}
	case 4:
	{
		printf("New Crossover chance:\n");
		cin >> crossoverChance;
		goto menuGenetic;
	}
	case 5:
	{
		printf("New Mutation chance:\n");
		cin >> mutationChance;
		goto menuGenetic;
	}
	case 6:
	{
		printf("Type of mutation:\n");
		printf("1: Transpostion\n");
		printf("2: Inversion\n");
		cin >> mutation;
		mutation--;
		goto menuGenetic;
	}
	case 7:
	{
		printf("New population size:\n");
		cin >> population;
		goto menuGenetic;
	}
	case 8:
	{
		graph->GeneticAlgorithm(time, 1, mutation, population, crossoverChance, mutationChance);
		graph->PrintPath();
		goto menuGenetic;
	}
	case 9:
	{
		goto menuAlgorithm;
	}
	case 10:
	{
		return 0;
	}
	}
	return 0;
}
	
	

