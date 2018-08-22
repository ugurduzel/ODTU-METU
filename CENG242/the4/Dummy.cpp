#include "Dummy.h"

/*
 YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
 IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
 */

Dummy::Dummy(uint id, int x, int y) : Player(id,x,y) {
    HP = 1000;
}

Armor Dummy::getArmor() const { return NOARMOR; }
Weapon Dummy::getWeapon() const { return NOWEAPON; }
std::vector<Move> Dummy::getPriorityList() const {
    std::vector<Move> priorityList;
    priorityList.push_back(NOOP);
    return priorityList;
}

const std::string Dummy::getFullName() const {
    return "Dummy" + getBoardID();
}

Color::Code Dummy::getColorID() const {
    return Color::FG_DEFAULT;
}

