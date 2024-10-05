#pragma once

/* programmer name: Genevieve Kochel
* Date:
file purpose: this file contains athe class declaration for the templated ListNode class */


#include "Linux.hpp"

template <class T, class U>
class ListNode {

public:
	
	// constructor/destructor 
	ListNode(T& command, U& description) {
		mCommand = command;
		mDescription = description;

		mpNext = nullptr; // init next ptr to null by default
	}

	~ListNode() {}

	// necessary setters/getters
	T getCommand() const { return mCommand; }
	U getDescription() const { return mDescription; }

	ListNode<T, U>* getNext() const { return mpNext; }
	void setNext(ListNode<T, U>* next) { mpNext = next; }


private:
	T mCommand;
	U mDescription;

	ListNode<T, U>* mpNext; 

};