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
  r.ParseData("data/FW_test2.tsv");
  //r.FindConnectedComponents();
  //r.PageRank();
  // r.PrintData();
  r.buildShortestPaths();
  //r.printFW();


  /*
  Vertex A;
  Vertex C;
  vector<Vertex> path = r.findPath(A, C);
  if(!path.empty()) {
      for(auto& vertex : path) {
        cout << vertex << "->";
      }
      cout << endl;
  }
  else cout << "no path found" << endl;
*/
  return 0;
}
