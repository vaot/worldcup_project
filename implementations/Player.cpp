#include "Player.h"
#include <string>
#include "vaot_utilities.h"

Player::Player() {

}

Player::Player(string n, int teamScore) {
  name = n;

  // We use temScore to weight the individual skills out
  // so we keep consistency
  speed = vaot::randomInt(MIN_PLAYER_SCORE, teamScore);
  power = vaot::randomInt(MIN_PLAYER_SCORE, teamScore);
  endurance = vaot::randomInt(MIN_PLAYER_SCORE, teamScore);
  defense = vaot::randomInt(MIN_PLAYER_SCORE, teamScore);
  _attack = vaot::randomInt(MIN_PLAYER_SCORE, teamScore);
}

string Player::getName() {
  return name;
}

void Player::setName(string n) {
  name = n;
}

int Player::getSkill(string type) {
  // I wish I could use #switch statement here
  // but c++ does allow switch with strings
  if (type == "power") {
    return power;
  }

  if (type == "speed") {
    return speed;
  }

  if (type == "endurance") {
    return endurance;
  }

  if (type == "defense") {
    return defense;
  }

  if (type == "attack") {
    return _attack;
  }

  // Should never get to this point
  return 0;
}

int Player::defend() {
  return ((power + endurance + speed) * defense);
}

int Player::attack() {
  return ((power + endurance + speed) * _attack);
}
