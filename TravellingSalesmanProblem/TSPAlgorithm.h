#ifndef TSPAlgorithm_HEADER
#define TSPAlgorithm_HEADER
#include <vector>

class TSPAlgorithm
{
public:
	std::vector<int> path;
	int** arrayGraph;
	int distance;
	int cityNum;
public:
	std::vector<int> getPath();
	int getDistance();
};
#endif