#include <iostream>
#include <chrono>
#include "../include/Company.h"

Company::Company() {
    Graph();
    this->graph.populate();
}

void Company::changeDataset(std::string dataset) {
    graph.populate(dataset);
}

std::list<Node> Company::maximizeJointAny(std::string s, std::string t, int &cap) {
    return graph.maximizeJointAny(s, t, cap);

}

int Company::getDatasetMax() {
    return graph.getDatasetMax();
}

void Company::minimizeJointTrans(std::string s, std::string t, std::list<Node> &path1, std::list<Node> &path2, int &cap) {
    auto startTime = std::chrono::high_resolution_clock::now();
    graph.minimizeJointTrans(s, t, path1, path2, cap);
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    std::cout << "\nAlgorithm Duration: "<< duration.count() << " microseconds" << std::endl;
}

void Company::ek(std::string s, std::string t) {
    auto startTime = std::chrono::high_resolution_clock::now();
    graph.edmondsKarp(s, t);
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    std::cout << "\nAlgorithm Duration: "<< duration.count() << " microseconds" << std::endl;
}

int Company::ekLimit(std::string s, std::string t, unsigned long size) {
    return graph.edmondsKarpLimit(s, t, size);
}

void Company::ekMaxPath(std::string s, std::string t, bool b) {
    auto startTime = std::chrono::high_resolution_clock::now();
    graph.edmondsKarpMaxPath(s, t, b);
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    std::cout << "\nAlgorithm Duration: "<< duration.count() << " microseconds" << std::endl;
}