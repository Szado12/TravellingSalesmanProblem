#include "TSPBruteForce.h"
#include <algorithm>

TSPBruteForce::TSPBruteForce(int** arrayGraph,int cityNum)
{
	this->cityNum = cityNum;
	this->arrayGraph = arrayGraph;
	this->distance = INT_MAX;
}

void TSPBruteForce::calculatePath()
{
	std::vector<int> currentPath;
	currentPath.push_back(0);
	bruteForce(currentPath, 0, 0);
}
void TSPBruteForce::bruteForce(std::vector<int> currentPath,int currentNode,int distance) 
{
	if (distance < this->distance) {
		if (currentPath.size() == this->cityNum)
		{
			distance += arrayGraph[currentNode][0];
			if (distance < this->distance) {
				this->distance = distance;
				this->path = currentPath;
			}
		}
		else
		{
			for (int i = 0; i < this->cityNum; i++)
				if (std::find(currentPath.begin(), currentPath.end(), i) == currentPath.end()) {
					currentPath.push_back(i);
					bruteForce(currentPath, i, distance + arrayGraph[currentNode][i]);
					currentPath.pop_back();
				}
		}
	}
			
}
