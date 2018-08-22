#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

/*You are free to add private/public members inside this template..*/
template <class T>
class MyStack {
    private:
    Node<T> *top;                
    public:
    /*Default constructor*/
    MyStack();                     					
    /*copy constructor*/
    MyStack(const MyStack<T>& rhs);  				
    /*destructor*/
    ~MyStack(); 
    /*overloaded = operator*/
    MyStack<T>& operator=(const MyStack<T>& rhs);  	
    /*returns true if stack is empty*/
    bool isEmpty() const;
    /*push newItem to stack*/
    void push(const T& newItem);
    /*pop item from stack*/
    void pop();
    /*return top item of the stack*/
    Node<T>* Top() const;
	/*Prints the stack entries. This method was already implemented. Do not modify.*/
    void print() const;
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/* TO-DO: method implementations below */
template <class T>
MyStack<T>::MyStack() { top = NULL; }

template <class T>
MyStack<T>::MyStack(const MyStack<T>& rhs){
    top = NULL;
    *this = rhs;
}

template <class T>
MyStack<T>::~MyStack() {
    while(!isEmpty()) {
        pop();
    }
    delete top;
}

template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& rhs) {
    if(this != &rhs) {
        while(!isEmpty()) { pop(); }
        if(!rhs.Top()) {
            top = NULL;
        }
        else {
            pop();
            top = new Node<T>(rhs.Top()->getData());
            Node<T> *ptrRhs = rhs.Top()->getNext();
            Node<T> *ptrThis = top;
            while(ptrRhs) {
                Node<T> *p = new Node<T>(ptrRhs->getData());
                ptrThis->setNext(p);
                ptrThis = ptrThis->getNext();
                ptrRhs = ptrRhs->getNext();
            }
            ptrThis->setNext(NULL);
        }
    }
    return *this;
}

template <class T>
bool MyStack<T>::isEmpty() const { return top == NULL; }

template <class T>
void MyStack<T>::push(const T& newItem) {
    if(isEmpty()) {
        top = new Node<T>(newItem);
    }
    else {
        Node<T> *newNode = new Node<T>(newItem);
        newNode->setNext(top);
        top = newNode;
    }
}

template <class T>
void MyStack<T>::pop() {
    if(isEmpty()) {
        return;
    }
    else {
        Node<T> *temp = top;
        top = top->getNext();
        temp->setNext(NULL);
        delete temp;
    }
}

template <class T>
Node<T>* MyStack<T>::Top() const { return top; }

#endif /* MYSTACK_HPP */

