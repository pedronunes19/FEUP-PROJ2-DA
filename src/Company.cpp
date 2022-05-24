#include <iostream>
#include "../include/Company.h"

void Company::readDataset(std::string dataset) {
}

Company::Company() {
    Graph();
    this->graph.populate();
}

void Company::changeDataset(std::string dataset) {
    readDataset(dataset);
}
