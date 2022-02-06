#pragma once

#include<string>
#include<iostream>
#include"Bookings.h"
#include <vector>
using namespace std;

// MAX_SIZE of the hash table is 24 as it will store booking history across 2 years
const int MAX_SIZE_DATE = 24;
typedef string KeyType;
typedef Bookings ItemType1;

struct NodeDate
{
	KeyType	 key;   // search key
	ItemType1 item;	// data item
	NodeDate* next;	// pointer pointing to next item with same search key
};

class ParticularDateHashTable
{
private:

	NodeDate* items[MAX_SIZE_DATE];
	int  size;			// number of items in the BookingHashTable

public:

	// constructor
	ParticularDateHashTable();

	// destructor
	~ParticularDateHashTable();

	int charvalue(char c);

	int hash(KeyType key);

	// add a new item with the specified key to the BookingHashTable
	// pre : none
	// post: new item is added to the BookingHashTable
	//       size of BookingHashTable is increased by 1
	bool add(KeyType newKey, ItemType1 newItem);

	// remove an item with the specified key in the BookingHashTable
	// pre : key must exist in the BookingHashTable
	// post: item is removed from the BookingHashTable
	//       size of BookingHashTable is decreased by 1
	void remove(KeyType key);


	// get an item with the specified key in the BookingHashTable (retrieve)
	// pre : key must exist in the BookingHashTable
	// post: none
	// return the item with the specified key from the BookingHashTable
	vector<ItemType1> getParticularDate(KeyType key);

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