#include "ParticularDateHashTable.h"
#include <sstream>
#include <ctime>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

ParticularDateHashTable::ParticularDateHashTable()
{
    size = 0;
}

ParticularDateHashTable::~ParticularDateHashTable()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        items[i] = NULL;
    }
}

int ParticularDateHashTable::charvalue(char c)
{
    //Check is character is alphabetic
    if (isalpha(c))
    {
        //Check is character is upper case
        //Get index of the letter in alphabetical order
        //If lowercase, add 26
        if (isupper(c))
            return (int)c - (int)'A';
        else
            return (int)c - (int)'a' + 26;
    }
    else
        return -1;
}
 
// Creating hash key with time_t variable, key will be seconds after 1900
int ParticularDateHashTable::hash(KeyType key)
{
    string delimiter = "/";
    size_t pos = 0;
    string token;
    while ((pos = key.find(delimiter)) != string::npos)
    {
        //key is DD/MM/YYYY, doing this removes the day
        key.erase(0, pos + delimiter.length());

        //key now contains MM/YYYY so seperate the MM and YYYY
        while ((pos = key.find(delimiter)) != string::npos) 
        {
            //Token takes on the value of the month
            token = key.substr(0, pos);

            //key now only contains the value of the year
            key.erase(0, pos + delimiter.length());

            int monthNumber = stoi(token);
            int yearNumber = stoi(key);

            if (yearNumber == 2021) 
            {
                return monthNumber * 2;
            }

            return monthNumber;
        }

    }
}

bool ParticularDateHashTable::add(KeyType newKey, ItemType1 newItem)
{
    int index = hash(newKey);
    if (items[index] == NULL) 
    {
        Node* n = new Node();
        n->key = newKey;
        n->item = newItem;
        n->next = NULL;
        items[index] = n;
    }
    else //collision
    {
        Node* temp = items[index];

        while (temp->next != NULL) {
            temp = temp->next;
        }

        Node* n = new Node();
        n->key = newKey;
        n->item = newItem;
        n->next = NULL;
        temp->next = n;
    }
    size++;
    return true;
}

void ParticularDateHashTable::remove(KeyType key)
{
    //Initializing the hash
    int i = hash(key);

    //If the position in the BookingHashTable is not empty,
    if (items[i] != NULL)
    {
        //Check if the first item shares the same key to delete it
        if (items[i]->key == key)
        {
            //Set the first BookingHashTable pointer to point to the second item
            items[i] = items[i]->next;
            //Decrease the size of the BookingHashTable
            size--;
        }
        //If first item does not share the same key that we want to delete,
        else
        {
            //Travel down the linked list
            Node* tempNode = items[i];
            //While the current node is not NULL,
            //Using tempNode != NULL so that the final iteration also gets checked
            //If using tempNode->next != NULL, tempNode will be set to the final node but will not be checked
            while (tempNode != NULL)
            {
                //If the next node from the current one that we are on shares the same key that we want to delete,
                if (tempNode->next->key == key)
                {
                    //Set the current node's next to the one after the next one
                    tempNode->next = tempNode->next->next;
                    //Decrease the size of the BookingHashTable
                    size--;
                }
                //Else if the next node from the current one that we are on does not share the same key that we want to delete, move on to the next node
                tempNode = tempNode->next;
            }
        }
    }
}

vector<ItemType1> ParticularDateHashTable::get(KeyType key)
{
    //Initializing hash
    int i = hash(key);

    //Item
    ItemType1 item;
    vector< ItemType1 > arr;

    //Travelling linked list
    Node* tempNode = items[i];
    while (tempNode != NULL)
    {
        //If the current item's key matches what we want to find,
        if (tempNode->key == key)
        {
            //Set the returning item to the tempNode's item
            item = tempNode->item;
            arr.push_back(item);
        }
        //Else move down the linked list
        tempNode = tempNode->next;
    }

    //Return the item, item = "" if nothing found
    return arr;
}

bool ParticularDateHashTable::isEmpty()
{
    //return bool 
    return size == 0;
}

int ParticularDateHashTable::getLength()
{
    return size;
}

void ParticularDateHashTable::print()
{
    //For every position in the BookingHashTable,
    for (int i = 0; i < MAX_SIZE; i++)
    {
        //If position is not NULL
        if (items[i] != NULL)
        {
            //Travel down the linked list
            Node* tempNode = items[i];
            //If the current tempNode is not NULLm
            while (tempNode != NULL)
            {
                //Print item and key
                cout << tempNode->item.getBookingID() << " | " << tempNode->key << endl;
                //Go to next node
                tempNode = tempNode->next;
            }
        }
    }
}