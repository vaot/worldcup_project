#ifndef WORLD_CUP_H
#define WORLD_CUP_H

#include "Team.h"
#include <string>
#include <vector>

using namespace std;

const int USER_SELECTED_TEAMS = 4;

class WorldCup {
  public:
    WorldCup(string configFileName);

    // Start the show
    void start();

    // Add team and return teams size
    int addTeam(Team& newTeam);

    void generateResultHtmlPage();

    void pickTeamsForSemifinals();

    void randomlyPickTeams();

    void displayTeams();

  private:
    string configFile;

    //  Will take of setting up our current object instance
    void setUpConfig();

    // All teams object will be stored here
    vector<Team> teams;

    // It will hold indexes of #teams, which in turn
    // is a vector.
    int selectedTeamsIndexes[USER_SELECTED_TEAMS];
};

#endif
