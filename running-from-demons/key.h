#ifndef KEY_H
#define KEY_H

#include <string>
#include "location.h"
#include "item.h"
using namespace std;

class Location;
class Player;

class Key : public Item {
    public:
        Key (string newName, string newDescription);
};

#endif
        


