#include <fstream>
#include <vector>
#include "reddit.h"

using namespace std;
using namespace reddit;

int main() {
  // These lines use the Reddit class to parse through the data
  Reddit r;
  r.ParseData("data/data1000.tsv");
  //r.FindConnectedComponents();
  //r.PageRank();
  // r.PrintData();


  return 0;
}
