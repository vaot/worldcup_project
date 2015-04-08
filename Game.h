#ifndef GAME_H
#define GAME_H

#include "Team.h"
#include <iostream>
#include <time.h>
#include <vector>

struct Foul {
  Player *player;
  clock_t when;
};

struct Goal {
  Player *player;
  bool fromPenalty;
  clock_t when;
};

class Game {
  public:
    Game(const Team&, const Team&);

    const Team& getTeam(char team) const;

    void play();

    void initTime();

    void computeFouls();

    void computeGoals();

    void determineWinner();

    void determineWinnerFromPenalties();

    Team* getWinner() const;

    Team* getLoser() const;

    // The user may choose what to see
    // while the teams are playing
    friend void switchDisplayMode(int);

    friend ostream& operator<<(ostream&, const Game&);

  private:
    Team *winner;

    Team *loser;

    Team teamA;

    Team teamB;

    clock_t startOfGame;

    int teamAComparisonsWin;

    int teamBComparisonsWin;

    vector<Foul> teamAFouls;

    vector<Foul> teamBFouls;

    vector<Goal> teamAGoals;

    vector<Goal> teamBGoals;

};

#endif
