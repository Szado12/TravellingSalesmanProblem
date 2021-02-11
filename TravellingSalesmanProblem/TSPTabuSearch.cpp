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
/// <summary>
/// Construtor with parameters arrayGraph-graph matrix, cityNum- number of cities, time - max time of searching, type type of neighbour
/// </summary>
/// <param name="arrayGraph"></param>
/// <param name="cityNum"></param>
/// <param name="second"></param>
/// <param name="type"></param>
/// <returns></returns>
TSPTabuSearch::TSPTabuSearch(int** arrayGraph, int cityNum, int time,int type)
{
	this->arrayGraph = arrayGraph;
	this->cityNum = cityNum;
	this->GenerateStartPath();
    this->time = time;
    switch (type)
    {
    case 0:
        findNeigbour = &TSPTabuSearch::FindPathSwap;
        break;
    case 1:
        findNeigbour = &TSPTabuSearch::FindPathReverse;
        break;
    case 2:
        findNeigbour = &TSPTabuSearch::FindPathInsert;
        break;
    default:
        findNeigbour = &TSPTabuSearch::FindPathSwap;
        break;
    }
    
    this->distance = CalculateCost(path);
    this->tabuList = new int *[cityNum];
    for (int i = 0; i < cityNum; i++) {
        tabuList[i] = new int[cityNum];
        for (int j = 0; j < cityNum; j++)
            tabuList[i][j] = 0;
    }
}
/// <summary>
/// Function generate new road, to escape the local minimum
/// </summary>
/// <param name="vector"></param>
void TSPTabuSearch::Restart() {
    int x;
    int y;
    for (int i = 0; i < this->cityNum / 3; i++) {
        x = rand() % (this->cityNum - 1) + 1;
        y = rand() % (this->cityNum - 1) + 1;
        std::swap(this->currentPath.at(x), this->currentPath.at(y));
    }
}
/// <summary>
/// Main funcion contains tabu search algorithm
/// </summary>
void TSPTabuSearch::TabuSearch() {
    this->currentPath = path;
    int currentDistance = CalculateCost(this->currentPath);
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
                    std::vector<int> newRoad = (this->*findNeigbour)(i, j, this->currentPath);
                    int distanceDif = CalculateCost(newRoad) - currentDistance;
                    if (bestneigbour == NULL)
                        bestneigbour = new BestNeighbour(i, j, distanceDif);
                    else
                        if (bestneigbour->value > distanceDif)
                            bestneigbour = new BestNeighbour(i, j, distanceDif);

                }
            }
        }
        std::swap(this->currentPath[bestneigbour->x], this->currentPath[bestneigbour->y]);
        currentDistance += bestneigbour->value;
        tabuList[bestneigbour->x][bestneigbour->y] = sqrt(cityNum);
        Untabu();
        if (currentDistance < this->distance) {
            path = this->currentPath;
            this->distance = currentDistance;
            restartCount = 0;
            this->findTime = (double)duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 1000000;
        }
        if (restartCount == 300) {
            restartCount = 0;
            this->Restart();
            this->ClearTabu();
            currentDistance = CalculateCost(this->currentPath);
        }
        
    }
    
}
/// <summary>
/// Function decrements number of iteration for moves in tabu list
/// </summary>
void TSPTabuSearch::Untabu() {
    for (int i = 0; i < cityNum; i++)
        for (int j = i + 1; j < cityNum; j++)
            if (tabuList[i][j] > 0)
                tabuList[i][j]--;
}
/// <summary>
/// Function clears tabu list
/// </summary>
void TSPTabuSearch::ClearTabu()
{
    for (int i = 0; i < cityNum; i++)
        for (int j = i; j < cityNum; j++)
            tabuList[i][j] = 0;
}
/// <summary>
/// Function finds new road by swapping 2 cities
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="currentPath"></param>
/// <returns></returns>
std::vector<int> TSPTabuSearch::FindPathSwap(int x, int y,std::vector<int> currentPath)
{
    std::vector<int> newPath = currentPath;
    std::swap(newPath[x], newPath[y]);
    return newPath;
}
/// <summary>
/// Function finds new road by reversing cities
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="currentPath"></param>
/// <returns></returns>
std::vector<int> TSPTabuSearch::FindPathReverse(int x, int y, std::vector<int> currentPath)
{
    std::vector<int> newPath = currentPath;
    std::reverse(std::begin(newPath)+x, std::begin(newPath) + y);
    return newPath;
}
/// <summary>
/// Function finds new road by swapping inserting city x in y place
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="currentPath"></param>
/// <returns></returns>
std::vector<int> TSPTabuSearch::FindPathInsert(int x, int y, std::vector<int> currentPath)
{
    std::vector<int> newPath = currentPath;
    for (int i = x; i < y; i++) {
        std::swap(newPath[i], newPath[i + 1]);
    }
    return newPath;
}