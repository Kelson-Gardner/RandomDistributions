//
//  Assignment2.cpp
//  Random
//
//  Created by Kelson on 9/22/24.
//
#include <iostream>
#include <vector>
#include <format>
#include <random>


class DistributionPair
{
  public:
    DistributionPair(std::uint32_t minValue, std::uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }

    std::uint32_t minValue;
    std::uint32_t maxValue;
    std::uint32_t count;
};

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins);
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins);
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins);
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize);

int main() {
    // insert code here...
    
    std::cout << "Hello, World!\n";
    std::uint32_t howMany = 100;
    float mean = 30.00;
    float stdev = 10.00;
    std::uint8_t numberBins = 5;
    std::uint8_t howOften = 10;
    generateNormalDistribution(howMany, mean, stdev, numberBins);
    auto uniform = generateUniformDistribution(howMany, 0, 24, numberBins);
    generatePoissonDistribution(howMany, howOften, numberBins);
    plotDistribution("--- Uniform ---", uniform, 80);
    return 0;
}

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize){
    std::cout << title << std::endl;
    for(DistributionPair pair : distribution){
        auto pairInfo = std::format("Range [{:<10}, {:<10}]", pair.minValue, pair.maxValue);
        std::cout << pairInfo;
        for(int i = 0; i < pair.count; i++){
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins){
    std::cout << "I am the generateUniformDistribution function\n";
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> dist(min, max);
    int range = (max + 1) / numberBins;
    int index = 0;
    std::vector<DistributionPair> pairs;
    for(int i = 0; i < numberBins; i++){
        DistributionPair pair(index, index + range - 1);
        pairs.push_back(pair);
        index += range;
    }
    
    for(int i = 0; i < howMany; i++){
        int randomNumber = dist(engine);
        int vectorIndex = randomNumber / range;
        pairs[vectorIndex].count += 1;
    }
    return pairs;
}

std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins){
    std::cout << "I am the generateNormalDistribution function\n";
    std::vector<DistributionPair> pair;
    return pair;
}

std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins){
    std::cout << "I am the generatePoissonDistribution function\n";
    std::vector<DistributionPair> pair;
    return pair;
}
