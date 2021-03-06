/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );


	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;



	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_size( 0 )
{
	// Default Constructor: Creates and assigns head and tail sentinel node pointers and binds them together
	list_tail = new Double_node(0, nullptr, nullptr);
	list_head = new Double_node(0, nullptr, list_tail);
	list_tail->previous_node = list_head;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_size( 0 )
{
	//Copy Constructor: Creates a new list that is a copy of the list passed as an argument.
    list_tail = new Double_node(0, nullptr, nullptr);
    list_head = new Double_node(0, nullptr, list_tail);
    list_tail->previous_node = list_head;
    if(list.empty()){
        return;
    }
    Double_node *trav = list.begin();
    while(trav != list.end()){
        push_back(trav->value());
        if(trav->next()==list.begin())
            break;
        trav=trav->next();
    }
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
list_head(nullptr),
list_tail(nullptr),
list_size( 0 )
{
    //Move Constructor: Swaps the pointers of the argument list with a dead list with only null pointers
    swap(list);
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    //Destructor: Deallocates all memory allocated for the list
    while(!empty())
		pop_front();
    delete (list_tail);
    delete (list_head);
	
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	//Returns the number of nodes in the list
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// Returns true if the list is empty, otherwise, returns false
	if (list_size==0){
		return true;
	}
	return false;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Returns the first non-sentinel node value in the list
    if(!empty()){
        return begin()->value();
    }
	else{
       throw underflow();
    }
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// Returns the last non-sentinel node value in the list
    if (!empty()) {
        return rbegin()->value();
    }
    else {
        throw underflow();
    }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Returns a pointer to first non-sentinel node in the list
	return list_head->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	// Returns a pointer to the list's tail sentinel
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Returns a pointer to the last non-sentinel node in the list
	return end()->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Returns a pointer to the list's head sentinel
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// Returns a pointer to the first node in the list with the value of the object passed as an argument
	Double_node *trav = begin();
	while(trav != list_tail && trav->value()!= obj){
		trav = trav->next();
	}
	return trav;
}


template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    // Returns the number of nodes containing the value passed as an argument
	int count = 0;
    Double_node *trav = begin();
    while(trav!=list_tail){
        if(trav->value()==obj){
            count++;
        }
        trav=trav->next();
    }
	return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    // Adds a new node with the specified value to the front of the list
	Double_node *temp = new Double_node(obj, list_head, list_head->next_node);
    list_head->next_node->previous_node = temp;
    list_head->next_node = temp;
	list_size++;
	
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    // Adds a new node with the specified value to the back of the list
    Double_node *temp = new Double_node(obj, list_tail->previous(), list_tail);
    list_tail->previous()->next_node = temp;
    list_tail->previous_node = temp;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Removes the first non-sentinel node in the list
	if(!empty()){
		Double_node *tmp = begin();
		list_head->next_node = tmp->next();
		tmp->next()->previous_node=list_head;
        delete(tmp);
		list_size--;
	}
	else {
		throw underflow();
	}
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// Removes the last non-sentinel node in the list
    if(!empty()) {
        Double_node *tmp = rbegin();
        tmp->previous()->next_node = list_tail;
        list_tail->previous_node = tmp->previous();
        delete(tmp);
        list_size--;
    } else {
        throw underflow();
    }
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    // Removes all nodes containing the value passed as an argument
    int count =0;
    if(empty()){
        return -1;
    }
    Double_node *trav = begin();
    while (trav!=list_tail){
        if(trav->value()==obj){
            Double_node *tmp = trav;
            trav->previous()->next_node = trav->next();
            trav->next()->previous_node = trav->previous();
            trav=trav->previous();
            delete(tmp);
            list_size--;
            count++;
        }
        trav = trav->next();
    }
	return count;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node( Type const &nv, Double_sentinel_list<Type>::Double_node *pn, Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv ), // This assigns 'node_value' the value passed in
previous_node( pn ), // Assigns the previous_node to the specified value
next_node( nn ) // Assigns next_node to the specified value
{

}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Returns the value of the node
	return node_value; // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Returns a pointer to the previous node
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Returns a pointer to the next node
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
