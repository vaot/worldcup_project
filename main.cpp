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
  newCup.generateResultHtmlPage();
  newCup.start();

  // TO DO: Implement time
  // clock_t gameTime;
  // double gameTimeInSec = 0;
  // gameTime = clock();


  // cout.setf(ios::fixed);
  // cout.setf(ios::showpoint);
  // cout.precision(4);
  // int run = 1;

  // do {
  //   cout << "time" << endl;
  //   clock_t temp = clock() - gameTime;
  //   gameTimeInSec = (((double)temp)/CLOCKS_PER_SEC);
  //   cout << gameTimeInSec;
  // } while (gameTimeInSec < 60.0 && run);

  return 0;
}
