#include <algorithm>
#include "TSPSimulatedAnnealing.h"

using namespace std::chrono;
TSPSimulatedAnnealing::TSPSimulatedAnnealing(int** arrayGraph, int cityNum, int time,double coolingValue)
{
    this->arrayGraph = arrayGraph;
    this->cityNum = cityNum;
    
    this->coolingValue = coolingValue;
    this->generateStartPath();
    this->time = time;
    this->distance = this->calculateCost(this->path);
    this->temperatureMax = 50;
}



void TSPSimulatedAnnealing::Annealing()
{
    temperatureCurrent = temperatureMax;
    this->currentPath = this->path;
    int cost = this->distance;
    long long unsigned i = 0;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    while (duration_cast<seconds>(high_resolution_clock::now() - start).count() < this->time) {
        this->temperatureCurrent *= coolingValue;
        std::vector<int> newPath = findPathSwap(currentPath);
        int newCost = this->calculateCost(newPath);

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
            if (x < exp((cost - newCost) / temperatureCurrent)) {
                cost = newCost;
                currentPath = newPath;
            }
        }
    }
}

std::vector<int> TSPSimulatedAnnealing::findPathSwap(std::vector<int> currentPath)
{
    int x = rand() % (this->cityNum - 1) + 1;
    int y = rand() % (this->cityNum - 1) + 1;
    std::vector<int> newPath = currentPath;
    std::swap(newPath[x], newPath[y]);
    return newPath;
}

double TSPSimulatedAnnealing::calculateInitalTemp(std::vector<int> vector)
{
    double temp = 0;
    for (int i = 0; i < cityNum; i++) {
        for (int j = i + 1; j < cityNum; j++) {
            std::vector<int> newRoad = vector;
            std::swap(newRoad[i], newRoad[j]);
            int distanceDif = calculateCost(newRoad);
            if (temp < distanceDif)
                temp = distanceDif;
        }
    }
    return temp;
}


