#ifndef _author_h__
#define _author_h__

#include "book.hpp"
#include <cstring>

class AuthorComparator
{
  	public:
  		
	    bool operator( ) (const Book::SecondaryKey & key1, 
	                      const Book::SecondaryKey & key2) const {
	      	//if key1 is less than key2 wrt specifications
	      	//return true
	      	//otherwise
	      	//return false
			std::string aut1 = key1.getAuthor();
			std::string aut2 = key2.getAuthor();
			for(int i=0; aut1[i]; i++) { aut1[i] = tolower(aut1[i]); }
			for(int i=0; aut2[i]; i++) { aut2[i] = tolower(aut2[i]); }
			if(aut1<aut2) {
				return true;
			}
			else if(aut2<aut1) { 
				return false;
			}
			std::string tit1 = key1.getTitle();
			std::string tit2 = key2.getTitle();
			for(int i=0; tit1[i]; i++) { tit1[i] = tolower(tit1[i]); }
			for(int i=0; tit2[i]; i++) { tit2[i] = tolower(tit2[i]); }
			if(tit1<tit2) {
				return true;
			}
			return false;
		}
};

#endif

