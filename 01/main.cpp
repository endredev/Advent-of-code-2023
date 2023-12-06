#include <numeric>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int partOne()
{
    std::fstream file("01");
    std::string line;
    std::vector<int> calibration_values;

    while (std::getline(file, line))
    {
        std::vector<int> digits;

        /* Iterate the lines */
        for (int i = 0; i < line.size(); i++)
        {

            /* Check for digits */
            const auto character = line[i];
            if (character >= '0' && character <= '9')
            {
                digits.push_back(character - '0'); // to int
            }
        }
        calibration_values.push_back(digits[0] * 10 + digits.back());
    }

    const auto sum = std::accumulate(std::begin(calibration_values), std::end(calibration_values), 0);
    std::cout << "Part one sum: " << sum << '\n';
}

int partTwo()
{
    std::fstream file("02");
    std::string line;
    std::vector<std::string> numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::vector<int> calibration_values;

    while (std::getline(file, line))
    {
        std::vector<int> digits;
        for (int i = 0; i < line.size(); i++)
        {
            const char character = line[i];

            /* If it is a digit already*/
            if (character >= '0' && character <= '9')
            {
                digits.push_back(character - '0');
            }
            else
            {
                for (int j = 0; j < numbers.size(); j++)
                {
                    const std::string number = numbers[j];
                    if (line.size() >= i + number.size())
                    {
                        if (line.substr(i, number.size()) == number)
                        {
                            digits.push_back(j + 1);
                        }
                    }
                }
            }
        }

        calibration_values.push_back(digits[0] * 10 + digits.back());
    }
    const auto sum = std::accumulate(std::begin(calibration_values), std::end(calibration_values), 0);
    std::cout << "Part two sum: " << sum << '\n';
    return 0;
}

int main()
{
    partOne();
    partTwo();
    return 0;
}