#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Race
{
    unsigned long long int time;
    unsigned long long int distance;
};

int calculate_ways_to_push_button(unsigned long long int raceDuration, unsigned long long int recordDistance)
{
    int ways = 0;

    for (int holdDuration = 1; holdDuration <= raceDuration; holdDuration++)
    {
        unsigned long long int durationLeft = raceDuration - holdDuration;
        unsigned long long int distanceCovered = durationLeft * holdDuration;
        if (distanceCovered > recordDistance)
        {
            ways++;
        }
    }

    return ways;
}

int part1(const std::vector<std::string> &data)
{
    std::vector<Race> raceData;
    int totalWays = 0;

    // init the data
    for (const auto &line : data)
    {
        std::stringstream stringStream(line);
        std::string startWord; // Temporary variable to ignore the first word
        unsigned long long int value;

        stringStream >> startWord;

        if (startWord == "Time:")
        {
            while (stringStream >> value)
            {
                Race currentRace = {value, 0};
                raceData.push_back(currentRace);
            }
        }
        else
        {

            int vectorIndex = 0;
            while (stringStream >> value)
            {
                raceData[vectorIndex].distance = value;
                vectorIndex++;
            }
        }
    }

    // calculate
    for (const Race &race : raceData)
    {
        int possibleWays = calculate_ways_to_push_button(race.time, race.distance);

        if (totalWays == 0)
        {
            totalWays += possibleWays;
        }
        else
        {
            totalWays *= possibleWays;
        }
    }

    return totalWays;
}

int part2(const std::vector<std::string> &data)
{
    std::vector<Race> raceData;
    int totalWays = 0;

    // init the data
    for (const auto &line : data)
    {
        std::stringstream stringStream(line);
        std::string startWord; // Temporary variable to ignore the first word
        int value;

        stringStream >> startWord;

        if (startWord == "Time:")
        {
            std::ostringstream concatenatedData;
            while (stringStream >> value)
            {
                concatenatedData << value;
            }
            std::string resultString = concatenatedData.str();
            unsigned long long int result = std::atof(resultString.c_str());

            Race currentRace = {result, 0};
            raceData.push_back(currentRace);
        }
        else if (startWord == "Distance:")
        {
            std::ostringstream concatenatedData;
            while (stringStream >> value)
            {
                concatenatedData << value;
            }

            std::string resultString = concatenatedData.str();
            unsigned long long int result = atof(resultString.c_str());
            raceData[0].distance = result;
        }
    }

    // calculate
    Race race = raceData[0];
    unsigned long long int ways = calculate_ways_to_push_button(race.time, race.distance);
    return ways;
}

int main()
{
    std::ifstream file1("01");
    if (!file1.is_open())
    {
        std::cerr << "Error opening file 01" << std::endl;
        return 1;
    }

    std::ifstream file2("02");
    if (!file2.is_open())
    {
        std::cerr << "Error opening file 02" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> data1;
    std::vector<std::string> data2;

    while (std::getline(file1, line))
    {
        char edge = line[line.size() - 1];
        if (edge == '\r' || edge == '\n')
        {
            line.pop_back();
        }
        data1.push_back(line);
    }

    while (std::getline(file2, line))
    {
        char edge = line[line.size() - 1];
        if (edge == '\r' || edge == '\n')
        {
            line.pop_back();
        }
        data2.push_back(line);
    }

    file1.close();
    file2.close();

    // Process the data for part 1 and part 2
    int part1Result = part1(data1);
    int part2Result = part2(data2);

    // Output the results
    std::cout << "Part 1: " << part1Result << std::endl;
    std::cout << "Part 2: " << part2Result << std::endl;

    return 0;
}
