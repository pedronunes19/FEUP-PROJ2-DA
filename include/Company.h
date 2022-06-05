#ifndef DA_PROJ_2_COMPANY_H
#define DA_PROJ_2_COMPANY_H

#include <string>
#include <fstream>

#include "utils.h"
#include "constants.h"
#include "graph.h"

/**
 * @brief Represents a fictional company with a network (graph) of vehicles that travel from/to specific locations (nodes).
 */
class Company {
    /*
     * @brief The company's graph.
     */
    Graph graph;
public:
    /**
     * @brief Creates a company with an associated graph, which gets populated with the dataset info.
     */
    Company();

    /**
     * @brief Calls the function that populates the graph with the specified dataset.
     *
     * @param dataset The dataset used to populate the graph.
     */
    void changeDataset(std::string dataset);

    /**
     * @brief Calls the function that gets the amount of nodes in the graph.
     *
     * @return The number of nodes in the graph.
     */
    int getDatasetMax();

    /**
     * @brief Calls the function that applies the regular dijkstra algorithm, and builds a path with the highest capacity.
     *
     * @param s The code of the source node.
     * @param t The code of the destination node.
     * @param cap A variable to store the capacity of the calculated path.
     * @return A list of nodes that represent the calculated path.
     */
    std::list<Node> maximizeJointAny(std::string s, std::string t, int &cap);

    /**
     * @brief Calls the function that applies the regular dijkstra algorithm, and builds two paths: One with the highest capacity and another one with the least amount of vehicle changes.
     *
     * @param s The code of the source node.
     * @param t The code of the destination node.
     * @param path1 A variable to store the highest capacity path.
     * @param path2 A variable to store the path with the least amount of vehicle changes.
     * @param cap A variable to store the capacity of the first calculated path.
     */
    void minimizeJointTrans(std::string s, std::string t, std::list<Node> &path1, std::list<Node> &path2, int &cap);

    /**
     * @brief Calls the function that applies the Edmonds-Karp algorithm.
     *
     * @param s The code of the source node.
     * @param t The code of the destination node.
     */
    void ek(std::string s, std::string t);

    /**
     * @brief Calls the function that applies the Edmonds-Karp algorithm with a maximum flow limit.
     *
     * @param s The code of the source node.
     * @param t The code of the destination node.
     * @param size The maximum flow limit.
     * @return The flow of the path.
     */
    int ekLimit(std::string s, std::string t, unsigned long size);

    /**
     * @brief Calls the function that applies the Edmonds-Karp algorithm followed by a separation/regroup location and a possible maximum wait time calculation, the latter being dependant on a boolean value.
     *
     * @param s The code of the source node.
     * @param t The code of the destination node.
     * @param b A boolean that determines whether or not the maximum wait time is calculated.
     */
    void ekMaxPath(std::string s, std::string t, bool b);
};


#endif
