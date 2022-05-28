#ifndef DA_PROJ_2_COMPANY_H
#define DA_PROJ_2_COMPANY_H

#include <string>
#include <fstream>

#include "utils.h"
#include "constants.h"
#include "graph.h"

class Company {
    Graph graph;
public:
    Company();
    void changeDataset(std::string dataset);
    double graphFord(int s, int t, std::vector<int> &path);
    int getDatasetMax();
    std::list<Node> maximizeJointAny(int s, int t);
};


#endif
