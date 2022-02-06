// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
#include "Rooms.h"
using namespace std;

typedef Rooms ItemType3;

class RoomsList
{
private:
	struct Node
	{
		ItemType3 item;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	RoomsList();

	// destructor
	~RoomsList();

	// add an item to the back of the list (append)
	bool add(ItemType3 item);

	// add an item at a specified position in the list (insert)
	bool add(int index, ItemType3 item);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	ItemType3 get(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void print();
};
#pragma once
