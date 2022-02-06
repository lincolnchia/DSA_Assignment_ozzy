// List.cpp - Implementation of List ADT using Array
#include "ArrayListingBookings.h"  // header file
#include <iostream>
using namespace std;
// constructor
 ArrayListingBookings::ArrayListingBookings() { size = 0; }

// add an item to the back of the list (append)
bool ArrayListingBookings::add(ItemType1 item)
{
	bool success = size < MAX_SIZEArrayListingBooking;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list (insert)
bool ArrayListingBookings::add(int index, ItemType1 item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZEArrayListingBooking);
	if (success)
	{  // make room for the item by shifting all items at
	   // positions >= index toward the end of the
	   // List (no shift if index == size + 1)
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		// insert the item
		items[index] = item;
		size++;  // increase the size by 1
	}
	return success;
}

// remove an item at a specified position in the list
void ArrayListingBookings::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{  // delete item by shifting all items at positions >
	   // index toward the beginning of the list
	   // (no shift if index == size)
		for (int pos = index; pos < size; pos++)
			items[pos] = items[pos + 1];
		size--;  // decrease the size by 1
	}

}

// get an item at a specified position of the list (retrieve)
ItemType1 ArrayListingBookings::get(int index)
{
	Bookings b; //default constructor
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return b;
}

// check if the list is empty
bool ArrayListingBookings::isEmpty() { return size == 0; }

// check the size of the list
int ArrayListingBookings::getLength() { return size; }

// display the items in the list
void ArrayListingBookings::print()
{
	for (int i = 0; i < size;i++)
	{

	}
	cout << endl;
}

// replace the  item in the specified index in the list
void ArrayListingBookings::replace(int index, ItemType1 item)
{
	if (index >= 0 && index < size) {
		items[index] = item;
	}
	else {
		cout << "Invalid";
	}
}
