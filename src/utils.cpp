#include <fstream>

#include "../include/utils.h"

std::vector<std::string> utils::file::readFile(const std::string& filePath) {

    std::ifstream file(filePath);

    if (!file.is_open())
        return {}; // error

    file.ignore(INT32_MAX, '\n');

    std::vector<std::string> lines;

    std::string line;
    while(std::getline(file, line))
        lines.push_back(line);

    return lines;
}