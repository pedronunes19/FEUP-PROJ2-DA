#include <algorithm>

#include <fstream>
#include <unistd.h>

#include "../include/utils.h"
#include "../include/constants.h"
#include "../include/graph.h"

// Add edge from source to destination with a certain weight
void Graph::addEdge(Node &src, Node &dest, const double &capacity,
                    const double &duration) {
    src.adj.push_back({dest.id, duration, capacity, false, 0});
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(const int &src, const int &dest,
                    const double &capacity, const double &duration) {
    addEdge(nodes[std::to_string(src)], nodes[std::to_string(dest)], capacity, duration);
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
        addEdge(std::stoi(parsedLine.at(0)), std::stoi(parsedLine.at(1)), std::stoul(parsedLine.at(2)), std::stoul(parsedLine.at(3)));
    }
}

void Graph::addNodes(unsigned long num_nodes) {
    for (int i{1}; i <= num_nodes; i++) {
        Node node;
        node.id = i;
        nodes.insert(std::pair<std::string, Node>(std::to_string(i), node));
    }
}

int Graph::bfsEK(const int &src, const int &dest) {
    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i){
        (*i).second.visited = false;
    }
    std::queue<int> q;
    q.push(src);
    nodes[std::to_string(src)].visited = true;
    nodes[std::to_string(src)].flow = INT32_MAX;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        nodes[std::to_string(u)].visited = true;
        for (auto &e : nodes[std::to_string(u)].adj) {
            int w = e.dest; // destination node of e (edge)

            if (!nodes[std::to_string(w)].visited && e.flow>0 && !e.residual) {
                nodes[std::to_string(w)].pred = std::to_string(u);
                nodes[std::to_string(w)].visited = true;
                int new_flow = std::min(nodes[std::to_string(u)].flow, e.flow);
                if (w == dest) {
                    return new_flow;
                }
                nodes[std::to_string(w)].flow = new_flow;
                e.flow = new_flow;
                q.push(w);
            }
        }
    }

    return 0;
}

int Graph::edmondsKarp(int src, int dest) {
    int flow = 0;
    int new_flow;

    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i){
        auto &adj = (*i).second.adj;
        for (auto j{adj.begin()}, end1{adj.end()}; j != end1; ++j){
            (*j).flow = (*j).capacity;

        }
    }

    while (new_flow = bfsEK(src, dest)) {
        flow += new_flow;
        int curr = dest;
        while (curr != src){
            int prev = stoi(nodes.at(std::to_string(curr)).pred);
            auto it_prev_to_curr = std::find_if(nodes.at(std::to_string(prev)).adj.begin(), nodes.at(std::to_string(prev)).adj.end(), [curr](const Edge & e){return e.dest==curr;});
            it_prev_to_curr->flow -= new_flow;
            auto it_curr_to_prev = std::find_if(nodes.at(std::to_string(curr)).adj.begin(), nodes.at(std::to_string(curr)).adj.end(), [prev](const Edge & e){return e.dest==prev;});
            if (it_curr_to_prev!=(nodes.at(std::to_string(prev)).adj.end())){
                nodes.at(std::to_string(prev)).adj.emplace_back(Edge{prev, it_prev_to_curr->duration, it_prev_to_curr->capacity, true, (int)it_prev_to_curr->capacity - it_prev_to_curr->flow});
            }
            it_curr_to_prev->flow += new_flow;
            curr = prev;
        }
    }
    std::cout << flow << "\n";
    return flow;
}

int Graph::getDatasetMax() {
    return dataset_max;
}
 

/*
NOTE: EXTREMELY DANGEROUS CODE ACTUALLY CHANGE THIS IF YOU INTEND TO EVER RUN IT
      THIS IS NOT A JOKE
      in regards on how to fix it... it most likely requires a maxHeap implementation
      the rest of the code should be working correctly
      good luck trying to fix this.


    THIS SHOULDN'T KILL YOUR PC NOW (I THINK)
    
    THIS IS WORKING :D, leaving this for posteriority's sake
*/
void Graph::dijkstra(const int src, const int dest) {
    MaxHeap<std::string, double> q(nodes.size(), "");

    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i) {
        i->second.cappd = 0;
        q.insert(i->first, -1);
        i->second.visited = false;
    }

    nodes[std::to_string(src)].cappd = INF;
    q.increaseKey(std::to_string(src), INF);
    nodes[std::to_string(src)].pred = std::to_string(src);

    while (q.getSize() > 0) {
        std::string uc = q.removeMax();
        Node &u = getNode(uc);
        u.visited = true;

        if (uc == std::to_string(dest))
            return;

        for (auto e : u.adj) {
            std::string vc = std::to_string(e.dest);
            Node &v = getNode(vc);

            if (!v.visited && (std::min(u.cappd, e.capacity) > v.cappd)) {
                v.cappd = std::min(u.cappd, e.capacity);
                v.pred = std::to_string(u.id);
                q.increaseKey(vc, v.cappd);
            }
        }
    }
}

bool Graph::bfs(const int src, const int dest) {
    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i)
        i->second.visited = false;

    std::queue<std::string> q; // queue of unvisited nodes
    q.push(std::to_string(src));
    nodes[std::to_string(src)].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front();
        q.pop();

        if (u == std::to_string(dest))
            return true;

        for (auto e : nodes[u].adj) {
            std::string w = std::to_string(e.dest);

            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].pred = u;
            }
        }
    }

    return false;
}

std::list<Node> Graph::maximizeJointAny(const int src, const int dest, int &cap) {
    dijkstra(src, dest);

    std::list<Node> path{};
    if (nodes[std::to_string(dest)].cappd == 0)
        return path;

    path.push_back(getNode(std::to_string(dest)));
    std::string v = std::to_string(dest);
    cap = nodes[v].cappd;
    while (v != std::to_string(src)) {
        v = nodes[v].pred;
        path.push_front(getNode(v));
    }

    return path;
}

void Graph::minimizeJointTrans(const int src, const int dest, std::list<Node> &path1, std::list<Node> &path2, int &cap) {
    dijkstra(src, dest);

    if (nodes[std::to_string(dest)].cappd != 0) {
        path1.push_back(getNode(std::to_string(dest)));
        std::string v = std::to_string(dest);
        cap = nodes[v].cappd;
        while (v != std::to_string(src)) {
            v = nodes[v].pred;
            path1.push_front(getNode(v));
        }
    }

    if (bfs(src, dest)) {
        path2.push_back(getNode(std::to_string(dest)));
        std::string v = std::to_string(dest);
        while (v != std::to_string(src)) {
            v = nodes[v].pred;
            path2.push_front(getNode(v));
        }
    }
}
