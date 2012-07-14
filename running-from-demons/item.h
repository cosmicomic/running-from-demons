#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "player.h"
using namespace std;

class Location;
class Player;

class Item {
    protected:
        string name;
        string description;
        Location *location;
    public:
        Item(string newName, string newDescription, Location *newLocation);
        string getName();
        string getDescription();
};

#endif
        
