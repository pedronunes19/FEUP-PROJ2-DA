#ifndef DA_PROJ_2_COMPANY_H
#define DA_PROJ_2_COMPANY_H

#include <string>
#include <fstream>

#include "utils.h"
#include "constants.h"
#include "graph.h"

class Company {
    Graph graph;
    static void readDataset(std::string dataset);
public:
    Company();
    void changeDataset(std::string dataset);
};


#endif
