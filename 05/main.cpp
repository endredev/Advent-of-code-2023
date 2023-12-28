#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Mapping
{
    long long destination_start;
    long long source_start;
    long long range;

    bool in_destination_range(const long long n) const
    {
        return n >= destination_start && n <= destination_start + range;
    }

    bool in_source_range(const long long n) const
    {
        return n >= source_start && n <= source_start + range;
    }

    long long get_mapping(const long long n) const
    {
        return destination_start + (n - source_start);
    }
};

struct Map
{
    std::string map_from;
    std::string map_to;
    std::vector<Mapping> mappings;
};

std::vector<long long> extract(const std::string &s)
{
    std::vector<long long> numbers;

    if (s.empty())
    {
        return numbers;
    }

    long long start = 0;
    long long end = s.find(' ');

    while (end != std::string::npos)
    {
        numbers.push_back(std::stoll(s.substr(start, end - start)));
        start = end + 1;
        end = s.find(' ', start);
    }

    numbers.push_back(std::stoll(s.substr(start, s.size() - start)));
    return numbers;
}

std::vector<std::pair<long long, long long>> extract_ranges(const std::string &s)
{
    std::vector<std::pair<long long, long long>> ranges;

    if (s.empty())
    {
        return ranges;
    }

    long long start = 0;
    long long end = s.find(' ');

    while (end != std::string::npos)
    {
        long long seed_start = std::stoll(s.substr(start, end - start));
        start = end + 1;
        end = s.find(' ', start);

        long long seed_length = std::stoll(s.substr(start, end - start));
        ranges.emplace_back(seed_start, seed_length);

        start = end + 1;
        end = s.find(' ', start);
    }

    return ranges;
}

long long get_location(long long value, const std::vector<Map> &maps, const std::string &map_from)
{
    if (map_from == "location")
    {
        return value;
    }
    const auto map = *std::find_if(
        std::begin(maps),
        std::end(maps),
        [&map_from](const auto &map)
        {
            return map.map_from == map_from;
        });
    for (const auto &mapping : map.mappings)
    {
        if (mapping.in_source_range(value))
        {
            return get_location(mapping.get_mapping(value), maps, map.map_to);
        }
    }
    return get_location(value, maps, map.map_to);
}

int part1(std::istream &input)
{
    std::string line;
    std::vector<Map> maps;
    if (std::getline(input, line))
    {
        std::vector<long long> seeds;
        if (!line.empty())
        {
            seeds = extract(line.substr(7, line.size() - 7));
        }

        while (std::getline(input, line))
        {
            if (line.empty())
            {
                std::getline(input, line);
                Map map;
                long long start = 0;
                long long end = line.find('-');
                map.map_from = line.substr(start, end - start);
                start = end + 4;
                end = line.find(' ', start);
                map.map_to = line.substr(start, end - start);
                maps.push_back(map);
                std::getline(input, line);
            }

            const auto numbers = extract(line);
            Mapping mapping;
            mapping.destination_start = numbers[0];
            mapping.source_start = numbers[1];
            mapping.range = numbers[2];

            maps.back().mappings.push_back(mapping);
        }

        std::vector<long long> locations;
        for (const auto &seed : seeds)
        {
            locations.push_back(get_location(seed, maps, "seed"));
        }

        int result = *std::min_element(std::begin(locations), std::end(locations));
        std::cout << result << '\n';

        return result;
    }
    return -1; // Return an error code if unable to read the first line
}

int part2(std::istream &input)
{
    std::string line;
    std::vector<Map> maps;
    if (std::getline(input, line))
    {
        std::vector<std::pair<long long, long long>> seed_ranges;
        if (!line.empty())
        {
            seed_ranges = extract_ranges(line.substr(7, line.size() - 7));
        }

        std::vector<long long> all_seeds;
        for (const auto &range : seed_ranges)
        {
            for (long long i = range.first; i <= range.second; ++i)
            {
                all_seeds.push_back(i);
            }
        }

        while (std::getline(input, line))
        {
            if (line.empty())
            {
                std::getline(input, line);
                Map map;
                long long start = 0;
                long long end = line.find('-');
                map.map_from = line.substr(start, end - start);
                start = end + 4;
                end = line.find(' ', start);
                map.map_to = line.substr(start, end - start);
                maps.push_back(map);
                std::getline(input, line);
            }

            const auto numbers = extract(line);
            Mapping mapping;
            mapping.destination_start = numbers[0];
            mapping.source_start = numbers[1];
            mapping.range = numbers[2];

            maps.back().mappings.push_back(mapping);
        }

        long long result = get_location(*std::min_element(std::begin(all_seeds), std::end(all_seeds)), maps, "seed");

        return result;
    }
    return -1; // Return an error code if unable to read the first line
}

int main()
{
    std::string input = "01";
    std::fstream file(input);

    int result_part1 = part1(file);
    int result_part2 = part2(file);

    std::cout << "Part 1 Result: " << result_part1 << '\n';
    std::cout << "Part 2 Result: " << result_part2 << '\n';

    return 0;
}
