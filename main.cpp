#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "reddit.h"

using namespace std;
using namespace boost::algorithm;
using namespace reddit;

int main() {
  // These lines use the Reddit class to parse through the data
  Reddit r;
  r.ParseData("data/small_data.tsv");
  r.FindConnectedComponents();
  // r.PageRank();
  r.PrintData();

  // ifstream file("data/small_data.tsv");           //load data into 'file'
  // string line;                                    //holds each data entry
  // while (getline(file, line)) {                   //extract each data entry into 'line'
  //     vector<string> parts;                       /*'parts' holds the elements of each line i.e. 
  //                                                   TARGET_SUBREDDIT (index 1) or 
  //                                                   SOURCE_SUBREDDIT (index 0)    */

  //     split(parts, line, boost::is_any_of("\t")); //parse data into parts
  //   }
  //   file.close();
  return 0;
}
