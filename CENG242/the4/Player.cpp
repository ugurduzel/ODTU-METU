#include "Player.h"

Player::Player(uint id, int x, int y) :id(id), coordinate(Coordinate(x,y)) { }

Player::~Player() = default;

uint Player::getID() const { return id; }

const Coordinate& Player::getCoord() const { return coordinate; }

int Player::getHP() const { return HP; }

std::string Player::getBoardID() const {
    std::string s;
    s.push_back( (char) (id/10+48) );
    s.push_back( (char) (id%10+48) );
    return s;
}

bool Player::isDead() const { return HP<=0 ? true : false; }

void Player::executeMove(Move move) {
    std::string moveDirection;
    if(move==UP) moveDirection = "UP.";
    else if(move==DOWN) moveDirection = "DOWN.";
    else if(move==LEFT) moveDirection = "LEFT.";
    else moveDirection = "RIGHT.";
    Coordinate newCoord = coordinate+move;
    if(newCoord!=coordinate) {
        std::cout << this->getFullName() << "(" << this->getHP() <<") moved " << moveDirection << std::endl;
    }
    coordinate = newCoord;
}

bool Player::attackTo(Player *player) {
    if(this==player) {
        return player->isDead();;
    }
    int damage = Entity::damageForWeapon(this->getWeapon())-Entity::damageReductionForArmor(player->getArmor());
    std::cout << this->getFullName() << "(" << this->getHP() <<") ATTACKED " << player->getFullName()<< "(" << player->getHP() <<")! (-" << damage << ")" << std::endl;
    player->HP -= damage<0 ? 0 : damage;
    return player->isDead();
}

void Player::reduceHP(int reduction) { HP -= reduction; }

