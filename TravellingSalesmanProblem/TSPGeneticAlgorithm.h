#pragma once
#include "TSPMetaheuristicAlgorithm.h"
#include <thread>
struct Descendant
{
    std::vector<int> path;
    int cost;
    double fitness;
    double probability;
};
struct GeneratedPath
{
    int orderNumber;
    int city;
};

class TSPGeneticAlgorithm :
    public TSPMetaheuristicAlgorithm
{
private:
    std::vector<Descendant> population;
    int time;
    double mutationChance;
    double crossoverChance;
    int populationSize;
    std::chrono::high_resolution_clock::time_point start;
    typedef Descendant(TSPGeneticAlgorithm::* func)(Descendant desc, Descendant desc2);
    TSPGeneticAlgorithm::func crossoverFunc;
    typedef Descendant(TSPGeneticAlgorithm::* func2)(Descendant);
    TSPGeneticAlgorithm::func2 mutationFunc;

public:
    TSPGeneticAlgorithm(int** arrayGraph, int cityNum, int time, int crossover, int mutation,int population, double crossoverChance, double mutationChance);
    Descendant OperatorInversionMutation(Descendant desc);
    Descendant OperatorTranspositionMutation(Descendant desc);
    Descendant CrossoverPMX(Descendant desc, Descendant desc2);
    Descendant CrossoverOX(Descendant desc, Descendant desc2);
    void addToPopulation(std::vector<Descendant>* population, Descendant desc);
    void GeneticAlgorithm();
    void GeneratePopulation();
    void CalculateFitness(std::vector<Descendant>* population);
    void CalculateProbability(std::vector<Descendant>* population, double sum);
    int SelectOne();
};

