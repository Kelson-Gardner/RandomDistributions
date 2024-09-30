//
//  distributions.cpp
//  Random
//
//  Created by Kelson on 9/28/24.
//

#include <format>
#include <iostream>
#include <random>
#include <vector>
#include "distributions.hpp"

void plotDistribution(std::string title,
                      const std::vector<DistributionPair>& distribution,
                      const std::uint8_t maxPlotLineSize)
{
    std::cout << title << std::endl;
    std::uint32_t max = 0;
    for (DistributionPair pair : distribution)
    {
        if (pair.count > max)
        {
            max = pair.count;
        }
    }
    for (DistributionPair pair : distribution)
    {
        auto pairInfo = std::format("Range [{:>3},{:>3}] : ", pair.minValue,
                                    pair.maxValue);
        std::cout << pairInfo;
        int range = static_cast<int>(
            (static_cast<float>(pair.count) / static_cast<float>(max)) *
            maxPlotLineSize);
        for (int i = 0; i < range; i++)
        {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

std::vector<DistributionPair>
generateUniformDistribution(std::uint32_t howMany, std::uint32_t min,
                            std::uint32_t max, std::uint8_t numberBins)
{
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<std::uint32_t> dist(min, max);
    std::uint32_t range =
        static_cast<std::uint32_t>((max + 1 - min) / numberBins);
    std::uint32_t index = min;
    std::vector<DistributionPair> pairs;
    for (int i = 0; i < static_cast<int>(numberBins); i++)
    {
        DistributionPair pair(index, index + range - 1);
        pairs.push_back(pair);
        index += range;
    }

    for (std::uint32_t i = 0; i < howMany; i++)
    {
        std::uint32_t randomNumber = static_cast<std::uint32_t>(dist(engine));
        if (randomNumber < min)
        {
            pairs[0].count += 1;
        }
        else if (randomNumber > max)
        {
            pairs[pairs.size() - 1].count += 1;
        }
        else
        {
            std::size_t vectorIndex = static_cast<std::size_t>(
                (randomNumber - static_cast<int>(min)) / range);
            pairs[vectorIndex].count += 1;
        }
    }
    return pairs;
}

std::vector<DistributionPair>
generateNormalDistribution(std::uint32_t howMany, float mean, float stdev,
                           std::uint8_t numberBins)
{
    std::random_device rd;
    std::default_random_engine engine{rd()};
    float min = mean - 4 * stdev;
    float max = mean + 4 * stdev - 1;
    std::normal_distribution<double> dist(mean, stdev);
    std::uint32_t range =
        static_cast<std::uint32_t>((max + 1 - min) / numberBins);
    std::uint32_t index = static_cast<std::uint32_t>(min);
    std::vector<DistributionPair> pairs;

    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        DistributionPair pair(index, index + range - 1);
        pairs.push_back(pair);
        index += range;
    }

    for (std::uint32_t i = 0; i < howMany; i++)
    {
        int randomNumber = static_cast<int>(dist(engine));
        if (randomNumber < static_cast<int>(min))
        {
            pairs[0].count += 1;
        }
        else if (randomNumber > static_cast<int>(max))
        {
            pairs[pairs.size() - 1].count += 1;
        }
        else
        {
            std::size_t vectorIndex = static_cast<std::size_t>(
                (randomNumber - static_cast<int>(min)) / range);
            pairs[vectorIndex].count += 1;
        }
    }
    return pairs;
}

std::vector<DistributionPair>
generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften,
                            std::uint8_t numberBins)
{
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::poisson_distribution<int> dist(howOften);
    std::vector<DistributionPair> pairs;
    std::uint32_t index = 0;
    std::uint32_t range = (howOften * 3) / numberBins;
    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        DistributionPair pair(index, index + range - 1);
        pairs.push_back(pair);
        index += range;

    }

    for (std::uint32_t i = 0; i < howMany; i++)
    {
        int randomNumber = dist(engine);
        if (randomNumber < 0)
        {
            pairs[0].count += 1;
        }
        else if (randomNumber > howOften * 3 - 1)
        {
            pairs[pairs.size() - 1].count += 1;
        }
        else
        {
            std::size_t vectorIndex =
                static_cast<std::size_t>(randomNumber / range);
            pairs[vectorIndex].count += 1;
        }
    }

    return pairs;
}
