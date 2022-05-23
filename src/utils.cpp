#include "../include/utils.h"

void utils::file::clearScreen() {std::cout << std::string(500, '\n') << std::endl;};

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

std::vector<std::string> utils::file::split(std::string str, char sep) {
    std::string temp;
    std::vector<std::string> final;

    for (auto i : str) {
        if (i == sep) {
            final.push_back(temp);
            temp = "";
        } else {
            temp += i;
        }
    }
    final.push_back(temp);

    return final;
}

void utils::file::waitForEnter(std::string prompt) {
    if (std::cin.good()) std::cout << prompt << std::endl;
    if (std::cin.peek() == '\n') std::cin.ignore(MAX_CHARS_IGNORE, '\n');
}

void utils::file::normalizeInput(std::string &input) {
    char last = 0;
    size_t i = 0;
    while (i < input.length()) {
        char &c = input.at(i);

        // Replace tabs with spaces
        if (c == '\t')
            c = ' ';

        // Delete character if it is a space at the begining, at the end or
        // after another space
        if (c == ' ' &&
            (last == ' ' || last == 0 || i == input.length() - 1 || i == 0)) {
            input.erase(i, 1);

            // If we're outside the string, go back one
            if (i == input.length())
                i--;
        } else {
            i++;
            last = c;
        }
    }
}