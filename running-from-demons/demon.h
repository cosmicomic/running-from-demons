#ifndef DEMON_H
#define DEMON_H

#include <string>
#include "location.h"
#include "player.h"
using namespace std;

class Location;

class Demon {
    private:
        string type;
        string description;
        Location *location;
        void interactRegret(Player *player);
        void interactDespair(Player *player);
        void interactIsolation(Player *player);
        void interactDistraction(Player *player);
        void interactSelfLoathing(Player *player);
    public:
        Demon(string newType, string newDescription, Location *newLocation);
        void interactDread(Player *player);
        void interact(Player *player);
        string getType();
};

#endif