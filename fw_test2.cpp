#include "reddit.h"

using namespace std;
using namespace reddit;

int main() {
    Reddit r;
  r.parseData("data/FW_test2.tsv");
  r.printFW();

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

