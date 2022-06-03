#ifndef DA_PROJ_2_GRAPH_H
#define DA_PROJ_2_GRAPH_H

class Graph;
struct Edge;
struct Node;

#include "maxHeap.h"
#include "minHeap.h"

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
     * @brief The distance between the two nodes.
     */
    int duration;
    /**
     * @brief The capacity between the two nodes.
     */
    int capacity;
    /**
     * @brief The capacity between the two nodes.
     */
    bool residual;
    /**
     * @brief The capacity between the two nodes.
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
     * @brief The distance between this node and its predecessor.
     *
     * @note Set after running an algorithm.
     */
    int cappd{};
        /**
     * @brief The distance between this node and its predecessor.
     *
     * @note Set after running an algorithm.
     */
    int flow{};

    friend bool operator==(const Node& lhs, const Node& rhs){
        return lhs.id == rhs.id;
    };

    friend bool operator!=(const Node& lhs, const Node& rhs){
        return lhs.id != rhs.id;
    };
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

    int getDatasetMax() const;

    /**
     * @brief Populates this graph with info from files and by foot edges.
     *
     * @param dataset The dataset to be read and populate the dataset.
     */
    void populate(std::string dataset = NORMAL_DATASET_1);

    void addNodes(const int num_nodes);

    /**
     * @brief Applies the bfs (breadth-first search) algorithm. [O(|V| + |E|)]
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     */
    void bfs(const std::string &src, const std::string &dest, std::vector<int> &path);

    /**
     * @brief Applies the bfs (breadth-first search) algorithm. [O(|V| + |E|)]
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     */
    int bfsEK(const std::string &src, const std::string &dest);

    /* SHOULD PROBABLY REMOVE THIS */
    // double fordFulk(int s, int t, std::vector<int> &path);

    int edmondsKarp(const std::string src, const std::string dest);
    int edmondsKarpLimit(const std::string src, const std::string dest, const unsigned long size);
    int edmondsKarpMaxPath(const std::string src, const std::string dest);
    /**
     * @brief Applies the regular dijkstra algorithm. [O(|E| log(|V|))]
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param f The filter to use in the creation of the path.
     */
    void dijkstra(const std::string src, const std::string dest);

    /**
     * @brief Applies the regular dijkstra algorithm. [O(|E| log(|V|))]
     *
     * @param src The code of the source node.
     * @param dest The code of the destination node.
     * @param f The filter to use in the creation of the path.
     */
    void dijkstraTrans(const std::string src, const std::string dest);

    std::list<Node> maximizeJointAny(const std::string src, const std::string dest, int &cap);

    void minimizeJointTrans(const std::string src, const std::string dest, std::list<Node> &path1, std::list<Node> &path2, int &cap);

    bool bfs(const std::string src, const std::string dest);
};

#endif
