#include "reddit.h"

namespace reddit {

void Reddit::ParseData(const std::string& data_file) {
    std::ifstream file(data_file);
    std::string line;
    while (getline(file, line)) {  
        std::stringstream ss;
        ss << line;
        Post post;
        ss >> post.source_subreddit >> post.target_subreddit >> post.post_id;
        data_.push_back(post);
    }
    file.close();
}

void Reddit::PrintData() {
    for (auto& post : data_) {
        std::cout << post.source_subreddit << " " << post.target_subreddit << " " << post.post_id << std::endl;
    }
}
}