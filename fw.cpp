#include "reddit.h"
#include <fstream>

using namespace std;
using namespace reddit;

int main() {
  Reddit r;
  r.FWParseData("data/data1000.tsv");
  r.buildShortestPaths();
  r.printFW();

  cout<<'\n'<<endl;

  string start;
  string dest;

  while(1){

  cout << "Enter starting subreddit: ";
  cin >> start;
  cout << "Enter ending subreddit: ";
  cin >> dest;

  cout<<'\n'<< '\n' <<endl;
  
  cout << "START:   " << start << "->" << endl;
  r.findPath(start, dest);
  int pathLength = r.path_.size();
  if(!r.path_.empty()) {
      for(int i=0; i<pathLength; i++) {
          if(i==pathLength-1) {
              cout << "END:     " << r.path_[i] << endl;
              break;
          } 
          cout << "              " << r.path_[i] << "->" << endl;
    }
  }
  else {
      if(start == dest) {
          cout << "path to itself" << endl;
          return 0;
      }
      cout << "no path found" << endl;
      return 0;
  }

      cout<<'\n'<< '\n' <<endl;
      cout << "LENGTH: " << r.getshortestDist(start, dest) << " subreddits" << endl;

      cout<<'\n'<< '\n' <<endl;

  }

    return 0;
  
}