#ifndef TEAM_H
#define TEAM_H

#include <string>
#include "Player.h"

using namespace std;

class Team {
  public:
    Team();

    void newFromConfig(string stringRow);

    string getName() const;

    Player& getPlayer(int index);

    int getOverallWeight() const;

    int getFoulsLikelihood() const;

    // Attack with a certain amount of players
    int attackWith(int);

    // Defend with a certain amount of players
    int defendWith(int);

  private:
    Player players[NUMBER_OF_PLAYERS];

    void generatePlayers();

    int overallWeight;

    int foulsLikelihood;

    string name;
};

#endif
