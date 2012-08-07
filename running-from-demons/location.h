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
    public:
        Location(string newName, string newDescription);
        string getName();
        string getDescription();
        string dependentDescription();
};
        
#endif
