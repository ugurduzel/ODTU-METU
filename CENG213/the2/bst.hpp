#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_

#include <functional>
#include <cstddef>
#include <stack>
#include <list>
#include <ostream>
//do not add any other library
//modify parts as directed by assignment text & comments here

template <typename Key, typename Object, typename Comparator=std::less<Key> >
class BinarySearchTree {
  	private: //do not change
	    struct BinaryNode { //node definition: a dependent type
	     	Key key; //keys will be kept constant
	      Object data; //objects that are referred to by keys may change
	      BinaryNode * left;
		    BinaryNode * right;
        size_t height; //height info should be updated per insert & delete

		    BinaryNode(const Key &, const Object &,
	            BinaryNode *, BinaryNode *, size_t =0);
	    };


  	public: //do not change except for your own private utility functions
	  	class Iterator { //iterator class will encapsulate the location within the BST
	     	public:
		        Iterator( ); //dummy constructor for type declaration purposes
		        Iterator & operator++( ); //inorder increment

		        Object & operator*( );  //update data
		        const Object & operator*( ) const; //view data

		        bool operator==(const Iterator & rhs) const; //compare iterators
		        bool operator!=(const Iterator & rhs) const; //compare iterators

	      	private:
	        	BinaryNode * current; //position
	        	const BinaryNode * root; //for error check not implemented
	        	std::stack<BinaryNode *> s; //will be used to conduct in order traversal if
	        	bool useStack; //this variable is set to true, ignored in == and !=

	     	private:
	        	Iterator(BinaryNode *, const BinarySearchTree &, bool =true);
	        	//other private utility functions can be declared by you
            void traverse_inorder(BinaryNode * &);

	      	friend class BinarySearchTree<Key, Object, Comparator>;
	    };

	public: //do not change
	    BinarySearchTree( ); //empty tree
	    ~BinarySearchTree( ); //reclaim all dyn allocated mem

	   	void insert(const Key &, const Object &); //to insert new key,item
	    void remove(const Key &); //remove the node with the key value (and also data)

	public: //do not change
	    Iterator find(const Key &) const; //single item
	    std::list<Iterator> find(const Key &, const Key &) const;//range queries

	    Iterator begin( ) const; //inorder begin
	    Iterator end( ) const; //dummy NULL iterator

  	public: //do not change
	    int height( ) const; //return height of the tree
	    size_t size( ) const; //return the number of items in the tree
	    bool empty( ) const; //return whether the tree is empty or not
	    void print(std::ostream &) const;

  	private: //do not change
	    BinaryNode * root; //designated root
	    size_t nodes; //number of nodes
    	Comparator isLessThan; //function object to compare keys

  	private:
	    /* private utility functions that are implemented */
	    void makeEmpty(BinaryNode * &);

	    BinaryNode * find(const Key &, BinaryNode *) const;
	    int height(BinaryNode *) const;
	    void print(BinaryNode *, std::ostream &) const;

	    template <typename T> //static utility function
	    static const T & max(const T &, const T &);

	    //balancing functions
	    void rotateWithLeftChild(BinaryNode * &);
	    void rotateWithRightChild(BinaryNode * &);
	    void doubleWithLeftChild(BinaryNode * &);
	    void doubleWithRightChild(BinaryNode * &);

    	//you may add your own private utility functions down here
  	    void check_insert_balance(const Key &, const Object &, BinaryNode * &);
     	BinaryNode * determine_bin_node(const Key & lower, const Key & upper, BinaryNode * t) const;
      	BinaryNode * min(BinaryNode *t);
      	int balance_factor(BinaryNode *);
      	void remove_helper(const Key & , BinaryNode * & );


 	private: //not copiable, DO NOT IMPLEMENT or change
	    BinarySearchTree(const BinarySearchTree &);
	    const BinarySearchTree & operator=(const BinarySearchTree &);
};

//node constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinaryNode::
BinaryNode(const K & _k, const O & _d,
           BinaryNode * _l, BinaryNode * _r, size_t _h)
  : key(_k), data(_d), left(_l), right(_r), height(_h) { }
//default constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinarySearchTree( )
  : root(NULL), nodes(0) { }
//destructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::~BinarySearchTree( )
{
  makeEmpty(root);
}
//private utility function for destructor, do not change
template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::makeEmpty(BinaryNode * & t) {
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    --nodes;
  }
  t = NULL;
}

//----------------------------------------------------------
//                         IMPLEMENT
//----------------------------------------------------------
template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::check_insert_balance(const K & k, const O & x, BinaryNode * & t) {
  if(!t) {
    t = new BinaryNode(k,x,NULL,NULL,0);
    nodes++;
  }
  else if(isLessThan(k,t->key)) { // k < t->key
    check_insert_balance(k,x,t->left);
    if(height(t->left)-height(t->right) == 2) {
      if(isLessThan(k,t->left->key)) {
        rotateWithLeftChild(t);
      }
      else {
        doubleWithLeftChild(t);
      }
    }
  }
  else if(isLessThan(t->key,k)) { // t->key < k
    check_insert_balance(k,x,t->right);
    if(height(t->right)-height(t->left) == 2) {
      if(isLessThan(k,t->right->key)) {
        doubleWithRightChild(t);
      }
      else {
        rotateWithRightChild(t);
      }
    }
  }
  else {
    t->data = x;
    return ;
  }
  t->height = max(height(t->left),height(t->right))+1;
}


//public function to insert into BST, IMPLEMENT
template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::insert(const K & k, const O & x) {
  check_insert_balance(k,x,root);
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::min(BinaryNode *t) {
  BinaryNode *_t = t;
  while(_t->left) {
    _t = _t->left;
  }
  return _t;
}

template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::balance_factor(BinaryNode *p) {
	if(height(p->left)<height(p->right)) {
		return 1;
	}
	else if(height(p->left)>height(p->right)) {
		return -1;
	}
	return 0;
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::remove_helper(const K & k, BinaryNode * & t) {
	if(!t) {
    	return ;  
  	}
  	else if(isLessThan(k,t->key)) { // k < t->key
    	remove_helper(k,t->left);
    	//BACKTRACK
    	if(1 < height(t->right)-height(t->left) && balance_factor(t) == 1 && balance_factor(t->right) == 0) {
			rotateWithRightChild(t);
		}
		else if(1 < height(t->right)-height(t->left) && balance_factor(t) == 1 && balance_factor(t->right) == -1) {
			doubleWithRightChild(t);
		}
		else if(1 < height(t->right)-height(t->left) && balance_factor(t) == 1 && balance_factor(t->right) == 1) {
			rotateWithRightChild(t);
		}
	}
  	else if(isLessThan(t->key,k)) { // k > t->key
    	remove_helper(k,t->right);
    	//BACKTRACK
    	if(1 < height(t->left)-height(t->right) && balance_factor(t) == -1 && balance_factor(t->left) == 0) {
			rotateWithLeftChild(t);
		}
		else if(1 < height(t->left)-height(t->right) && balance_factor(t) == -1 && balance_factor(t->left) == 1) {
			doubleWithLeftChild(t);
		}
		else if(1 < height(t->left)-height(t->right) && balance_factor(t) == -1 && balance_factor(t->left) == -1) {
			rotateWithLeftChild(t);
		}
   }
   else { //FOUND
   		if(!(t->left) && !(t->right)) { // NO CHILD
   			delete t;
   			t = NULL;
   			nodes--;
   			return ;
   		}
   		else if(t->left && !(t->right)) { // ONE LEFT CHILD
   			BinaryNode *temp = t;
   			t = t->left;
   			temp->right = NULL;
   			temp->left = NULL;
   			delete temp;
   			nodes--;
   		}
   		else if(!(t->left) && t->right) { // ONE RIGHT CHILD
   			BinaryNode *temp = t;
   			t = t->right;
   			temp->right = NULL;
   			temp->left = NULL;
   			delete temp;
   			nodes--;
   		}
   		else if(t->left && t->right){ // 2 CHILDREN
   			BinaryNode *p = t->right;
   			if(!(t->right->left) && !(t->right->left)) {
   				t->right->left = t->left;
   				t->left = NULL;
   				BinaryNode *temp = t->right->right;
   				t->right->right = t;
   				t->right = temp;
   				t = p;
   			}
   			else {
   				while(p->left->left) {
   				p = p->left;
	   			}
	   			BinaryNode *temp = p->left->right;
	   			p->left->left = t->left;
	   			p->left->right = t->right;
	   			t->left = NULL;
	   			t->right = temp;
	   			temp = t;
	   			t = p->left;
	   			p->left = temp;
   			}
   			remove_helper(k,t->right);
    		//BACKTRACK
	    	if(1 < height(t->left)-height(t->right) && balance_factor(t) == -1 && balance_factor(t->left) == 0) {
				rotateWithLeftChild(t);
			}
			else if(1 < height(t->left)-height(t->right) && balance_factor(t) == -1 && balance_factor(t->left) == 1) {
				doubleWithLeftChild(t);
			}
			else if(1 < height(t->left)-height(t->right) && balance_factor(t) == -1 && balance_factor(t->left) == -1) {
				rotateWithLeftChild(t);
			}
   		}
   }
   t->height = max(height(t->left),height(t->right))+1;
}


//public function to remove key,
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::remove(const K & k) {
	remove_helper(k,root);
}
//----------------------------------------------------------
//----------------------------------------------------------

//public function to search elements, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::find(const K & key) const
{
  BinaryNode * node = find(key, root);

  if (node == NULL)
  {
    return end();
  }
  else
  {               //not inorder iterator
    return Iterator(node, *this, false);
  }
}
/*
 * private utility function to search elements
 * do not change
 */
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::find(const K & key, BinaryNode * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

//----------------------------------------------------------
//                         IMPLEMENT
//----------------------------------------------------------
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::determine_bin_node(const K & lower, const K & upper, BinaryNode * t) const {
  if(isLessThan(lower,t->key) && isLessThan(t->key,upper)) {
    return t;
  }
  else if(isLessThan(lower,t->key) && isLessThan(upper,t->key)) {
    return determine_bin_node(lower,upper,t->left);
  }
  else if(isLessThan(t->key,lower) && isLessThan(t->key,upper)) {
    return determine_bin_node(lower,upper,t->right);
  }
  else {
    return root;
  }
}  

//range queries those within range are inserted to the list
//IMPLEMENT
template <typename K, typename O, typename C>
std::list<typename BinarySearchTree<K,O,C>::Iterator>
BinarySearchTree<K,O,C>::find(const K & lower, const K & upper) const {
  std::list<Iterator> return_list;
  BinaryNode *smallest, *largest;
  BinaryNode *p = root;
  while(p->left) {
    p = p->left;
  }
  smallest = p;
  p = root;
  while(p->right) {
    p = p->right;
  }
  largest = p;
  if(isLessThan(upper,smallest->key)) { return return_list; }
  if(isLessThan(largest->key,lower)) { return return_list; }
  BinaryNode * bin_node = determine_bin_node(lower,upper,root);
  Iterator it(bin_node, *this);
  while(it.current && isLessThan(it.current->key,lower)) {
    ++it;
  }
  while(it.current && (isLessThan(it.current->key,upper))) {
    Iterator it_temp(it.current,*this,false);
    return_list.push_back(it_temp);
    ++it;
  }
  if(it.current && it.current->key == upper) {
    Iterator it_temp(it.current,*this,false);
    return_list.push_back(it_temp);
    ++it;
  }
  return return_list;
}



//----------------------------------------------------------
//----------------------------------------------------------

//INORDER iterator begins at ++root, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::begin() const
{
  return Iterator(root, *this);
}
//no more increment after end() also
//returned in case of unsuccessful search
//or when no more applicance of ++ is possible
//do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::end() const
{
  return Iterator(NULL, *this);
}
//public function to return height, do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height( ) const
{
  return height(root);
}
/* private utility function for computing height */
//do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height(BinaryNode * t) const
{
  return (t == NULL) ? -1 : t->height;
}
//public function to return number of nodes in the tree
//do not change
template <typename K, typename O, typename C>
size_t
BinarySearchTree<K,O,C>::size( ) const
{
  return nodes;
}
//public true if empty false o.w.
//do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::empty( ) const
{
  return nodes == 0;
}
//public function to print keys inorder to some ostream
//do not change
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}
/* private utility function to print, do not change */
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(BinaryNode * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL)
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << '}';
    }
  }

  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}
/* static function to compute maximum of two elements */
//do not change
template <typename K, typename O, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,C>::max(const T & el1, const T & el2)
{
	/*std::cout << "First one is : " << el1 << std::endl;
	std::cout << "Second one is : " << el2 << std::endl;
	std::cout << "Returning " << el1 > el2 ? el1 : el2 << std::endl;*/
  return el1 > el2 ? el1 : el2;
}

/* ROTATIONS, do not change */
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::rotateWithLeftChild(BinaryNode * & k2)
{
  BinaryNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->left),
                                            height(k2->right)) + 1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left),
                                            height(k2)) + 1;
  k2 = k1;
}
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::rotateWithRightChild(BinaryNode * & k1)
{
  BinaryNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left),
                                            height(k1->right)) + 1;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->right),
                                            height(k1)) + 1;
  k1 = k2;
}
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::doubleWithLeftChild(BinaryNode * & k3)
{
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::doubleWithRightChild(BinaryNode * & k1)
{
  rotateWithLeftChild(k1->right);
  rotateWithRightChild(k1);
}

/* ITERATOR functions */

// dummy constructor, do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::Iterator( )
  : current(NULL), root(NULL), useStack(false) { }

//----------------------------------------------------------
//                         IMPLEMENT √√
//----------------------------------------------------------

// dereferencing operator non-const version, IMPLEMENT
template <typename K, typename O, typename C>
O &
BinarySearchTree<K,O,C>::Iterator::operator*( ) {
  return current->data;
}

// dereferencing operator const version, IMPLEMENT
template <typename K, typename O, typename C>
const O &
BinarySearchTree<K,O,C>::Iterator::operator*( ) const {
  return current->data;
}
//----------------------------------------------------------
//----------------------------------------------------------

// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::Iterator::
operator==(const Iterator & rhs) const
{
  return current == rhs.current &&
         root == rhs.root;
}
// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::Iterator::
operator!=(const Iterator & rhs) const
{
  return !(*this == rhs);
}

//----------------------------------------------------------
//                         IMPLEMENT
//----------------------------------------------------------

// increment Iterator to point to the inorder next
// node of then-current node, in case that no further
// advances are possible return an Iterator that is
// equal to end( ) , IMPLEMENT
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator &
BinarySearchTree<K,O,C>::Iterator::operator++( ) {
    if(!useStack) {
      current = NULL;
      return *this;
    }
    if(!s.size()) {
      current = NULL;
      return *this;
    }
    s.pop();
    if(!s.size()) {
      current = NULL;
      return *this;
    }
    current = s.top();
    return *this;
}

/* real Iterator constructor will be invoked by
 * BST member function only. if no inorder iterator
 * is required by the computation designer should
 * explicitly set useStack variable to false, o.w.
 * it will be assumed to be true. IMPLEMENT
 */
template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::Iterator::
  traverse_inorder(BinaryNode * & p) {
   if(p) {
     traverse_inorder(p->right);
     s.push(p);
     traverse_inorder(p->left);
   }
 }

template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::
Iterator(BinaryNode * p, const BinarySearchTree & rhs, bool stk) {
  if(stk) {
    if(!p) {
      current = NULL;
      root = rhs.root;
      useStack = stk;
    }
    else {
      BinaryNode * _p = p;
      traverse_inorder(_p);
      current = s.top();
      root = rhs.root;
      useStack = stk;
    }
  }
  else {
    current = p;
    root = rhs.root;
    useStack = stk;
  }
}

#endif
