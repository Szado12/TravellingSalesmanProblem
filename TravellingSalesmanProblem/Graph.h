#include <vector>

class Graph
{
private:
	std::vector<int> path;
	int distance;
	int** arrayGraph;
	int cityNum;
	double time;
public:
	Graph(int cityNum);
	void LoadGraph(int i, int j, int value);
	void PrintGraph();
	void DynamicPrograming();
	void BranchAndBound();
	void BruteForce();
	void PrintPath();
	void PrintPathAndTime();
	void SimulatedAnnealing(int time, double coolingValue);
	void TabuSearch(int time, int type);
	void GeneticAlgorithm(int runningTime, int crossover, int mutation, int population, double crossOverChance, double mutationChance);
};

