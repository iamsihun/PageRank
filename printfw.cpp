#include "reddit.h"
#include <fstream>

using namespace std;
using namespace reddit;

int main() {     
  Reddit r;
  r.FWParseData("data/mult_connected.tsv");
  r.buildShortestPaths();
  r.printFW();
  return 0;
}