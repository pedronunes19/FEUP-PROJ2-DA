#include <iostream>
#include "../include/Company.h"


Company::Company() {
    Graph();
    this->graph.populate();
}

void Company::changeDataset(std::string dataset) {
    graph.populate(dataset);
}

double Company::graphFord(int s, int t, std::vector<int> &path) {
    // return graph.fordFulk(s-1, t-1, path);
    return 0;
}

std::list<Node> Company::maximizeJointAny(int s, int t, int &cap) {
    return graph.maximizeJointAny(s, t, cap);
}

int Company::getDatasetMax() {
    return graph.getDatasetMax();
}

std::unordered_map<std::string, Node> Company::getGraph() {
    return graph.getNodes();
}

void Company::minimizeJointTrans(int s, int t, std::list<Node> &path1, std::list<Node> &path2, int &cap) {
    graph.minimizeJointTrans(s, t, path1, path2, cap);
}

void Company::ek(int s, int t) {
    graph.edmondsKarp(s, t);
}