// Class automatically generated by Dev-C++ New Class wizard

#include "gamestate.h" // class's header file
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#define STARTING_HEALTH 4 // must be even number
using namespace std;

// class constructor
GameState::GameState(bool newGame)
{
    if (newGame) {
        int genOnce = 0;
        int notice = 0;
        int giveHint = 0;
        int health = STARTING_HEALTH;
        bool demonPresent = false;
        bool videotapeOn = false;
        bool pathOpen = false;
        bool batteryIn = false;
        bool labOn = false;
        bool doorOpen = false;
        bool childOnce = false;
        bool pastTurnstile = false;
        bool descripOnce = true;
        bool iOnce = true;
    } else {
	   load();
    }
}

void GameState::save() 
{
    ofstream saveFile;
    saveFile.open("savefile.txt");
    saveFile << location << "#" << inventory << "#" << genOnce << "#" << notice << "#" << giveHint << "#" << health << "#" << demonPresent << "#" << videotapeOn << "#" << pathOpen << "#" <<
    batteryIn << "#" << labOn << "#" << doorOpen << "#" << childOnce << "#" << pastTurnstile << "#" << descripOnce << "#" << iOnce;
    saveFile.close();
}

void GameState::load() 
{
    char file_input[100];
    
    ifstream saveFile;
    saveFile.open("savefile.txt");
    
    saveFile.getline(file_input, 30, '#');
    location = file_input;
    
    saveFile.getline(file_input, 100, '#');
    inventory = file_input;
    
    saveFile.getline(file_input, 1, '#');
    genOnce = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    notice = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    giveHint = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    health = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    demonPresent = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    videotapeOn = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    pathOpen = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    batteryIn = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    labOn = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    doorOpen = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    childOnce = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    pastTurnstile = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    descripOnce = atoi(file_input);
    
    saveFile.getline(file_input, 1, '#');
    iOnce = atoi(file_input);
    
    saveFile.close();
}

string GameState::getLocation() {
    return location;
}

string GameState::getInventory() {
    return inventory;
}
