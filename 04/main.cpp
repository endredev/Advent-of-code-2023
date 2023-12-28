#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const int CARD_ID_PREFIX_LENGTH = 5;
const int CARD_NUMBER_LENGTH = 2;

std::vector<int> extract_numbers(const std::string& s) {
    std::vector<int> numbers;
    for (int i = 0; i < s.size(); i += 3) {
        if (s[i] == ' ') {
            numbers.push_back(std::stoi(s.substr(i + 1, CARD_NUMBER_LENGTH)));
        } else {
            numbers.push_back(std::stoi(s.substr(i, CARD_NUMBER_LENGTH)));
        }
    }
    return numbers;
}

int count_wins(const std::vector<int>& winning_numbers, const std::vector<int>& card_numbers) {
    return std::count_if(
        card_numbers.begin(),
        card_numbers.end(),
        [&winning_numbers](int card_number) {
            return std::find(winning_numbers.begin(), winning_numbers.end(), card_number) != winning_numbers.end();
        }
    );
}

int part1(std::istream& input) {
    std::string line;
    std::size_t total_points = 0;

    while (std::getline(input, line)) {
        std::size_t start = 0;
        std::size_t end = line.find(':');
        const int card_id = std::stoi(line.substr(CARD_ID_PREFIX_LENGTH, end - CARD_ID_PREFIX_LENGTH));
        start = end + 2;
        end = line.find('|', start);
        const auto winning_numbers = extract_numbers(line.substr(start, end - start));
        const auto card_numbers = extract_numbers(line.substr(end + 2, line.size() - end));
        int count = count_wins(winning_numbers, card_numbers);

        if (count > 0) {
            total_points += std::pow(2, count - 1);
        }
    }

    return total_points;
}

int part2_recursive(const std::vector<std::vector<int>>& scratchcards, int card_id) {
    int total_copies = 1; // Include the original card

    for (int i = card_id + 1; i < scratchcards.size(); ++i) {
        int count = count_wins(scratchcards[card_id], scratchcards[i]);
        if (count > 0) {
            total_copies += count * part2_recursive(scratchcards, i);
        }
    }

    return total_copies;
}

int part2(std::istream& input) {
    std::string line;
    std::vector<std::vector<int>> scratchcards;

    while (std::getline(input, line)) {
        scratchcards.push_back(extract_numbers(line));
    }

    int total_scratchcards = 0;

    for (std::size_t i = 0; i < scratchcards.size(); ++i) {
        total_scratchcards += part2_recursive(scratchcards, i);
    }

    return total_scratchcards;
}

int main(int argc, char* argv[]) {
    std::string input = "02";


    std::fstream file(input);

    if (!file.is_open()) {
        std::perror("Error opening file");
        return 1;
    }

    int result_part1 = part1(file);

    file.clear();
    file.seekg(0);

    int result_part2 = part2(file);

    std::cout << "Part 1: " << result_part1 << '\n';
    std::cout << "Part 2: " << result_part2 << '\n';

    return 0;
}