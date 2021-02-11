#ifndef TSPMetaheuristicAlgorithm_HEADER
#define TSPMetaheuristicAlgorithm_HEADER
#include "TSPAlgorithm.h"
#include <chrono>
#include <ratio>

class TSPMetaheuristicAlgorithm : public TSPAlgorithm
{
protected:
	int time;
	double findTime;
	std::vector<int> currentPath;
public:
	void GenerateStartPath();
	int CalculateCost(std::vector<int> newPath);
	double GetFindTime();
};
#endif
