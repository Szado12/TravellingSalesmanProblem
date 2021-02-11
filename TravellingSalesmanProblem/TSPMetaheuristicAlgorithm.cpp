#include "TSPMetaheuristicAlgorithm.h"

/// <summary>
/// Greedy algortihm for TSP to find good starting path
/// </summary>
void TSPMetaheuristicAlgorithm::GenerateStartPath()
{
    this->path.push_back(0);
    for (int i = 1; i < this->cityNum; i++) {
        int min = INT_MAX;
        int node = NULL;
        for (int j = 0; j < this->cityNum; j++) {
            if (std::find(this->path.begin(), this->path.end(), j) == this->path.end())
            {
                if (min > this->arrayGraph[this->path.back()][j])
                {

                    min = this->arrayGraph[this->path.back()][j];
                    node = j;
                }
            }

        }
        this->path.push_back(node);
    }
}
/// <summary>
/// Function returns cost of the road
/// </summary>
/// <param name="newPath"></param>
/// <returns></returns>
int TSPMetaheuristicAlgorithm::CalculateCost(std::vector<int> newPath)
{
    int newCost = 0;
    for (int i = 1; i < newPath.size(); i++)
        newCost += arrayGraph[newPath[i - 1]][newPath[i]];
    newCost += arrayGraph[newPath.back()][newPath.front()];
    return newCost;
}
/// <summary>
/// Function returns time, when best solution was found.
/// </summary>
/// <returns></returns>
double TSPMetaheuristicAlgorithm::GetFindTime()
{
    return this->findTime;
}
