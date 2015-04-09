#ifndef PAGE_CONSTRUCTOR_H
#define PAGE_CONSTRUCTOR_H

#include <string>
#include <vector>
#include "WorldCup.h"

using namespace std;

// This class should be able to write out a html file
// that lets users visualize the results of the games
class PageConstructor {
  public:
    PageConstructor(string fileName, WorldCup *cup);

    void generateTeamsProfile(ofstream& file);

    void generateFoulsProfile(ofstream& file);

    void generateGoalsProfile(ofstream& file);

    void generateRowsFoulsProfile(ofstream& file, char type);

    void generateRowsGoalsProfile(ofstream& file, char type);

    void generateTeamsTab(ofstream& file);

    void generateTeamsTabContent(ofstream& file);

    void generateTeamsTabContentRow(ofstream& file, int& index);

    void generateOverallSummary(ofstream& file);

    void build();

  private:
    WorldCup *worldCup;

    string outputFileName;
};

#endif
