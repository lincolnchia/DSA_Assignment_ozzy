#include<string>
#include<iostream>
#include "List.h"
using namespace std;

//constructor 
List::List() {
	firstNode = NULL;
	size = 0;
}
List::~List() { firstNode = NULL; }

bool List::add(ItemType item) {
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
bool List::add(int index, ItemType item) {
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
void List::remove(int index) {
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

ItemType List::get(int index)
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
bool List::isEmpty() {
	if (firstNode == NULL) {
		return true;
	}
	else {
		return false;
	}
}

// check the size of the list
int List::getLength() {
	return size;
}

void List::print() {
	Node* temp = firstNode;

	if (!isEmpty()) {

		while (temp != NULL) {
			cout << temp->item << endl;
			temp = temp->next;
		}
	}
	else {
		cout << "The List is empty." << endl;
	}
}
