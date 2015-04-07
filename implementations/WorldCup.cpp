#include "WorldCup.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <time.h>
#include "PageConstructor.h"

using namespace std;

WorldCup::WorldCup(string configFileName) {
  configFile = configFileName;
  setUpConfig();
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

  for (int i = 0; i < teams.size(); ++i) {
    cout << teams[i].getPlayer(1).getName() << endl;
    cout << teams[i].getPlayer(1).getSkill("power") << endl;
    cout << teams[i].attackWith(3) << endl;
  }
}

int WorldCup::addTeam(Team& newTeam) {
  teams.push_back(newTeam);
  return teams.size();
}

void WorldCup::generateResultHtmlPage() {
  PageConstructor newPage("results.html");
  newPage.generateTeamsProfile(teams);
}

void WorldCup::initTime() {
  // TO DO: Implement time
  clock_t gameTime;
  double gameTimeInSec = 0;
  gameTime = clock();

  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(4);

  do {
    cout << "time" << endl;
    clock_t temp = clock() - gameTime;
    gameTimeInSec = (((double)temp)/CLOCKS_PER_SEC);
    cout << gameTimeInSec;
  } while (gameTimeInSec < 1.0);
}
