#include "Miner.h"




/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

int Miner::getNextAvailableBlockchainID() const {
	return depo.size();
}


bool Miner::is_in(Koin* p) const {
	int l = soft_forked_list.size();
	for(int i=0; i<l; ++i) {
		if(soft_forked_list[i]==p) {
			return true;
		}
	}
	return false;
}

bool Miner::is_inb(Blockchain *p) const {
	int l = soft_forked.size();
	for(int i=0; i<l; ++i) {
		if(soft_forked[i]==p) {
			return true;
		}
	}
	return false;
}


Miner::Miner(std::string name) : nm(name), depo(1,NULL), soft_forked(1,NULL), soft_forked_list(1,NULL) { 
	depo.pop_back();
	soft_forked.pop_back();
	soft_forked_list.pop_back();
}


void Miner::createNewBlockchain() {
	depo.push_back(new Blockchain(getNextAvailableBlockchainID()));
}


Miner::~Miner() {
	int k = soft_forked.size();
	for(int i=0; i<k; ++i) {
		(soft_forked[i])->setHead(NULL);
	}
	int l = depo.size();
	for(int i=0; i<l; ++i) {
		delete depo[i];
	}
	k = soft_forked.size();
	depo.clear();
	soft_forked.clear();
	soft_forked_list.clear();
}


void Miner::mineUntil(int cycleCount) {
	int l = depo.size();
	for(int i=0; i<l; ++i) {
		for(int j=0; j<cycleCount; ++j) {
			++(*(depo[i]));
		}
	}
}


void Miner::demineUntil(int cycleCount) {
	int l = depo.size();
	for(int i=0; i<l; ++i) {
		for(int j=0; j<cycleCount; ++j) {
			if(is_in((depo[i])->son())) {
				break;
			}
			--(*(depo[i]));
		}
	}
}


double Miner::getTotalValue() const {
	int l = depo.size();
	double thot = 0;
	for(int i=0; i<l; ++i) {
		if(is_inb(depo[i])) {
			continue;
		}
		thot+=(depo[i])->getTotalValue();
	}
	return thot;
}


long Miner::getBlockchainCount() const {
	return depo.size();

}


Blockchain* Miner::operator[](int id) const {
	int l = depo.size();
	for(int i=0; i<l; ++i) {
		if((depo[i])->getID()==id) {
			return depo[i];
		}
	}
	return NULL;
}





std::ostream& operator<<(std::ostream& os, const Miner& miner) {
	os<<std::fixed<<std::setprecision(Utilizer::koinPrintPrecision());
	os<<"-- BEGIN MINER --\nMiner name: "<<miner.nm<<"\nBlockchain count: ";
	os<<miner.getBlockchainCount()<<"\nTotal value: "<<miner.getTotalValue() << "\n\n";
	int l = (miner.depo).size();
	for(int i=0; i<l; ++i) {
		os<<*((miner.depo)[i])<<"\n";
	}
	os<<"\n-- END MINER --\n";
	return os;
}



bool Miner::softFork(int blockchainID) {
	Blockchain *b = (*this)[blockchainID], *n;
	if(!b) { return false;}
	Koin *k=b->son();
	int m = getNextAvailableBlockchainID();
	n = new Blockchain(m, k);
	depo.push_back(n);
	soft_forked.push_back(n);
	soft_forked_list.push_back(k);
	return true;
}


bool Miner::hardFork(int blockchainID) {
	Blockchain *b = (*this)[blockchainID], *n;
	if(!b) { return false;}
	Koin *k=new Koin((b->son())->getValue());
	int m = getNextAvailableBlockchainID();
	n = new Blockchain(m, k);
	depo.push_back(n);
	return true;
}







