#include "TSPTabuSearch.h"
using namespace std::chrono;
struct BestNeighbour
{
    int x, y, value;
    BestNeighbour(int x, int y, int value) {
        this->x = x;
        this->y = y;
        this->value = value;
    }
};
TSPTabuSearch::TSPTabuSearch(int** arrayGraph, int cityNum, int second,int type)
{
	this->arrayGraph = arrayGraph;
	this->cityNum = cityNum;
	this->generateStartPath();
    this->time = second;
    switch (type)
    {
    case 0:
        findNeigbour = &TSPTabuSearch::findPathSwap;
        break;
    case 1:
        findNeigbour = &TSPTabuSearch::findPathInsert;
        break;
    case 2:
        findNeigbour = &TSPTabuSearch::findPathReverse;
        break;
    default:
        findNeigbour = &TSPTabuSearch::findPathSwap;
        break;
    }
    
    this->distance = calculateCost(path);
    printf("%d \n", distance);
    this->tabuList = new int *[cityNum];
    for (int i = 0; i < cityNum; i++) {
        tabuList[i] = new int[cityNum];
        for (int j = 0; j < cityNum; j++)
            tabuList[i][j] = 0;
    }
}

void TSPTabuSearch::restart(std::vector<int> *vector) {
    int x;
    int y;
    for (int i = 0; i < this->cityNum / 3; i++) {
        x = rand() % (this->cityNum - 1) + 1;
        y = rand() % (this->cityNum - 1) + 1;
        std::swap(vector->at(x), vector->at(y));
    }
}

void TSPTabuSearch::search() {
    std::vector<int> bestRoad = path;
    int currentDistance = calculateCost(bestRoad);
    BestNeighbour* bestneigbour;
    int restartCount = 0;
    float timex = 0;
    high_resolution_clock::time_point start= high_resolution_clock::now();
    while(duration_cast<seconds>(high_resolution_clock::now() - start).count() < this->time) {
        restartCount++;
        bestneigbour = NULL;
        for (int i = 0; i < cityNum; i++) {
            for (int j = i + 1; j < cityNum; j++) {
                if (tabuList[i][j] == 0) {
                    std::vector<int> newRoad = (this->*findNeigbour)(i, j, bestRoad);
                    int distanceDif = calculateCost(newRoad) - currentDistance;
                    if (bestneigbour == NULL)
                        bestneigbour = new BestNeighbour(i, j, distanceDif);
                    else
                        if(bestneigbour->value > distanceDif)
                            bestneigbour = new BestNeighbour(i, j, distanceDif);
                }
               
            }
        }
        std::swap(bestRoad[bestneigbour->x], bestRoad[bestneigbour->y]);
        currentDistance += bestneigbour->value;
        tabuList[bestneigbour->x][bestneigbour->y] = 10;
        untabu();
        if (currentDistance < this->distance) {
            path = bestRoad;
            this->distance = currentDistance;
            restartCount = 0;
            this->findTime = (double)duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 1000000;
        }
        if (restartCount == 300) {
            restartCount = 0;
            this->restart(&bestRoad);
            this->clearTabu();
            currentDistance = calculateCost(bestRoad);
        }
        
    }
    
}
void TSPTabuSearch::untabu() {
    for (int i = 0; i < cityNum; i++)
        for (int j = i + 1; j < cityNum; j++)
            if (tabuList[i][j] > 0)
                tabuList[i][j]--;
}

void TSPTabuSearch::clearTabu()
{
    for (int i = 0; i < cityNum; i++)
        for (int j = i; j < cityNum; j++)
            tabuList[i][j] = 0;
}

std::vector<int> TSPTabuSearch::findPathSwap(int x, int y,std::vector<int> currentPath)
{
    std::vector<int> newPath = currentPath;
    std::swap(newPath[x], newPath[y]);
    return newPath;
}

std::vector<int> TSPTabuSearch::findPathReverse(int x, int y, std::vector<int> currentPath)
{
    std::vector<int> newPath = currentPath;
    std::reverse(std::begin(newPath)+x, std::begin(newPath) + y);
    return newPath;
}

std::vector<int> TSPTabuSearch::findPathInsert(int x, int y, std::vector<int> currentPath)
{
    std::vector<int> newPath = currentPath;
    for (int i = x; x < y; x++) {
        std::swap(newPath[x], newPath[x + 1]);
    }
    return newPath;
}