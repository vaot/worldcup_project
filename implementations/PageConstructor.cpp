#include "PageConstructor.h"
#include <fstream>
#include "Team.h"
#include <string>
#include <iostream>

const string OPENING_PAGE =
  "<!DOCTYPE html> \
    <html> \
    <head> \
    <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css'> \
    <link rel='stylesheet' href='world_cup.css'> \
    </head> \
    <body> \
    <div class='container'> \
    <div class='jumbotron'>\
    <h1 class='text-center'>Soccer World Cup 2040</h1> \
    <p>Author: Victor Andrey</p> \
    <iframe src='https://ghbtns.com/github-btn.html?user=vaot&type=follow&count=false&size=large' frameborder='0' scrolling='0' width='220px' height='30px'></iframe> \
    </div> \
    <div class='teams-container'>";

const string CLOSING_PAGE =
  "</div> \
      <div class='podcast-container'> \
        <iframe width='100%' height='450' scrolling='no' frameborder='no' src='https://w.soundcloud.com/player/?url=https%3A//api.soundcloud.com/playlists/37750463&amp;auto_play=true&amp;hide_related=false&amp;show_comments=true&amp;show_user=true&amp;show_reposts=false&amp;visual=true'></iframe> \
      </div> \
    </div> \
    <div class='container'> \
      <div class='field-container'> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
          <span class='player'></span> \
        </div> \
      </div> \
    </body> \
    </html>";

using namespace std;

PageConstructor::PageConstructor(string fileName) {
  outputFileName = fileName;
}

void PageConstructor::generateTeamsProfile(const vector<Team>& teams) {

  string rows;

  for (int i = 0; i < teams.size(); ++i) {
    rows += "<tr><td>" + teams[i].getName() + "</td><td>" + to_string(teams[i].getOverallWeight()) + "</td><td>" + to_string(teams[i].getFoulsLikelihood())  + "</td></tr>";
  }

  string table =
    "<table class='table table-striped'> \
        <thead> \
          <tr> \
            <th>Team</th> \
            <th>Overall Weight</th> \
            <th>Fouls Likelihood</th> \
          </tr> \
        </thead> \
        <tbody>" + rows + "</tbody> \
    </table>";

  ofstream outStream;
  outStream.open(outputFileName);

  outStream << (OPENING_PAGE + table + CLOSING_PAGE);
  outStream.close();
}

void PageConstructor::addPageElement(string& newElement) {
  pageElements.push_back(newElement);
}
