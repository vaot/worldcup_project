#include "WorldCup.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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
}

int WorldCup::addTeam(Team newTeam) {
  teams.push_back(newTeam);
  return teams.size();
}
