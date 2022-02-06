#include "BookingHashTable.h"
#include "ArrayList.h"

BookingHashTable::BookingHashTable()
{
    size = 0;
}

BookingHashTable::~BookingHashTable()
{
    for (int i = 0; i < MAX_SIZEHashTable; i++)
    {
        items[i] = NULL;
    }
}

int BookingHashTable::charvalue(char c)
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

int BookingHashTable::hash(KeyType key)
{
    //int i = value of the first letter of Key/Name
    int i = charvalue(key[0]);

    //For every letter in the name
    for (int j = 1; j < key.length(); j++)
    {
        //From second letter of name onwards, us this hash

        //index of first letter * 52 + index of iteration letter % max size
        i = (i * 52 + charvalue(key[j])) % MAX_SIZEHashTable;
    }

    return i;
}

bool BookingHashTable::add(KeyType newKey, ItemType1 newItem)
{
    int index = hash(newKey);
    if (items[index] == NULL) {
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

void BookingHashTable::remove(KeyType key)
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

void BookingHashTable::remove(KeyType key, ItemType1 bookingItem)
{
    //Initializing the hash
    int i = hash(key);

    //If the position in the BookingHashTable is not empty,
    if (items[i] != NULL)
    {
        //Check if the first item shares the same key to delete it
        if (items[i]->item.getBookingID() == bookingItem.getBookingID())
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
            while (tempNode->next != NULL)
            {
                //If the next node from the current one that we are on shares the same key that we want to delete,
                if (tempNode->next->item.getBookingID() == bookingItem.getBookingID())
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
ArrayListingBookings BookingHashTable::get(KeyType key)
{
    //Initializing hash
    int i = hash(key);

    //Item
    ItemType1 item ;
    ArrayListingBookings arr;

    //Travelling linked list
    Node* tempNode = items[i];
    while (tempNode != NULL)
    {
        //If the current item's key matches what we want to find,
        if (tempNode->key == key)
        {
            //Set the returning item to the tempNode's item
            item = tempNode->item;
            arr.add(item);
        }
        //Else move down the linked list
        tempNode = tempNode->next;
    }

    //Return the item, item = "" if nothing found
    return arr;
}

bool BookingHashTable::isEmpty()
{
    //return bool 
    return size == 0;
}

int BookingHashTable::getLength()
{
    return size;
}

void BookingHashTable::print()
{
    //For every position in the BookingHashTable,
    for (int i = 0; i < MAX_SIZEHashTable; i++)
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