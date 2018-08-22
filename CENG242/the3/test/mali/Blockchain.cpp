#include "Blockchain.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Blockchain::Blockchain(int id) : id(id) { head=NULL; }


Blockchain::Blockchain(int id, Koin *head) : id(id), head(head) { }



void Blockchain::emp() {
	Koin *p = head;
	Koin *q;
	while(p) {
		q=p->getNext();
		delete p;
		p=q;
	}
	head=NULL;
}

void Blockchain::setHead(Koin *p) {
	head=p;
}


Blockchain::Blockchain(const Blockchain& rhs) : id(rhs.id) {
	Koin *p = rhs.head, *q=NULL;
	while(p) {
		if(!q) {
			head = new Koin(p->getValue());
			head->setNext(NULL);
			q=head;
		}
		else {
			q->setNext(new Koin(p->getValue()));
			q=q->getNext();
			q->setNext(NULL);
		}
		p=p->getNext();
	}
}


Blockchain& Blockchain::operator=(Blockchain&& rhs) noexcept {
	emp();
	head=rhs.head;
	rhs.head=NULL;
	return *this;
}


Blockchain::~Blockchain() {
	emp();
}


int Blockchain::getID() const {
	return id;
}


Koin* Blockchain::getHead() const {
	return head;
}


double Blockchain::getTotalValue() const {
	double total=0;
	Koin *p = head;
	while(p) {
		total+=p->getValue();
		p=p->getNext();
	}
	return total;
}


long Blockchain::getChainLength() const {
	long l=0;
	Koin *p = head;
	while(p) {
		++l;
		p=p->getNext();
	}
	return l;
}


void Blockchain::operator++() {
	Koin *p = son();
	if(!p) {
		head=new Koin(Utilizer::fetchRandomValue());
		head->setNext(NULL);
		return;
	}
	p->setNext(new Koin(Utilizer::fetchRandomValue()));
	p=p->getNext();
	p->setNext(NULL);
}


void Blockchain::operator--() {
	Koin *p = head;
	if(!p) {
		return;
	}
	if(!(p->getNext())) {
		delete p;
		head=NULL;
		return;
	}
	while(p) {
		if(p->getNext() && !((p->getNext())->getNext())) {
			delete (p->getNext());
			p->setNext(NULL);
			return;
		}
		else {
			p=p->getNext();
		}
	}
}


Blockchain& Blockchain::operator*=(int multiplier) {
	Koin *p = head;
	while(p) {
		*p *= multiplier;
		p=p->getNext();
	}
	return *this;
}


Blockchain& Blockchain::operator/=(int divisor) {
	Koin *p = head;
	while(p) {
		*p /= divisor;
		p=p->getNext();
	}
	return *this;
}

Koin* Blockchain::son() {
	if(!head) {
		return NULL;
	}
	Koin *p = head;
	while(p) {
		if(p->getNext()==NULL) {
			return p;
		}
		p=p->getNext();
	}
	return NULL;
}


std::ostream& operator<<(std::ostream& os, const Blockchain& blockchain) {
	os<<std::fixed<<std::setprecision(Utilizer::koinPrintPrecision());

	if(blockchain.getChainLength() == 0) {
		os<<"Block "<<blockchain.id<<": "<<"Empty.";
		return os;
	}
	os<<"Block "<<blockchain.id<<": "<< *(blockchain.head)  << "(" << blockchain.getTotalValue() << ")";
	return os;
}



