#include "bookstore.hpp"

bool is_it_smaller(std::string str1, std::string str2) {
  std::string _str1 = str1;
  std::string _str2 = str2;
  for(int i=0; _str1[i]; i++) { _str1[i] = tolower(_str1[i]); }
  for(int i=0; _str2[i]; i++) { _str2[i] = tolower(_str2[i]); }  
  if(_str1<_str2){
    return true;
  }
  return false;
}

bool are_they_equal(std::string str1, std::string str2) {
  std::string _str1 = str1;
  std::string _str2 = str2;
  for(int i=0; _str1[i]; i++) { _str1[i] = tolower(_str1[i]); }
  for(int i=0; _str2[i]; i++) { _str2[i] = tolower(_str2[i]); }  
  if(_str1==_str2) {
    return true;
  }
  return false;
}


BookStore::BookStore( ) //implemented, do not change
{
}

void
BookStore::insert(const Book & book)
{
  primaryIndex.insert(book.getISBN(),book); 
  BSTP::Iterator it = primaryIndex.find(book.getISBN());
  secondaryIndex.insert(SKey(book.getTitle(),book.getAuthor()),&*it);
  ternaryIndex.insert(SKey(book.getTitle(),book.getAuthor()),&*it);
}

void
BookStore::remove(const std::string & isbn)
{
  BSTP::Iterator it_pri = primaryIndex.find(isbn);
  if(it_pri == primaryIndex.end()) {
    return ;
  }
  primaryIndex.remove(isbn);
  SKey sk( (*it_pri).getTitle(),(*it_pri).getAuthor() );
  secondaryIndex.remove(sk);
  ternaryIndex.remove(sk);
}

void
BookStore::remove(const std::string & title,
                  const std::string & author)
{
  SKey sk(title,author);
  BSTS::Iterator it_sec = secondaryIndex.find(sk);
  if(it_sec == secondaryIndex.end()) {
    return ;
  }
  std::string isbn = (**it_sec).getISBN();
  primaryIndex.remove(isbn);
  secondaryIndex.remove(sk);
  ternaryIndex.remove(sk);
}

void
BookStore::removeAllBooksWithTitle(const std::string & title)
{
  BSTS::Iterator it;
  std::list<std::string> lst;
  for (it=secondaryIndex.begin(); it != secondaryIndex.end(); )
  {
    std::string _title = (**it).getTitle();
    if(are_they_equal(title,_title)) {
      std::string isbn = (**it).getISBN();
      ++it;
      lst.push_back(isbn);
      continue;
    }
  ++it;
  } 
  while(!lst.empty()) {
    remove(lst.front());
    lst.pop_front();
  }
}

void
BookStore::makeAvailable(const std::string & isbn)
{
  BSTP::Iterator it_pri = primaryIndex.find(isbn);
  if(it_pri == primaryIndex.end()) {
    return ;
  }
  SKey sk( (*it_pri).getTitle(),(*it_pri).getAuthor() );
  (*it_pri).setAvailable();
  //( *(secondaryIndex.find(sk)) )->setAvailable();
  BSTT::Iterator it_ter = ternaryIndex.find(sk);
  ( *it_ter )->setAvailable();
}

void
BookStore::makeUnavailable(const std::string & title,
                           const std::string & author)
{
  BSTS::Iterator it_sec = secondaryIndex.find(SKey(title,author));
  if(it_sec == secondaryIndex.end()) {
    return ;
  }
  std::string isbn = (*it_sec)->getISBN();
  BSTP::Iterator it_pri = primaryIndex.find(isbn);
  ( *it_pri ).setUnavailable();
  //( **(secondaryIndex.find(sk)) ).setUnavailable();
  BSTT::Iterator it_ter = ternaryIndex.find(SKey(title,author));
  ( *it_ter )->setUnavailable();
}

void
BookStore::updatePublisher(const std::string & author, 
                           const std::string & publisher)
{
  BSTP::Iterator it;
  for (it=primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    std::string _author = (*it).getAuthor();
    if(are_they_equal(author,_author)) {
      (*it).setPublisher(publisher);
    }
  } 
  
}

void
BookStore::printBooksWithISBN(const std::string & isbn1,
                              const std::string & isbn2,
                              unsigned short since) const
{
  BSTP::Iterator it;
  for(it=primaryIndex.begin(); it!=primaryIndex.end(); ++it) {
    std::string str = (*it).getISBN();
    if(since<=(*it).getYear() && isbn1<=str && str<=isbn2) {
      std::cout << *it << std::endl;
    }
  }
}

void
BookStore::printBooksOfAuthor(const std::string & author,
                              const std::string & first,
                              const std::string & last) const
{
  BSTT::Iterator it;
  for (it=ternaryIndex.begin(); it != ternaryIndex.end(); ++it) {
    std::string _author = (**it).getAuthor();
    std::string title = (**it).getTitle(); 
    if(are_they_equal(author,_author)){
      if( (is_it_smaller(first,title)||are_they_equal(first,title)) && 
        (is_it_smaller(title,last)||are_they_equal(title,last)) ) {
        std::cout << **it << std::endl;
      }  
    }
  }
}

void //implemented, do not change
BookStore::printPrimarySorted( ) const
{
  BSTP::Iterator it;

  for (it=primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}

void //implemented, do not change
BookStore::printSecondarySorted( ) const
{
  BSTS::Iterator it;
  
  for (it = secondaryIndex.begin(); it != secondaryIndex.end(); ++it)
  {

    std::cout << *(*it) << std::endl;
  }
}

void //implemented, do not change
BookStore::printTernarySorted( ) const
{
  BSTT::Iterator it;

  for (it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

