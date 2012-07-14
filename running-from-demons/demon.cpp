#include <string>
#include <iostream>
#include "location.h"
#include "demon.h"

Demon::Demon(string newType, string newDescription, Location *newLocation) {
    type = newType;
    description = newDescription;
    location = newLocation;
}

void Demon::interact(Player *player) {
    if (type == "self-loathing"){
        interactSelfLoathing(player);
    } else if (type == "despair") {
        interactDespair(player);
    } else if (type == "isolation") {
        interactIsolation(player);
    } else if (type == "distraction") {
        interactDistraction(player);
    } else if (type == "regret") {
        interactRegret(player);
    }
}
            

void Demon::interactDread(Player *player) {
    cout << "It's so heavy; you can't get up.";
    player->setImmobilized(true);
}

void Demon::interactRegret(Player *player) {
    cout << "message";
    player->setHealth(50);
}

void Demon::interactDespair(Player *player) {
    cout << "message";
    player->setHealth(50);
}

void Demon::interactIsolation(Player *player) {
    cout << "message";
    player->setHealth(50);
}

void Demon::interactDistraction(Player *player) {
    cout << "message";
    player->setHealth(50);
}

void Demon::interactSelfLoathing(Player *player) {
    cout << "message";
    player->setHealth(50);
}

string Demon::getType() {
    return type;
}
