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

void Demon::interact(Player *player, Location *street, Location *bedroom) {
    if (type == "self-loathing"){
        interactSelfLoathing(player, location);
    } else if (type == "despair") {
        interactDespair(player);
    } else if (type == "distraction") {
        interactDistraction(player, bedroom);
    } else if (type == "regret") {
        interactRegret(player);
    }
}
            
void Demon::interactDread(Player *player) {
    cout << endl << "It's so heavy; you can't get up.";
    player->setImmobilized(true);
}

void Demon::interactRegret(Player *player) {
    cout << endl << "The demon casually raises its clawed hand and swipes it at your leg, leaving a deep, painful, throbbing gash. You collapse "
    << "to the ground in pain and soon lose consciousness.";
    cin.get();
    cout << endl << "..."; 
    cin.get();
    cout << endl << "You wake up bound to a chair in the theatre. "
    << "Your eyelids are held open by a crude metal instrument."; cin.get();
    cout << endl << endl << "The film begins. As the images flash before your eyes, you are seized with an overwhelming sense of nausea. You feel sick to your stomach. "
    << "You vomit a thin, yellow substance on yourself. You oscillate between feeling icy cold and unbearably hot. You tremble uncontrollably. You desperately "
    << "want to close your eyes and shut out the horrible images, but are prevented by the cold metal claws gripping your eyelids open. Your eyes feel as if "
    << "they are shrivelling up. You scream in pain and horror until you once again lose consciousness."; cin.get();
    cout << endl << "You wake up, your joints aching, on the cold floor. Strangely, "
    << "the vomit that was on your shirt is now gone. Was it all just a dream? The memory of the pain is so vivid, you can almost still feel it. Certainly, you feel "
    << "much weaker now.";
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

void Demon::interactDistraction(Player *player, Location *bedroom) {
    cout << endl << "Unlike most demons, this one seems a lot less motivated to cause you unspeakable pain. Instead, it calmly walks towards you, and pokes you on the shoulder."
    << " Suddenly, it feels as if you have been swept up by a whirlwind. Or, more fittingly, a black hole; you feel like you're being squeezed into an impossibly small space."
    << " Soon enough, the tension releases, and you are plopped onto the beige carpet of your bedroom.";
    player->setLocation(bedroom);
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
}

string Demon::getType() {
    return type;
}
