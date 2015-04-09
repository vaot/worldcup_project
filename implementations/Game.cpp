#include "Game.h"
#include "Team.h"
#include <fstream>
#include <time.h>
#include <csignal>
#include <math.h>
#include "vaot_utilities.h"

int GLOBAL_CLOCK_FLAG = 1;
Game *currentGame;

Game::Game(Team& a, Team& b) {
  teamA = &a;
  teamB = &b;
  teamAComparisonsWin = 0;
  teamBComparisonsWin = 0;
}

void Game::play() {
  if (teamA->attackWith(vaot::randomInt(0, 22)) > teamB->defendWith(vaot::randomInt(0, 22))) {
    teamAComparisonsWin++;
  } else {
    teamBComparisonsWin++;
  }
}

void Game::computeFouls() {
  float now = vaot::clockToSeconds(clock() - startOfGame);

  if ((vaot::randomInt(0, 100)*teamA->getFoulsLikelihood()) > (vaot::randomInt(0, 100)*teamB->getFoulsLikelihood())) {

    Foul foulA = {teamA->getPlayer(vaot::randomInt(0,14)), &teamB->getName(), now};
    teamAFouls.push_back(foulA);
    cout << "Wowwww foul from " <<  teamB->getName() << endl;

  } else {

    Foul foulB = {teamB->getPlayer(vaot::randomInt(0,14)), &teamB->getName(), now};
    teamBFouls.push_back(foulB);
    cout << "Wowwww foul from " <<  teamB->getName() << endl;

  }

  ifstream foulAscii;
  foulAscii.open("foulAscii.txt");
  cout << foulAscii.rdbuf() << endl << endl;
  foulAscii.close();
}

void Game::computeGoals() {
  float now = vaot::clockToSeconds(clock() - startOfGame);

  if ((vaot::randomInt(0, 100)*teamA->getOverallWeight()) > (vaot::randomInt(0, 100)*teamB->getOverallWeight())) {

    Goal goalA = {teamA->getPlayer(vaot::randomInt(0,14)), &teamB->getName(), false, now};
    teamAGoals.push_back(goalA);
    cout << "Wowwww goal from " <<  teamB->getName() << endl;

  } else {

    Goal goalB = {teamB->getPlayer(vaot::randomInt(0,14)), &teamB->getName(), false, now};
    teamBGoals.push_back(goalB);
    cout << "Wowwww goal from " <<  teamB->getName() << endl;
  }

  ifstream goalAscii;
  goalAscii.open("goalAscii.txt");
  cout << goalAscii.rdbuf() << endl << endl;
  goalAscii.close();
}

ostream& operator<<(ostream& os, Game& game) {
  os << endl;

  os << "====================  "
     << game.getTeam('A')->getName()
     << " x "
     << game.getTeam('B')->getName()
     << "  ===================="
     << endl;

  ifstream soccerFieldAscii;
  soccerFieldAscii.open("soccerFieldAscii.txt");
  os << soccerFieldAscii.rdbuf() << endl;
  soccerFieldAscii.close();
  return os;
}

Team* Game::getTeam(char team) {
  switch(team) {
    case 'A':
      return teamA;
      break;
    case 'B':
      return teamB;
      break;
  }
}

vector<Goal>& Game::getGoals(char type) {
  switch(type) {
    case 'A':
      return teamAGoals;
      break;
    case 'B':
      return teamBGoals;
      break;
  }
}

vector<Foul>& Game::getFouls(char type) {
  switch(type) {
    case 'A':
      return teamAFouls;
      break;
    case 'B':
      return teamBFouls;
      break;
  }
}

// Friend Function
void switchDisplayMode(int signum) {
  cout << "You want to see live ? (type the number)\n";
  cout << "1 - Game time\n";
  cout << "2 - Open Results Page\n";
  cout << "3 - Change Player\n";

  int choice;

  cin >> choice;

  switch(choice) {
    case 1:
      cout << "Time again" << endl;
      break;
    case 2:
      cout << "Opening Results Page" << endl;
      vaot::openUrl("results.html");
      break;
    case 3:
      cout << "Choose Team to change player" << endl;
      currentGame->exchangePlayer();
      break;
  }
}

void Game::determineWinner() {
  if (teamAGoals.size() > teamBGoals.size()) {
    winner = teamA;
    loser = teamB;
  } else if (teamAGoals.size() < teamBGoals.size()) {
    winner = teamB;
    loser = teamA;
  } else {
    determineWinnerFromPenalties();
    return;
  }

  cout << "Wowwwwwwwwwwwww" << endl;
  cout << "============= "
       << getWinner()->getName() << " Won!!"
       << " ============"
       << endl;

  cout << "========== "
       << teamB->getName()
       << " " << teamAGoals.size()
       << " X "
       << teamBGoals.size() << " "
       << teamB->getName() << "\n\n";
}

string Game::displayResult() {
  string temp;
  temp += teamB->getName();
  temp += " ";
  temp += to_string(teamAGoals.size());
  temp += " X ";
  temp += to_string(teamBGoals.size());
  temp += " ";
  temp += teamB->getName();
  return temp;
}

void Game::determineWinnerFromPenalties() {
  int penaltiesA = 0, penaltiesB = 0;
  float now = vaot::clockToSeconds(clock() - startOfGame);

  for (int i = 0; i < NUMBER_OF_PLAYERS ; ++i) {
    Player *tempPlayerA, *tempPlayerB;
    tempPlayerA = teamA->getPlayer(i);
    tempPlayerB = teamB->getPlayer(i);

    if (tempPlayerA->attack() > tempPlayerA->defend()){
      penaltiesA++;
      Goal goalA = {tempPlayerA, &teamB->getName(), true, now};
      teamAGoals.push_back(goalA);
    }

    if (tempPlayerB->attack() > tempPlayerB->defend()) {
      penaltiesB++;
      Goal goalB = {tempPlayerB, &teamB->getName(), true, now};
      teamBGoals.push_back(goalB);
    }
  }

  // Determine who won
  if(penaltiesA > penaltiesB) {
    winner = teamA;
    loser = teamB;
  } else {
    winner = teamB;
    loser = teamA;
  }

  cout << "\n\n";
  cout << "============== Wooww Victory in Penalty Shootout by: "
       << winner->getName()
       << " =============\n\n" << endl;

}

void Game::initTime() {
  currentGame = this;
  startOfGame = clock();

  float gameTimeInSec = 0;

  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  // We will switch modes whenenver they want to
  signal(SIGINT, switchDisplayMode);

  int halfTime = 1;

  do {
    clock_t temp = clock() - startOfGame;
    gameTimeInSec = (((float)temp)/CLOCKS_PER_SEC);

    if (gameTimeInSec > 10.0) {
      halfTime = 2;
    }

    cout << halfTime << " half - "
         << "(Press ctr + c to switch modes): Game Time: "
         << gameTimeInSec << "\r";

    if (fmod(gameTimeInSec, 1.5) == 0.0) {
      cout << "\n";
      computeFouls();
    }

    if (fmod(gameTimeInSec, 2.5) == 0.0) {
      cout << "\n";
      computeGoals();
    }

    // Lets play
    play();
  } while (gameTimeInSec < 14.0 && GLOBAL_CLOCK_FLAG);

  vaot::playSound("GameStart.wav");
  determineWinner();
}

Team* Game::getWinner() const {
  return winner;
}

Team* Game::getLoser() const {
  return loser;
}
