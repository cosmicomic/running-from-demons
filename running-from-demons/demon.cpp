#include <string>
#include <iostream>
#include "location.h"
#include "demon.h"
#define STARTING_HEALTH 4 // must be even number

Demon::Demon(string newType, string newDescription, Location *newLocation) {
    type = newType;
    description = newDescription;
    location = newLocation;
}

void Demon::interact(Player *player, Location *location) {
    if (type == "self-loathing"){
        interactSelfLoathing(player, location);
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
    cout << endl << "It's so heavy; you can't get up.";
    player->setImmobilized(true);
}

void Demon::interactRegret(Player *player) {
    cout << endl << "message";
    player->setHealth(player->getHealth() - STARTING_HEALTH/2);
}

void Demon::interactDespair(Player *player) {
    cout << endl << "The demon raises its dusky arm; its fingernails look unbelievably long, spindly, and sharp."
    << "Your mind goes blank when you used to feel apprehensive. But no matter how hard you try to numb yourself beforehand, the pain is just as excruciating.";
    cin.get();
    cout << endl << endl << "First, it slashes at your arm. Then your stomach. Then your thigh. Blood blossoms out and drips to the ground. "
    << "The pain emanates from the wounds, like shock waves from an earthquake. Like you're burning from the inside. Like a hundred needles tearing at your flesh. "
    << "You try to pull away, but the demon reels you back in, gripping and yanking your hair until you can feel a patch of your scalp detach from your skull. "
    << "It kicks you in the stomach with a clawed foot. Blood and acid pour out, searing the exposed flesh. The tattered hole in your stomach twitches as convulsions of pain overtake you. "
    << "The demon kicks you again in the knee, cleaving through bone.";
    cin.get();
    cout << endl << endl << "The demon is satisfied. It leaves you collapsed on the ground, a writhing, agonized wretch, hardly able to muster the effort to groan in pain.";
    cin.get();
    player->setHealth(player->getHealth() - STARTING_HEALTH/2);
}

void Demon::interactIsolation(Player *player) {
    cout << endl << "message";
    player->setHealth(player->getHealth() - STARTING_HEALTH/2);
}

void Demon::interactDistraction(Player *player) {
    cout << endl << "message";
    player->setHealth(player->getHealth() - STARTING_HEALTH/2);
}

void Demon::interactSelfLoathing(Player *player, Location *location) {
    cout << endl << "The demon slips a knife in your hand. It grips your arm and forces it towards you.";
    cin.get();
    cout << endl << endl << "You carve a thick, red line across your stomach. Green and red fluids, as well as bile, leaks out. "
    << "Soon you are gutting yourself by your own volition. The demon stands back and watches you conduct your own vivisection. "
    << "You find yourself grinning and screaming in agony and horror simultaneously.";
    cin.get();
    cout << endl << endl << "You lose consciousness and wake up sprawled on the cold, cracked asphalt of the street in front of your apartment building.";
    cin.get();
    cout << endl << endl << "Peeking under your shirt, you find that the cuts have been sloppily stitched up.";
    player->setHealth(player->getHealth() - STARTING_HEALTH/2);
    player->setLocationNoDescrip(location);
    player->setImmobilized(true);
}

string Demon::getType() {
    return type;
}
