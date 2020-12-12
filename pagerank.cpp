#include <fstream>
#include <vector>
#include "reddit.h"

using namespace std;
using namespace reddit;

int main() {
  // These lines use the Reddit class to parse through the data
  Reddit r;
  r.parseData("data/mult_connected.tsv");
  r.pagerank();
  // r.printData();

  return 0;
}
