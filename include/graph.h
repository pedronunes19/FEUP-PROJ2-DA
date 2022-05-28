#ifndef DA_PROJ_2_GRAPH_H
#define DA_PROJ_2_GRAPH_H

class Graph;
struct Edge;
struct Node;

#include "minHeap.h"

#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>
#include <unordered_map>

#define INF (std::numeric_limits<double>::max() / 2)

/**
 * @brief Represents an edge connecting two nodes.
 */
struct Edge {
    /**
     * @brief The destination node.
     */
    double dest;
    /**
     * @brief The distance between the two nodes.
     */
    double distance;
    /**
     * @brief The capacity between the two nodes.
     */
    double capacity;
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
    double id;
    /**
     * @brief The distance between this node and its predecessor.
     *
     * @note Set after running an algorithm.
     */
    double dist{};
    /**
     * @brief This node's predecessor.
     *
     * @note Set after running an algorithm.
     */
    std::string pred{};
};

/**
 * @brief A directed multigraph representing a public transit network.
 */
class Graph {
    /**
     * @brief This graph's nodes.
     *
     * The keys are each node's stop code and the values are the nodes
     * themselves.
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
    void addEdge(const double &src, const double &dest,
                 const double &capacity, const double &distance = 1.0);
    /**
     * @brief Adds a new edge between two nodes with the specified distance and
     *        code.
     *
     * @param src The source node.
     * @param dest The destination node.
     * @param capacity The capacity between the two nodes.
     * @param distance The distance between the nodes.
     */
    void addEdge(Node &src, Node &dest, const double &capacity,
                 const double &distance = 1.0);

    /**
     * @return This graph's nodes.
     */
    std::unordered_map<std::string, Node>  getNodes() { return nodes; };

    /**
     * @brief Get the node with the specified code.
     *
     * @param id The stop code.
     * @return The node.
     */
    Node &getNode(std::string id) { return nodes[id]; };

    int getDatasetMax();


    /**
     * @brief Populates this graph with info from files and by foot edges.
     *
     * @param dataset The dataset to be read and populate the dataset.
     */
    void populate(std::string dataset = NORMAL_DATASET_1);

    void addNodes(unsigned long nodes);

    /**
     * @brief Applies the bfs (breadth-first search) algorithm. [O(|V| + |E|)]
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     */
    void bfs(const int &src, const int &dest, std::vector<int> &path);

    /**
     * @brief Applies the bfs (breadth-first search) algorithm. [O(|V| + |E|)]
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     */
    bool bfsResidual(std::vector<Node> residual, const int &src, const int &dest, std::vector<int> &path);

    double fordFulk(int s, int t, std::vector<int> &path);

    /**
     * @brief Applies the regular dijkstra algorithm. [O(|E| log(|V|))]
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param f The filter to use in the creation of the path.
     */
    void dijkstra(const int src, const int dest);

    std::list<Node> maximizeJointAny(const int src, const int dest);
};

#endif
