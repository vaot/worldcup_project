#ifndef TEAM_H
#define TEAM_H

#include <string>

using namespace std;

class Team  {
  public:
    Team();
    void newFromConfig(string stringRow);
  private:
    int overallWeight;
    int foulsLikelihood;
    string name;
};

#endif
