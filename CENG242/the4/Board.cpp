#include "Board.h"

/*
 YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
 IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
 */


Board::Board(uint boardSize, std::vector<Player *> *players) : boardSize(boardSize), players(players), stormWidth(0) { }

uint Board::getSize() const { return boardSize; }

Board::~Board() = default;

bool Board::isCoordInBoard(const Coordinate& coord) const {
    if(coord.x < 0 || coord.y < 0 || coord.x >= boardSize || coord.y >= boardSize ) {
        return false;
    }
    return true;
}

bool Board::isStormInCoord(const Coordinate &coord) const {
    if(stormWidth <= coord.x && coord.x < boardSize-stormWidth && stormWidth <= coord.y && coord.y < boardSize-stormWidth) {
        return false;
    }
    if(isCoordHill(coord) || !isCoordInBoard(coord)) {
        return false;
    }
    return true;
}

bool Board::isCoordHill(const Coordinate& coord) const {
    if(coord.x==boardSize/2 && coord.y==boardSize/2) {
        return true;
    }
    return false;
}

Player *Board::operator[](const Coordinate& coord) const {
    for(int i=0; i<players->size(); i++) {
        if((*players)[i]->getCoord() == coord) {
            return (*players)[i];
        }
    }
    return nullptr;
}

Coordinate Board::calculateCoordWithMove(Move move, const Coordinate &coord) const {
    if(move==NOOP || move==ATTACK || !isCoordInBoard(coord+move) || (*this)[coord+move]) {
        return coord;
    }
    return coord+move;
}

std::vector<Coordinate> Board::visibleCoordsFromCoord(const Coordinate &coord) const {
    std::vector<Coordinate> visible;
    if(!isCoordInBoard(coord)) {
        return visible;
    }
    if(isCoordInBoard(coord+UP)) {
        visible.push_back(coord+UP);
    }
    if(isCoordInBoard(coord+DOWN)) {
        visible.push_back(coord+DOWN);
    }
    if(isCoordInBoard(coord+LEFT)) {
        visible.push_back(coord+LEFT);
    }
    if(isCoordInBoard(coord+RIGHT)) {
        visible.push_back(coord+RIGHT);
    }
    return visible;
}

void Board::updateStorm(uint currentRound) {
    stormWidth = Entity::stormWidthForRound(currentRound);
}

std::vector<Player *> * Board::getPlayers() const { return players; }

void Board::removePlayer(Player * p) {
    for(std::vector<Player *>::iterator it=players->begin(); it!=players->end(); ++it) {
        if(*it==p) {
            players->erase(it);
            break;
        }
    }
}
