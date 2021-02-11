#include "TSPMetaheuristicAlgorithm.h"

class TSPSimulatedAnnealing : public TSPMetaheuristicAlgorithm
{
	double temperatureMax, temperatureCurrent, coolingValue;
	
public:
	TSPSimulatedAnnealing(int** arrayGraph, int cityNum,int time, double coolingValue);
	void Annealing();
	std::vector<int> FindPathSwap(std::vector<int> currentPath);
};

