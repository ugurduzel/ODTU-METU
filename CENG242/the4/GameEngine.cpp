#include "GameEngine.h"

/*
 YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
 IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
 */


GameEngine::GameEngine(uint boardSize, std::vector<Player *> *players) : board(Board(boardSize,players)), currentRound(0) { }

GameEngine::~GameEngine() {
    std::vector<Player *> *players = board.getPlayers();
    while(players->size()) {
        delete (*players)[0];
        players->erase(players->begin());
    }
    delete players;
}

const Board& GameEngine::getBoard() const { return board; }

Player* GameEngine::operator[](uint id) const {
    std::vector<Player *> *players = board.getPlayers();
    for(int i=0; i<players->size(); i++) {
        if((*players)[i]->getID()==id) {
            return (*players)[i];
        }
    }
    return nullptr;
}

bool GameEngine::isFinished() const {
    std::vector<Player *> *players = board.getPlayers();
    if(players->size()==0) {
        return true;
    }
    else if(players->size()==1 &&
            board.isCoordHill((*(board.getPlayers()))[0]->getCoord()) ) {
        return true;
    }
    return false;
}

void GameEngine::takeTurn() {
    currentRound++;
    std::cout << "-- START ROUND " << currentRound << " --" << std::endl;
    board.updateStorm(currentRound);
    std::vector<Player *> *players = board.getPlayers();
    std::sort(players->begin(), players->begin()+players->size(), [](Player * const & a, Player * const & b) -> bool
              { return a->getID() < b->getID(); } );
    unsigned long prevSize=players->size();
    for(int i=0; i<players->size(); i++) {
        Player * currentPlayer = (*players)[i];
        if(currentPlayer->getHP()>0) {
            Move m = takeTurnForPlayer((currentPlayer->getID()));
            if(m==NOOP && players->size()<prevSize) {
                i--;
            }
            else if(m==ATTACK && players->size()<prevSize) {
                if((*players)[i]!=currentPlayer) {
                    i--;
                }
            }
            prevSize = players->size();
        }
    }
    std::cout << "-- END ROUND " << currentRound << " --" << std::endl;
}

Move GameEngine::takeTurnForPlayer(uint playerID) {
    Player * p = (*this)[playerID];
    std::vector<Move> priorityList = p->getPriorityList();
    std::vector<Coordinate> visibles = board.visibleCoordsFromCoord(p->getCoord());
    int stormDmg = Entity::stormDamageForRound(currentRound);
    if(board.isStormInCoord(p->getCoord())) {
        std::cout << p->getFullName() << "(" << p->getHP() << ") is STORMED! (-" << stormDmg << ")" << std::endl;
        p->reduceHP(stormDmg);
    }
    if(p->isDead()) {
        std::cout << p->getFullName() << "(" << p->getHP() << ") DIED." << std::endl;
        delete p;
        board.removePlayer(p);
        return NOOP;
    }
    for(int i=0; i<priorityList.size(); i++) {
        if(priorityList[i]==NOOP) {
            return NOOP;
        }
        
        if(priorityList[i]==ATTACK) {
            std::vector<Player *> attackables;
            for(int i=0; i<visibles.size(); i++) {
                if(board[visibles[i]]) {
                    attackables.push_back(board[visibles[i]]);
                }
            }
            if(attackables.size()!=0) {
                std::sort(attackables.begin(), attackables.begin()+attackables.size(),
                          [](Player * const & a, Player * const & b) -> bool { return a->getID() < b->getID(); } );
                bool isPlayerDead = p->attackTo(attackables[0]);
                if(isPlayerDead) {
                    std::cout << attackables[0]->getFullName() << "(" << attackables[0]->getHP() << ") DIED." << std::endl;
                    delete attackables[0];
                    board.removePlayer(attackables[0]);
                }
                
                return ATTACK;
            }
        }
        
        
        Move direction = priorityList[i];
        Coordinate hill = Coordinate(board.getSize()/2,board.getSize()/2);
        Coordinate newCoord = board.calculateCoordWithMove(direction, p->getCoord());
        if(newCoord != p->getCoord() && newCoord-hill < p->getCoord()-hill) {
            p -> executeMove(direction);
            return direction;
        }
            
        
    }
    return NOOP;
}

Player * GameEngine::getWinnerPlayer() const {
    if(isFinished()) {
        std::vector<Player *> *players = board.getPlayers();
        if(players->size()==0) {
            return nullptr;
        }
        else {
            return (*players)[0];
        }
    }
    return nullptr;
}





