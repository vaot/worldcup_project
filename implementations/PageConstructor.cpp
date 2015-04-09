#include "PageConstructor.h"
#include <fstream>
#include "Team.h"
#include <string>
#include <iostream>

using namespace std;

PageConstructor::PageConstructor(string fileName, WorldCup *cup) {
  outputFileName = fileName;
  worldCup = cup;
}

void PageConstructor::generateOverallSummary(ofstream& file) {
  file << "<div class='result-container'><ol class='result'>"
       << "<li>" << worldCup->getGame(3)->getWinner()->getName() << "</li>"
       << "<li>" << worldCup->getGame(3)->getLoser()->getName() << "</li>"
       << "<li>" << worldCup->getGame(2)->getWinner()->getName() << "</li>"
       << "<li>" << worldCup->getGame(2)->getLoser()->getName() << "</li>"
       << "</ol></div>";

  file << "<div class='alert alert-success' role='alert'>"
       << "<span class='label label-danger'>"
       << worldCup->getGame(3)->displayResult()
       << "</span>"
       << "</div>"

       << "<div class='alert alert-success' role='alert'>"
       << "<span class='label label-danger'>"
       << worldCup->getGame(2)->displayResult()
       << "</span>"
       << "</div>"

       << "<div class='alert alert-success' role='alert'>"
       << "<span class='label label-danger'>"
       << worldCup->getGame(1)->displayResult()
       << "</span>"
       << "</div>"

       << "<div class='alert alert-success' role='alert'>"
       << "<span class='label label-danger'>"
       << worldCup->getGame(0)->displayResult()
       << "</span>"
       << "</div>";
}

void PageConstructor::generateTeamsProfile(ofstream& file) {
  file << "<!DOCTYPE html> \
          <html> \
          <head> \
          <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css'> \
          <link rel='stylesheet' href='world_cup.css'> \
          <script src='jquery-2-1-3.js'></script> \
          <script src='bootstrap.min.js'></script> \
          </head> \
          <body> \
          <div class='container'> \
          <div class='jumbotron'>\
          <h1 class='text-center'>Soccer World Cup 2040</h1> \
          <p>Author: Victor Andrey</p> \
          <iframe src='https://ghbtns.com/github-btn.html?user=vaot&type=follow&count=false&size=large' frameborder='0' scrolling='0' width='220px' height='30px'></iframe> \
          </div>";

  generateOverallSummary(file);

  file << "<ul class='nav nav-tabs' role='tablist'> \
          <li role='presentation' class='active'><a href='#weights' aria-controls='home' role='tab' data-toggle='tab'>Weights</a></li> \
          <li role='presentation'><a href='#fouls' aria-controls='profile' role='tab' data-toggle='tab'>Fouls</a></li> \
          <li role='presentation'><a href='#goals' aria-controls='messages' role='tab' data-toggle='tab'>Goals</a></li> \
          </ul>";

  file << "<div class='tab-content'> \
          <div role='tabpanel' class='tab-pane active' id='weights'> \
          <div class='teams-container'> \
          <table class='table table-striped'> \
          <thead> \
          <tr> \
          <th>Team</th> \
          <th>Overall Weight</th> \
          <th>Fouls Likelihood</th> \
          </tr> \
          </thead> \
          <tbody>";

  for (int i = 0; i < worldCup->getTeamsCount(); ++i) {
    file << "<tr><td>" << worldCup->getTeam(i)->getName() << "</td><td>" << to_string(worldCup->getTeam(i)->getOverallWeight()) << "</td><td>" << to_string(worldCup->getTeam(i)->getFoulsLikelihood())  << "</td></tr>";
  }

  file << "</tbody> \
          </table> \
          </div> \
          </div> <!-- END OF TAB-->";
}

void PageConstructor::generateRowsFoulsProfile(ofstream& file, char type) {
  file.setf(ios::fixed);
  file.setf(ios::showpoint);
  file.precision(2);

  for (int i = 0; i < (worldCup->getGameCurrentIndex()); ++i) {
    for (int j = 0; j < worldCup->getGame(i)->getFouls(type).size(); ++j) {
      file << "<tr><td>"
          << *(worldCup->getGame(i)->getFouls(type)[j].teamName)
          << "</td><td>"
          << worldCup->getGame(i)->getFouls(type)[j].player->getName()
          << "</td><td>"
          << worldCup->getGame(i)->getFouls(type)[j].when
          << "</td></tr>";
    }
  }
}

void PageConstructor::generateRowsGoalsProfile(ofstream& file, char type) {
  file.setf(ios::fixed);
  file.setf(ios::showpoint);
  file.precision(2);

  for (int i = 0; i < (worldCup->getGameCurrentIndex()); ++i) {
    for (int j = 0; j < worldCup->getGame(i)->getGoals(type).size(); ++j) {
      file << "<tr><td>"
          << *(worldCup->getGame(i)->getGoals(type)[j].teamName)
          << "</td><td>"
          << worldCup->getGame(i)->getGoals(type)[j].player->getName()
          << "</td><td>"
          << worldCup->getGame(i)->getGoals(type)[j].when
          << "</td></tr>";
    }
  }
}

void PageConstructor::build() {
  ofstream file;
  file.open(outputFileName);

  generateTeamsProfile(file);
  generateFoulsProfile(file);
  generateGoalsProfile(file);

  file << "</div> <!-- END OF TAB CONTENT --> \
          <div class='podcast-container'> \
          <iframe width='100%' height='450' scrolling='no' frameborder='no' src='https://w.soundcloud.com/player/?url=https%3A//api.soundcloud.com/playlists/37750463&amp;auto_play=false&amp;hide_related=false&amp;show_comments=true&amp;show_user=true&amp;show_reposts=false&amp;visual=true'></iframe> \
          </div> \
          </div><!-- CONTAINER --> \
          <div class='container'>";

  generateTeamsTab(file);
  generateTeamsTabContent(file);

  file << "</div><!-- CONTAINER -->";
  file << "</body></html>";
  file.close();
}

void PageConstructor::generateTeamsTab(ofstream& file) {
  file << "<ul class='nav nav-tabs' role='tablist'>";
  for (int i = 0; i < 4; ++i) {
    int teamIndex = *(worldCup->getQualifiedTeams() + i);
    file << "<li role='presentation' class='"
         << (i == 0 ? "active" : "nothing")
         << "'><a href='#team" << i << "'aria-controls='home' role='tab' data-toggle='tab'>"
         << worldCup->getTeam(teamIndex)->getName()
         << "</a></li>";
  }
  file << "</ul>";
}

void PageConstructor::generateTeamsTabContent(ofstream& file) {
  file << "<div class='tab-content'>";
  for (int i = 0; i < 4; ++i) {
    file << "<div role='tabpanel' class='tab-pane "
         << (i == 0 ? "active" : "nothing") << "' id='team" << i << "'> \
           <div class='teams-container'><table class='table table-striped'> \
           <thead> \
           <tr> \
           <th>Player</th> \
           <th>Speed</th> \
           <th>Power</th> \
           <th>Endurance</th> \
           <th>Defense</th> \
           <th>Attack</th> \
           </tr> \
           </thead> \
           <tbody>";

    generateTeamsTabContentRow(file, i);

    file << "</tbody> \
          </table> \
          </div> \
          </div> <!-- END OF TAB -->";
  }
  file << "</div> <!-- END OF TAB CONTENT -->";
}

void PageConstructor::generateTeamsTabContentRow(ofstream& file, int& index) {
  int teamIndex = *(worldCup->getQualifiedTeams() + index);
  for (int i = 0; i < 15; ++i) {
    file << "<tr><td>"
         << worldCup->getTeam(teamIndex)->getPlayer(i)->getName()
         << "</td>"
         << "<td>"
         << worldCup->getTeam(teamIndex)->getPlayer(i)->getSkill("speed")
         << "</td>"
         << "<td>"
         << worldCup->getTeam(teamIndex)->getPlayer(i)->getSkill("power")
         << "</td>"
         << "<td>"
         << worldCup->getTeam(teamIndex)->getPlayer(i)->getSkill("endurance")
         << "</td>"
         << "<td>"
         << worldCup->getTeam(teamIndex)->getPlayer(i)->getSkill("defense")
         << "</td>"
         << "<td>"
         << worldCup->getTeam(teamIndex)->getPlayer(i)->getSkill("attack")
         << "</td></tr>";
  }
}

void PageConstructor::generateFoulsProfile(ofstream& temp) {
  temp << "<div role='tabpanel' class='tab-pane' id='fouls'> \
          <div class='teams-container'><table class='table table-striped'> \
           <thead> \
             <tr> \
               <th>Team</th> \
               <th>Player</th> \
               <th>Time</th> \
             </tr> \
           </thead> \
           <tbody>";

  generateRowsFoulsProfile(temp, 'A');
  generateRowsFoulsProfile(temp, 'B');

  temp << "</tbody> \
          </table> \
          </div> \
          </div> <!-- END OF TAB -->";
}

void PageConstructor::generateGoalsProfile(ofstream& temp) {
  temp << "<div role='tabpanel' class='tab-pane' id='goals'> \
          <div class='teams-container'><table class='table table-striped'> \
           <thead> \
             <tr> \
               <th>Team</th> \
               <th>Player</th> \
               <th>Time</th> \
             </tr> \
           </thead> \
           <tbody>";

  generateRowsGoalsProfile(temp, 'A');
  generateRowsGoalsProfile(temp, 'B');

  temp << "</tbody> \
          </table> \
          </div> \
          </div> <!-- END OF TAB -->";
}
