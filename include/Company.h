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
    // double graphFord(int s, int t, std::vector<int> &path);
    int getDatasetMax();
    std::list<Node> maximizeJointAny(std::string s, std::string t, int &cap);
    void minimizeJointTrans(std::string s, std::string t, std::list<Node> &path1, std::list<Node> &path2, int &cap);
    void ek(std::string s, std::string t);
    int ekLimit(std::string s, std::string t, unsigned long size);
    void ekMaxPath(std::string s, std::string t);
    std::unordered_map<std::string, Node> getGraph();
};


#endif
