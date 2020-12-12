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
    ~Reddit();

    /**
     * Parses through a data file to create the graph.
     * @param data_file the string representing the path of the file
     */
    void parseData(const std::string& data_file);

    /**
     * Prints out the graph.
     */
    void printData();

    /**
     * Uses the page rank algorithm to print out a distribution of the nodes in each connected component.
     */
    void pagerank();

    //FLOYD WARSHALL FUNCTIONS
    void printInputPath(const Vertex& start, const Vertex& dest);
    void printFW();

  private:

    // PAGERANK HELPER METHODS
    /**
     * Splits the graph into its connected components and populates the vector connected_components_ with each
     * component/subgraph, used for the Pagerank algorithm.
     */
    void findConnectedComponents();

    /**
     * Helper method for findConnectedComponents() that uses DFS to traverse through the graph.
     */
    void DFS(const Vertex& visited_vertex, std::map<Vertex, bool>& visited, std::vector<Vertex>& connected);

    /**
     * Handles dangling nodes in the connected components by having them point to all other nodes.
     * A dangling node is one with no outgoing edges.
     */
    void handleDanglingNodes();

    // FLOYD-WARSHALL HELPER METHODS
    void buildShortestPaths();
    int getshortestDist(const Vertex& source, const Vertex& dest); 
    void findPath(const Vertex& source, const Vertex& dest);
    
    vector<Vertex> path_;
    Graph g_;
    Graph g_flipped_;
    std::vector<std::map<Vertex, double>> pagerank_distr_;
    std::vector<std::vector<Vertex>> connected_components_;

    //FLOYD WARSHALL VARIABLES
    std::map<Vertex, int> vertextoInt;
    int* minDist = NULL;
    int* next = NULL;
    
};


}