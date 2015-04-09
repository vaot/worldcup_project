#ifndef WORLD_CUP_H
#define WORLD_CUP_H

#include "Team.h"
#include <string>
#include <vector>
#include "Game.h"

using namespace std;

// Because we know how many games there will
// be we dont need to dynamically allocate
// these variables, we know their value upfront
const int USER_SELECTED_TEAMS = 4;
const int GAMES_COUNT = 4;

class WorldCup {
  public:
    WorldCup(string configFileName);

    // Start the show
    void start();

    // Add team and return teams size
    int addTeam(Team& newTeam);

    void buildHtmlPage();

    void pickTeamsForSemifinals();

    void randomlyPickTeams();

    void displayTeams();

    Team* getTeam(int index);

    int getTeamsCount();

    Game* getGame(int index);

    int getGameCurrentIndex();

    void addGame(Game *game);

    int* getQualifiedTeams();

  private:
    int _currentGameIndex;

    string configFile;

    //  Will take of setting up our current object instance
    void setUpConfig();

    // Store all games that happen in this cup
    // Array of pointers
    Game *games[GAMES_COUNT];

    // All teams object will be stored here
    vector<Team> teams;

    // It will hold indexes of #teams, which in turn
    // is a vector.
    int selectedTeamsIndexes[USER_SELECTED_TEAMS];
};

#endif
