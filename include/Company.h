#ifndef DA_PROJ_1_COMPANY_H
#define DA_PROJ_1_COMPANY_H

#include <string>
#include <fstream>

#include "utils.h"
#include "constants.h"

class Company {
    // TODO: graph
    static void readDataset(std::string dataset);
public:
    Company();
    void changeDataset(std::string dataset);
};


#endif //DA_PROJ_1_COMPANY_H
