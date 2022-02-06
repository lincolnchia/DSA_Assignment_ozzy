// List.cpp - Implementation of List ADT using Array
#include "ArrayList.h"  // header file
#include <iostream>
using namespace std;
// constructor
ArrayList::ArrayList() { size = 0; }

// add an item to the back of the list (append)
bool ArrayList::add(ItemType item)
{
	bool success = size < MAX_SIZEArrayList;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list (insert)
bool ArrayList::add(int index, ItemType item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZEArrayList);
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
void ArrayList::remove(int index)
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
ItemType ArrayList::get(int index)
{
	string b; //default constructor
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return b;
}

// check if the list is empty
bool ArrayList::isEmpty() { return size == 0; }

// check the size of the list
int ArrayList::getLength() { return size; }

// display the items in the list
void ArrayList::print()
{
	for (int i = 0; i < size;i++)
	{

	}
	cout << endl;
}

// replace the  item in the specified index in the list
void ArrayList::replace(int index, ItemType item)
{
	if (index >= 0 && index < size) {
		items[index] = item;
	}
	else {
		cout << "Invalid";
	}
}