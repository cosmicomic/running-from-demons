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
        void interactDistraction(Player *player, Location *bedroom);
        void interactSelfLoathing(Player *player, Location *location);
    public:
        Demon(string newType, string newDescription, Location *newLocation);
        void interactDread(Player *player);
        void interact(Player *player, Location *street, Location *bedroom);
        string getType();
};

#endif
