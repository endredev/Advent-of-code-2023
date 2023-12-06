#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Game
{
public:
    int id;
    std::vector<std::array<int, 3>> rounds;

    void parseGameString(const std::string &gameStr);
    std::array<int, 3> parseRound(const std::string &roundStr);
    int calculateScore() const;
    int calculateMinimalValues() const;
};

std::array<int, 3> Game::parseRound(const std::string &roundStr)
{
    size_t start = 0;
    std::size_t end = roundStr.find(',');
    std::array<int, 3> round{{0, 0, 0}};

    while (end != std::string::npos)
    {
        const std::string colourData = roundStr.substr(start, end - start);
        const auto i = colourData.find(' ');
        const auto colour = colourData.substr(i + 1, colourData.size() - i - 1);
        const auto n = std::stoi(colourData.substr(0, i));

        if (colour == "red")
        {
            round[0] = n;
        }
        else if (colour == "green")
        {
            round[1] = n;
        }
        else if (colour == "blue")
        {
            round[2] = n;
        }
        else
        {
            std::cout << "This should not happen" << __LINE__ << '\n';
            exit(0);
        }

        start = end + 2;
        end = roundStr.find(',', start);
    }

    const std::string colourData = roundStr.substr(start, roundStr.size() - start);
    const auto i = colourData.find(' ');
    const auto colour = colourData.substr(i + 1, colourData.size() - i - 1);
    const int n = std::stoi(colourData.substr(0, i));

    if (colour == "red")
    {
        round[0] = n;
    }
    else if (colour == "green")
    {
        round[1] = n;
    }
    else if (colour == "blue")
    {
        round[2] = n;
    }
    else
    {
        std::cout << "This should not happen" << __LINE__ << '\n';
        exit(0);
    }

    return round;
}

void Game::parseGameString(const std::string &gameStr)
{
    size_t start = 0;
    std::size_t end = gameStr.find(':');
    const int gameNumber = std::stoi(gameStr.substr(5, end - 5));

    start = end + 1;
    end = gameStr.find(';', start);

    id = gameNumber;

    while (end != std::string::npos)
    {
        const std::string roundData = gameStr.substr(start + 1, end - start - 1);
        rounds.push_back(parseRound(roundData));
        start = end + 1;
        end = gameStr.find(';', start);
    }

    const std::string roundData = gameStr.substr(start + 1, gameStr.size() - start - 1);
    rounds.push_back(parseRound(roundData));
}

int Game::calculateScore() const
{
    int count = 0;
    for (const auto round : rounds)
    {
        if (round[0] > 12 || round[1] > 13 || round[2] > 14)
        {
            return 0;
        }
    }

    return id;
}

int Game::calculateMinimalValues() const
{
    int count = 0;
    int minimalRed = 0;
    int minimalGreen = 0;
    int minimalBlue = 0;
    for (const auto round : rounds)
    {
        int roundRed = round[0];
        int roundGreen = round[1];
        int roundBlue = round[2];

        if (roundRed > minimalRed)
        {
            minimalRed = roundRed;
        }

        if (roundGreen > minimalGreen)
        {
            minimalGreen = roundGreen;
        }

        if (roundBlue > minimalBlue)
        {
            minimalBlue = roundBlue;
        }
    }

    return minimalRed * minimalGreen * minimalBlue;
}

void partOne()
{
    std::string input = "01";
    std::fstream file(input);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << input << '\n';
        return;
    }

    std::vector<Game> games;
    std::string line;
    while (std::getline(file, line))
    {
        Game currentGame;
        currentGame.parseGameString(line);
        games.push_back(currentGame);
    }

    int totalScore = 0;
    for (const auto game : games)
    {
        totalScore += game.calculateScore();
    }

    std::cout << "Part one: " << totalScore << '\n';
}

void partTwo()
{
    std::string input = "02";
    std::fstream file(input);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << input << '\n';
        return;
    }

    std::vector<Game> games;
    std::string line;
    while (std::getline(file, line))
    {
        Game currentGame;
        currentGame.parseGameString(line);
        games.push_back(currentGame);
    }

    int totalScore = 0;
    for (const auto game : games)
    {
        totalScore += game.calculateMinimalValues();
    }

    std::cout << "Part two: " << totalScore << '\n';
}

int main()
{
    partOne();
    partTwo();
    return 0;
}