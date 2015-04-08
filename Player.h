#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

using namespace std;

const int NUMBER_OF_PLAYERS = 12;
const int MIN_PLAYER_SCORE = 30;

class Player {
  public:
    Player();

    Player(string, int);

    string getName();

    int getSkill(string type);

    int defend();

    int attack();


  private:
    string name;
    int speed;
    int power;
    int endurance;
    int defense;
    int _attack;
};

#endif
