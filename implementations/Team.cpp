#include "Team.h"
#include "vaot_utilities.h"
#include <iostream>
#include <sstream>

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
}
