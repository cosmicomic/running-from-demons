#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "key.h"
#include "exit.h"
#include "item.h"
#include "demon.h"
#include "location.h"
#define STARTING_HEALTH 4 // must be even number
using namespace std;

// Declare various functions
void getUserInput(string& user_input);
int probabilityGenerator(int range);
bool demonInArea(int chance);
Demon* getDemon();
void demonEncounter(string& user_input, int& notice, int& genOnce, Player *mPlayer, Location *mStreet, int prob);
void resetEncounterData(int& notice, int& genOnce, bool& demonPresent);

// Declare maps
map<string, Item*> outItems;
map<string, Key*> outKeys;
vector<Demon*> demons;

int main() { 
    // Initialize locations
    ifstream location("location.txt");
    char name_input[20];
    char description_input[1000];
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    
    Location street(name_input, description_input);
    
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    Location bedroom(name_input, description_input);
    
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    Location library(name_input, description_input);
    
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    Location park(name_input, description_input);
    
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    Location subway(name_input, description_input);
    
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    Location road(name_input, description_input);
    
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    Location hallway(name_input, description_input);
    
    location.getline(name_input, 20, '#');
    location.getline(description_input, 1000, '#');
    Location lobby(name_input, description_input);
    
    Location theatre("Theatre", "Description");
    
    Location streetWest("Street - West", "Description");
    
    Location hill("Hill", "Description");
    
    Location shop("Shop", "Description");
    
    //Intialize pointers to locations
    Location *mStreet = &street; // 1/4 chance of encounter
    Location *mBedroom = &bedroom;
    Location *mLibrary = &library; // 1/2 chance of encounter
    Location *mPark = &park; // 2/3 chance of encounter
    Location *mSubway = &subway;
    Location *mRoad = &road;
    Location *mHallway = &hallway;
    Location *mLobby = &lobby; // 1/10 chance of encounter
    Location *mTheatre = &theatre;// 4/5 chance of encounter
    Location *mStreetWest = &streetWest; // 1/3 chance of encounter
    Location *mHill = &hill;
    
    //Initialize exits
    Exit bedroomToHallway(1, mHallway);
    Exit *mBedroomToHallway = &bedroomToHallway;
    
    Exit hallwayToLobby(1, mLobby);
    Exit *mHallwayToLobby = &hallwayToLobby;
       
    //Initialize player character
    Player player(mBedroom, STARTING_HEALTH);
    player.setHasKey(false);
    
    //Initialize pointer to player character
    Player *mPlayer = &player;
    
    //Initialize keys
    Key paperHeart("paper heart", "An origami heart, folded from red paper.", mBedroom);
    Key *mPaperHeart = &paperHeart;
    mPlayer->addToInventory(mPaperHeart);
    
    Key telescope("telescope", "Description", mStreet);
    Key *mTelescope = &telescope;
    outKeys.insert( pair<string, Key*>(mTelescope->getName(), mTelescope) );
    
    Key lab("lab", "Description", mBedroom);
    Key *mLab = &lab;
    outKeys.insert( pair<string, Key*>(mLab->getName(), mLab) );
    
    Key letter("letter", "Description", mLobby);
    Key *mLetter = &letter;
    outKeys.insert( pair<string, Key*>(mLetter->getName(), mLetter) );
    
    Key joke("joke", "Description", mPark);
    Key *mJoke = &joke;
    outKeys.insert( pair<string, Key*>(mJoke->getName(), mJoke) );
    
    Key daisyChain("daisy chain", "Description", mPark);
    Key *mDaisyChain = &daisyChain;
    outKeys.insert( pair<string, Key*>(mDaisyChain->getName(), mDaisyChain) );
    
    Key videotape("videotape", "Description", mTheatre);
    Key *mVideotape = &videotape;
    outKeys.insert( pair<string, Key*>(mVideotape->getName(), mVideotape) );
    
    // Intialize non-key items
    Item crowbar("crowbar", "Description", mStreet);
    Item *mCrowbar = &crowbar;
    outItems.insert( pair<string, Item*>(mCrowbar->getName(), mCrowbar) );    
    
    // Intialize misc stuff
    string user_input;
    int jokeOnce = 0;
    int genOnce = 0;
    int notice = 0;
    srand(time(NULL));
    bool demonPresent = false;
    
    //Initialize demons
    Demon dreadDemon("dread", "description", mBedroom);
    Demon *mDreadDemon = &dreadDemon;
    demons.push_back(mDreadDemon);
    
    Demon selfLoathingDemon("self-loathing", "description", mPark);
    Demon *mSelfLoathingDemon = &selfLoathingDemon;
    demons.push_back(mSelfLoathingDemon);
    
    Demon despairDemon("despair", "description", mPark);
    Demon *mDespairDemon = &despairDemon;
    demons.push_back(mDespairDemon);
    
    // declare demon encounter probabilities
    const int
    streetProb = 25,
    altStreetProb = 33,
    libraryProb = 50,
    parkProb = 66,
    lobbyProb = 10,
    theatreProb = 80;
    
    // Intro
    ifstream intro("intro.txt");
    char intro_input[1000];
    
    while (!intro.eof()) {
        intro.getline(intro_input, 1000, '#');
        cout << endl << intro_input;
        cin.get();
    }
    
    //Intro level
    mDreadDemon->interactDread(mPlayer);
    while (mPlayer->getImmobilized()) {
        if (user_input == "inventory") {
            mPlayer->displayInventory();
            demons.erase(demons.begin());
            mPlayer->setImmobilized(false);
            cin.get();
            cout << endl << "You are no longer immobilized.";
            cin.get();
            cout << endl << endl << "* * * * *" << endl << endl
            << "Congrats! You have finished the introductory level."
            << endl << "A few tips:" << endl << "* To look at your surroundings, enter the command \"LOOK\"."
            << endl << "* To access your inventory, enter the command, \"INVENTORY\"."
            << endl << "    To access an item in your inventory, enter the name of the item."
            << endl << "    To leave the inventory menu, enter \"EXIT\"," 
            << endl << "    or simply press ENTER without typing any commands."
            << endl << "* Keep an eye out for exits. To use an exit, enter its direction name."
            << endl << "    For example, to take an exit leading to the south, type \"SOUTH\"."
            << endl << "* To examine something, enter the \"EXAMINE\", followed by the object name."
            << endl << "    For example, to examine a flower, enter \"EXAMINE FLOWER\"."
            << endl << "* For your own sanity's sake, avoid using definite articles in your commands."
            << endl << "* To check your health, enter the command \"HEALTH\"."
            << endl << endl << "Good luck!"
            << endl << endl << "* * * * *";
            break;
        }
        
        getUserInput(user_input);
        
        if (user_input.size() == 0) {
            // do nothing
        }
        if (user_input != "inventory" && user_input.size() > 0) {
            cout << endl << "It's no use. You can't get up." << endl;
        }
    }
    
    mPlayer->setImmobilized(true);
    
    // Main loop
    while(mPlayer->getLocation() != mSubway && mPlayer->getHealth() != 0) {  
        while (mPlayer->getLocation() == mBedroom && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            
            if (user_input == "look") {
                mPlayer->look();
            } else if (user_input == "inventory") {
                mPlayer->displayInventory();
            } else if (user_input == "health") {
                cout << endl << "Health: " << mPlayer->getHealth();
            } else if (user_input == "break") {
                break;
            } else if (user_input == "get up" && mPlayer->getImmobilized()) {
                mPlayer->setImmobilized(false);
                cout << endl << "You get up from the bed.";
            } else if (user_input == "get up" && !mPlayer->getImmobilized()) {
                cout << endl << "The effort of trying to overcome the physical impossibility of getting up from bed twice"
                << " nearly kills you.";
            } else if (user_input == "north" && !mPlayer->getImmobilized()) {
                mPlayer->setLocation(mBedroomToHallway->getLeadsTo());
                break;
            } else if (user_input == "north" && mPlayer->getImmobilized()) {
                cout << endl << "You can't really leave the room if you're still in bed, can you?";
            } else if (user_input == "examine bed") {
                cout << endl << "The bed is comprised of some rumpled sheets and a duvet on a springy mattress, set on a metal frame.";
                cin.get();
                cout << endl << "You know that if you fall asleep in this bed, it will be forever.";
                cin.get();
                cout << endl << "You nearly did fall asleep, but as you were drifting off, you remembered there was a paper heart in your back pocket.";
                cout << "You knew that if you did fall asleep, you'd crush the heart. That's when you snapped awake, only to find that grinning demon on your chest.";
            } else if (user_input == "examine chair") {
                cout << endl << "A simple wooden chair.";
            } else if (user_input == "examine desk" || user_input == "examine the desk") {
                cout << endl << "A simple wooden desk.";
            } else if (user_input == "examine drawer") {
                cout << endl << "A small, sturdy chest of drawers, made from oak wood. There are two drawers.";
            } else if (user_input == "open top drawer" || user_input == "look in top drawer" || user_input == "examine top drawer") {
                cout << endl << "The top drawer contains some socks.";
            } else if (user_input == "take socks") {
                cout << endl << "The socks are glued firmly to the bottom of the drawer. There's no way you could pry them off.";
            } else if (user_input == "bash drawer open with hammer") {
                cout << endl << "You haven't got a hammer, silly.";
            } else if (user_input == "open bottom drawer" || user_input == "look in bottom drawer" || user_input == "examine bottom drawer") {
                cout << endl << "It's jammed. Maybe you can open it if you find a crowbar or something like that...?";
            } else if (user_input.size() == 0) {
                // do nothing
            } else if (user_input == "inventory") {
                mPlayer->displayInventory();
            } else {
                cout << endl << "Sorry, I didn't understand that.";
            }
        }
        
        while (mPlayer->getLocation() == mHallway && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            if (user_input == "look") {
                mPlayer->look();
            } else if (user_input == "inventory") {
                mPlayer->displayInventory();
            } else if (user_input == "health") {
                cout << endl << "Health: " << mPlayer->getHealth();
            } else if (user_input == "east") {
                mPlayer->setLocation(mHallwayToLobby->getLeadsTo());
            } else if (user_input == "south") {
                mPlayer->setLocation(mBedroom);
            } else if (user_input == "look out window" || user_input == "examine window") {
                cout << endl << "You can get a pretty good view of the city from this window.";
                cin.get();
                // some control structure here, dependent on number of keys
                cout << endl << "There are a lot of apartment buildings along the street below. "
                << "You can see a library, a park, a movie theatre, and subway station in the distance. "
                << "There is a writhing, shadowy mass enveloping the subway station. "
                << endl << endl << "Very far away, you can just about make out a wide, cobblestone road. "
                << "However, there is an unscalable barbed wire fence lining its edges.";
            } else if (user_input.size() == 0) {
                // do nothing
            } else {
                cout << endl << "Sorry, I didn't understand that.";
            }
        }
        
        while (mPlayer->getLocation() == mLobby && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(lobbyProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            if (user_input == "look") {
                mPlayer->look();
            } else if (user_input == "inventory") {
                mPlayer->displayInventory();
            } else if (user_input == "health") {
                cout << endl << "Health: " << mPlayer->getHealth();
            } else if (user_input == "west") {
                resetEncounterData(notice, genOnce, demonPresent);
                mPlayer->setLocation(mStreet);
            } else if (user_input == "south") {
                resetEncounterData(notice, genOnce, demonPresent);
                mPlayer->setLocation(mHallway);
            } else if (user_input == "examine mailboxes") {
                cout << endl << "On closer inspection, all of the mailboxes, save one,"
                << " are not mailboxes at all, but painted squares in the wall.";
            } else if ((user_input == "examine real mailbox" || user_input == "examine true mailbox") && !mPlayer->getHasKey()) {
                cout << endl << "It's locked. You'll need to find a key, I'm afraid.";
                cin.get();
                cout << endl << "Well, what did you expect? This is a text adventure game, after all.";
            } else if ((user_input == "examine real mailbox" || user_input == "examine true mailbox") && mPlayer->getHasKey()) {
                cout << endl << "It's locked... and you've got a key! What are you waiting for? Open the blasted thing!";
            } else if ((user_input == "open real mailbox" || user_input == "open true mailbox") && mPlayer->getHasKey()) {
                cout << endl << "The mailbox contains a parcel in rather poor condition; the paper is wrinkled, and ripped at the edges.";
                cin.get();
                cout << endl << endl << "You open the parcel; it contains a videotape.";
                cout << endl << endl << "The videotape has been added to your inventory.";
                mPlayer->addToInventory(mVideotape);
                outKeys.erase("videotape");
            } else if ((user_input == "open real mailbox" || user_input == "open true mailbox") && !mPlayer->getHasKey()) {
                cout << endl << "You need the key.";
            } else if (user_input.size() == 0) {
                // do nothing
            } else if (user_input == "hide" && !demonPresent) {
                cout << endl << "You cower for a little while until you realize there's nothing to be hiding from, after which "
                << "you slap yourself for being so silly.";
            } else if (user_input == "hide" && notice > 0) {
                // allow following if-statement to handle this
            } else if (user_input == "hide" && demonPresent && notice == 0) {
                cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                continue;
            } else if ((user_input == "fight demon" || user_input == "attack demon" || user_input == "kill demon" || user_input == "punch demon") && demonPresent) {
                // allow demonEncounter function to handle this
            } else if ((user_input == "fight demon" || user_input == "attack demon" || user_input == "kill demon" || user_input == "punch demon") && !demonPresent) {
                cout << endl << "You punch the air -- a wholly futile action.";
            } else if (user_input == "run") {
                cout << endl << "Run where? Specify a direction.";
            } else {
                cout << endl << "Sorry, I didn't understand that.";
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, lobbyProb);
            }
        }
        
        while (mPlayer->getLocation() == mStreet && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(streetProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            if (user_input == "look") {
                mPlayer->look();
            } else if (user_input == "inventory") {
                mPlayer->displayInventory();
            } else if (user_input == "health") {
                cout << endl << "Health: " << mPlayer->getHealth();
            } else if (user_input == "east") {
                resetEncounterData(notice, genOnce, demonPresent);
                mPlayer->setLocation(mPark);
            } else if (user_input == "west") {
                resetEncounterData(notice, genOnce, demonPresent);
                mPlayer->setLocation(mStreetWest);
            } else if (user_input == "south") {
                resetEncounterData(notice, genOnce, demonPresent);
                mPlayer->setLocation(mLobby);
            } else if (user_input == "enter apartment building") {
                cout << endl << "It's locked. They're all locked.";
            } else if (user_input.size() == 0) {
                // do nothing
            } else {
                cout << endl << "Sorry, I didn't understand that.";
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, streetProb);
            }
        }
        
        while (mPlayer->getLocation() == mPark && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(parkProb);
                genOnce++;
            }
            
            if (jokeOnce == 0) {
                cin.get();
                cout << endl << endl << "As you walk in, a red balloon floats down from the grey sky, and lands at your feet."
                << endl << "There is a small piece of lined paper tied to it.";
                cin.get();
                cout << endl << "You read the note...";
                cin.get();
                cout << endl << "It's the funniest joke you've ever read! You burst out laughing for a full twenty seconds. "
                << "You put it in your pocket for safekeeping.";
                mPlayer->addToInventory(mJoke);
                jokeOnce++;
            }
            
            getUserInput(user_input);
            if (user_input == "look") {
                mPlayer->look();
            } else if (user_input == "health") {
                cout << endl << "Health: " << mPlayer->getHealth();
            } else if (user_input == "inventory") {
                mPlayer->displayInventory();
            } else if (user_input == "west") {
                resetEncounterData(notice, genOnce, demonPresent);
                mPlayer->setLocation(mStreet);
            } else if (user_input == "pick flower") {
                cout << endl << "You pick a small, red flower.";
                cin.get();
                cout << endl << "It crumbles to ash in your hand.";
            } else if (user_input == "climb tree") {
                cout << endl << "The bark is strangely slippery. You fail to gain more than a few feet before falling.";
            } else if (user_input.size() == 0) {
                // do nothing
            } else {
                cout << endl << "Sorry, I didn't understand that.";
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, parkProb);
            }
        }
        
        while (mPlayer->getLocation() == mStreetWest && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(altStreetProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            if (user_input == "look") {
                mPlayer->look();
            } else if (user_input == "health") {
                cout << endl << "Health: " << mPlayer->getHealth();
            } else if (user_input == "inventory") {
                mPlayer->displayInventory();
            } else if (user_input == "east") {
                resetEncounterData(notice, genOnce, demonPresent);
                mPlayer->setLocation(mStreet);
            } else if (user_input.size() == 0) {
                // do nothing
            } else {
                cout << endl << "Sorry, I didn't understand that.";
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, altStreetProb);
            }
        }
    }
    
    if (mPlayer->getHealth() == 0) {
        cin.get();
        cout << endl << endl << "...";
        cin.get();
        cout << endl << endl << "An external force overtakes you. You begin walking towards your apartment building. "
        << "As you approach the building, the world grows darker. The city crawls with multitudes of demons. "
        << "Although you find it disturbing that you are being controlled, you surrender yourself to the mysterious force and resign yourself to what you "
        << "strongly believe is your inexorable fate. You float like a ghost across the lobby, up the stairs, down the hallway... you reach your room.";
        cin.get();
        cout << endl << endl << "You pause in your progress towards the bed, not due to reluctance, but because you are suddenly gripped with an unexplainable impulse to "
        << "touch everything in the room. You run your fingers along the desk. You stroke the back of the chair, noting that it's shaped like a madeleine. ";
        cin.get();
        cout << endl << endl << "You fail to find solidity in these objects. The rumpled bedsheets beckon you to lose yourself in their myriad creases and folds.";
        cin.get();
        cout << endl << endl << "You bury your own grave, embalming yourself in the sheets, interring yourself in the duvet.";
        cin.get();
        cout << endl << endl << "The demons appear round your bed. The last sight you see is that of their grinning faces, and you close your eyes in resignation, convinced that this is what you must do.";
        cin.get();
        cout << endl << endl << "Thus, you fall away.";
    }
    
    cin.ignore();
    cin.get();
    
    return 0;
}

void getUserInput(string& user_input) {
    cout << endl << endl << ">> ";
    getline(cin, user_input);
    for (int i = 0; i < user_input.size(); i++) {
        user_input[i] = tolower(user_input[i]);
    }
}

int probabilityGenerator(int range) {
    return rand() % range;
}
    
bool demonInArea(int chance) {
    int n = probabilityGenerator(100) + 1;
    
    if (n < chance) {
        cout << endl << endl << "There is a demon in the area.";
        return true;
    } else {
        return false;
    }
}

Demon* getDemon() {
    int d = probabilityGenerator(demons.size());
    return demons[d];
}

void demonEncounter(string& user_input, int& notice, int& genOnce, Player *mPlayer, Location *mStreet, int prob) {
    if (user_input == "hide" && notice > 0) {
            if (notice == 1) {
                int n = probabilityGenerator(100);
                if (n < 90) {
                    cout << endl << "...";
                    cin.get();
                    cout << endl << "The demon shrugs and walks away.";
                    notice = 0;
                } else {
                    cout << endl << "...";
                    cin.get();
                    cout << endl << "The demon is staring right at you now.";
                    notice++;
                }
            } else if (notice == 2) {
                int n = probabilityGenerator(100);
                if (n < 70) {
                    cout << endl << "...";
                    cin.get();
                    cout << endl << "The demon shrugs and walks away.";
                    notice = 0;
                } else {
                    cout << endl << "...";
                    cin.get();
                    cout << endl << "The demon approaches.";
                    notice++;
                }
            } else if (notice == 3) {
                cout << endl << "No use now; the demon is attacking.";
            } 
        } else if (user_input == "fight demon" || user_input == "attack demon" || user_input == "kill demon" || user_input == "punch demon") {
            cout << endl << "Your fist passes uselessly through the demon's shadowy, incorporeal form. The demon emits a metallic chuckle.";
            cout << endl << "...";
            cin.get();
            (getDemon())->interact(mPlayer, mStreet);
            notice = 0;
            genOnce = 0;
            return;
        } else {
            int p = probabilityGenerator(100);
            if (p < prob && notice == 0) {
                notice++;
            } else if (notice == 1) {
                notice++;
            } else if (notice == 2) {
                cout << endl << "The demon approaches.";
                notice++;
            }
        }
        
        if (!(user_input == "hide") || notice == 3) {
            switch (notice) {
                case 0:
                    break;
                case 1:
                    cout << endl << endl << "The demon stops, and slowly turns its head in your direction.";
                    break;
                case 2:
                    cout << endl << endl << "The demon has noticed you.";
                    break;
                case 3:
                    cout << endl << "...";
                    cin.get();
                    (getDemon())->interact(mPlayer, mStreet);
                    notice = 0;
                    genOnce = 0;
                    return;
            }
        }
}

void resetEncounterData(int& notice, int& genOnce, bool& demonPresent) {
    notice = 0;
    genOnce = 0;
    demonPresent = false;
}
