#include "Koin.h"
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Koin::Koin(double value) : value(value), next(NULL), numberOfForkedTimes(0), numberOfForkedTimesForTotal(0) { }
double Koin::getValue() const { return value; }
Koin* Koin::getNext() const { return next; }
void Koin::setNext(Koin *next) { this->next = next; }

Koin::Koin(const Koin& rhs) {
    value = rhs.value;
    next = rhs.next;
    numberOfForkedTimes = rhs.numberOfForkedTimes;
    numberOfForkedTimesForTotal = rhs.numberOfForkedTimesForTotal;
}

Koin::~Koin() { }

Koin& Koin::operator=(const Koin& rhs) {
    value = rhs.value;
    next = rhs.next;
    numberOfForkedTimes = rhs.numberOfForkedTimes;
    return *this;
}

Koin& Koin::operator*=(int multiplier) {
    value *= multiplier;
    return *this;
}

Koin& Koin::operator/=(int divisor) {
    value /= divisor;
    return *this;
}

const double Koin::abs(double number) const {
    return number<0 ? (-1)*number : number;
}

bool Koin::operator==(const Koin& rhs) const {
    double errorMargin = Utilizer::doubleSensitivity();
    if(abs(value-rhs.value)>errorMargin) {
        return false;
    }
    Koin *lhsPtr = next;
    Koin *rhsPtr = rhs.next;
    bool notEqualFlag = false;
    while(lhsPtr && rhsPtr) {
        double lhsValue = lhsPtr->value;
        double rhsValue = rhsPtr->value;
        if(abs(lhsValue-rhsValue)>errorMargin) { // Not equal pair exists
            notEqualFlag = true;
        }
        lhsPtr = lhsPtr->next;
        rhsPtr = rhsPtr->next;
    }
    return (!lhsPtr && !rhsPtr) ? !notEqualFlag : false;
}

bool Koin::operator!=(const Koin& rhs) const {
    return !(*this==rhs);
}

std::ostream& operator<<(std::ostream& os, const Koin& koin) {
    int givenPrecision = Utilizer::koinPrintPrecision();
    os << std::fixed;
    os << std::setprecision(givenPrecision);
    os << koin.value << "--";
    Koin *p = koin.next;
    while(p) {
        os << p->value << "--";
        p = p->next;
    }
    os << "|";
    return os;
}

void Koin::softForked() {
    numberOfForkedTimes++;
    numberOfForkedTimesForTotal++;
}




