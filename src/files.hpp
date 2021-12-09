#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

// Function to build frequency table for text from file
auto get_freq_map(std::string filename) -> std::unordered_map<char, size_t>
{
    std::ifstream fin { filename };
    std::unordered_map<char, size_t> map;
    std::string buf;

    while (std::getline(fin, buf)) {
        for (auto c : buf)
            map[c]++;
    }

    return map;
}

// Function writes bytes from std::string to file 
void write_bytes(std::string filename, std::string bytes)
{
}