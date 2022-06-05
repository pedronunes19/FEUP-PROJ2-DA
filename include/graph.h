#ifndef DA_PROJ_2_GRAPH_H
#define DA_PROJ_2_GRAPH_H

class Graph;
struct Edge;
struct Node;

#include "maxHeap.h"

#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define INF (std::numeric_limits<int>::max()/2)

/**
 * @brief Represents an edge connecting two nodes.
 */
struct Edge {
    /**
     * @brief The destination node.
     */
    int dest;
    /**
     * @brief The travel duration between the two nodes.
     */
    int duration;
    /**
     * @brief The capacity (number of people transported) between the two nodes.
     */
    int capacity;
    /**
     * @brief Indicates if the edge is part of a residual graph or not.
     */
    bool residual;
    /**
     * @brief The current flow being transported between the two nodes. Always lower than or equal to the capacity.
     */
    int flow{};
};

/**
 * @brief Represents a node in a Graph.
 */
struct Node {
    /**
     * @brief The outgoing edges connecting this node to others.
     */
    std::deque<Edge> adj{};
    /**
     * @brief Whether this node has been visited.
     *
     * @note Set after running an algorithm.
     */
    bool visited{false};
    /**
     * @brief The identifier of the node.
     */
    int id;
    /**
     * @brief The distance between this node and its predecessor.
     *
     * @note Set after running an algorithm.
     */
    int dur{};
    /**
     * @brief This node's predecessor.
     *
     * @note Set after running an algorithm.
     */
    std::string pred{};
    /**
     * @brief The capacity between this node and its predecessor.
     *
     * @note Set after running an algorithm.
     */
    int cappd{};
        /**
     * @brief The current flow between this node and its predecessor. Always lower than or equal to the capacity.
     *
     * @note Set after running an algorithm.
     */
    int flow{};

    /**
     * @brief Overload of the equality operator to compare two Nodes by their id value.
     * @param lhs The first Node.
     * @param rhs The second Node.
     * @return A boolean that indicates whether or not the two Nodes have an equal id.
     */
    friend bool operator==(const Node& lhs, const Node& rhs){
        return lhs.id == rhs.id;
    };
};

/**
 * @brief A directed graph representing a public transit network.
 */
class Graph {
    /**
     * @brief This graph's nodes.
     *
     * @note The keys are each node's stop code and the values are the nodes themselves.
     */
    std::unordered_map<std::string, Node> nodes;

    int dataset_max;

public:
    /**
     * @brief Creates an empty graph.
     */
    Graph(){};

    /**
     * @brief Adds a new edge between two nodes with the specified distance and
     *        code.
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param capacity The capacity between the two nodes.
     * @param distance The distance between the nodes.
     */
    void addEdge(const std::string &src, const std::string &dest,
                 const int &capacity, const int &distance = 1.0);
    /**
     * @brief Adds a new edge between two nodes with the specified distance and
     *        code.
     *
     * @param src The source node.
     * @param dest The destination node.
     * @param capacity The capacity between the two nodes.
     * @param distance The distance between the nodes.
     */
    void addEdge(Node &src, Node &dest, const int &capacity,
                 const int &distance = 1.0);

    /**
     * @brief Get the node with the specified code.
     *
     * @param id The stop code.
     * @return The node.
     */
    Node &getNode(std::string id) { return nodes[id]; };

    /**
     * @brief Get the maximum id value for a node in the current dataset.
     * @return The maximum id value in the dataset.
     */
    int getDatasetMax() const;

    /**
     * @brief Populates this graph with info from files and by foot edges.
     *
     * @param dataset The dataset to be read and populate the dataset.
     */
    void populate(std::string dataset = NORMAL_DATASET_1);

    /**
     * @brief Add the given amount of nodes to the graph.
     *
     * @param num_nodes The number of nodes.
     */
    void addNodes(const int num_nodes);

    /**
     * @brief Applies the bfs (breadth-first search) algorithm used inside the Edmonds-Karp algorithm, that also calculates the duration ond flow of the path..
     * @note Time Complexity: O(|V| + |E|); Space Complexity: O(|V|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @return The flow of the path.
     */
    int bfsEK(const std::string &src, const std::string &dest);

    /**
     * @brief Applies the Edmonds-Karp algorithm.
     * @note Time Complexity: O(|V| |E|^2); Space Complexity: O(|V| + |E|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @return The flow of the path.
     */
    int edmondsKarp(const std::string src, const std::string dest);

    /**
     * @brief Applies the Edmonds-Karp algorithm with a maximum flow limit.
     * @note Time Complexity: O(|V| |E|^2); Space Complexity: O(|V| + |E|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param size The maximum flow limit.
     * @return The flow of the path.
     */
    int edmondsKarpLimit(const std::string src, const std::string dest, const unsigned long size);

    /**
     * @brief Applies the Edmonds-Karp algorithm followed by a separation/regroup location and a possible maximum wait time calculation, the latter being dependant on a boolean value.
     * @note Time Complexity: O(|V|*|E|^2); Space Complexity: O(|V| + |E|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param waitTime A boolean that determines whether or not the maximum wait time is calculated.
     * @return The flow of the path.
     */
    int edmondsKarpMaxPath(const std::string src, const std::string dest, bool waitTime);

    /**
     * @brief Applies the regular dijkstra algorithm.
     * @note Time Complexity: O(|E| log(|V|)) Space Complexity: O(|V|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     */
    void dijkstra(const std::string src, const std::string dest);

    /**
     * @brief Applies the regular dijkstra algorithm, and builds a path with the highest capacity.
     * @note Time Complexity: O(|E| log(|V|)) Space Complexity: O(|V|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param cap A variable to store the capacity of the calculated path.
     * @return A list of nodes that represent the calculated path.
     */
    std::list<Node> maximizeJointAny(const std::string src, const std::string dest, int &cap);

    /**
     * @brief Applies the regular dijkstra algorithm, and builds two paths: One with the highest capacity and another one with the least amount of vehicle changes.
     * @note Time Complexity: O(|E| log(|V|)) Space Complexity: O(|V|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param path1 A variable to store the highest capacity path.
     * @param path2 A variable to store the path with the least amount of vehicle changes.
     * @param cap A variable to store the capacity of the first calculated path.
     */
    void minimizeJointTrans(const std::string src, const std::string dest, std::list<Node> &path1, std::list<Node> &path2, int &cap);

    /**
     * @brief Applies the bfs (breadth-first search) algorithm.
     * @note Time Complexity: O(|V| + |E|); Space Complexity: O(|V|)
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @return A boolean that represents the success/failure of the algorithm.
     */
    bool bfs(const std::string src, const std::string dest);
};

#endif
