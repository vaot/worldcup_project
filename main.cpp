#include <string>
#include <iostream>
#include "WorldCup.h"
#include <vector>
#include "vaot_utilities.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char const *argv[]) {
  srand(time(0));
  WorldCup newCup("WorldCup.txt");
  newCup.start();
  return 0;
}
