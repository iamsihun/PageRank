#include "reddit.h"
#include <fstream>

using namespace std;
using namespace reddit;

int main() {     
  Reddit r;
  r.parseData("data/mult_connected.tsv");
  r.printFW();
  return 0;
}