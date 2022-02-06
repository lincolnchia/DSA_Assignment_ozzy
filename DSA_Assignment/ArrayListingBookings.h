#include "Bookings.h"
#pragma once;
using namespace std;

const int MAX_SIZEArrayListingBooking = 200;
typedef Bookings ItemType1;

class ArrayListingBookings
{
private:
	ItemType1 items[MAX_SIZEArrayListingBooking];
	int      size;

public:

	// constructor
	ArrayListingBookings();

	// add an item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: item is added to the back of the list
	//       size of list is increased by 1
	bool add(ItemType1 item);

	// add an item at a specified position in the list (insert)
	// pre : 0 <= index < size && size < MAX_SIZE
	// post: item is added to the specified position in the list
	//       size of list is increased by 1
	bool add(int index, ItemType1 item);

	// remove an item at a specified position in the list
	// pre : 0 <= index < size
	// post: item is removed the specified position in the list
	//       size of list is decreased by 1
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	ItemType1 get(int index);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();

	//purpose: prints the items in the list 
	// pre: none
	// post: none
	void print();

	// purpose: replace the item in the specified index in the list
	// pre : 0<= index < size 
	// post: item in index location updated
	void replace(int index, ItemType1 item);
};
