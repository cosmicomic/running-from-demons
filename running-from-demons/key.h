#ifndef KEY_H
#define KEY_H

#include <string>
#include "location.h"
#include "item.h"
using namespace std;

class Location;
class Player;

class Key : public Item {
    private:
        bool found;
        bool valid;
    public:
        Key (string newName, string newDescription, Location *newLocation);
        void setFound(bool state);
        void setValid(bool state);
        bool isFound();
        bool isValid();
};

#endif
        


