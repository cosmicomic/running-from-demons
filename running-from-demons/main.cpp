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
void demonEncounter(string& user_input, int& notice, int& genOnce, Player *mPlayer, Location *mStreet);
void resetEncounterData(int& notice, int& genOnce, bool& demonPresent);
bool commonActions(string user_input, bool demonPresent, Player *player, int notice);
void help(bool first);

// Declare maps
map<string, Item*> outItems;
map<string, Key*> outKeys;
vector<Demon*> demons;

int main() { 
    // Initialize locations
    ifstream location("location.txt");
    char name_input[30];
    char description_input[1000];
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location street(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location bedroom(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location library(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location park(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location subway(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location road(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location hallway(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location lobby(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location theatre(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location streetWest(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location hill(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location shop(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location plaza(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location tower(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location streetNorth(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location streetSouthwest(name_input, description_input);
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location garden(name_input, description_input);
    
    Location projectorRoom("Projector room", "Description");
    
    //Intialize pointers to locations
    Location *mStreet = &street;
    Location *mBedroom = &bedroom;
    Location *mLibrary = &library;
    Location *mPark = &park;
    Location *mSubway = &subway;
    Location *mRoad = &road;
    Location *mHallway = &hallway;
    Location *mLobby = &lobby;
    Location *mTheatre = &theatre;
    Location *mStreetWest = &streetWest;
    Location *mHill = &hill;
    Location *mShop = &shop;
    Location *mPlaza = &plaza;
    Location *mTower = &tower;
    Location *mStreetNorth = &streetNorth;
    Location *mStreetSouthwest = &streetSouthwest;
    Location *mGarden = &garden;
    Location *mProjectorRoom = &projectorRoom;
    
    //Initialize exits
    Exit bedroomToHallway(1, mHallway);
    Exit *mBedroomToHallway = &bedroomToHallway;
    
    Exit hallwayToLobby(1, mLobby);
    Exit *mHallwayToLobby = &hallwayToLobby;
       
    //Initialize player character
    Player player(mBedroom, STARTING_HEALTH);
    
    //Initialize pointer to player character
    Player *mPlayer = &player;
    
    //Initialize keys
    Key paperHeart("paper heart", "An origami heart, folded from red paper.", mBedroom);
    Key *mPaperHeart = &paperHeart;
    mPlayer->addToInventory(mPaperHeart);
    
    Key telescope("telescope", "Description", mHill);
    Key *mTelescope = &telescope;
    outKeys.insert( pair<string, Key*>(mTelescope->getName(), mTelescope) );
    
    Key lab("lab", "Description", mShop);
    Key *mLab = &lab;
    outKeys.insert( pair<string, Key*>(mLab->getName(), mLab) );
    
    Key letter("letter", "Description", mLobby);
    Key *mLetter = &letter;
    outKeys.insert( pair<string, Key*>(mLetter->getName(), mLetter) );
    
    Key daisyChain("daisy chain", "Description", mGarden);
    Key *mDaisyChain = &daisyChain;
    outKeys.insert( pair<string, Key*>(mDaisyChain->getName(), mDaisyChain) );
    
    Key memory("memory", "Description", mGarden);
    Key *mMemory = &memory;
    outKeys.insert( pair<string, Key*>(mMemory->getName(), mMemory) );
    
    // Intialize non-key items
    Item crowbar("crowbar", "Description", mTower);
    Item *mCrowbar = &crowbar;
    outItems.insert( pair<string, Item*>(mCrowbar->getName(), mCrowbar) );
    
    Item battery("battery", "Description", mHill);
    Item *mBattery = &battery;
    outItems.insert( pair<string, Item*>(mBattery->getName(), mBattery) );
    
    Item key("key", "Description", mHill);
    Item *mKey = &key;
    outItems.insert( pair<string, Item*>(mKey->getName(), mKey) );
    
    Item videotape("videotape", "Description", mLobby);
    Item *mVideotape = &videotape;
    outItems.insert( pair<string, Item*>(mVideotape->getName(), mVideotape) );
    
    // Intialize misc stuff
    string user_input;
    int genOnce = 0;
    int notice = 0;
    srand(time(NULL));
    bool demonPresent = false;
    bool videotapeOn = false;
    bool pathOpen = false;
    bool batteryIn = false;
    bool labOn = false;
    bool childOnce = false;
    bool descripOnce = true;
    
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
    theatreProb = 80,
    plazaProb = 40,
    shopProb = 20;
    
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
            mPlayer->setImmobilized(true);
            cin.get();
            help(true);
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
    while(mPlayer->getLocation() != mRoad && mPlayer->getHealth() != 0) {  
        // bedroom
        while (mPlayer->getLocation() == mBedroom && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "get up" && mPlayer->getImmobilized()) {
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
                    if (mPlayer->hasItem("crowbar") && user_input == "open bottom drawer") {
                        cout << endl << "You yank the drawer open with your crowbar and it pops out with a thud. Peering inside, you find a key in the drawer. You pick it up and store it in your pocket.";
                        mPlayer->addToInventory(mKey);
                    } else if (mPlayer->hasItem("crowbar") && user_input != "open bottom drawer") {
                        cout << endl << "It's jammed. You can open it with your crowbar.";
                    } else {
                        cout << endl << "It's jammed. Maybe you can open it if you find a crowbar or something like that...?";
                    }
                } else if (user_input == "sleep in bed" || user_input == "sleep" || user_input == "go to sleep") {
                    cout << endl << "Haha, no.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // hallway
        while (mPlayer->getLocation() == mHallway && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "east") {
                    mPlayer->setLocation(mHallwayToLobby->getLeadsTo());
                } else if (user_input == "south") {
                    mPlayer->setLocation(mBedroom);
                } else if (user_input == "look out window" || user_input == "examine window") {
                    cout << endl << "You can get a pretty good view of the city from this window.";
                    cout << endl << "There are a lot of apartment buildings along the street below. "
                    << "You can see a library, a park, a movie theatre, a shop, a plaza, and subway station in the distance.";
                    cin.get();
                    if (outKeys.size() == 5 || outKeys.size() == 4) {
                        cout << "There is a writhing, shadowy mass enveloping the subway station.";
                    } else if (outKeys.size() == 3 || outKeys.size() == 2) {
                        cout << "There is a sizeable crowd of shadows surround the subway station.";
                    } else if (outKeys.size() == 1) {
                        cout << "There are a few stray shadows patrolling the outside of the subway station.";
                    } else {
                        cout << "The subway station appears to be completely clear of any threatening entities.";
                    }
                    
                    cout << endl << endl << "Very far away, you can just about make out a wide, cobblestone road. "
                    << "However, there is an unscalable barbed wire fence lining its edges.";
                } else if (user_input == "take key" && !mPlayer->getHasKey()) {
                    cout << endl << "You take the key.";
                    mPlayer->setHasKey(true);
                } else if (user_input == "take key" && mPlayer->getHasKey()) {
                    cout << endl << "You already have the key!";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // lobby
        while (mPlayer->getLocation() == mLobby && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(lobbyProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "west") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreet);
                } else if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mHallway);
                } else if (user_input == "examine mailboxes") {
                    cout << endl << "On closer inspection, all of the mailboxes, save one,"
                    << " are not mailboxes at all, but painted squares in the wall.";
                } else if (user_input == "examine real mailbox" || user_input == "examine true mailbox") {
                    if (mPlayer->hasItem("key")) {
                        cout << endl << "It's locked... and you've got a key! What are you waiting for? Open the blasted thing!";
                    } else {
                        cout << endl << "It's locked. You'll need to find a key, I'm afraid.";
                        cin.get();
                        cout << endl << "Well, what did you expect? This is a text adventure game, after all.";
                    }
                } else if (user_input == "open real mailbox" || user_input == "open true mailbox") {
                    if (mPlayer->hasItem("key")) {
                        cout << endl << "The mailbox contains a parcel in rather poor condition; the paper is wrinkled, and ripped at the edges.";
                        cin.get();
                        cout << endl << endl << "You open the parcel; it contains a videotape.";
                        cout << endl << endl << "The videotape has been added to your inventory.";
                        mPlayer->addToInventory(mVideotape);
                        outKeys.erase("videotape");
                    } else {
                        cout << endl << "You need the key.";
                    }
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "examine mailbox" || user_input == "open mailbox") {
                    cout << endl << "Which mailbox?";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                    continue;
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // street
        while (mPlayer->getLocation() == mStreet && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(streetProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "east") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mPark);
                } else if (user_input == "west") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetWest);
                } else if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mLobby);
                } else if (user_input == "north") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetNorth);
                } else if (user_input == "enter apartment building") {
                    cout << endl << "It's locked. They're all locked.";
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // park
        while (mPlayer->getLocation() == mPark && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(parkProb);
                genOnce++;
            }
            
            if (childOnce == false && labOn) {
                cin.get();
                cout << endl << "As you enter a park, you find a child there waiting for you; strange, as you haven't hitherto met anyone in the city. "
                << "The child beckons you to follow, and leads you through a small gap in a hedge leading into the woods. "
                << "You pass through a thickly wooded area, guided by the child who almost seems to glow. ";
                cin.get();
                cout << endl << "Finally, you come to a clearing. It appears to be a secret garden of some sort. As you reach the middle of the garden, "
                << "the child turns around and places a daisy chain on your head. The child smiles at you warmly, skips off, and, alarmingly, fades into the aether.";
                cin.get();
                mPlayer->setLocation(mGarden);
                mPlayer->addToInventory(mDaisyChain);
                outKeys.erase("daisy chain");
                childOnce = true;
                continue;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "west") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreet);
                } else if (user_input == "pick flower") {
                    cout << endl << "You pick a small, red flower.";
                    cin.get();
                    cout << endl << "It crumbles to ash in your hand.";
                } else if (user_input == "climb tree") {
                    cout << endl << "The bark is strangely slippery. You fail to gain more than a few feet before falling.";
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // street - west
        while (mPlayer->getLocation() == mStreetWest && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(altStreetProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "east") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreet);
                } else if (user_input == "north") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mLibrary);
                } else if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocationNoDescrip(mStreetSouthwest);
                } else if (user_input == "west") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mPlaza);
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // library
        while (mPlayer->getLocation() == mLibrary && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(libraryProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetWest);
                } else if (user_input == "examine red book") {
                    cout << endl << "The book seems to beam at you, as if it is delighted to see you after a long, painful period of separation.";
                } else if (user_input == "take red book" || user_input == "examine red book") {
                    cout << endl << "You grab the red book and proceed to stow it in your pocket. You note that the book is warm and glows cheerfully in your hand.";
                    cin.get();
                    cout << endl << endl << "As you move the book from the shelf to your pocket, a luminous piece of paper falls out of the book. With alarming rapidity, the book fades from "
                    << "red to dull mahogany to grey, after which it crumbles into dust. You pick up the piece of paper and stow it in your inventory.";
                    mPlayer->addToInventory(mLetter);
                    outKeys.erase("letter");
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "examine book" || user_input == "take book" || user_input == "remove book") {
                    cout << endl << "Which book? There are loads of them here.";
                } else if (user_input == "examine books") {
                    cout << endl << "Besides the glowy red one, they all look old, grey, and liable to crumble into dust at the slightest movement.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // theatre
        while (mPlayer->getLocation() == mTheatre && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(theatreProb);
                genOnce++;
            }
            
            if (videotapeOn == true) {
                cin.get();
                cout << endl << "It looks like the video is about to start. Why don't you have a seat over there?";
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "enter door" || user_input == "open door" ||user_input == "go through door") {
                    cout << endl << "You open the door and find a flight of stairs.";
                } else if (user_input == "go up stairs" || user_input == "climb stairs" || user_input == "climb up stairs") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mProjectorRoom);
                } else if (user_input == "east") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mPlaza);
                } else if (user_input == "sit in chair" || user_input == "sit down in chair" || user_input == "sit on chair" || user_input == "sit down on chair") {
                    if (videotapeOn) {
                        cout << endl << "You sit in the chair and focus your attention on the video.";
                        mPlayer->addToInventory(mMemory);
                        outKeys.erase("memory");
                        videotapeOn = false;
                    } else {
                        cout << endl << "You sit in the chair and gaze absentmindedly at the blank grey screen.";
                    }
                } else if (user_input == "sit" || user_input == "sit down") {
                    if (videotapeOn) {
                        cout << endl << "You sit down on the cold, concrete floor. You can't get a good view of the video from here, and your bottom starts to hurt. You get up.";
                    } else {
                        cout << endl << "You sit down on the cold, concrete floor. Your bottom starts to hurt. You get up.";
                    }
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                    continue;
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // projector room
        while (mPlayer->getLocation() == mProjectorRoom && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "put videotape in VCR" || user_input == "play videotape" || user_input == "play videotape in VCR") {
                    if (mPlayer->hasItem("videotape")) {
                        cout << endl << "The VCR makes some whirring and clicking noises. The projector flickers on. "
                        << "Strangely, the machine spits the videotape out and back at you. Mystified, you take the videotape back and put it in your pocket."
                        << endl << endl << "The projector is still on, and the machine is still running. You should probably check things out downstairs.";
                        videotapeOn = true;
                    } else {
                        cout << endl << "You haven't got a videotape.";
                    }
                } else if (user_input == "south") {
                    mPlayer->setLocation(mTheatre);
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }  
        }
        
        // hill
        while (mPlayer->getLocation() == mHill && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "take battery" || user_input == "pick up battery") {
                    cout << endl << "You pick up the battery and put it in your infinitely spacious pocket.";
                    mPlayer->addToInventory(mBattery);
                } else if (user_input == "examine telescope") {
                    cout << endl << "It's a silver telescope mounted on a tripod. It looks like there's a small black container at its feet.";
                } else if (user_input == "take container" || user_input == "examine container") {
                    cout << endl << "Examining the container, you find a battery inside.";
                } else if (user_input == "look through telescope") {
                    cout << endl << "It's a pitch black sky. Nothing to see.";
                } else if (user_input == "west") {
                    mPlayer->setLocation(mPlaza);
                } else if (user_input == "take telescope") {
                    cout << endl << "You remove the telescope from its mount and place it in your pocket.";
                    mPlayer->addToInventory(mTelescope);
                    outKeys.erase("telescope");
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // shop
        while (mPlayer->getLocation() == mShop && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(shopProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mPlaza);
                } else if (user_input == "examine device" || user_input == "examine rectangular device") {
                    cout << endl << "The device is an old, defunct electronic lab. On closer inspection, though, it looks like the only problem is that it's missing the battery. You could probably fit the device in your pocket.";
                } else if (user_input == "put battery in device" || user_input == "put battery in lab") {
                    if (mPlayer->hasItem("battery")) {
                        cout << endl << "You put the battery in the device.";
                        batteryIn = true;
                    } else {
                        cout << endl << "You don't have a battery.";
                    }
                } else if (user_input == "turn device on" || user_input == "turn lab on") {
                    if (batteryIn) {
                        cout << endl << "Message";
                        labOn = true;
                    } else {
                        cout << endl << "Nothing happens; there's no battery.";
                    }
                } else if (user_input == "take device" || user_input == "take lab") {
                    if (labOn) {
                        cout << endl << "With a great deal of strain and effort, you manage to shoehorn the lab into your absurdly capacious pocket.";
                        mPlayer->addToInventory(mLab);
                        outKeys.erase("lab");
                    } else {
                        cout << endl << "You can't pick it up unless you get it to work. Sorry, those are the rules of the game.";
                    }
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // plaza
        while (mPlayer->getLocation() == mPlaza && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(plazaProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "east") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetWest);
                } else if (user_input == "west") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mTheatre);
                } else if (user_input == "north") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mShop);
                } else if (user_input == "examine fence") {
                    cout << endl << "It's a simple, rusty chain link fence... hmm, it looks like there's a small gap to the south. Too small for you to fit through, though (at least in its current state).";
                } else if (user_input == "use crowbar on fence") {
                    if (mPlayer->hasItem("crowbar")) {
                        cout << endl << "You batter the edges of the gap with your crowbar until it is sufficiently large to crawl through. It looks like there's some kind of path leading into the wilderness.";
                        pathOpen = true;
                    } else {
                        cout << endl << "You don't have a crowbar.";
                    }
                } else if (user_input == "south") {
                    if (pathOpen) {
                        cout << endl << "You crawl through the newly enlarged gap in the fence and follow the path. The path is surprisingly long, and winds every which way through the woods."
                        << " The path is, in fact, so long that, by the time you reach its end, it's nighttime." << endl;
                        resetEncounterData(notice, genOnce, demonPresent);
                        mPlayer->setLocation(mHill);
                    } else {
                        cout << endl << "There's nothing to the south but a chain link fence.";
                    }
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // tower
        while (mPlayer->getLocation() == mTower && mPlayer->getHealth() != 0) {
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetNorth);
                } else if (user_input == "take crowbar" || user_input == "pick up crowbar") {
                    cout << endl << "You pick up the crowbar and somehow manage to fit it in your pocket.";
                    mPlayer->addToInventory(mCrowbar);
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // street - north
        while (mPlayer->getLocation() == mStreetNorth && mPlayer->getHealth() != 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(altStreetProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "north") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mTower);
                } else if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreet);
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet);
            }
        }
        
        // street - southwest
        while (mPlayer->getLocation() == mStreetSouthwest && mPlayer->getHealth() != 0) {
            
            if (descripOnce) {
                cout << endl << "Street - Southwest" << endl << endl
                << "This street resembles the other streets. It comes to a dead end to the south; at the end is the subway station.";
                cin.get();
                if (outKeys.size() == 5 || outKeys.size() == 4) {
                    cout << endl << "There is a writhing, shadowy mass enveloping the subway station.";
                } else if (outKeys.size() == 3 || outKeys.size() == 2) {
                    cout << endl << "There is a sizeable crowd of shadows surrounding the subway station.";
                } else if (outKeys.size() == 1) {
                    cout << endl << "There are a few stray shadows patrolling the outside of the subway station.";
                } else {
                    cout << endl << "The subway station appears to be completely clear of any threatening entities.";
                }
                descripOnce = false;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "north") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetWest);
                    descripOnce = true;
                } else if (user_input == "south") {
                    if (outKeys.size() == 5 || outKeys.size() == 4) {
                        cout << endl << "Slowly, you approach the umbral leviathan which almost seems to swallow the subway station in shadow. As you get closer, "
                        << "you feel some force that repels you. Nevertheless, you continue until suddenly it feels like you are being battered from all sides. The "
                        << "shadow consumes you and spits you back out. You find yourself back at the intersection and much the worse for wear.";
                        mPlayer->setHealth(mPlayer->getHealth() - 1);
                    } else if (outKeys.size() == 3 || outKeys.size() == 2) {
                        cout << endl << "You approach the crowd of shadows surrounding the subway and feel a repelling force. You decide against continuing and turn back.";
                    } else if (outKeys.size() == 1) {
                        cout << endl << "As you approach the shadowy figures milling about just outside of the subway station, you feel a force pushing you back. One of "
                        << "demons almost notices you. You decide it's best to turn back, for now.";
                    } else {
                        cout << endl << "You make your way across the cold expanse of cement towards the subway station. The objects filling your pockets feel warm "
                        << "against your torso, almost like they collectively comprise a protective blanket. You notice that the sky, albeit still grey, seems a lot brighter now."
                        << " The station door opens with a small creak, and you enter.";
                        mPlayer->setLocation(mSubway);
                    }
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // garden
        while (mPlayer->getLocation() == mGarden && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "northwest") {
                    mPlayer->setLocation(mPark);
                }
            }
        }
        
        // subway
        while (mPlayer->getLocation() == mSubway && mPlayer->getHealth() != 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "north") {
                    mPlayer->setLocation(mStreetSouthwest);
                } else if (user_input == "examine turnstile" || user_input == "examine turnstiles") {
                    cout << endl << "To your surprise, the card slots of every turnstile already contain cards. It looks like you can just go ahead and pass through.";
                } else if (user_input == "pass through turnstile" || user_input == "pass through turnstiles") {
                    cout << endl << "You push down the metal rods of one of the turnstiles, and pass through to the platform. The entrance to the train lies invitingly "
                    << "a few yards before you.";
                } else if (user_input == "enter train" || user_input == "go through train door") {
                    cout << endl << "You step through the train door, which closes behind you. The train is well-lit, with a lavendar carpet and leather seats. You sit down, "
                    << "and the train slowly accelerates. It barrels past the monochrome urban edifices and into the countryside, which passes in a green blur. The train "
                    << "enters a tunnel in the hills, and you are plunged into darkness. The train grinds to a halt as it draws closer to a source of light. Looking up at the "
                    << "electronic display near the ceiling of the train, you find that you have arrived at the final destination. The doors open, and you step out.";
                    mPlayer->setLocationNoDescrip(mRoad);
                } else if (user_input == "examine ticket counter") {
                    cout << endl << "The ticket counter is closed.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }

    }
    
    // bad ending
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
    
    // good ending
    if (mPlayer->getLocation() == mRoad) {
        cout << endl << endl << "You walk across the platform, through the turnstiles, out the station door, and into the light. To your surprise, the cobblestone road "
        << "lies a few yards in front of you. The luminosity of the sun and the blueness of the sky dazzle you. For a moment, you want to turn back, but before you "
        << "can seriously consider it, you see a figure in the distance, waving at you. As it approaches, you recognize it as Annie. She extends her hand towards you, "
        << "and you can't help but grab it. She helps you back onto the road and, as soon as your feet touch the cobblestone, she embraces you. The two of you continue "
        << "along the road, hand in hand, together.";
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

void demonEncounter(string& user_input, int& notice, int& genOnce, Player *mPlayer, Location *mStreet) {
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
            cin.get();
            cout << endl << endl << "...";
            cin.get();
            (getDemon())->interact(mPlayer, mStreet);
            notice = 0;
            genOnce = 0;
            return;
        } else {
            int p = probabilityGenerator(100);
            if (p < 33 && notice == 0) {
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
                    cin.get();
                    cout << endl << "The demon stops, and slowly turns its head in your direction.";
                    break;
                case 2:
                    cin.get();
                    cout << endl << "The demon has noticed you.";
                    break;
                case 3:
                    cin.get();
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

bool commonActions(string user_input, bool demonPresent, Player *player, int notice) {
    if (user_input == "look") {
        player->look();
    } else if (user_input == "health") {
        cout << endl << "Health: " << player->getHealth();
    } else if (user_input == "inventory") {
        player->displayInventory();
    } else if (user_input.size() == 0) {
        // do nothing
    } else if (user_input == "hide" && !demonPresent) {
        cout << endl << "You cower for a little while until you realize there's nothing to be hiding from, after which "
        << "you slap yourself for being so silly.";
    } else if (user_input == "hide" && notice > 0) {
        // allow following if-statement to handle this
    } else if ((user_input == "fight demon" || user_input == "attack demon" || user_input == "kill demon" || user_input == "punch demon") && demonPresent) {
        // allow demonEncounter function to handle this
    } else if ((user_input == "fight demon" || user_input == "attack demon" || user_input == "kill demon" || user_input == "punch demon") && !demonPresent) {
        cout << endl << "You punch the air -- a wholly futile action.";
    } else if (user_input == "run") {
        cout << endl << "Run where? Specify a direction.";
    } else if (user_input == "help") {
        help(false);
    } else {
        return false;
    }
    return true;
}

void help(bool first) {
    cout << endl << endl << "* * * * *" << endl << endl;
    if (first) {
        cout << "Congrats! You have completed the introductory level.";
    } else {
        cout << "Congrats! You have called the help menu.";
    }
    
    cout << endl << "A few tips:" << endl << "* To look at your surroundings, enter the command \"LOOK\"."
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
    << endl << "* To bring up this list of tips again, enter the command \"HELP\"."
    << endl << endl << "Good luck!"
    << endl << endl << "* * * * *";
}

