#include <iostream>
#include "Graph.h"
#include <fstream>

int main()
{
	int m1, m2;
	Graph* graph;
menu1:
	printf("1. Generate graph\n");
	printf("2. Read graph from file\n");
	printf("3. End\n");
	scanf_s("%d",&m1);
	switch (m1) {
	case 1:
	{
		int n;
		printf("Set size:\n");
		scanf_s("%d", &n);
		if (n < 2) {
			printf("Size must be bigger than 2\n");
			goto menu1;
		}
		graph = new Graph(n);
		graph->generateGraph();
		goto menu2;
	}
	case 2:
	{
		std::string filename;
		printf("File path:\n");
		scanf_s("%s", filename);
		std::ifstream myfile;
		myfile.open(filename);
		if (!myfile) {
			printf("Couldn't read file");
			goto menu1;
		}
		else {
			int n, data;
			myfile >> n;
			graph = new Graph(n);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					myfile >> data;
					graph->loadGraph(i, j, data);
				}
			goto menu2;
		}
	}
	case 3:
		return 0;
	default:
		goto menu1;
	}
menu2:
	printf("1. Print graph\n");
	printf("2. Print path\n");
	printf("3. Bruteforce algorithm\n");
	printf("4. Branch and Bound algorithm\n");
	printf("5. Dynamic Programming algorithm\n");
	printf("6. Back\n");
	printf("7. End\n");
	scanf_s("%d", &m2);
	switch (m2) {
	case 1:
	{
		graph->printGraph();
		goto menu2;
	}
	case 2:
	{
		graph->printPath();
		goto menu2;
	}
	case 3:
	{
		graph->bruteForce();
		goto menu2;
	}
	case 4:
	{
		graph->branchAndBound();
		goto menu2;
	}
	case 5:
	{
		graph->dynamicPrograming();
		goto menu2;
	}
	case 6:
	{
		goto menu1;
	}
	case 7:
		return 0;
	default:
		goto menu2;
	}

	return 0;
}
