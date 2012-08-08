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
        map<string, Item*> inventoryMap;
        map<string, Item*>::iterator mapIt;
        vector<Key*> keys;
        vector<Item*> inventory;
        vector<Item*>::iterator vecIt;
        bool immobilized;
        bool hasKey;
    public:
        Player(Location *newLocation, int newHealth);
        int getHealth();
        int setHealth(int newHealth);
        int getKeySize();
        Location* getLocation();
        void setLocation(Location *newLocation);
        void setLocationNoDescrip(Location *newLocation);
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
        string getInventoryString();
        void removeFromInventory(Item *item);
        //template<class Type> void setVar(Type a, Type b);
};

/*template<class Type> void Player::setVar(Type a, Type b) {
    a = b;
}*/

#endif
        
        
