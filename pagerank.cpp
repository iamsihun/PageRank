#include <fstream>
#include <vector>
#include "reddit.h"

using namespace std;
using namespace reddit;

int main() {
  Reddit r;
  r.parseData("data/data1000.tsv");
  r.pagerank();
  // r.printData();

  return 0;
}
