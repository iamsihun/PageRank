#include "reddit.h"
#include <fstream>

using namespace std;
using namespace reddit;

int main() {     
  Reddit r;
  r.parseData("data/mult_connected.tsv");

  cout<<'\n'<<endl;

  string start;
  string dest;

  while(1){

  cout << "Enter starting subreddit: ";
  cin >> start;
  cout << "Enter ending subreddit: ";
  cin >> dest;

  r.printInputPath(start, dest);
  }
return 0;
}