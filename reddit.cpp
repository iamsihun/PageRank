#include "reddit.h"

namespace reddit {

void Reddit::ParseData(const std::string& data_file) {
    std::ifstream file(data_file);
    std::string line;
    std::stringstream ss;
    while (getline(file, line)) {  
        ss << line;
        std::string source;
        std::string target;
        ss >> source >> target;
        if (!g_.vertexExists(source)) {
            g_.insertVertex(source);
            g_flipped_.insertVertex(source);
        }
        if (!g_.vertexExists(target)) {
            g_.insertVertex(target);
            g_flipped_.insertVertex(target);
        }
        
        if (!g_.edgeExists(source, target)) {
            g_.insertEdge(source, target);
            g_.setEdgeWeight(source, target, 1); 
            g_flipped_.insertEdge(target, source);
        } else {
            g_.setEdgeWeight(source, target, g_.getEdgeWeight(source, target) + 1);
        }
        ss.str(std::string()); // clears the stringstream
    }
    file.close();
}

void Reddit::FindConnectedComponents() {
    std::map<Vertex, bool> visited;
    for (auto& vertex : g_.getVertices()) {
        visited[vertex] = false;
    }
    for (auto& vertex : g_.getVertices()) {
        if (!visited[vertex]) {
            std::vector<Vertex> connected;
            DFS(vertex, visited, connected);
            connected_components_.push_back(connected);
        }
    }
}

void Reddit::DFS(Vertex visited_vertex, std::map<Vertex, bool>& visited, std::vector<Vertex>& connected) {
    visited[visited_vertex] = true;
    connected.push_back(visited_vertex);
    for (auto& adj : g_.getAdjacent(visited_vertex)) {
        if (!visited[adj]) {
            DFS(adj, visited, connected);
        }
    }
    for (auto& adj : g_flipped_.getAdjacent(visited_vertex)) {
        if (!visited[adj]) {
            DFS(adj, visited, connected);
        }
    }
}

void Reddit::PageRank() {
    // initialize the distributions to 1 / # vertices in component
    std::vector<std::map<Vertex, double>> init_distr;
    for (auto& comp : connected_components_) {
        std::map<Vertex, double> init_map;
        std::map<Vertex, double> pagerank_map;
        for (auto& vertex : comp) {
            init_map[vertex] = 1.0 / comp.size();
            pagerank_map[vertex] = 0.0;
        }
        init_distr.push_back(init_map);
        pagerank_distr_.push_back(pagerank_map);
    }

    for (unsigned int i = 0; i < connected_components_.size(); i++) {
        for (auto& vertex : connected_components_[i]) {
            for (auto& source : g_flipped_.getAdjacent(vertex)) { // gets all vertices pointing TO vertex
                pagerank_distr_[i][vertex] += init_distr[i][source] / g_.getAdjacent(source).size();
                // adds the initial probabiliity of each source pointing to vertex divided by
                // the number of vertices that source points to
            }
        }
    }

    for (unsigned int i = 0; i < pagerank_distr_.size(); i++) {
        std::cout << "component: " << i << std::endl;
        double total = 0.0;
        for (auto& vertex : pagerank_distr_[i]) {
            std::cout << vertex.first << " " << vertex.second << std::endl;
            total += vertex.second;
        }
        std::cout << total << std::endl;
    }
}

void Reddit::PrintData() {
    for (unsigned int i = 0; i < connected_components_.size(); i++) {
        std::cout << i << std::endl;
        for (auto& comp : connected_components_[i]) {
            std::cout << comp << " ";
        }
        std::cout << "\n";
    }
}
}