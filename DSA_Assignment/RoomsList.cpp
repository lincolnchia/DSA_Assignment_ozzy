#include<string>
#include<iostream>
#include "RoomsList.h"
using namespace std;

//constructor 
RoomsList::RoomsList() {
	firstNode = NULL;
	size = 0;
}
RoomsList::~RoomsList() { firstNode = NULL; }

bool RoomsList::add(ItemType3 item) {
	bool success = size > 0;
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	if (isEmpty())
		firstNode = newNode;
	else {
		Node* temp = firstNode;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	size++;//dont forget to increase size 
	return success;
}
bool RoomsList::add(int index, ItemType3 item) {
	bool success = (index >= 0) && (index < size);
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	if (index == 0)
	{
		newNode->next = firstNode;
		firstNode = newNode;
	}

	else {
		Node* temp = firstNode;
		for (int i = 0;i < index - 1; i++) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
	size++;//dont forget to increase size 
	return success;
}
void RoomsList::remove(int index) {
	bool success = (index >= 0) && (index < size);
	if (success) {
		if (index == 0) {
			Node* temp = firstNode;
			firstNode = firstNode->next;
			temp->next = NULL;
			delete temp;
		}
		else {
			Node* current = firstNode;
			Node* previous = firstNode;
			for (int i = 0; i < index; i++) {
				previous = current;
				current = current->next;
			}
			previous->next = current->next;
			current->next = NULL;
			delete current;
		}
		size--;//dont forget to decrease size
	}
}

ItemType3 RoomsList::get(int index)
{
	//Has to be >= 0 and less than the current size of the linked list
	bool success = (index >= 0) && (index < size);

	if (success)
	{
		//Traveling down to the specific node
		Node* temp = firstNode;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		//Returning the item in the specified Node
		return temp->item;
	}
}

// check if the list is empty
bool RoomsList::isEmpty() {
	if (firstNode == NULL) {
		return true;
	}
	else {
		return false;
	}
}

// check the size of the list
int RoomsList::getLength() {
	return size;
}

void RoomsList::print() {
	Node* temp = firstNode;

	if (!isEmpty()) {

		while (temp != NULL) {
			cout << temp->item.getRoom_number() << endl;
			cout << temp->item.getRoom_Type() << endl;
			cout << temp->item.getCost_per_night() << endl;
			temp = temp->next;
		}
	}
	else {
		cout << "The List is empty." << endl;
	}
}
