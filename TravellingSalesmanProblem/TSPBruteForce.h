#include "TSPAlgorithm.h"
class TSPBruteForce : public TSPAlgorithm
{

public:
	TSPBruteForce(int** arrayGraph, int cityNum);
	void calculatePath();
	void bruteForce(std::vector<int> currentPath, int currentNode, int distance);
	
};

