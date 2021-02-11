#include "TSPBruteForce.h"
#include <algorithm>
/// <summary>
/// Constructor with parameters
/// </summary>
/// <param name="arrayGraph"></param>
/// <param name="cityNum"></param>
TSPBruteForce::TSPBruteForce(int** arrayGraph,int cityNum)
{
	this->cityNum = cityNum;
	this->arrayGraph = arrayGraph;
	this->distance = INT_MAX;
}
/// <summary>
/// Function starts BruteForce algorithm. 
/// </summary>
void TSPBruteForce::CalculatePath()
{
	std::vector<int> currentPath;
	currentPath.push_back(0);
	BruteForce(currentPath, 0, 0);
}
/// <summary>
/// Functions try all possible n! solutions
/// </summary>
/// <param name="currentPath"></param>
/// <param name="currentNode"></param>
/// <param name="distance"></param>
void TSPBruteForce::BruteForce(std::vector<int> currentPath,int currentNode,int distance) 
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
					BruteForce(currentPath, i, distance + arrayGraph[currentNode][i]);
					currentPath.pop_back();
				}
		}
	}
			
}
