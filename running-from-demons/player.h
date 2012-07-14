#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include <string>
using namespace std;

class Location;
class Item;
class Key;

class Player {
    private:
        Location *location;
        int health;
        vector<Item*> inventory;
        vector<Item*>::iterator it;
        map<string, Item*> inventoryMap;
        map<string, Item*>::iterator mapIt;
        bool immobilized;
        bool hasKey;
    public:
        Player(Location *newLocation, int newHealth);
        int getHealth();
        int setHealth(int newHealth);
        Location* getLocation();
        void setLocation(Location *newLocation);
        bool getImmobilized();
        void setImmobilized(bool state);
        bool getHasKey();
        void setHasKey(bool state);
        void displayInventory();
        void displayLocationName();
        void displayLocationDescription();
        void addToInventory(Item *item);
        void addToInventory(Key *key);
        void look();
        bool hasItem(string itemName);
        //template<class Type> void setVar(Type a, Type b);
};

/*template<class Type> void Player::setVar(Type a, Type b) {
    a = b;
}*/

#endif
        
        
