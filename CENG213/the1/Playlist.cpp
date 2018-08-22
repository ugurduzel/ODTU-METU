#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist() {
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const {
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print() {
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory() {
    cout<<"[HISTORY]";
    history.print();
}

/* TO-DO: method implementations below */

void Playlist::load(string fileName) {
	ifstream file;
	string line;

	file.open(fileName.c_str());

	while(file.good()) {
		getline(file, line);

		int len1 = line.find_first_of(";", 0);
		int len2 = line.find_last_of(";", line.npos)-len1-1;
		int len3 = line.length() - len2 - len1 - 2;
		string temp_title = line.substr(0,len1);
		string temp_genre = line.substr(line.find_first_of(";", 0)+1,len2);
		string temp_year = line.substr(line.find_last_of(";", line.npos)+1,len3);
		Entry temp_entry(temp_title,temp_genre,temp_year);
		insertEntry(temp_entry);
	}

	file.close();
}

void Playlist::insertEntry(const Entry &e) {
	Node<Entry> *traverse = entries.getHead();
	while(traverse) {
		if( traverse->getData() == e ) { return; }
		traverse = traverse -> getNext();
	}
	entries.insertNode(entries.getTail(), e);
	HistoryRecord h(INSERT,e);
	history.push(h);
}
	

void Playlist::deleteEntry(const string &_title) {
	Entry temp_entry(_title);
	Node<Entry> *toBeDeletedNode = entries.findNode(temp_entry);
	if(!toBeDeletedNode) { 
		return; 
	}
	HistoryRecord h(DELETE, toBeDeletedNode->getData());
	history.push(h);
	Node<Entry> *theOneBefore = entries.findPrev(temp_entry);
	entries.deleteNode(theOneBefore);
}

void Playlist::shift(const string &_title1, const string &_title2) {
	Entry e1(_title1), e2(_title2);
	Node<Entry> *before1 = entries.findPrev(e1);
	Node<Entry> *swap1 = entries.findNode(e1);
	Node<Entry> *swap2 = entries.findNode(e2);
	if(!before1) {
		//Swap1 is head, delete it and insert to the place
		//This is to make swap2 the head otherwise we can't alter the head
		Entry e3(swap1->getData().getTitle(),swap1->getData().getGenre(),swap1->getData().getYear());
		entries.deleteNode(before1);
		entries.insertNode(swap2,e3);	
		return;
	}
	else if(swap2 == entries.getTail()) {
		//Swap2 is tail, delete it and insert to the place
		//This is to make swap1 the tail otherwise we can't alter the tail
		Entry e3(swap2->getData().getTitle(),swap2->getData().getGenre(),swap2->getData().getYear());
		entries.deleteNode(swap1);
		entries.insertNode(before1,e3);	
		return;
	}
	swap1->setNext(swap2->getNext());
	swap2->setNext(swap1);
	before1->setNext(swap2);
}

void Playlist::swap(const string &_title1, const string &_title2) {

	if(_title1 == _title2) {
		return;
	}

	Entry e1(_title1), e2(_title2);

	Node<Entry> *before1 = entries.findPrev(e1), *before2 = entries.findPrev(e2);
	
	Node<Entry> *swap1 = entries.findNode(e1), *swap2 = before2->getNext();

	if(swap1 == before2){
		//If they are next to each other
		shift(_title1,_title2);
	}
	else if(swap2 == entries.getTail() and !before1) {
		//Swapping head and tail

		swap2->setNext(swap1->getNext());
		before2->setNext(swap1);
		swap1->setNext(NULL);
		entries.setHead(swap2);
		entries.setTail(swap1);
		
	}
	else if(!before1) {
		//Swapping involves head
		Node<Entry> *temp = swap1->getNext();
		swap1->setNext(swap2->getNext());
		swap2->setNext(temp);
		before2->setNext(swap1);
		entries.setHead(swap2);
	}
	else if(swap2 == entries.getTail()) {
		//Swapping involves tail
		swap2->setNext(swap1->getNext());
		before1->setNext(swap2);
		before2->setNext(swap1);
		entries.setTail(swap1);
		swap1->setNext(NULL);
	}
	else {
		before1->setNext(swap2);
		before2->setNext(swap1);
		Node<Entry> *temp = swap1->getNext();
		swap1->setNext(swap2->getNext());
		swap2->setNext(temp);
	}

}

void Playlist::moveLeft(const string &title) {
	Entry e(title);
	Node<Entry> *leftOne = entries.findPrev(e);
	if(!leftOne) { return; }
	shift(leftOne->getData().getTitle(),title);
}

void Playlist::moveRight(const string &title) {
	Entry e(title);
	Node<Entry> *rightOne = (entries.findNode(e))->getNext();
	if(!rightOne) { return; }
	shift(title,rightOne->getData().getTitle());
}

void Playlist::reverse() {
	MyStack <Entry> stack;
	Node<Entry> *p = entries.getHead();
	while(p) {
		stack.push(p->getData());
		entries.deleteNode(NULL);
		p = entries.getHead();
	}
	entries.setHead(NULL);
	entries.setTail(NULL);
	p = stack.Top();
	while(!stack.isEmpty()) {
		entries.insertNode(entries.getTail(),p->getData());
		stack.pop();
		p = stack.Top();
	}
	HistoryRecord h(REVERSE);
	history.push(h);
}


void Playlist::sort() {
	Node<Entry> *pass = entries.getHead();
	Node<Entry> *traverse, *temp_pass;
	string temp, min;
	while(pass) {
		min = pass->getData().getTitle();
		traverse = pass->getNext();
		//cout << "First min is (also the pass is): " << min << endl;
		while(traverse) {
			temp = traverse->getData().getTitle();
			if(temp<min) {
				min = temp; 
				//cout << "Min is now : " << min << endl;
			}
			traverse = traverse->getNext();
		}
		//cout << "Swapping : " << pass->getData().getTitle() << " " << min << endl << endl;
		temp_pass = pass->getNext();
		swap(pass->getData().getTitle(),min);
		pass = temp_pass;
	}

}


void Playlist::merge(const Playlist & pl) {
	Node<Entry> *first_list_traverse = entries.getHead();
	Node<Entry> *second_list_traverse = pl.entries.getHead();
	if(!first_list_traverse) {
		while(second_list_traverse) {
			Entry e2 = second_list_traverse->getData();
			Entry temp_entry(e2.getTitle(),e2.getGenre(),e2.getYear());
			if(!entries.getHead()) {
				entries.insertNode(NULL,temp_entry);
				second_list_traverse = second_list_traverse->getNext();
				continue;
			}
			entries.insertNode(entries.getTail(),temp_entry);
			second_list_traverse = second_list_traverse->getNext();
		}	
	}
	
	while(second_list_traverse) {
		Entry e1 = first_list_traverse->getData();
		Entry e2 = second_list_traverse->getData();
		if( e2.getTitle() <= e1.getTitle() ) {
			Entry temp_entry(e2.getTitle(),e2.getGenre(),e2.getYear());
			if(first_list_traverse == entries.getHead()) {
				entries.insertNode(NULL,temp_entry);
				second_list_traverse = second_list_traverse->getNext();
				continue;
			}
			entries.insertNode(entries.findPrev(e1),temp_entry);
			second_list_traverse = second_list_traverse->getNext();
			continue;
		}	
		else if(first_list_traverse==entries.getTail()) {
			Entry temp_entry(e2.getTitle(),e2.getGenre(),e2.getYear());
			entries.insertNode(first_list_traverse,temp_entry);
			second_list_traverse = second_list_traverse->getNext();
			continue;
		}
		first_list_traverse = first_list_traverse->getNext();
	}
}

Entry Playlist::find_index(int index) {
	
	Node<Entry> *p = entries.getHead();
	int i = 0;
	while(i!=index) {
		p = p->getNext();
		i++;
	}
	return p->getData();
}

void Playlist::shuffle() {
	int n = entries.getSize();
	for(int i = 0; i < n-1; i++) {
		int j = getRandomNumber(i,n);
		Entry e1 = find_index(i);
		Entry e2 = find_index(j);
		swap(e1.getTitle(),e2.getTitle());
	}
}

void Playlist::undo() {
	if(history.Top()->getData().getOperation() == INSERT) {
		Entry e = history.Top()->getData().getEntry();
		deleteEntry(e.getTitle());
	}
	else if(history.Top()->getData().getOperation() == DELETE) {
		Entry e = history.Top()->getData().getEntry();
		insertEntry(e);
	}
	else if(history.Top()->getData().getOperation() == REVERSE) {
		reverse();
	}
	history.pop();
	history.pop();
}

