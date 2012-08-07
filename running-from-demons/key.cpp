#include "key.h"
using namespace std;

Key::Key (string newName, string newDescription) : Item(newName, newDescription)
{
    name = newName;
    description = newDescription;
}
