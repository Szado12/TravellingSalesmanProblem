#include "TSPGeneticAlgorithm.h"
#include <algorithm>
#include <thread>
using namespace std::chrono;
/// <summary>
/// Constructor with parameteters 
/// </summary>
/// <param name="arrayGraph"></param>
/// <param name="cityNum"></param>
/// <param name="time"></param>
/// <param name="crossover"></param>
/// <param name="mutation"></param>
/// <param name="population"></param>
/// <param name="crossoverChance"></param>
/// <param name="mutationChance"></param>
TSPGeneticAlgorithm::TSPGeneticAlgorithm(int** arrayGraph, int cityNum, int time, int crossover, int mutation, int population,double crossoverChance, double mutationChance)
{
    this->arrayGraph = arrayGraph;
    this->cityNum = cityNum;
    this->time = time;
    this->mutationChance = mutationChance;
    this->crossoverChance = crossoverChance;
    this->population = std::vector<Descendant>();
    this->populationSize = population;
    printf("%d;",populationSize);
    if (crossover == 0)
    {
        crossoverFunc = &TSPGeneticAlgorithm::CrossoverPMX;
        printf("PMX;");
    }
    else
    {
        crossoverFunc = &TSPGeneticAlgorithm::CrossoverOX;
        printf("OX;");
    }
    if (mutation == 0)
    {
        mutationFunc = &TSPGeneticAlgorithm::OperatorTranspositionMutation;
        printf("Transposition;");
    }
    else
    {
        mutationFunc = &TSPGeneticAlgorithm::OperatorInversionMutation;
        printf("Inversion;");
    }

    this->distance = INT32_MAX;
    printf("%f;", crossoverChance);
    printf("%f;\n", mutationChance);
}

bool Compare(const Descendant& x, const Descendant& y)
{
    return x.cost < y.cost;
}

bool CompareToOrderPath(const GeneratedPath& x, const GeneratedPath& y)
{
    return x.orderNumber < y.orderNumber;
}
/// <summary>
/// Mutation operator Inverse
/// </summary>
/// <param name="desc"></param>
/// <returns></returns>
Descendant TSPGeneticAlgorithm::OperatorInversionMutation(Descendant desc)
{
    int x = rand() % (this->cityNum);
    int y = rand() % (this->cityNum);
    int min = std::min(x, y);
    int max = std::max(x, y);
    std::reverse(std::begin(desc.path) + min, std::begin(desc.path) + max);
    desc.cost = CalculateCost(desc.path);
    return desc;
}

/// <summary>
/// Mutation operator Transposition
/// </summary>
/// <param name="desc"></param>
/// <returns></returns>
Descendant TSPGeneticAlgorithm::OperatorTranspositionMutation(Descendant desc)
{
    int x = rand() % (this->cityNum);
    int y = rand() % (this->cityNum);
    std::swap(desc.path[x], desc.path[y]);
    desc.cost = CalculateCost(desc.path);
    return desc;
}
/// <summary>
/// Crossover Operator PMX
/// </summary>
/// <param name="desc"></param>
/// <param name="desc2"></param>
/// <returns></returns>
Descendant TSPGeneticAlgorithm::CrossoverPMX(Descendant desc, Descendant desc2)
{
    Descendant newChild;
    int* mapping = new int[this->cityNum];
    int startSegment, endSegment;
    for (int i = 0; i < cityNum; i++) {
        newChild.path.push_back(0);
        mapping[i] = -1;
    }
    
    do
    {
        startSegment = rand() % (cityNum-1)+1;
        endSegment = rand() % (cityNum-1)+1;
    } while (startSegment == endSegment);
    if (startSegment > endSegment)
    {
        int temp = startSegment;
        startSegment = endSegment;
        endSegment = temp;
    }

    for (int i = startSegment; i <= endSegment; i++)
    {
        newChild.path[i] = desc2.path[i];
        mapping[desc2.path[i]] = desc.path[i];
    }

    for (int i = 1; i < startSegment; i++)
    {
        if (mapping[desc.path[i]] == -1)
            newChild.path[i] = desc.path[i];
        else
        {
            int x = desc.path[i];
            while (mapping[x] != -1) x = mapping[x];
            newChild.path[i] = x;
        }

    }

    for (int i = endSegment + 1; i < cityNum; i++)
    {
        if(mapping[desc.path[i]] == -1)
            newChild.path[i] = desc.path[i];
        else
        {
            int x = desc.path[i];
            while (mapping[x] != -1) x = mapping[x];
            newChild.path[i] = x;
        }
    }
    newChild.cost = CalculateCost(newChild.path);
    return newChild;
}
/// <summary>
/// Crossover Operator OX
/// </summary>
/// <param name="desc"></param>
/// <param name="desc2"></param>
/// <returns></returns>
Descendant TSPGeneticAlgorithm::CrossoverOX(Descendant desc, Descendant desc2)
{
    int startSegment, endSegment;
    do
    {
        startSegment = rand() % (cityNum);
        endSegment = rand() % (cityNum);
    } 
    while (startSegment == endSegment);
    int tempMin = std::min(startSegment, endSegment);
    endSegment = std::max(startSegment, endSegment);
    startSegment = tempMin;
    std::vector<bool> visited;
    Descendant newChild;
    newChild.path = desc.path;
    for (int i = 0; i < this->cityNum; i++)
    {
            visited.push_back(false);
    }
    for (int i = startSegment; i < endSegment; i++)
    {
        visited[newChild.path[i]] = true;
    }
    int j = 0;
    for (int i = 0; i < this->cityNum; i++) 
    {
        if ((i+ endSegment)%cityNum < startSegment or (i + endSegment) % cityNum >= endSegment) {
            for (j; j < this->cityNum; j++) {
                if (!visited[desc2.path[(j + endSegment) % cityNum]]) {
                    visited[desc2.path[(j + endSegment) % cityNum]] = true;
                    break;
                }
            }
            newChild.path[(i + endSegment) % cityNum] = desc2.path[(j + endSegment) % cityNum];
        }
    }        
    newChild.cost = CalculateCost(newChild.path);
    return newChild;
}
/// <summary>
/// Adding to current population with mutation chance
/// </summary>
/// <param name="population"></param>
/// <param name="desc"></param>
void TSPGeneticAlgorithm::addToPopulation(std::vector<Descendant>* population, Descendant desc)
{
    double chance = (double(rand())) / RAND_MAX;
    if (chance < mutationChance)
        desc = (this->*mutationFunc)(desc);
    population->push_back(desc);
}
/// <summary>
/// Main function of genetic algorithm
/// </summary>
void TSPGeneticAlgorithm::GeneticAlgorithm()
{
    GeneratePopulation();
    CalculateFitness(&population);
    this->start = high_resolution_clock::now();
    while (duration_cast<seconds>(high_resolution_clock::now() - this->start).count() < this->time) {
        std::vector<Descendant> newPopulation = std::vector<Descendant>();
        for (int j = 0; j < populationSize; j++) {
            int selectedParentIndex = SelectOne();
            double chance = (double(rand())) / RAND_MAX;
            if (chance < crossoverChance) {
                int parentIndex2;
                do
                {
                    parentIndex2 = SelectOne();

                } while (selectedParentIndex == parentIndex2);
                addToPopulation(&newPopulation, (this->*crossoverFunc)(population[selectedParentIndex], population[parentIndex2]));
                addToPopulation(&newPopulation, (this->*crossoverFunc)(population[parentIndex2],population[selectedParentIndex]));
            }
            else{
                Descendant newDescendant = population[selectedParentIndex];
                addToPopulation(&newPopulation, newDescendant);
            }
        }
        for (int i = 0; i < 0.03*(float)populationSize; i++)
            newPopulation.push_back(population[i]);
        sort(newPopulation.begin(), newPopulation.end(), Compare);
        while (newPopulation.size() > populationSize)
            newPopulation.pop_back();
        this->population = newPopulation;
        CalculateFitness(&population);
        if (population[0].cost < this->distance) {
            this->path = population[0].path;
            this->distance = population[0].cost;
        }
    }
}
/// <summary>
/// Generating first population
/// </summary>
void TSPGeneticAlgorithm::GeneratePopulation()
{
    std::vector<int>randomPath = std::vector<int>();
    for (int i = 0; i < this->cityNum; i++)
        randomPath.push_back(i);
    int x = CalculateCost(randomPath);
    Descendant newDescendant;
    for (int i = 0; i < this->populationSize; i++) {
        newDescendant.path = randomPath;
        std::random_shuffle(newDescendant.path.begin(), newDescendant.path.end());
        newDescendant.cost = CalculateCost(newDescendant.path);
        population.push_back(newDescendant);
    }
    sort(this->population.begin(), this->population.end(), Compare);
}
/// <summary>
/// Calculating fitness of solutions
/// </summary>
/// <param name="population"></param>
void TSPGeneticAlgorithm::CalculateFitness(std::vector<Descendant>* population)
{
    double sum = 0;
    for (int i = 0; i < this->populationSize; i++) {
        population->at(i).fitness = 1.0 / population->at(i).cost*10;
        sum += population->at(i).fitness;
    }
    CalculateProbability(population, sum);
}

void TSPGeneticAlgorithm::CalculateProbability(std::vector<Descendant>* population, double sum)
{
    for (int i = 0; i < this->populationSize; i++) {
        population->at(i).probability = population->at(i).fitness / sum;
    }
}
/// <summary>
/// Function selects one Solution from population
/// </summary>
/// <returns></returns>
int TSPGeneticAlgorithm::SelectOne()
{
    double x = (double(rand())) / (RAND_MAX+1);
    int i = 0;
    for (; x >= 0; i++) {
        x -= population[i].probability;
    }
    if (i >= populationSize)
        return populationSize - 1;
    return(i-1);
}


