#include <algorithm>
#include "TSPSimulatedAnnealing.h"
#include <iostream>

using namespace std::chrono;
/// <summary>
/// Construtor with parameters arrayGraph-graph matrix, cityNum- number of cities, time - max time of searching, coolingValue
/// </summary>
/// <param name="arrayGraph"></param>
/// <param name="cityNum"></param>
/// <param name="time"></param>
/// <param name="coolingValue"></param>
/// <returns></returns>
TSPSimulatedAnnealing::TSPSimulatedAnnealing(int** arrayGraph, int cityNum, int time,double coolingValue)
{
    this->arrayGraph = arrayGraph;
    this->cityNum = cityNum;
    this->coolingValue = coolingValue;
    this->GenerateStartPath();
    this->time = time;
    this->distance = this->CalculateCost(this->path);
    this->temperatureMax = cityNum* cityNum;
}


/// <summary>
/// Function contains simulated annealing alorithm
/// </summary>
void TSPSimulatedAnnealing::Annealing()
{
    temperatureCurrent = temperatureMax;
    this->currentPath = this->path;
    int cost = this->distance;
    long long unsigned i = 0;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    while (duration_cast<seconds>(high_resolution_clock::now() - start).count() < this->time) {
        this->temperatureCurrent *= coolingValue;
        std::vector<int> newPath = FindPathSwap(currentPath);
        int newCost = this->CalculateCost(newPath);
        if (newCost < cost)
        {
            cost = newCost;
            currentPath = newPath;
            if (newCost < this->distance) {
                this->distance = cost;
                this->path = newPath;
                this->findTime = (double)duration_cast<microseconds>(high_resolution_clock::now() - start).count() /1000000;
            }
        }
        else
        {
            
            double x = (double(rand())) / RAND_MAX;
            double y = exp((cost - newCost) / temperatureCurrent);
            if (x < y) {
                cost = newCost;
                currentPath = newPath;
            }
            
        }
    }
}
/// <summary>
/// Function returns road created by swapping 2 random cities
/// </summary>
/// <param name="currentPath"></param>
/// <returns></returns>
std::vector<int> TSPSimulatedAnnealing::FindPathSwap(std::vector<int> currentPath)
{
    int x = rand() % (this->cityNum - 1) + 1;
    int y = rand() % (this->cityNum - 1) + 1;
    std::vector<int> newPath = currentPath;
    std::swap(newPath[x], newPath[y]);
    return newPath;
}


