#ifndef PAGE_CONSTRUCTOR_H
#define PAGE_CONSTRUCTOR_H

#include <string>
#include <vector>
#include "Team.h"

using namespace std;

// This class should be able to write out a html file
// that lets users visualize the results of the games
class PageConstructor {
  public:
    PageConstructor(string fileName);

    void generateTeamsProfile(const vector<Team> &teams);

    void addPageElement(string& newElement);

  private:
    string outputFileName;
    vector<string> pageElements;
};

#endif
