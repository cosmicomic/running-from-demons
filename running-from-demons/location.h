#ifndef LOCATION_H
#define LOCATION_H

#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Exit;

class Location {
    private:
        string name;
        string description;
        vector<Exit*> exits;
        vector<Exit*>::iterator it;
    public:
        Location(string newName, string newDescription);
        void addExit(Exit *newExit);
        string getName();
        string getDescription();
        string dependentDescription();
};
        
#endif
