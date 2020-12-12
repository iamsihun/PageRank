#include "reddit.h"
#include <fstream>

using namespace std;
using namespace reddit;

int main() {     
  Reddit r;
  r.parseData("data/data1000.tsv");
  r.printFW();
  return 0;
}