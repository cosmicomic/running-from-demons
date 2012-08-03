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
    for (mapIt = inventoryMap.begin(); mapIt != inventoryMap.end(); mapIt++) 
    {
        decIt = mapIt;
        if (++decIt == inventoryMap.end()) {
            // do nothing
        } else {
            cout << (*mapIt).second->getName() << ", ";
        }
    }
    if ( mapIt++ == inventoryMap.end()) {
        cout << (*mapIt).second->getName() << ".";
    }
    
    cout << endl << endl << "To examine an item, enter the name of the item.";
    
    string itemName;
    
    while (itemName != "exit") {
        cout << endl;
        cout << endl << ">> "; getline(cin, itemName);
        for (int i = 0; i < itemName.size(); i++) {
            itemName[i] = tolower(itemName[i]);
        }
        if ((itemName == "read letter" || itemName == "open letter") && hasItem("letter")) {
            cout << endl << "\"Hello, troubled soul. I hope I have the right address, and that you're doing well... but I know you're not."
            << " For a while, I have been watching you. Not in a creepy way (but who am I to judge?). It's just that you reminded me "
            << "of myself a few years ago.\n\nI do not mean to make assumptions about or pry into your life. I just want to tell you "
            << "that you musn\'nt be too hard on yourself. Please try to remember the things that colour your life and keep them "
            << "close to you.\n\nYou can\'t fight the demons on your own. You\'ll need to find someone to help you at some "
            << "point. Please, please, please be kind to yourself."
            << "\n\n-- a stranger";
        } else if (itemName.size() == 0) {
            // do nothing
        } else if (itemName == "exit") {
            cout << endl << "You have exited the inventory menu.";
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
    inventoryMap.insert( pair<string, Item*>(item->getName(), item) );
}

void Player::addToInventory(Key *key) {
    inventoryMap.insert( pair<string, Key*>(key->getName(), key) );
    keys.push_back(key);
}

void Player::look() {
    cout << endl; displayLocationName();
    cout << endl << endl;
    displayLocationDescription();
    
    if (location->getName() == "Tower") {
        if (!hasItem("crowbar")) {
            cout << " A crowbar leans against the wall to your left; "
            << "it's probably there to administer percussive maintenance in case the lift breaks down or something.";
        }
    } else if (location->getName() == "Hill") {
        if (!hasItem("telescope")) {
            cout << " There is a silver telescope mounted on a tripod at the peak of the hill, though the sky is devoid of stars.";
        } else {
            cout << " There is an empty tripod standing at the peak of the hill.";
        }
        if (!hasItem("battery")) {
            cout << " At the foot of the tripod is a black container.";
        }
    } else if (location->getName() == "Shop") {
        if (!hasItem("lab")) {
            cout << endl << " The only thing here in decent condition is a rectangular electrical device about the size of a board game box.";
        }
    } else if (location->getName() == "Street - Southwest") {
        switch (keys.size()) {
            case 0:
            case 1:
                cout << endl << endl << "There is a writhing, shadowy mass enveloping the train station.";
                break;
            case 2:
            case 3:
                cout << endl << endl << "There is a sizeable crowd of shadows surrounding the train station.";
                break;
            case 4:
                cout << endl << endl << "There are a few stray shadows patrolling the outside of the train station.";
                break;
            case 5:
                cout << endl << endl << "The train station appears to be completely clear of any threatening entities.";
                break;
        }
    }
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

string Player::getInventoryString() {
    string inventoryString;
    for (mapIt = inventoryMap.begin();
         mapIt != inventoryMap.end();
         mapIt++) 
    {
        inventoryString.append((*mapIt).second->getName());
        inventoryString.append(" ");
    }
    return inventoryString;
}

void Player::removeFromInventory(Item *item) {
    inventoryMap.erase(item->getName());
}
    
int Player::getKeySize() {
    return keys.size();
}
