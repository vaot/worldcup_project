#include "Game.h"
#include "Team.h"
#include <fstream>
#include <time.h>
#include <csignal>

int GLOBAL_CLOCK_FLAG = 1;

Game::Game(const Team& a, const Team& b) {
  teamA = a;
  teamB = b;
}

void Game::play() {
  startOfGame = clock();
  // TO DO: Play mechanism
}

ostream& operator<<(ostream& os, const Game& game) {
  os << endl;

  os << "====================  "
     << game.getTeam('A').getName()
     << " x "
     << game.getTeam('B').getName()
     << "  ===================="
     << endl;

  ifstream soccerFieldAscii;
  soccerFieldAscii.open("soccerFieldAscii.txt");
  os << soccerFieldAscii.rdbuf();
  os << endl;
  return os;
}

const Team& Game::getTeam(char team) const {
  switch(team) {
    case 'A':
      return teamA;
      break;
    case 'B':
      return teamB;
      break;
  }
}

void switchDisplayMode(int signum) {
  cout << "You want to see live ? (type the number)\n";
  cout << "1 - Game time\n";
  cout << "2 - The plays\n";
  cout << "3 - Advance and show result\n";

  int choice;

  cin >> choice;

  switch(choice) {
    case 1:
      cout << "Time again" << endl;
      break;
    case 2:
      cout << "Ohhh he played" << endl;
      GLOBAL_CLOCK_FLAG = 0;
      break;
    case 3:
      cout << "We hear the whistle" << endl;
      GLOBAL_CLOCK_FLAG = 0;
      break;
  }
}

void Game::initTime() {
  // TO DO: Implement time
  double gameTimeInSec = 0;

  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(4);

  signal(SIGINT, switchDisplayMode);

  do {
    clock_t temp = clock() - startOfGame;
    gameTimeInSec = (((double)temp)/CLOCKS_PER_SEC);
    cout << "Game Time: " << gameTimeInSec << "\r";
  } while (gameTimeInSec < 60.0 && GLOBAL_CLOCK_FLAG);
}
