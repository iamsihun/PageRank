#pragma once
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include "graph.h"

namespace reddit {

class Reddit {

  public:
    Reddit() : g_(true, true), g_flipped_(false, true) {};

    /**
     * Parses through a data file
     * @param data_file the string representing the path of the file
     */

    ~Reddit();
    void ParseData(const std::string& data_file);
    void PrintData();
    void PageRank();
    void FindConnectedComponents();
    void buildShortestPaths();
    int shortestPath(Vertex source, Vertex dest); 
    void printFW();
    vector<Vertex> findPath(Vertex source, Vertex dest);

  private:
    void DFS(Vertex visited_vertex, std::map<Vertex, bool>& visited, std::vector<Vertex>& connected);

    Graph g_;
    Graph g_flipped_;
    std::vector<std::map<Vertex, double>> pagerank_distr_;
    std::vector<std::vector<Vertex>> connected_components_;
    std::map<Vertex, int> vertextoInt;
    int* minDist;
    int* next;
};


}