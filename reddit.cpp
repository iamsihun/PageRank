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
        }
        if (!g_.vertexExists(target)) {
            g_.insertVertex(target);
        }
        if (!g_.edgeExists(source, target)) {
            g_.insertEdge(source, target);
            g_.setEdgeWeight(source, target, 1); 
        } else {
            g_.setEdgeWeight(source, target, g_.getEdgeWeight(source, target) + 1);
        }
        ss.str(std::string()); // clears the stringstream
    }
    file.close();
}

void Reddit::PrintData() {
    g_.print();
}
}