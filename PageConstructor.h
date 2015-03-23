#ifndef PAGE_CONSTRUCTOR_H
#define PAGE_CONSTRUCTOR_H

#include <string>

using namespace std;

// This class should be able to write out a html file
// that lets users visualize the results of the games
class PageConstructor {
  public:
    PageConstructor(string fileName);

    void writeTeams();

  private:
    string outputFileName;
};

#endif
