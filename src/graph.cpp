#include <algorithm>
#include <filesystem>
#include <fstream>

#include "../include/utils.h"
#include "../include/constants.h"
#include "../include/graph.h"

// Add edge from source to destination with a certain weight
void Graph::addEdge(Node &src, Node &dest, const double &capacity,
                    const double &distance) {
    src.adj.push_back({dest.id, distance, capacity});
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(const double &src, const double &dest,
                    const double &capacity, const double &distance) {
    addEdge(nodes[src], nodes[dest], capacity, distance);
}

void Graph::populate() {
    std::fstream f{NORMAL_DATASET_1};
    unsigned long nodes;
    if (!f.is_open())
        return;

    std::string line;
    std::vector<std::string> parsedLine;
    getline(f, line);
    parsedLine = utils::file::split(line, ' ');
    nodes = std::stoul(parsedLine.at(0));

    addNodes(nodes);

    while (!f.eof()) {
        getline(f, line);

        if (line == "") break;

        parsedLine = utils::file::split(line, ' ');
        addEdge(std::stoul(parsedLine.at(0)), std::stoul(parsedLine.at(1)), std::stoul(parsedLine.at(2)), std::stoul(parsedLine.at(1)));
    }
}

void Graph::addNodes(unsigned long nodes) {
    for (double i{0}; i < nodes; i++) {
        this->nodes.push_back({i});
    }
}
