#include "Article.h"

Article::Article( int table_size,int h1_param, int h2_param ) 
: table_size(table_size), h1_param(h1_param), h2_param(h2_param) {    
	n = 0;
	table = new std::pair<std::string, int>[table_size];
	std::pair<std::string, int> empty(EMPTY_KEY,EMPTY_INDEX);
	for(int i=0; i<table_size; i++) {
		table[i] = empty;
	}
}

Article::~Article() {
	delete []table;
}

int Article::get( std::string key, int nth, std::vector<int> &path ) const {
  	int occurence = 1;
	for(int i=0; i<table_size; i++) {
		int table_index = hash_function(key, i);
		if(i) {
			path.push_back(table_index);
		}	
		if(table[table_index].first == key) {
			if(occurence==nth) {
				return table[table_index].second;
			}
			else if(nth<occurence) {
				return -1;
			}
			occurence++;
		}
		else if(table[table_index].second == EMPTY_INDEX) {
			return -1;
		}
	}
	return -1;
}

int Article::insert( std::string key, int original_index ) {
    if(MAX_LOAD_FACTOR<getLoadFactor()) {
    	expand_table();
    }
    int probes = 0, i = 0;
	while(i<table_size) {
		int table_index = hash_function(key,i);
		if(table[table_index].second == EMPTY_INDEX || table[table_index].second == MARKED_INDEX) {
			table[table_index] = std::pair<std::string,int>(key,original_index);
			n++;
			break;
		}
		else if(table[table_index].first == key
			&& table[table_index].second > original_index ) {
			//WE FOUND A CORRECT LOCATION
			//THERE IS A LARGER INDEXED ITEM
			int temp = original_index;
			original_index = table[table_index].second;
			table[table_index].second = temp;
		}
		i++;
		probes++;
	}
	return probes;
}


int Article::remove( std::string key, int nth )
{
    /*#########################################
    #                  TO-DO                  #
    #      Remove the nth key at the hash     #
    #                  table.                 #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #   If there is no such a key, return -1  #
    #     If there, put a mark to the table   #
    #########################################*/
  	int occurence = 1;
  	int probes = 0;
	for(int i=0; i<table_size; i++) {
		int table_index = hash_function(key, i);
		if(table[table_index].first == key) {
			if(occurence==nth) {
				table[table_index] = std::pair<std::string,int>(EMPTY_KEY,MARKED_INDEX);
				n--;
				return probes;
			}
			else if(nth<occurence) {
				return -1;
			}
			occurence++;
		}
		else if(table[table_index].second == EMPTY_INDEX) {
			return -1;
		}
		probes++;
	}
	return -1;
}

double Article::getLoadFactor() const {
	return (double) n / (double) table_size;
}

void Article::getAllWordsFromFile( std::string filepath ) {
    std::ifstream file;
    std::string word;
    file.open(filepath.c_str());
    int index = 1;
    while(file >> word) {
    	insert(word,index);
    	index++;
	}
	file.close();
}

void Article::expand_table() {
  	int new_table_size = nextPrimeAfter(2*table_size);
  	int new_h2_param = firstPrimeBefore(new_table_size);
    Article temp(new_table_size,h1_param,new_h2_param);
    for(int i=0; i<table_size; i++) {
    	if(table[i].second!=EMPTY_INDEX && table[i].second!=MARKED_INDEX) {
    		temp.insert(table[i].first,table[i].second);
    	}
    }
    table_size = temp.table_size;
    h2_param = temp.h2_param;
 	std::pair<std::string, int>* t;
 	t = table;
    table = temp.table;
    temp.table = NULL;
    delete []t;
}
int Article::hash_function( std::string& key, int i ) const {
	int _key = convertStrToInt(key);
	int _h1 = h1(_key);
	int _h2 = h2(_key);
	if(( _h1 + i*_h2 )<0) {
	    return (( _h1 + i*_h2 ) % table_size)+table_size;
	}
	return ( _h1 + i*_h2 ) % table_size;
}

int Article::give_me_ones( int key ) const {
	int ones = 0;
	while(key) {
		if(key%2) { ones++; }  
		key /= 2;
	}
	return ones;
}

int Article::h1( int key ) const {
	return h1_param*give_me_ones(key);
}

int Article::h2( int key ) const {
	return h2_param-(key%h2_param);
}
