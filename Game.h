#ifndef GAME_H
#define GAME_H

#include "Team.h"
#include <iostream>
#include <time.h>

class Game {
  public:
    Game(const Team&, const Team&);

    const Team& getTeam(char team) const;

    void play();

    void initTime();

    // The user may choose what to see
    // while the teams are playing
    friend void switchDisplayMode(int);

    friend ostream& operator<<(ostream&, const Game&);

  private:
    Team teamA;
    Team teamB;
    clock_t startOfGame;
};

#endif
