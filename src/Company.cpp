#include <iostream>
#include "../include/Company.h"

void Company::readDataset(std::string dataset) {
    std::fstream f{dataset};
    std::string nodes, edges;
    if (!f.is_open())
        return;

    std::string line;
    std::vector<std::string> parsedLine;
    getline(f, line);
    parsedLine = utils::file::split(line, ' ');
    nodes = parsedLine.at(0);
    edges = parsedLine.at(1);

    std::cout << nodes << " " << edges << std::endl;

    while (!f.eof()) {
        getline(f, line);
        parsedLine = utils::file::split(line, ' ');

        if (line == "") break;

        parsedLine = utils::file::split(line, ' ');
        for (int i{0}; i < parsedLine.size(); i++) {
            std::cout << parsedLine.at(i) << " ";
        }
        std::cout << "\n" << std::flush;
    }
}

Company::Company() {
    readDataset(NORMAL_DATASET_1);
}

void Company::changeDataset(std::string dataset) {
    readDataset(dataset);
}
