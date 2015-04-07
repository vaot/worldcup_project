#ifndef WORLD_CUP_H
#define WORLD_CUP_H

#include <time.h>
#include "Team.h"
#include <string>
#include <vector>

using namespace std;

class WorldCup {
  public:
    WorldCup(string configFileName);

    // Keep track of time
    void initTime();

    // Add team and return teams size
    int addTeam(Team& newTeam);

    // DISPLAY FUNCTIONS
    void generateResultHtmlPage();

    clock_t getStartOfGame() { return startOfGame; }

  private:
    clock_t startOfGame;

    string configFile;

    //  Will take of setting up our current object instance
    void setUpConfig();

    // All teams object will be stored here
    vector<Team> teams;
};

#endif
