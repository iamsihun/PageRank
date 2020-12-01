#pragma once
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "graph.h"

namespace reddit {

class Reddit {

  public:
    Reddit() : g_(true, true) {};

    /**
     * Parses through a data file
     * @param data_file the string representing the path of the file
     */
    void ParseData(const std::string& data_file);
    void PrintData();

  private:
    Graph g_;
};
}