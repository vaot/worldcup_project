#include "Team.h"
#include "vaot_utilities.h"
#include <iostream>
#include <sstream>
#include "Player.h"

using namespace std;

Team::Team() {

}

void Team::newFromConfig(string stringRow) {
  // We will put back the string in a stream
  // so we can iterate word by word
  istringstream stringStream(stringRow);
  string word;
  int column = 1;

  while (stringStream >> word) {
    switch(column) {
      case 1:
        name = word;
        column++;
        break;
      case 2:
        overallWeight = vaot::toInt(word);
        column++;
        break;
      case 3:
        foulsLikelihood = vaot::toInt(word);
        column++;
        break;
    }
  }

  // Create players
  generatePlayers();
}

Player& Team::getPlayer(int index) {
  return players[index];
}

string Team::getName() const {
  return name;
}

int Team::getOverallWeight() const {
  return overallWeight;
}

int Team::getFoulsLikelihood() const {
  return foulsLikelihood;
}

void Team::generatePlayers() {
  for (int i = 0; i < NUMBER_OF_PLAYERS; ++i) {
    // Will name players as such:
    // P - 1 Braz, P - 2 Braz, P - 2 Braz
    // Based off the team name.
    string playerName = "P - " + to_string(i) + " " + getName().substr(0, 4);
    players[i] = Player(playerName, overallWeight);
  }
}

// Attack with a certain amount of players
int Team::attackWith(int numberOfplayers) {
  int memo = 0;
  for (int i = 0; i < numberOfplayers; ++i) {
    // Get a random player, from index 0 to 21
    int randIndex = vaot::randomInt(0, NUMBER_OF_PLAYERS - 1);
    memo += players[randIndex].attack();
  }
  return memo;
}

// Defend with a certain amount of players
int Team::defendWith(int numberOfplayers) {
  int memo = 0;
  for (int i = 0; i < numberOfplayers; ++i) {
    // Get a random player, from index 0 to 21
    int randIndex = vaot::randomInt(0, NUMBER_OF_PLAYERS - 1);
    memo += players[randIndex].defend();
  }
  return memo;
}
