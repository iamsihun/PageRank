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

void Reddit::PageRank() {
    std::map<Vertex, double> init_distr;
    for (auto& vertex : g_.getVertices()) {
        init_distr[vertex] = 1.0 / g_.getVertices().size();
        pagerank_distr_[vertex] = 0;
    }
    for (auto& vertex : g_.getVertices()) {
        for (auto& source : g_flipped_.getAdjacent(vertex)) { // gets all vertices pointing TO vertex
            pagerank_distr_[vertex] += init_distr[source] / g_.getAdjacent(source).size();
            // adds the initial probabiliity of each source pointing to vertex divided by
            // the number of vertices that source points to
        }
    }
    double total = 0.0;
    for (auto& vertex : pagerank_distr_) {
        std::cout << vertex.first << " " << vertex.second << std::endl;
        total += vertex.second;
    }
    std::cout << total << std::endl;
}

void Reddit::PrintData() {
    g_.print();
}
}