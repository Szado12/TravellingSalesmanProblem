#include "TSPMetaheuristicAlgorithm.h"

void TSPMetaheuristicAlgorithm::generateStartPath()
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

    int TSPMetaheuristicAlgorithm::calculateCost(std::vector<int> newPath)
    {
        int newCost = 0;
        for (int i = 1; i < newPath.size(); i++)
            newCost += arrayGraph[newPath[i - 1]][newPath[i]];
        newCost += arrayGraph[newPath.back()][newPath.front()];
        return newCost;
    }

    double TSPMetaheuristicAlgorithm::getFindTime()
    {
        return this->findTime;
    }
