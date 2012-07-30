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
void isolation();
void demonEncounter(string& user_input, int& notice, int& genOnce, Player *mPlayer, Location *mStreet, Location *mBedroom);
void resetEncounterData(int& notice, int& genOnce, bool& demonPresent);
bool commonActions(string user_input, bool demonPresent, Player *player, int notice);
void help(bool first);
void getEnter();

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
    Location station(name_input, description_input);
    
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
    
    location.getline(name_input, 30, '#');
    location.getline(description_input, 1000, '#');
    Location projectorRoom(name_input, description_input);
    
    //Intialize pointers to locations
    Location *mStreet = &street;
    Location *mBedroom = &bedroom;
    Location *mLibrary = &library;
    Location *mPark = &park;
    Location *mStation = &station;
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
       
    //Initialize player character
    Player player(mBedroom, STARTING_HEALTH);
    
    //Initialize pointer to player character
    Player *mPlayer = &player;
    
    //Initialize keys
    Key paperHeart("paper heart", "An origami heart, folded from red paper.", mBedroom);
    Key *mPaperHeart = &paperHeart;
    mPlayer->addToInventory(mPaperHeart);
    
    Key telescope("telescope", "It's a silver telescope, made for stargazing.", mHill);
    Key *mTelescope = &telescope;
    outKeys.insert( pair<string, Key*>(mTelescope->getName(), mTelescope) );
    
    Key lab("lab", "An old electronic science lab -- the kind you'd get for Christmas as a child and run electrical experiments on.", mShop);
    Key *mLab = &lab;
    outKeys.insert( pair<string, Key*>(mLab->getName(), mLab) );
    
    Key letter("letter", "It's an old letter you had received from a friend, but tossed without reading. Enter the command \'read letter\' to read it.", mLobby);
    Key *mLetter = &letter;
    outKeys.insert( pair<string, Key*>(mLetter->getName(), mLetter) );
    
    Key daisyChain("daisy chain", "A wreath of daisies, connected at the stems.", mGarden);
    Key *mDaisyChain = &daisyChain;
    outKeys.insert( pair<string, Key*>(mDaisyChain->getName(), mDaisyChain) );
    
    Key memory("memory", "A fond memory of the most perfect day of your life.", mGarden);
    Key *mMemory = &memory;
    outKeys.insert( pair<string, Key*>(mMemory->getName(), mMemory) );
    
    // Intialize non-key items
    Item crowbar("crowbar", "A piece of cast iron, shaped like a crow's foot at one end.", mTower);
    Item *mCrowbar = &crowbar;
    outItems.insert( pair<string, Item*>(mCrowbar->getName(), mCrowbar) );
    
    Item battery("battery", "It's a 9-volt battery.", mHill);
    Item *mBattery = &battery;
    outItems.insert( pair<string, Item*>(mBattery->getName(), mBattery) );
    
    Item key("key", "A small, slightly rusty key.", mHill);
    Item *mKey = &key;
    outItems.insert( pair<string, Item*>(mKey->getName(), mKey) );
    
    Item videotape("videotape", "It's a VHS cassette.", mLobby);
    Item *mVideotape = &videotape;
    outItems.insert( pair<string, Item*>(mVideotape->getName(), mVideotape) );
    
    // Intialize misc stuff
    string user_input;
    int genOnce = 0;
    int notice = 0;
    int giveHint = 0;
    srand(time(NULL));
    bool demonPresent = false;
    bool videotapeOn = false;
    bool pathOpen = false;
    bool batteryIn = false;
    bool labOn = false;
    bool doorOpen = false;
    bool childOnce = false;
    bool pastTurnstile = false;
    bool descripOnce = true;
    bool iOnce = true;
    
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
    
    Demon regretDemon("regret", "description", mStreet);
    Demon *mRegretDemon = &regretDemon;
    demons.push_back(mRegretDemon);
    
    Demon distractDemon("distraction", "description", mStreet);
    Demon *mDistractDemon = &distractDemon;
    demons.push_back(mDistractDemon);
    
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
    
    cout << endl << "Running from Demons: a text adventure game" << endl << "by Crystal Liang" << endl << "dedicated to Michael Lee" 
    << endl << endl << endl << "Press \'e\' and \'ENTER\' to begin. ";
    getline(cin, user_input);
    
    while (user_input != "e") {
        getline(cin, user_input);
    }
    
    while (!intro.eof()) {
        intro.getline(intro_input, 1000, '#');
        cout << endl << intro_input;
        getEnter();
    }
    
    //Intro level
    mDreadDemon->interactDread(mPlayer);
    while (mPlayer->getImmobilized()) {
        getUserInput(user_input);
        if (user_input.size() != 0) {
            if (user_input == "inventory" || user_input == "look in pocket" || user_input == "check pocket" || user_input == "check in pocket"
                || user_input == "search pocket" || user_input == "look inside pocket" || user_input == "search through pocket" || user_input == "look through pocket"
                || user_input == "open pocket") {
                cout << endl << "Digging in your pocket, you find that it contains... a paper heart, folded from red paper.";
                getEnter();
                cout << endl << "As it sits in your hand, the heart begins to fade to grey and crumple... as if your touch causes it to decay.";
                getEnter();
                cout << endl << "The demon fades away, disappearing altogether. You find that you can move now.";
                getEnter();
                demons.erase(demons.begin());
                mPlayer->setImmobilized(true);
                help(true);
                break;
            } else {
                cout << endl << "It's no use; you can't get up.";
                giveHint++;
            }
        }
        
        if (giveHint == 10) {
            cout << endl << endl << "You can feel something in your pocket.";
        }
    }
    
    mPlayer->setImmobilized(true);
    
    // Main loop
    while(mPlayer->getLocation() != mRoad && mPlayer->getHealth() > 0) {  
        // bedroom
        while (mPlayer->getLocation() == mBedroom && mPlayer->getHealth() > 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "get up" && mPlayer->getImmobilized()) {
                    mPlayer->setImmobilized(false);
                    cout << endl << "You get up from the bed.";
                } else if (user_input == "get up" && !mPlayer->getImmobilized()) {
                    cout << endl << "You're already up.";
                } else if (user_input == "north" && !mPlayer->getImmobilized()) {
                    mPlayer->setLocation(mHallway);
                    break;
                } else if (user_input == "north" && mPlayer->getImmobilized()) {
                    cout << endl << "You can't really leave the room if you're still in bed, can you?";
                } else if (user_input == "examine bed") {
                    cout << endl << "The bed is comprised of some rumpled sheets and a duvet on a springy mattress, set on a metal frame.";
                    getEnter();
                    cout << endl << "This is a deathly bed. You mustn't fall asleep in it.";
                    getEnter();
                } else if (user_input == "examine chair") {
                    cout << endl << "A simple wooden chair.";
                } else if (user_input == "examine desk" || user_input == "examine the desk") {
                    cout << endl << "A simple wooden desk.";
                } else if (user_input == "examine drawer" || user_input == "examine drawers") {
                    cout << endl << "A small, sturdy chest of drawers, made from oak wood. There are two drawers.";
                } else if (user_input == "open top drawer" || user_input == "look in top drawer" || user_input == "examine top drawer") {
                    if (mPlayer->getImmobilized()) {
                        cout << endl << "You can't reach it from your bed.";
                    } else {
                        cout << endl << "The top drawer contains some socks.";
                    }
                } else if (user_input == "take socks") {
                    if (mPlayer->getImmobilized()) {
                        cout << endl << "You can't reach it from your bed.";
                    } else {
                        cout << endl << "The socks are glued firmly to the bottom of the drawer. There's no way you could pry them off.";
                    }
                } else if (user_input == "bash drawer open with hammer") {
                    cout << endl << "You haven't got a hammer, silly.";
                } else if (user_input == "open bottom drawer" || user_input == "look in bottom drawer" || user_input == "examine bottom drawer" || user_input == "open bottom drawer with crowbar") {
                    if (mPlayer->getImmobilized()) {
                        cout << endl << "You can't reach it from your bed.";
                    } else {
                        if (mPlayer->hasItem("crowbar") && (user_input == "open bottom drawer" || user_input == "open bottom drawer with crowbar")) {
                            if (!mPlayer->hasItem("key")) {
                                cout << endl << "You yank the drawer open with your crowbar and it pops out with a thud. Peering inside, you find a key in the drawer. You pick it up and store it in your pocket.";
                                mPlayer->addToInventory(mKey);
                            } else {
                                cout << endl << "The drawer is empty.";
                            }
                        } else if (mPlayer->hasItem("crowbar") && user_input != "open bottom drawer") {
                            cout << endl << "It's jammed. You can open it with your crowbar.";
                        } else {
                            cout << endl << "It's jammed. Maybe you can open it if you find a crowbar or something like that...?";
                        }
                    }
                } else if (user_input == "sleep in bed" || user_input == "sleep" || user_input == "go to sleep") {
                    cout << endl << "Haha, no.";
                } else if (user_input == "examine carpet" || user_input == "examine floor" || user_input == "examine ground") {
                    cout << endl << "It's a rather unremarkable beige carpet.";
                } else if (user_input == "examine walls" || user_input == "examine wall" || user_input == "examine ceiling") {
                    cout << endl << "Hopeless greyness.";
                } else if (user_input == "look in drawer") {
                    cout << endl << "Which drawer? Top or bottom?";
                } else if (user_input == "south" || user_input == "west" || user_input == "east") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "sit") {
                    cout << endl << "You sit down on the carpet and linger there until you realize that the action is wholly pointless, so you get up.";
                } else if (user_input == "sit in chair" || user_input == "sit on chair") {
                    cout << endl << "You sit in the chair and relax for a moment. Then you get up, fully rejuvenated.";
                } else if (user_input == "close top drawer" || user_input == "close bottom drawer" || user_input == "close drawer" || user_input == "close drawers") {
                    cout << endl << "Already closed.";
                } else if (user_input == "open drawer" || user_input == "open drawers") {
                    cout << endl << "Which drawer? Top or bottom?";
                } else if (user_input == "look under bed" || user_input == "look underneath bed" || user_input == "look beneath bed") {
                    cout << endl << "To your surprise, you find a family of mice sleeping amidst the dust beneath your bed. They eventually take notice of you, and scurry off, "
                    << "seeming to disappear into the dust.";
                } else if (user_input == "examine door") {
                    cout << endl << "It's a wooden door that opens in.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // hallway
        while (mPlayer->getLocation() == mHallway && mPlayer->getHealth() > 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "east" || user_input == "go down stairs" || user_input == "go downstairs" || user_input == "descend stairs") {
                    mPlayer->setLocation(mLobby);
                } else if (user_input == "south") {
                    mPlayer->setLocation(mBedroom);
                } else if (user_input == "look out window" || user_input == "examine window" || user_input == "west" || user_input == "look west") {
                    cout << endl << "You can get a pretty good view of the city from this window.";
                    getEnter();
                    cout << endl << "There are a lot of apartment buildings along the street below. "
                    << "You can see a library, a park, a movie theatre, a shop, a plaza, and train station in the distance." << endl;
                    getEnter();
                    if (outKeys.size() == 5 || outKeys.size() == 4) {
                        cout << "There is a writhing, shadowy mass enveloping the train station.";
                    } else if (outKeys.size() == 3 || outKeys.size() == 2) {
                        cout << "There is a sizeable crowd of shadows surrounding the train station.";
                    } else if (outKeys.size() == 1) {
                        cout << "There are a few stray shadows patrolling the outside of the train station.";
                    } else {
                        cout << "The train station appears to be completely clear of any threatening entities.";
                    }
                    getEnter();
                    cout << endl << "Very far away, you can just about make out a wide, cobblestone road. "
                    << "However, there is an unscalable barbed wire fence lining its edges.";
                } else if (user_input == "north" || user_input == "west") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "open window") {
                    cout << endl << "You open the window. You'd expect a draft to blow in shortly, but the air is still and stale.";
                } else if (user_input == "jump out window" || user_input == "jump out of window") {
                    cout << endl << "The window is too big to fit through.";
                } else if (user_input == "lick window") {
                    cout << endl << "You lick the grimy surface of the window, and end up gagging with a mouthful of dust.";
                } else if (user_input == "examine stairs") {
                    cout << endl << "The stairs lead down.";
                }
                else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // lobby
        while (mPlayer->getLocation() == mLobby && mPlayer->getHealth() > 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(lobbyProb);
                genOnce++;
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "west") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreet);
                } else if (user_input == "south" || user_input == "go up stairs" || user_input == "go upstairs" || user_input == "ascend stairs") {
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
                        if (mPlayer->hasItem("videotape")) {
                            cout << endl << "There's nothing in the mailbox.";
                        } else {
                            cout << endl << "The mailbox contains a parcel in rather poor condition; the paper is wrinkled, and ripped at the edges.";
                            getEnter();
                            cout << endl << "You open the parcel; it contains a videotape.";
                            cout << endl << endl << "The videotape has been added to your inventory.";
                            mPlayer->addToInventory(mVideotape);
                            outKeys.erase("videotape");
                        }
                    } else {
                        cout << endl << "You need the key.";
                    }
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "examine mailbox" || user_input == "open mailbox") {
                    cout << endl << "Which mailbox?";
                } else if (user_input == "north" || user_input == "east") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine desk") {
                    cout << endl << "It's a nondescript imitation wood desk.";
                } else if (user_input == "examine stairs") {
                    cout << endl << "The stairs go up to the hallway.";
                } else if (user_input == "push desk") {
                    cout << endl << "It won't budge.";
                } else if (user_input == "sit on desk") {
                    cout << endl << "You sit on the desk for a few moments, and then get up.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                    continue;
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // street
        while (mPlayer->getLocation() == mStreet && mPlayer->getHealth() > 0) {
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
                } else if (user_input == "south" || user_input == "enter my building" || user_input == "enter my apartment building") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mLobby);
                } else if (user_input == "north") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetNorth);
                } else if (user_input == "enter apartment building" || user_input == "enter apartment buildings") {
                    cout << endl << "It's locked. They're all locked.";
                } else if (user_input == "enter building" || user_input == "enter buildings") {
                    cout << endl << "Which building?";
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // park
        while (mPlayer->getLocation() == mPark && mPlayer->getHealth() > 0) {
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
                getEnter();
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
                } else if (user_input == "pick flower" || user_input == "pick red flower" || user_input == "pick flowers" || user_input == "pick red flowers") {
                    cout << endl << "You pick a small, red flower.";
                    getEnter();
                    cout << endl << "It crumbles to ash in your hand.";
                } else if (user_input == "climb tree") {
                    cout << endl << "The bark shrivels at your touch. You fail to gain more than a few feet before falling.";
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "north" || user_input == "south" || user_input == "east") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine fountain") {
                    cout << endl << "It's a dry, cracked fountain made of whitish stone. There are a few dead spiders and cobwebs in the basin.";
                } else if (user_input == "examine trees" || user_input == "examine tree") {
                    cout << endl << "There are three poplar trees scattered in the park. Instead of livening up the drab place, the trees, standing stark against "
                    << "the dead grass and concrete walls of the surrounding buildings, succeed only in adding a feeling of loneliness to the "
                    << "muffled despair that pervades the entire city.";
                } else if (user_input == "examine flowers" || user_input == "examine flower") {
                    cout << endl << "Most of the flowers are dead. There are, however, some rather sprightly-looking red flowers standing tall above the rest.";
                } else if (user_input == "examine grass") {
                    cout << endl << "It's overgrown, and dies as you step on it.";
                } else if (user_input == "pull grass") {
                    cout << endl << "The grass becomes dessicated at your touch.";
                } else if (user_input == "pick up dead spiders" || user_input == "pick up spiders" || user_input == "take spiders" || user_input == "take dead spiders"
                           || user_input == "eat spiders" || user_input == "eat dead spiders") {
                    cout << endl << "The spiders turn to ash.";
                } else if (user_input == "take cobwebs") {
                    cout << endl << "Why would you want to do that?";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // street - west
        while (mPlayer->getLocation() == mStreetWest && mPlayer->getHealth() > 0) {
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
                } else if (user_input == "enter apartment building" || user_input == "enter apartment buildings") {
                    cout << endl << "It's locked. They're all locked.";
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // library
        while (mPlayer->getLocation() == mLibrary && mPlayer->getHealth() > 0) {
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
                } else if (user_input == "take red book" || user_input == "pick up red book") {
                    if (!mPlayer->hasItem("letter")) {
                        cout << endl << "You grab the red book and proceed to stow it in your pocket. You note that the book is warm and glows cheerfully in your hand.";
                        getEnter();
                        cout << endl << "As you move the book from the shelf to your pocket, a luminous piece of paper falls out of the book. With alarming rapidity, the book fades from "
                        << "red to dull mahogany to grey, after which it crumbles into dust. You pick up the piece of paper and stow it in your inventory.";
                        mPlayer->addToInventory(mLetter);
                        outKeys.erase("letter");
                    } else {
                        cout << endl << "The red book has crumbled to dust.";
                    }
                } else if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "examine book" || user_input == "take book" || user_input == "remove book" || user_input == "pick up book" || user_input == "pick up books") {
                    cout << endl << "Which book? There are loads of them here.";
                } else if (user_input == "examine books") {
                    cout << endl << "They all look old, grey, and liable to crumble at the slightest movement.";
                    if (!mPlayer->hasItem("letter")) {
                        cout << " There is, however, an exception: a red book, almost glowing with vividness, sits wedged among multitudes of more forlorn-looking books.";
                    }
                } else if (user_input == "north" || user_input == "west" || user_input == "east") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine shadows" || user_input == "examine shadow") {
                    cout << endl << "Normal, dark shadows.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // theatre
        while (mPlayer->getLocation() == mTheatre && mPlayer->getHealth() > 0) {
            if (genOnce == 0) {
                demonPresent = demonInArea(theatreProb);
                genOnce++;
            }
            
            if (videotapeOn == true) {
                cout << endl << endl << "It looks like the video is about to start. Why don't you have a seat over there? (in the chair?)";
            }
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "hide" && demonPresent && notice == 0) {
                    cout << endl << "You hide. The demon mills about, oblivious to your presence.";
                    continue;
                } else if (user_input == "enter door" || user_input == "open door" ||user_input == "go through door" || user_input == "go through doorway" || user_input == "enter doorway") {
                    cout << endl << "You open the door and find a flight of stairs.";
                    doorOpen = true;
                } else if (user_input == "go up stairs" || user_input == "climb stairs" || user_input == "climb up stairs" || user_input == "go upstairs") {
                    if (!doorOpen) {
                        cout << endl << "There's a door in the way.";
                    } else {
                        resetEncounterData(notice, genOnce, demonPresent);
                        mPlayer->setLocation(mProjectorRoom);
                    }
                } else if (user_input == "east") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mPlaza);
                } else if (user_input == "sit in chair" || user_input == "sit down in chair" || user_input == "sit on chair" || user_input == "sit down on chair") {
                    if (videotapeOn) {
                        cout << endl << "You sit in the chair and focus your attention on the video.";
                        getEnter();
                        cout << endl << "The film starts. You are slow to recognize it, but when you do, it is unmistakable."
                        << " It is a film of the greatest, most perfect day of your life.";
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
                } else if (user_input == "north" || user_input == "south" || user_input == "west") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine chair") {
                    cout << endl << "It's a metal folding chair.";
                } else if (user_input == "examine doorway" || user_input == "examine door") {
                    cout << endl << "The doorway is illuminated with red light.";
                } else if (user_input == "examine seats") {
                    cout << endl << "The proper movie seats have been ripped from their places and scattered onto the floor. The red fabric is faded and ripped.";
                } else if (user_input == "examine screen") {
                    if (videotapeOn) {
                        cout << endl << "The movie is starting. You should probably take a seat over there, in the chair.";
                    } else {
                        cout << endl << "It's a blank, silver screen.";
                    }
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                    continue;
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // projector room
        while (mPlayer->getLocation() == mProjectorRoom && mPlayer->getHealth() > 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "put videotape in vcr" || user_input == "play videotape" || user_input == "play videotape in vcr") {
                    if (mPlayer->hasItem("videotape")) {
                        cout << endl << "The VCR makes some whirring and clicking noises. The projector flickers on. "
                        << "Strangely, the machine spits the videotape out and back at you. Mystified, you take the videotape back and put it in your pocket."
                        << endl << endl << "The projector is still on, and the machine is still running. You should probably check things out downstairs.";
                        videotapeOn = true;
                    } else {
                        cout << endl << "You haven't got a videotape.";
                    }
                } else if (user_input == "south" || user_input == "go down stairs" || user_input == "go downstairs" || user_input == "descend stairs") {
                    mPlayer->setLocation(mTheatre);
                } else if (user_input == "north" || user_input == "east" || user_input == "west") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine vcr") {
                    cout << endl << "The VCR is fully functional.";
                } else if (user_input == "examine projector") {
                    cout << endl << "Like the VCR, the projector is fully functional.";
                } else if (user_input == "examine cables") {
                    cout << endl << "The black cables hang from the ceiling like vines.";
                } else if (user_input == "pull cables" || user_input == "take cables" || user_input == "rip cables from ceiling") {
                    cout << endl << "They won't budge.";
                } else if (user_input == "swing on cables") {
                    cout << endl << "You swing on the cables, and are tempted to emit a tribal battlecry.";
                } else if (user_input == "examine glass pane" || user_input == "examine pane" || user_input == "examine window") {
                    cout << endl << "You can see the theatre through the window.";
                } else if (user_input == "examine stairs" || user_input == "examine stairway") {
                    cout << endl << "They lead down to the theatre.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }  
        }
        
        // hill
        while (mPlayer->getLocation() == mHill && mPlayer->getHealth() > 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "take battery" || user_input == "pick up battery") {
                    if (mPlayer->hasItem("battery")) {
                        cout << endl << "You already have the battery.";
                    } else {
                        cout << endl << "You pick up the battery and put it in your infinitely spacious pocket.";
                        mPlayer->addToInventory(mBattery);
                    }
                } else if (user_input == "examine telescope") {
                    if (mPlayer->hasItem("telescope")) {
                        cout << endl << "The telescope is in your pocket.";
                    } else {
                        cout << endl << "It's a silver telescope mounted on a tripod. It looks like there's a black, open-top container at its feet.";
                    }
                } else if (user_input == "take container" || user_input == "examine container") {
                    if (mPlayer->hasItem("battery")) {
                        cout << endl << "The container is empty.";
                    } else {
                        cout << endl << "Examining the open-top container, you find a battery inside.";
                    }
                } else if (user_input == "look through telescope") {
                    cout << endl << "It's a pitch black sky. Nothing to see.";
                } else if (user_input == "west") {
                    mPlayer->setLocation(mPlaza);
                } else if (user_input == "take telescope") {
                    if (mPlayer->hasItem("telescope")) {
                        cout << endl << "You already have the telescope.";
                    } else {
                        cout << endl << "You remove the telescope from its mount and place it in your pocket.";
                        mPlayer->addToInventory(mTelescope);
                        outKeys.erase("telescope");
                    }
                } else if (user_input == "north" || user_input == "east" || user_input == "south") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine grass") {
                    cout << endl << "It's green and slightly overgrown.";
                } else if (user_input == "examine tripod") {
                    cout << endl << "A simple, black tripod made of plastic.";
                } else if (user_input == "take tripod") {
                    cout << endl << "It's too big to fit in your pocket. You snap your fingers in disappointment.";
                } else if (user_input == "examine battery") {
                    cout << endl << "It's a 9-volt battery.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // shop
        while (mPlayer->getLocation() == mShop && mPlayer->getHealth() > 0) {
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
                } else if (user_input == "turn device on" || user_input == "turn lab on" || user_input == "use device" || user_input == "activate device"
                           || user_input == "turn on device" || user_input == "turn on lab" || user_input == "use lab" || user_input == "activate lab") {
                    if (batteryIn) {
                        cout << endl << "The lab flickers on.";
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
                } else if (user_input == "north" || user_input == "south" || user_input == "east") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine cash register") {
                    cout << endl << "The empty cash register lies in a heap, defeated on the dusty floor.";
                } else if (user_input == "examine crisp bags" || user_input == "examine bean cans" || user_input == "examine crisp bag" || user_input == "examine crisp bag") {
                    cout << endl << "They're empty.";
                } else if (user_input == "examine soda bottles") {
                    cout << endl << "Empty. Some are broken.";
                } else if (user_input == "take crisp bags" || user_input == "take soda bottles" || user_input == "take bean cans") {
                    cout << endl << "No matter how hard you try, you can't seem to fit them in your pocket. Darn.";
                } else if (user_input == "take cash register") {
                    cout << endl << "It's too heavy to pick up.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // plaza
        while (mPlayer->getLocation() == mPlaza && mPlayer->getHealth() > 0) {
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
                    cout << endl << "It's a simple, rusty chain link fence... hmm, it looks like there's a small gap to the south. Too small for you to fit through, though (at least in its current state)."
                    << " You might be able to enlarge the gap by beating the fence with a crowbar or something like that...";
                } else if (user_input == "use crowbar on fence" || user_input == "hit fence using crowbar" || user_input == "hit fence with crowbar" || user_input == "beat fence with crowbar") {
                    if (mPlayer->hasItem("crowbar")) {
                        if (!pathOpen) {
                            cout << endl << "You batter the edges of the gap with your crowbar until it is sufficiently large to crawl through. It looks like there's some kind of path leading into the wilderness to the south.";
                            pathOpen = true;
                        } else {
                            cout << endl << "You've already used the crowbar on the fence.";
                        }
                    } else {
                        cout << endl << "You don't have a crowbar.";
                    }
                } else if (user_input == "south" || user_input == "go down path") {
                    if (pathOpen) {
                        cout << endl << "You crawl through the newly enlarged gap in the fence and follow the path. The path is surprisingly long, and winds every which way through the woods."
                        << " The path is, in fact, so long that, by the time you reach its end, it's nighttime." << endl;
                        resetEncounterData(notice, genOnce, demonPresent);
                        getEnter();
                        mPlayer->setLocation(mHill);
                    } else {
                        cout << endl << "There's nothing to the south but a chain link fence.";
                    }
                } else if (user_input == "climb fence") {
                    cout << endl << "The fence is twisted enough that it hurts to climb it.";
                } else if (user_input == "use crowbar") {
                    if (mPlayer->hasItem("crowbar")) {
                        cout << endl << "On what?";
                    } else {
                        cout << endl << "You don't have a crowbar.";
                    }
                } else if (user_input == "hit fence" || user_input == "beat fence") {
                    cout << endl << "You hit the fence and immediately pull back in pain, your knuckles scratched and bleeding.";
                } else if (user_input == "examine shop") {
                    cout << endl << "The shop bears the sign \'GENERAL GOODS'\ in big, friendly letters.";
                } else if (user_input == "examine theatre") {
                    cout << endl << "It's a regular old movie theatre. The ticket booth is empty. It looks like you can go right in.";
                } else if (user_input == "examine wilderness") {
                    cout << endl << "Trees and such.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // tower
        while (mPlayer->getLocation() == mTower && mPlayer->getHealth() > 0) {
            
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "south") {
                    resetEncounterData(notice, genOnce, demonPresent);
                    mPlayer->setLocation(mStreetNorth);
                } else if (user_input == "take crowbar" || user_input == "pick up crowbar") {
                    cout << endl << "You pick up the crowbar and somehow manage to fit it in your pocket.";
                    mPlayer->addToInventory(mCrowbar);
                } else if (user_input == "examine lift") {
                    cout << endl << "The lift is completely defunct. The doors won't open and the cord has snapped.";
                } else if (user_input == "examine crowbar") {
                    cout << endl << "It's a simple crowbar made of cast iron.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // street - north
        while (mPlayer->getLocation() == mStreetNorth && mPlayer->getHealth() > 0) {
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
                } else if (user_input == "west" || user_input == "east") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine tower") {
                    cout << endl << "It's a tall, skinny futuristic tower with a giant disk at the top. It seems there's an elevator shaft leading from the bottom to the top.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
            
            if (demonPresent) { 
                demonEncounter(user_input, notice, genOnce, mPlayer, mStreet, mBedroom);
            }
        }
        
        // street - southwest
        while (mPlayer->getLocation() == mStreetSouthwest && mPlayer->getHealth() > 0) {
            
            if (descripOnce) {
                cout << endl << "Street - Southwest" << endl << endl
                << "This street resembles the other streets. It comes to a dead end to the south; at the end is the train station.";
                cin.get();
                if (outKeys.size() == 5 || outKeys.size() == 4) {
                    cout << endl << "There is a writhing, shadowy mass enveloping the train station.";
                } else if (outKeys.size() == 3 || outKeys.size() == 2) {
                    cout << endl << "There is a sizeable crowd of shadows surrounding the train station.";
                } else if (outKeys.size() == 1) {
                    cout << endl << "There are a few stray shadows patrolling the outside of the train station.";
                } else {
                    cout << endl << "The train station appears to be completely clear of any threatening entities.";
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
                } else if (user_input == "south" || user_input == "approach mass" || user_input == "approach shadows") {
                    if (outKeys.size() == 5 || outKeys.size() == 4) {
                        cout << endl << "Slowly, you approach the umbral leviathan which almost seems to swallow the train station in shadow. As you get closer, "
                        << "you feel some force that repels you. Nevertheless, you continue until suddenly it feels like you are being battered from all sides. The "
                        << "shadow consumes you and spits you back out. You find yourself back at the intersection and much the worse for wear.";
                        mPlayer->setHealth(mPlayer->getHealth() - 1);
                    } else if (outKeys.size() == 3 || outKeys.size() == 2) {
                        cout << endl << "You approach the crowd of shadows surrounding the train station and feel a repelling force. You decide against continuing and turn back.";
                    } else if (outKeys.size() == 1) {
                        cout << endl << "As you approach the shadowy figures milling about just outside of the train station, you feel a force pushing you back. One of "
                        << "demons almost notices you. You decide it's best to turn back, for now.";
                    } else {
                        cout << endl << "You make your way across the cold expanse of cement towards the train station. The objects filling your pockets feel warm "
                        << "against your torso, almost like they collectively comprise a protective blanket. You notice that the sky, albeit still grey, seems a lot brighter now."
                        << " The station door opens with a small creak, and you enter.";
                        cin.get();
                        mPlayer->setLocation(mStation);
                    }
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // garden
        while (mPlayer->getLocation() == mGarden && mPlayer->getHealth() > 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "northwest") {
                    mPlayer->setLocation(mPark);
                } else if (user_input == "north" || user_input == "south" || user_input == "west" || user_input == "east") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine trees" || user_input == "examine cherry trees" || user_input == "examine tree" || user_input == "examine cherry tree") {
                    cout << endl << "The trees are blooming with life, and add to the sense of beauty of the garden.";
                } else if (user_input == "examine pond") {
                    cout << endl << "The pond is cool and clear.";
                } else if (user_input == "jump in pond" || user_input == "jump into pond") {
                    cout << endl << "You take a quick swim in the pond. It is quite refreshing.";
                } else if (user_input == "examine daffodils" || user_input == "examine daisies" || user_input == "examine lilies" || user_input == "examine orchids" || user_input == "examine gardenias" || user_input == "examine flowers") {
                    cout << endl << "The flowers are variegated and beautiful.";
                } else if (user_input == "pick daffodils" || user_input == "pick daisies" || user_input == "pick lilies" || user_input == "pick orchids" || user_input == "pick gardenias" || user_input == "pick flowers"
                           || user_input == "pick reeds") {
                    cout << endl << "The plants are so virile that they seem implacably rooted to the ground. They don't come up no matter how hard you pull.";
                } else if (user_input == "examine grass") {
                    cout << endl << "It's green and springy.";
                } else if (user_input == "climb trees" || user_input == "climb cherry trees" || user_input == "climb cherry tree" || user_input == "climb tree") {
                    cout << endl << "You climb a cherry tree and repose in its branches amidst the blossoms.";
                } else if (user_input == "examine reed" || user_input == "examine reeds") {
                    cout << endl << "They're brown cattails.";
                } else if (user_input == "dance" || user_input == "frolic" || user_input == "frolic in the meadow") {
                    cout << endl << "You frolic happily.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }
        
        // train station
        while (mPlayer->getLocation() == mStation && mPlayer->getHealth() > 0) {
            getUserInput(user_input);
            
            if (!commonActions(user_input, demonPresent, mPlayer, notice)) {
                if (user_input == "north") {
                    mPlayer->setLocation(mStreetSouthwest);
                } else if (user_input == "examine turnstile" || user_input == "examine turnstiles") {
                    cout << endl << "To your surprise, the card slots of every turnstile already contain cards. It looks like you can just go ahead and pass through.";
                } else if (user_input == "pass through turnstile" || user_input == "pass through turnstiles" || user_input == "pass turnstile" || user_input == "pass turnstiles"
                           || user_input == "walk past turnstile" || user_input == "walk past turnstiles" || user_input == "walk by turnstiles" || user_input == "walk by turnstile") {
                    cout << endl << "You push down the metal rods of one of the turnstiles, and pass through to the platform. The entrance to the train lies invitingly "
                    << "a few yards before you.";
                    pastTurnstile = true;
                } else if (user_input == "enter train" || user_input == "go through train door") {
                    if (!pastTurnstile) {
                        cout << endl << "You can't enter the train if you're not past the turnstiles.";
                    } else {
                        cout << endl << "You step through the train door, which closes behind you. The train is well-lit, with a lavendar carpet and leather seats. You sit down, "
                        << "and the train slowly accelerates. It barrels past the monochrome urban edifices and into the countryside, which passes in a green blur. The train "
                        << "enters a tunnel in the hills, and you are plunged into darkness. The train grinds to a halt as it draws closer to a source of light. Looking up at the "
                        << "electronic display near the ceiling of the train, you find that you have arrived at the final destination. The doors open, and you step out.";
                        mPlayer->setLocationNoDescrip(mRoad);
                    }
                } else if (user_input == "examine ticket counter" || user_input == "examine counter") {
                    cout << endl << "The ticket counter is closed.";
                } else if (user_input == "south" || user_input == "east" || user_input == "west") {
                    cout << endl << "You can't go that way.";
                } else if (user_input == "examine screen" || user_input == "examine aluminum screen") {
                    cout << endl << "It's a lustrous aluminum screen.";
                } else if (user_input == "pull up screen" || user_input == "pull up aluminum screen") {
                    cout << endl << "Your fingers can't fit between the screen and the counter.";
                } else {
                    cout << endl << "Sorry, I didn't understand that.";
                }
            }
        }

    }
    
    // bad ending
    if (mPlayer->getHealth() < 0) {
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
        cin.get();
        cout << endl << endl << "You walk across the platform, through the turnstiles, out the station door, and into the light. To your surprise, the cobblestone road "
        << "lies a few yards in front of you. It's just barely dawn. Tendrils of light creep from the horizon to an indigo sky. A few stars "
        << "twinkle with hope. For a moment, you want to turn back, but you are seized "
        << "with the compulsion to dig in your pocket. You pull out the crumpled grey wad of paper that was once a red paper heart. You stare at it for a few moments... "
        << "You stride towards the cobblestone road. The first few steps are difficult, but you manage to muddle along, determined to find someone who can help you, and someday, "
        << "find Annie.";
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

void demonEncounter(string& user_input, int& notice, int& genOnce, Player *mPlayer, Location *mStreet, Location *mBedroom) {
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
            (getDemon())->interact(mPlayer, mStreet, mBedroom);
            notice = 0;
            genOnce = 0;
            return;
        } else if (user_input == "look at demon" || user_input == "examine demon") {
            cout << endl << "As soon as you lay your gaze on the demon, it whips its head round to stare straight back at you. The enormous eyes, with its black scleras and "
            << "white irises, mesmerize you.";
            notice = 2;
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
                    cout << endl << "The demon looks just about ready to attack.";
                    break;
                case 3:
                    cin.get();
                    cout << endl << "...";
                    cin.get();
                    (getDemon())->interact(mPlayer, mStreet, mBedroom);
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
    } else if (user_input == "look at demon" || user_input == "examine demon") {
        // allow demonEncounter function to handle this
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
    << endl << "    To leave the inventory menu, enter \"EXIT\"."
    << endl << "* Keep an eye out for exits. To use an exit, enter its direction name."
    << endl << "    For example, to take an exit leading to the south, type \"SOUTH\"."
    << endl << "* Examine _everything_."
    << endl << "* To examine something, enter the \"EXAMINE\", followed by the object name."
    << endl << "    For example, to examine a flower, enter \"EXAMINE FLOWER\"."
    << endl << "* For your own sanity's sake, avoid using definite articles in your commands."
    << endl << "* To check your health, enter the command \"HEALTH\"."
    << endl << "* Read carefully."
    << endl << "* Don't fight the demons."
    << endl << "* To bring up this list of tips again, enter the command \"HELP\"."
    << endl << endl << "Good luck!"
    << endl << endl << "* * * * *";
}

void getEnter() {
    string input;
    getline(cin, input);
    while (input.size() != 0) {
        getline(cin, input);
    }
}

void isolation() {
    cout << endl << endl << "Out of apparently nowhere, you see some friendly-looking figures on the horizon. As they come closer, "
    << "you realize that they are your friends. You are shocked that they would even bother to visit. To your dismay, a demon "
    << "reaches them before you can. It drives them away with blows and slashes.";
}
    

