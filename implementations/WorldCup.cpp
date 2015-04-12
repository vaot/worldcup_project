#include "WorldCup.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "PageConstructor.h"
#include "Game.h"
#include "vaot_utilities.h"

using namespace std;

WorldCup::WorldCup(string configFileName) {
  configFile = configFileName;
  _currentGameIndex = 0;
  setUpConfig();
}

inline void displayChampionPresentation() {
  ifstream winnerPresentation;
  winnerPresentation.open("winnerPresentation.txt");
  cout << winnerPresentation.rdbuf() << endl << endl;
  winnerPresentation.close();
}


inline void displayStartPresentation() {
  ifstream presentation;
  presentation.open("presentation.txt");
  cout << presentation.rdbuf() << endl << endl;
  presentation.close();
}

inline void displayNoteOnStatistics() {
  cout << "Hey hang on tight ... We are preparing a web interface for World Cup Statistics"
       << endl;

  for (int i = 0; i < 50; ++i) {
    cout << ".";
  }
  cout << endl;

  vaot::openUrl("results.html");
}

inline void cleanUpResultsPage() {
  ifstream resultsInit;
  resultsInit.open("results_init.html");

  ofstream results;
  results.open("results.html");
  results << resultsInit.rdbuf();

  results.close();
  resultsInit.close();
}

int* WorldCup::getQualifiedTeams() {
  return selectedTeamsIndexes;
}

void WorldCup::setUpConfig() {
  ifstream iStream;
  iStream.open(configFile);

  // Start getting country config
  string newTeamConfigRow;

  // Get line by line the content of the config file
  while(!iStream.eof()) {
    getline(iStream, newTeamConfigRow);

    Team newTeam;
    newTeam.newFromConfig(newTeamConfigRow);

    addTeam(newTeam);
  }
}

int WorldCup::addTeam(Team& newTeam) {
  teams.push_back(newTeam);
  return teams.size();
}

Team* WorldCup::getTeam(int index) {
  return &teams[index];
}

Game* WorldCup::getGame(int index) {
  return games[index];
}

int WorldCup::getTeamsCount() {
  return (teams.size());
}

void WorldCup::addGame(Game *game) {
  games[_currentGameIndex] = game;
  _currentGameIndex++;
}

int WorldCup::getGameCurrentIndex() {
  return _currentGameIndex;
}

void WorldCup::buildHtmlPage() {
  PageConstructor newPage("results.html", this);
  newPage.build();
}

void WorldCup::pickTeamsForSemifinals() {
  cout << "Hey, hang tight there, the semi-finals are on the way\n";
  cout << "1 - Press (1) for letting us randomly select 4 teams.\n";
  cout << "2 - Press (2) if you want to select 4 teams.\n";
  int choice;
  cin >> choice;

  if (choice == 1) {
    randomlyPickTeams();
    return;
  }

  // If we got to this point, choice --> 2
  for (int i = 0; i < USER_SELECTED_TEAMS; ++i) {
    printf("Please type the number of %dth Team: ", (i+1));
    cin >> selectedTeamsIndexes[i];
  }
}

void WorldCup::randomlyPickTeams() {
  for (int i = 0; i < USER_SELECTED_TEAMS; ++i) {
    // We can now randomly pick indexes of our teams vector
    int temp = 2;

    // We need to ensure we pick unique indexes
    while (vaot::include(selectedTeamsIndexes, temp, USER_SELECTED_TEAMS)) {
      temp = vaot::randomInt(0, (teams.size()-1));
    }

    selectedTeamsIndexes[i] = temp;
  }
}

void WorldCup::start() {

  cleanUpResultsPage();
  displayStartPresentation();

  for (int i = 0; i < teams.size(); ++i) {
    printf("%d %s \n", i, teams[i].getName().c_str());
  }

  cout << endl;

  // Pick the teams for semi-finals
  pickTeamsForSemifinals();

  cout << "Alright !!!!!!!! \n";
  cout << "================================================ \n";

  for (int i = 0; i < USER_SELECTED_TEAMS; ++i) cout << selectedTeamsIndexes[i] << endl;

  Game firstSemiFinal =
    Game(teams[selectedTeamsIndexes[0]], teams[selectedTeamsIndexes[1]]);
  addGame(&firstSemiFinal);

  Game secondSemiFinal =
    Game(teams[selectedTeamsIndexes[2]], teams[selectedTeamsIndexes[3]]);
  addGame(&secondSemiFinal);

  cout << "===== FIRST SEMI - FINAL ======" << endl;
  vaot::playSound("GameStart.wav");
  cout << firstSemiFinal << endl;
  firstSemiFinal.initTime();

  cout << "===== SECOND SEMI - FINAL ======" << endl;
  cout << secondSemiFinal << endl;
  secondSemiFinal.initTime();

  Game thirdPlace =
    Game(*firstSemiFinal.getLoser(), *secondSemiFinal.getLoser());
  addGame(&thirdPlace);
  cout << "====== THIRD PLACE - GAME ======" << endl;
  cout << thirdPlace << endl;
  thirdPlace.initTime();

  Game final =
    Game(*firstSemiFinal.getWinner(), *secondSemiFinal.getWinner());
  addGame(&final);
  cout << "===== WORLD CUP FINAL ======" << endl;
  cout << final << endl;
  final.initTime();

  displayChampionPresentation();
  vaot::playSound("WinnerSound.wav");
  cout << "Wowowowowowoow Champion of Soccer World Cup 2014: "
       << final.getWinner()->getName();
  cout << "\n\n\n\n\n\n";

  buildHtmlPage();
  displayNoteOnStatistics();
}

