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

    void exchangePlayer() {
      cout << "0 - " << teamA->getName() << endl;
      cout << "1 - " << teamB->getName() << endl;
      cout << "Choose team: ";
      int choice;
      cin >> choice;

      Team *chosenTeam;
      chosenTeam = choice == 0 ? teamA : teamB;

      for (int i = 0; i < 15; ++i) {
        cout << i << " - " << chosenTeam->getPlayer(i)->getName() << endl;
      }
      cout << "\n";

      int playerChoice;
      string newPlayersName;
      cout << "Type player id: ";
      cin >> playerChoice;
      cout << "\n";
      cout << "Type new player's name: \n";
      cin.ignore();
      getline(cin, newPlayersName);
      chosenTeam->getPlayer(playerChoice)->setName(newPlayersName);
    }

    // The user may choose what to see
    // while the teams are playing
    friend void switchDisplayMode(int);

    friend ostream& operator<<(ostream&, Game&);

  private:
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
