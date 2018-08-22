#include <cstdlib>
#include <iostream>
#include <string>
#include "Entry.hpp"

using namespace std;

std::ostream &operator<<(std::ostream &out, const Entry& t){
    out <<"{"<< t.title<<","<<t.genre<<","<<t.year<<"}";
    return out;
};


/* TO-DO: method implementations below */
Entry::Entry(): title(""), genre(""), year("") { } 
       
Entry::Entry(string _title, string _genre, string _year) {
	title = _title;
	genre = _genre;
	year = _year;
}
        
string Entry::getTitle() const { return title; }
        
string Entry::getGenre() const { return genre; }
        
string Entry::getYear() const { return year; }
        
bool Entry::operator==(const Entry & rhs) const {
	if(title == rhs.getTitle()) { return  true; }
	return false;
}
   
