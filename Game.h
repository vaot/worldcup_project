#ifndef GAME_H
#define GAME_H

#include "Team.h"
#include <iostream>
#include <time.h>
#include <vector>

struct Foul {
  Player *player;
  const string *teamName;
  float when;
};

struct Goal {
  Player *player;
  const string *teamName;
  bool fromPenalty;
  float when;
};

struct Referee {
  int control; // Signifies game control
};

class Game {
  public:
    Game(Team&, Team&);

    Team* getTeam(char team);

    void play();

    void initTime();

    void computeFouls();

    void computeGoals();

    void determineWinner();

    void determineWinnerFromPenalties();

    Team* getWinner() const;

    Team* getLoser() const;

    vector<Goal>& getGoals(char type);

    vector<Foul>& getFouls(char type);

    string displayResult();

    void exchangePlayer();

    // The user may choose what to see
    // while the teams are playing
    friend void switchDisplayMode(int);

    friend ostream& operator<<(ostream&, Game&);

  private:
    Referee referee;

    Team *winner;

    Team *loser;

    Team *teamA;

    Team *teamB;

    clock_t startOfGame;

    int teamAComparisonsWin;

    int teamBComparisonsWin;

    vector<Foul> teamAFouls;

    vector<Foul> teamBFouls;

    vector<Goal> teamAGoals;

    vector<Goal> teamBGoals;

};

#endif
