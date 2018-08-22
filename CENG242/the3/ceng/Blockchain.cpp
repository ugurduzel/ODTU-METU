#include "Blockchain.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Blockchain::Blockchain(int id) : id(id), head(NULL) { }
Blockchain::Blockchain(int id, Koin *head) : id(id), head(head) { }

int Blockchain::getID() const { return id; }
Koin* Blockchain::getHead() const { return head; }

double Blockchain::getTotalValue() const {
    double total = 0;
    Koin *p = head;
    while(p) {
        total += p->getValue();
        p = p->getNext();
    }
    return total;
}
long Blockchain::getChainLength() const {
    long len = 0;
    Koin *p = head;
    while(p) {
        len++;
        p = p->getNext();
    }
    return len;
}
Blockchain& Blockchain::operator*=(int multiplier) {
    Koin * p = head;
    while(p) {
        *p*=multiplier;
        p = p->getNext();
    }
    return *this;
}
Blockchain& Blockchain::operator/=(int divisor) {
    Koin * p = head;
    while(p) {
        *p /= divisor;
        p = p->getNext();
    }
    return *this;
}

void Blockchain::operator++() {
    float newKoinValue = Utilizer::fetchRandomValue();
    Koin *newKoin = new Koin(newKoinValue);
    if(!head) {
        head = newKoin;
        return;
    }
    Koin *p = head;
    while(p->getNext()) {
        p = p->getNext();
    }
    p->setNext(newKoin);
}

void Blockchain::operator--() {
    if(head==NULL) {
        return;
    }
    Koin *p = head;
    if(!p->getNext() && p->numberOfForkedTimes==0) {
        delete head;
        head = NULL;
        return;
    }
    else if(!p->getNext()) {
        return ;
    }
    while(p->getNext()->getNext()) {
        p = p->getNext();
    }
    if(p->getNext()->numberOfForkedTimes>0) {
        return;
    }
    delete p->getNext();
    p->setNext(NULL);
}

Blockchain::~Blockchain() {
    Koin *p = head;
    while(p && p->numberOfForkedTimes==0) {
        Koin *temp = p->getNext();
        p->setNext(NULL);
        delete p;
        p = temp;
    }
    if(p && p->numberOfForkedTimes>0) {
        p->numberOfForkedTimes -= 1;
    }
    head = NULL;
}

Blockchain::Blockchain(const Blockchain& rhs) : id(rhs.id) {
    head = new Koin(rhs.head->getValue());
    Koin *lhsPtr = head->getNext();
    Koin *rhsPtr = rhs.head->getNext();
    while(rhsPtr) {
        Koin *temp = new Koin(rhsPtr->getValue());
        lhsPtr->setNext(temp);
        lhsPtr = lhsPtr->getNext();
        rhsPtr = rhsPtr->getNext();
    }
}

Blockchain& Blockchain::operator=(Blockchain&& rhs) noexcept {
    Koin *p = head;
    while(p && p->numberOfForkedTimes==0) {
        Koin *temp = p->getNext();
        p->setNext(NULL);
        delete p;
        p = temp;
    }
    if(p && p->numberOfForkedTimes>0) {
        p->numberOfForkedTimes -= 1;
    }
    head = NULL;
    /*
    head = new Koin(rhs.head->getValue());
    Koin *lhsPtr = head->getNext();
    Koin *rhsPtr = rhs.head->getNext();
    while(rhsPtr) {
        Koin *temp = new Koin(rhsPtr->getValue());
        lhsPtr->setNext(temp);
        lhsPtr = lhsPtr->getNext();
        rhsPtr = rhsPtr->getNext();
    }
    */
    head=rhs.head;
    rhs.head=NULL;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Blockchain& blockchain) {
    int givenPrecision = Utilizer::koinPrintPrecision();
    os << std::fixed;
    os << std::setprecision(givenPrecision);
    if(!blockchain.head) {
        os << "Block " << blockchain.getID() << ": Empty.";
    }
    else {
        os << "Block " << blockchain.getID() << ": " << *blockchain.head;
        os << "(" << blockchain.getTotalValue() << ")";
    }
    return os;
}
