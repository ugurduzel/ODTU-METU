#include "Berserk.h"

/*
 YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
 IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
 */

Berserk::Berserk(uint id, int x, int y) : Player(id,x,y) {
    HP = 100;
}

Armor Berserk::getArmor() const { return WOODEN; }
Weapon Berserk::getWeapon() const { return PISTOL; }
std::vector<Move> Berserk::getPriorityList() const {
    std::vector<Move> priorityList;
    priorityList.push_back(ATTACK);
    priorityList.push_back(UP);
    priorityList.push_back(LEFT);
    priorityList.push_back(DOWN);
    priorityList.push_back(RIGHT);
    return priorityList;
}

const std::string Berserk::getFullName() const {
    return "Berserk" + getBoardID();
}

Color::Code Berserk::getColorID() const {
    return Color::FG_RED;
}

