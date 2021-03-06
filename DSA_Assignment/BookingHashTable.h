#pragma once

#include<string>
#include<iostream>
#include"Bookings.h"
#include <vector>
#include "ArrayListingBookings.h"

using namespace std;

const int MAX_SIZEHashTable = 201;
typedef string KeyType;
typedef Bookings ItemType1;

struct Node
{
	KeyType	 key;   // search key
	ItemType1 item;	// data item
	Node* next;	// pointer pointing to next item with same search key
};

class BookingHashTable
{
private:

	Node* items[MAX_SIZEHashTable];
	int size;			// number of items in the BookingHashTable
	int deluxeCVCounter;
	int standardCVCounter;
	int executiveSVCounter;
	int presidentSuiteCounter;

public:

	// constructor
	BookingHashTable();

	// destructor
	~BookingHashTable();

	int charvalue(char c);

	int hash(KeyType key);

	// add a new item with the specified key to the BookingHashTable
	// pre : none
	// post: new item is added to the BookingHashTable
	//       size of BookingHashTable is increased by 1
	bool add(KeyType newKey, ItemType1 newItem);

	void returnPopularRoom();

	// remove an item with the specified key in the BookingHashTable
	// pre : key must exist in the BookingHashTable
	// post: item is removed from the BookingHashTable
	//       size of BookingHashTable is decreased by 1
	void remove(KeyType key);
	void remove(KeyType key, ItemType1 item);

	// get an item with the specified key in the BookingHashTable (retrieve)
	// pre : key must exist in the BookingHashTable
	// post: none
	// return the item with the specified key from the BookingHashTable
	ArrayListingBookings get(KeyType key);

	ArrayListingBookings getAll(int intkey);

	// check if the BookingHashTable is empty
	// pre : none
	// post: none
	// return true if the BookingHashTable is empty; otherwise returns false
	bool isEmpty();

	// check the size of the BookingHashTable
	// pre : none
	// post: none
	// return the number of items in the BookingHashTable
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the BookingHashTable
	void print();

	// void replace(KeyType key, ItemType1 item);
	// bool contains(KeyType key);
};