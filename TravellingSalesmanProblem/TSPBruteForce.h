#include <vector>

class TSPBruteForce
{
private:
	int** arrayGraph;
	int distance;
	int cityNum;
	std::vector<int> path;
public:
	TSPBruteForce(int** arrayGraph, int cityNum);
	void calculatePath();
	void bruteForce(std::vector<int> currentPath, int currentNode, int distance);
	int getDistance();
	std::vector<int> getPath();
};

