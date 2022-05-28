#include <algorithm>
#include <filesystem>
#include <fstream>

#include "../include/utils.h"
#include "../include/constants.h"
#include "../include/graph.h"

// Add edge from source to destination with a certain weight
void Graph::addEdge(Node &src, Node &dest, const double &capacity,
                    const double &distance) {
    src.adj.push_back({dest.id, distance, capacity});
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(const double &src, const double &dest,
                    const double &capacity, const double &distance) {
    addEdge(nodes[std::to_string(src)], nodes[std::to_string(dest)], capacity, distance);
}

void Graph::populate(std::string dataset) {
    if (!nodes.empty())
        nodes.clear();

    std::fstream f{dataset};
    unsigned long nodes_num;
    if (!f.is_open())
        return;

    std::string line;
    std::vector<std::string> parsedLine;
    getline(f, line);
    parsedLine = utils::file::split(line, ' ');
    nodes_num = std::stoul(parsedLine.at(0));
    dataset_max = nodes_num;
    addNodes(nodes_num);

    while (!f.eof()) {
        getline(f, line);

        if (line == "") break;

        parsedLine = utils::file::split(line, ' ');
        addEdge(std::stoul(parsedLine.at(0)), std::stoul(parsedLine.at(1)), std::stoul(parsedLine.at(2)), std::stoul(parsedLine.at(1)));
    }
}

void Graph::addNodes(unsigned long num_nodes) {
    for (double i{1}; i <= num_nodes; i++) {
        Node node;
        node.id = i;
        nodes.insert(std::pair<std::string, Node>(std::to_string(i), node));
    }
}
/*
bool Graph::bfsResidual(std::vector<Node> residual, const int &src, const int &dest, std::vector<int> &path) {
    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i)
       // i->visited = false;
    std::queue<int> q;
    q.push(src);
    residual.at(src).visited = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto e : residual.at(u).adj) {
            int w = e.dest;

            if (!residual.at(w).visited && e.capacity > 0) {
                path.push_back(w);

                if (u == dest) {
                    return true;
                }

                q.push(w);
                residual.at(w).visited = true;
            }
        }
    }

    std::cout << "hi" << std::endl;
    return false;
}

double Graph::fordFulk(int s, int t, std::vector<int> &path) {

    // std::vector<Node> residual = nodes;

    double mflow = 0;

    while (bfsResidual(residual, s, t, path)) {
        double pflow = INT_MAX;

        // Checking minimum flow
        for (int i = t; t != s; i = path.at(i)) {
            int j = path[i];
            for (auto e : residual.at(j).adj) {
                if (e.dest == i) {
                    pflow = std::min(pflow, e.capacity);
                }
            }
        }

        // Updating capacities
        for (int i = t; t != s; i = path.at(i)) {
            int j = path[i];
            for (auto e : residual.at(j).adj) {
                e.capacity -= pflow;
            }
        }

        mflow += pflow;
    }

    return mflow;
}

int Graph::getDatasetMax() {
    return dataset_max;
}
 */

/*
NOTE: EXTREMELY DANGEROUS CODE ACTUALLY CHANGE THIS IF YOU INTEND TO EVER RUN IT
      THIS IS NOT A JOKE
      in regards on how to fix it... it most likely requires a maxHeap implementation
      the rest of the code should be working correctly
      good luck trying to fix this.

void Graph::dijkstra(const int src, const int dest) {
    MinHeap<std::string, double> q(nodes.size(), "");

    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i) {
        i->second.dist = INF; // change this to -1
        q.insert(i->first, -1);
        i->second.visited = false;
    }

    nodes[std::to_string(src)].dist = 0; // change this to INF
    q.decreaseKey(std::to_string(src), 0);
    nodes[std::to_string(src)].pred = std::to_string(src);

    while (q.getSize() > 0) {
        std::string uc = q.removeMin();
        Node &u = getNode(uc);
        u.visited = true;

        if (uc == std::to_string(dest))
            return;

        for (auto e : u.adj) {
            std::string vc = std::to_string(e.dest);
            Node &v = getNode(vc);

            if (!v.visited && std::min(u.dist, e.capacity) > v.dist) {
                v.dist = std::min(u.dist, e.capacity);
                q.decreaseKey(vc, v.dist);
            }
        }
    }
}

std::list<Node> Graph::maximizeJointAny(const int src, const int dest) {
    dijkstra(src, dest);

    std::list<Node> path{};
    if (nodes[std::to_string(dest)].dist == INF)
        return path;

    path.push_back(getNode(std::to_string(dest)));
    std::string v = std::to_string(dest);
    while (v != std::to_string(src)) {
        v = nodes[v].pred;
        path.push_front(getNode(v));
    }
    return path;
}
*/