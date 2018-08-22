#include "Koin.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Koin::Koin(double value) : value(value) { next=NULL;}



Koin::Koin(const Koin& rhs) = default;
Koin& Koin::operator=(const Koin& rhs) = default;
Koin::~Koin() = default;


double Koin::getValue() const {
	return value;
}


Koin* Koin::getNext() const {
	return next;
}


void Koin::setNext(Koin *next) {
	this->next=next;
}


bool Koin::operator==(const Koin& rhs) const {
	const Koin *p;
	const Koin *q;
	double senser = Utilizer::doubleSensitivity();
	p=this;
	q=&rhs;
	while(q || p) {
		if(!(p && q)) {
			return false;
		}
		if(((p->getValue() - q->getValue() > 0) ? p->getValue() - q->getValue() : (-(p->getValue() - q->getValue()))) > senser) {
			return false;
		}
		q=q->next;
		p=p->next;
	}
	return true;
}


bool Koin::operator!=(const Koin& rhs) const {
	return !(*this == rhs);
}


Koin& Koin::operator*=(int multiplier) {
	value*=multiplier;
	return *this;
}


Koin& Koin::operator/=(int divisor) {
	value/=divisor;
	return *this;
}


std::ostream& operator<<(std::ostream& os, const Koin& koin) {
	os<<std::fixed<<std::setprecision(Utilizer::koinPrintPrecision());
	const Koin *p = &koin;
	while(p) {
		os<<p->value<<"--";
		p=p->next;
	}
	os<<"|";
	return os;
}













