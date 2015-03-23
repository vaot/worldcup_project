#include "PageConstructor.h"
#include <fstream>

using namespace std;

PageConstructor::PageConstructor(string fileName) {
  outputFileName = fileName;
}

void PageConstructor::writeTeams() {
  ofstream result;
  result.open(outputFileName);
  result << "<h1>Hiiii</h1>" << endl;
  result.close();
}
