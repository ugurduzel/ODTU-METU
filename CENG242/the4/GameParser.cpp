#include "GameParser.h"

/*
 YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
 IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
 */


std::pair<int, std::vector<Player *> *> GameParser::parseFileWithName(const std::string& filename) {
    std::ifstream file;
    std::string line;
    file.open(filename.c_str());
    int boardSize;
    int playerCount;
    std::vector<Player *> *playerVector;
    
    playerVector = new std::vector<Player *>;
    
    getline(file,line);
    line = line.substr(line.find(":")+2);
    boardSize = std::stoi(line);
    
    getline(file,line);
    
    while(file >> line) {
        std::size_t first = line.find("::",0,2);
        std::size_t second = line.find("::",first+1,2);
        std::size_t third = line.find("::",second+1,2);
        std::string id = line.substr(0,first);
        std::string name = line.substr(first+2,second-(first+2));
        std::string x = line.substr(second+2,third-(second+2));
        std::string y = line.substr(third+2);
        int x_coord = std::stoi(x);
        int y_coord = std::stoi(y);
        int iid = std::stoi(id);
        Player *p;
        if(name=="Ambusher") {
            p = new Ambusher(iid,x_coord,y_coord);
        }
        else if(name=="Berserk") {
            p = new Berserk(iid,x_coord,y_coord);
        }
        else if(name=="Pacifist") {
            p = new Pacifist(iid,x_coord,y_coord);
        }
        else if(name=="Tracer") {
            p = new Tracer(iid,x_coord,y_coord);
        }
        else if(name=="Dummy"){
            p = new Dummy(iid,x_coord,y_coord);
        }
        playerVector->push_back(p);
    }
    file.close();
    std::pair<int, std::vector<Player *> *> pr(boardSize,playerVector);
    return pr;
}

