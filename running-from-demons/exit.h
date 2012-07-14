#ifndef EXIT_H
#define EXIT_H

#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Location;

class Exit {
    private:
        Location *leadsTo;
        int direction;
        string directionName;
        string shortDirectionName;
    public:
        Exit(int newDirection, Location *newLeadsTo);
        string getDirectionName();
        void setDirectionName(string newDirectionName);
        void setShortDirectionName(string newShortName);
        string getShortDirectionName();
        void setLeadsTo(Location *newLeadsTo);
        Location* getLeadsTo();
};

#endif
        
        
            
