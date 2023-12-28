#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int part1(const std::vector<std::string>& data)
{
    return 0; 
}

int part2(const std::vector<std::string>& data)
{
    return 0; 
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
    int part1_sum = part1(data1);
    int part2_gear_ratio_value = part2(data2);

    // Output the results
    std::cout << "Part 1: " << part1_sum << std::endl;
    std::cout << "Part 2: " << part2_gear_ratio_value << std::endl;

    return 0;
}