#ifndef GAME_H
#define GAME_H

class Game {
  public:
    void start();

    void stop();

  private:
    Team teamA;
    Team teamB;
    Referee referee;
};

#endif
