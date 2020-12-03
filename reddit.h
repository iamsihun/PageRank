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
    void ParseData(const std::string& data_file);
    void PrintData();
    void PageRank();
    void DFS();

  private:
    Graph g_;
    Graph g_flipped_;
    std::map<Vertex, double> pagerank_distr_;
};
}