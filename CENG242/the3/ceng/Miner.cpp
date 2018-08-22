#include "Miner.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

int Miner::getNextAvailableBlockchainID() const {
    return minerCount;
}

Miner::Miner(std::string name) : name(name), minerCount(0) { }

Miner::~Miner() {
    for(long j=0; j<minerCount; j++) {;
        if(miner[j]) {
            delete miner[j];
            miner[j] = NULL;
        }
    }
    miner.clear();
}

double Miner::getTotalValue() const {
    double total = 0;
    for(long j=0; j<minerCount; j++) {
        if(miner[j]->getHead()==NULL) {
            total += 0;
            continue;
        }
        if(miner[j]->getHead()->numberOfForkedTimesForTotal==0) {
            total += (miner[j])->getTotalValue();
        }
        else {
            miner[j]->getHead()->numberOfForkedTimesForTotal -= 1;
        }
    }
    for(long j=0; j<minerCount; j++) {
        if(miner[j]->getHead()==NULL) {
            continue;
        }
        miner[j]->getHead()->numberOfForkedTimesForTotal = miner[j]->getHead()->numberOfForkedTimes;
    }
    return total;
}
long Miner::getBlockchainCount() const {
    long len = miner.size();
    return len;
}

void Miner::createNewBlockchain() {
    int newID = getNextAvailableBlockchainID();
    Blockchain *bp = new Blockchain(newID);
    minerCount++;
    miner.push_back(bp);
}

void Miner::mineUntil(int cycleCount) {
    for(int i=0; i<cycleCount; i++) {
        for(long j=0; j<minerCount; j++) {
            ++(*miner[j]);
        }
    }
}

void Miner::demineUntil(int cycleCount) {
    for(int i=0; i<cycleCount; i++) {
        for(long j=0; j<minerCount; j++) {
            --(*miner[j]);
        }
    }
}

Blockchain* Miner::operator[](int id) const {
    for(int j=0; j<minerCount; j++) {
        if(id == miner[j]->getID()) {
            return miner[j];
        }
    }
    return NULL;
}

std::ostream& operator<<(std::ostream& os, const Miner& miner) {
    int givenPrecision = Utilizer::koinPrintPrecision();
    os << std::fixed;
    os << std::setprecision(givenPrecision);
    os << "-- BEGIN MINER --" << std::endl;
    os << "Miner name: " << miner.name << std::endl;
    os << "Blockchain count: " << miner.getBlockchainCount() << std::endl;
    os << "Total value: " << miner.getTotalValue() << std::endl << std::endl;
    for(int j=0; j<miner.getBlockchainCount(); j++) {
        os << *miner[j] << std::endl;
        if(j+1==miner.getBlockchainCount()) {
            break;
        }
    }
    os << std::endl << "-- END MINER --" << std::endl;
    return os;
}

bool Miner::softFork(int blockchainID) {
    Blockchain *fork = miner[blockchainID];
    if(fork) {
        Koin *tail = fork->getHead();
        if(!tail) {
            createNewBlockchain();
            return true;
        }
        while(tail->getNext()) {
            tail = tail->getNext();
        }
        int nextID = getNextAvailableBlockchainID();
        miner.push_back(new Blockchain(nextID,tail));
        minerCount++;
        tail->softForked();
        return true;
    }
    return false;
}

bool Miner::hardFork(int blockchainID) {
    Blockchain *fork = miner[blockchainID];
    if(fork) {
        Koin *tail = fork->getHead();
        if(!tail) {
            createNewBlockchain();
            return true;
        }
        while(tail->getNext()) {
            tail = tail->getNext();
        }
        Koin *copyTail = new Koin(tail->getValue());
        int nextID = getNextAvailableBlockchainID();
        miner.push_back(new Blockchain(nextID,copyTail));
        minerCount++;
        return true;
    }
    return false;
}
