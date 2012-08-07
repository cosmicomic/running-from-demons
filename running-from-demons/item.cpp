#include "item.h"
using namespace std;

Item::Item (string newName, string newDescription) {
    name = newName;
    description = newDescription;
}

string Item::getName() {
    return name;
}

string Item::getDescription() {
    return description;
}
