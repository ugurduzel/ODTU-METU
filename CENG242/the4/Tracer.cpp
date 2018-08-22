#include "Tracer.h"

/*
 YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
 IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
 */

Tracer::Tracer(uint id, int x, int y) : Player(id,x,y) {
    HP = 100;
}

Armor Tracer::getArmor() const { return BRICK; }
Weapon Tracer::getWeapon() const { return SHOVEL; }
std::vector<Move> Tracer::getPriorityList() const {
    std::vector<Move> priorityList;
    priorityList.push_back(UP);
    priorityList.push_back(LEFT);
    priorityList.push_back(DOWN);
    priorityList.push_back(RIGHT);
    priorityList.push_back(ATTACK);
    return priorityList;
}

const std::string Tracer::getFullName() const {
    return "Tracer" + getBoardID();
}

Color::Code Tracer::getColorID() const {
    return Color::FG_YELLOW;
}

