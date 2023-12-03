#include "pet.h"
#include <iostream>

using namespace std;

string getPetType() {
    return "human (his name is Rick)";
}

bool patPet(int times_unused) {
    cout << "You pat Rick\n";
    return true;
}
