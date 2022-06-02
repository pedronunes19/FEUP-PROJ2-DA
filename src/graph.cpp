#include <algorithm>

#include <fstream>
#include <unistd.h>

#include "../include/utils.h"
#include "../include/constants.h"
#include "../include/graph.h"

int Graph::getDatasetMax() const {
    return dataset_max;
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(Node &src, Node &dest, const int &capacity,
                    const int &duration) {
    src.adj.push_back({dest.id, duration, capacity, false, 0});
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(const std::string &src, const std::string &dest,
                    const int &capacity, const int &duration) {
    addEdge(nodes[src], nodes[dest], capacity, duration);
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
    nodes_num = std::stoi(parsedLine.at(0));
    dataset_max = nodes_num;
    addNodes(nodes_num);

    while (!f.eof()) {
        getline(f, line);

        if (line == "") break;

        parsedLine = utils::file::split(line, ' ');
        addEdge(parsedLine.at(0), parsedLine.at(1), std::stoi(parsedLine.at(2)), std::stoi(parsedLine.at(3)));
    }
}

void Graph::addNodes(const int num_nodes) {
    for (int i{1}; i <= num_nodes; i++) {
        Node node;
        node.id = i;
        nodes.insert(std::pair<std::string, Node>(std::to_string(i), node));
    }
}

int Graph::bfsEK(const std::string &src, const std::string &dest) {
    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i){
        (*i).second.visited = false;
    }

    std::queue<std::string> q;
    q.push(src);
    nodes[src].visited = true;
    nodes[src].flow = INT32_MAX;
    while (!q.empty()) {
        std::string u = q.front();
        q.pop();
        nodes[u].visited = true;
        for (auto &e : nodes[u].adj) {
            std::string w = std::to_string(e.dest); // destination node of e (edge)

            if (!nodes[w].visited && e.flow>0) {
                nodes[w].pred = u;
                nodes[w].visited = true;
                int new_flow = std::min(nodes[u].flow, e.flow);
                if (w == dest) {
                    return new_flow;
                }
                nodes[w].flow = new_flow;
                e.flow = new_flow;
                q.push(w);
            }
        }
    }

    return 0;
}

int Graph::edmondsKarp(const std::string src, const std::string dest) {
    int flow = 0;
    int new_flow;

    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i){
        auto &adj = (*i).second.adj;
        for (auto j{adj.begin()}, end1{adj.end()}; j != end1; ++j){
            if (!(*j).residual) (*j).flow = (*j).capacity;
            else (*j).flow = 0;
        }
    }

    new_flow = bfsEK(src, dest);
    while (new_flow) {
        flow += new_flow;
        std::string curr = dest;
        while (curr != src){
            std::string prev = nodes.at(curr).pred;
            auto it_prev_to_curr = std::find_if(nodes.at(prev).adj.begin(), nodes.at(prev).adj.end(), [curr](const Edge & e){return e.dest==stoi(curr);});
            it_prev_to_curr->flow -= new_flow;
            auto it_curr_to_prev = std::find_if(nodes.at(curr).adj.begin(), nodes.at(curr).adj.end(), [prev](const Edge & e){return e.dest==stoi(prev);});
            if (it_curr_to_prev==(nodes.at(prev).adj.end())){
                nodes.at(prev).adj.emplace_back(Edge{stoi(prev), it_prev_to_curr->duration, it_prev_to_curr->capacity, true, (int)it_prev_to_curr->capacity - it_prev_to_curr->flow});
                it_curr_to_prev = std::find_if(nodes.at(curr).adj.begin(), nodes.at(curr).adj.end(), [prev](const Edge & e){return e.dest==stoi(prev);});
            }
            it_curr_to_prev->flow += new_flow;
            curr = prev;
        }
        std::string v = dest;
        std::list<Node> path{};
        path.push_front(getNode(v));
        while (v != src) {
            v = nodes[v].pred;
            path.push_front(getNode(v));
        }
        std::cout << "send " << new_flow << " people\n";
        for (auto a: path){
            if (a == path.back()) std::cout << a.id;
            else std::cout << a.id << " -> ";
        }
        std::cout << "\n\n";
        new_flow = bfsEK(src, dest);
    }
    if (!flow) std::cout << "Flow: " << flow << " - No path was found between the source and destination.\n";
    else std::cout << "Flow: " << flow << "\n";
    return flow;
}


int Graph::edmondsKarpLimit(const std::string src, const std::string dest, const unsigned long size) {
    int flow = 0;
    int new_flow, old_flow;

    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i){
        auto &adj = (*i).second.adj;
        for (auto j{adj.begin()}, end1{adj.end()}; j != end1; ++j){
            if (!(*j).residual) (*j).flow = (*j).capacity;
            else (*j).flow = 0;
        }
    }

    new_flow = bfsEK(src, dest);
    while (new_flow) {
        if (flow == size) break;
        old_flow = flow;
        flow += new_flow;
        if (flow > size) flow = size; new_flow = flow - old_flow;
        std::string curr = dest;
        while (curr != src){
            std::string prev = nodes.at(curr).pred;
            auto it_prev_to_curr = std::find_if(nodes.at(prev).adj.begin(), nodes.at(prev).adj.end(), [curr](const Edge & e){return e.dest==stoi(curr);});
            it_prev_to_curr->flow -= new_flow;
            auto it_curr_to_prev = std::find_if(nodes.at(curr).adj.begin(), nodes.at(curr).adj.end(), [prev](const Edge & e){return e.dest==stoi(prev);});
            if (it_curr_to_prev==(nodes.at(prev).adj.end())){
                nodes.at(prev).adj.emplace_back(Edge{stoi(prev), it_prev_to_curr->duration, it_prev_to_curr->capacity, true, (int)it_prev_to_curr->capacity - it_prev_to_curr->flow});
                it_curr_to_prev = std::find_if(nodes.at(curr).adj.begin(), nodes.at(curr).adj.end(), [prev](const Edge & e){return e.dest==stoi(prev);});
            }
            it_curr_to_prev->flow += new_flow;
            curr = prev;
        }
        std::string v = dest;
        std::list<Node> path{};
        path.push_front(getNode(v));
        while (v != src) {
            v = nodes[v].pred;
            path.push_front(getNode(v));
        }
        std::cout << "send " << new_flow << " people\n";
        for (auto a: path){
            if (a == path.back()) std::cout << a.id;
            else std::cout << a.id << " -> ";
        }
        std::cout << "\n\n";
        new_flow = bfsEK(src, dest);
    }
    if (!flow) std::cout << "Flow: " << flow << " - No path was found between the source and destination.\n";
    else std::cout << "Flow: " << flow << "\n";

    if (flow < size && flow != 0) std::cout << "The desired group dimension (" << size << ") was not possible to accomplish in the given path.\n";
    return flow;
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
void Graph::dijkstra(const std::string src, const std::string dest) {
    MaxHeap<std::string, double> q(nodes.size(), "");

    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i) {
        i->second.cappd = 0;
        q.insert(i->first, -1);
        i->second.visited = false;
    }

    nodes[src].cappd = INF;
    q.increaseKey(src, INF);
    nodes[src].pred = src;

    while (q.getSize() > 0) {
        std::string uc = q.removeMax();
        Node &u = getNode(uc);
        u.visited = true;

        if (uc == dest)
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

bool Graph::bfs(const std::string src, const std::string dest) {
    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i)
        i->second.visited = false;

    std::queue<std::string> q; // queue of unvisited nodes
    q.push(src);
    nodes[src].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        std::string u = q.front();
        q.pop();

        if (u == dest)
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

std::list<Node> Graph::maximizeJointAny(const std::string src, const std::string dest, int &cap) {
    dijkstra(src, dest);

    std::list<Node> path{};
    if (nodes[dest].cappd == 0)
        return path;

    path.push_back(getNode(dest));
    std::string v = dest;
    cap = nodes[v].cappd;
    while (v != src) {
        v = nodes[v].pred;
        path.push_front(getNode(v));
    }

    return path;
}

void Graph::minimizeJointTrans(const std::string src, const std::string dest, std::list<Node> &path1, std::list<Node> &path2, int &cap) {
    dijkstra(src, dest);

    if (nodes[dest].cappd != 0) {
        path1.push_back(getNode(dest));
        std::string v = dest;
        cap = nodes[v].cappd;
        while (v != src) {
            v = nodes[v].pred;
            path1.push_front(getNode(v));
        }
    }

    if (bfs(src, dest)) {
        path2.push_back(getNode(dest));
        std::string v = dest;
        while (v != src) {
            v = nodes[v].pred;
            path2.push_front(getNode(v));
        }
    }
}
