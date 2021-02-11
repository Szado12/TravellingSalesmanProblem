#include "TSPAlgorithm.h"
class TSPBruteForce : public TSPAlgorithm
{

public:
	TSPBruteForce(int** arrayGraph, int cityNum);
	void CalculatePath();
	void BruteForce(std::vector<int> currentPath, int currentNode, int distance);
};

