#include "player.h"
#include "location.h"
#include "item.h"
#include "key.h"
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <cctype>
using namespace std;

Player::Player(Location *newLocation, int newHealth) {
    location = newLocation;
    health = newHealth;
}
    
int Player::getHealth() {
    return health;
}

int Player::setHealth(int newHealth) {
    health = newHealth;
}

void Player::displayInventory() {
    cout << endl << "Inventory: ";
    for (it = inventory.begin();
         it < inventory.end() - 1;
         it++) 
    {
        cout << (*it)->getName() << ", ";
    }
    if ( it == inventory.end() - 1 ) {
        cout << (*it)->getName() << ".";
    }
    
    string itemName;
    
    while (true) {
        cout << endl;
        cout << endl << ">> "; getline(cin, itemName);
        for (int i = 0; i < itemName.size(); i++) {
            itemName[i] = tolower(itemName[i]);
        }
        if (itemName == "exit" || itemName.size() == 0) {
            break;
        } else {
            if (hasItem(itemName)) {
                cout << endl << (inventoryMap.find(itemName)->second)->getDescription();
            } else {
                cout << endl << "You don't have a " << itemName << ".";
            }
            
        }
    }
}

void Player::displayLocationName() {
    cout << location->getName();
}

void Player::displayLocationDescription() {
    cout << location->getDescription();
}

bool Player::getImmobilized() {
    return immobilized;
}

Location* Player::getLocation() {
    return location;
}

void Player::setLocation(Location *newLocation) {
    location = newLocation;
    look();
}

void Player::setLocationNoDescrip(Location *newLocation) {
    location = newLocation;
}

void Player::setImmobilized(bool state) {
    immobilized = state;
}

void Player::addToInventory(Item *item) {
    inventory.push_back(item);
}

void Player::addToInventory(Key *key) {
    inventory.push_back(key);
    inventoryMap.insert( pair<string, Key*>(key->getName(), key) );
}

void Player::look() {
    cout << endl; displayLocationName();
    cout << endl << endl;
    displayLocationDescription();
}

bool Player::getHasKey() {
    return hasKey;
}

void Player::setHasKey(bool state) {
    hasKey = state;
}

bool Player::hasItem(string itemName) {
    return inventoryMap.count(itemName) != 0;
}
                
                
