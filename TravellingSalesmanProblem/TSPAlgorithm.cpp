#include "TSPAlgorithm.h"
/// <summary>
/// Returns path fo solution as vector
/// </summary>
/// <returns></returns>
std::vector<int> TSPAlgorithm::GetPath()
{
    return this->path;
}
/// <summary>
/// Return distance of road as int
/// </summary>
/// <returns></returns>
int TSPAlgorithm::GetDistance()
{
    return this->distance;
}
