#pragma once
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>
#include <iostream>

namespace reddit {

class Reddit {

  public:
    Reddit(){};

    /**
     * Parses through a data file
     * @param data_file the string representing the path of the file
     */
    void ParseData(const std::string& data_file);
    void PrintData();

  private:

    struct Post {
        std::string source_subreddit;
        std::string target_subreddit;
        std::string post_id;
        std::string timestamp; // may need to find a better object if we want to compare times. time_point may be an option?
        int post_label;
        std::vector<float> post_properties; // depending on what we want to use from post_properties, we may want to create another 
                                       // struct representing this
    };

    std::vector<Post> data_;
};
}