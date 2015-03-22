#ifndef WORLD_CUP_H
#define WORLD_CUP_H

#include "Team.h"
#include <string>
#include <vector>

using namespace std;

class WorldCup {
  public:
    WorldCup(string configFileName);

    // Add team and return teams size
    int addTeam(Team newTeam);

  private:
    string configFile;

    //  Will take of setting up our current object instance
    void setUpConfig();

    // All teams object will be stored here
    vector<Team> teams;
};

#endif
