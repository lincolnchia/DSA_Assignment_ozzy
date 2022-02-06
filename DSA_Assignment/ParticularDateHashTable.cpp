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
    for (int i = 0; i < MAX_SIZE_DATE; i++)
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
 
// Creating hashkey using the month of the year, hash table will contain bookings over 2 years so months in 2021 have 12 added to them
// Hash table will hold 24 months
// i.e Jan 2020 = 1, Jan 2021 = 13, Nov 2020 = 11, Nov 2021 = 23
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
                return monthNumber + 12;
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
        NodeDate* n = new NodeDate();
        n->key = newKey;
        n->item = newItem;
        n->next = NULL;
        items[index] = n;
        //size++;
    }
    else //collision
    {
        NodeDate* temp = items[index];

        while (temp->next != NULL) {
            temp = temp->next;
        }

        NodeDate* n = new NodeDate();
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
            NodeDate* tempNode = items[i];
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

// Returns the guests staying in the hotel on a particular date
vector<ItemType1> ParticularDateHashTable::getParticularDate(KeyType key)
{
    //Initializing hash
    int i = hash(key);

    //Item
    ItemType1 item;
    vector< ItemType1 > arr;

    // Turning the user input into time_t object so I can compare to a room's checkIn/checkOut date
    char keyString[20];
    tm keyResult{};
    strcpy_s(keyString, key.c_str());
    sscanf_s(keyString, "%d/%d/%4d  %d:%d:%d", &keyResult.tm_mday, &keyResult.tm_mon, &keyResult.tm_year, &keyResult.tm_hour, &keyResult.tm_min, &keyResult.tm_sec);
    keyResult.tm_year = keyResult.tm_year - 1900;
    keyResult.tm_mon = keyResult.tm_mon - 1;
    time_t keyTime = mktime(&keyResult);

    //Travelling linked list
    NodeDate* tempNode = items[i];
    while (tempNode != NULL)
    {
        // Turning Booking object checkIn date to time_t object
        char checkInString[20];
        tm checkInResult{};
        strcpy_s(checkInString, tempNode->item.getCheckIn().c_str());
        sscanf_s(checkInString, "%d/%d/%4d  %d:%d:%d", &checkInResult.tm_mday, &checkInResult.tm_mon, &checkInResult.tm_year, &checkInResult.tm_hour, &checkInResult.tm_min, &checkInResult.tm_sec);
        checkInResult.tm_year = checkInResult.tm_year - 1900;
        checkInResult.tm_mon = checkInResult.tm_mon - 1;
        time_t checkInTime = mktime(&checkInResult);

        // Turning Booking object checkOut date to time_t object
        char checkOutString[20];
        tm checkOutResult{};
        strcpy_s(checkOutString, tempNode->item.getCheckOut().c_str());
        sscanf_s(checkOutString, "%d/%d/%4d  %d:%d:%d", &checkOutResult.tm_mday, &checkOutResult.tm_mon, &checkOutResult.tm_year, &checkOutResult.tm_hour, &checkOutResult.tm_min, &checkOutResult.tm_sec);
        checkOutResult.tm_year = checkOutResult.tm_year - 1900;
        checkOutResult.tm_mon = checkOutResult.tm_mon - 1;
        time_t checkOutTime = mktime(&checkOutResult);

        // If the date that was input falls between checkIn and checkOut dates, return the item
        if (checkInTime <= keyTime && keyTime <= checkOutTime)
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

// Hashing function for words i.e November 2021 and not DD/MM/YYYY
int ParticularDateHashTable::hashMonthWords(KeyType monthKey, KeyType yearKey) 
{
    int monthKeyInt;
    // If length of month is more than 2, it is a word
    if (monthKey.length() > 2)
    {
        // Convert the month to lower case
        for (int i = 0; i < monthKey.length(); i++)
        {
            monthKey[i] = tolower(monthKey[i]);
        }

        // Assign a month value
        if (monthKey == "january")
        {
            monthKeyInt = 1;
        }
        else if (monthKey == "february")
        {
            monthKeyInt = 2;
        }
        else if (monthKey == "march")
        {
            monthKeyInt = 3;
        }
        else if (monthKey == "april")
        {
            monthKeyInt = 4;
        }
        else if (monthKey == "may")
        {
            monthKeyInt = 5;
        }
        else if (monthKey == "june")
        {
            monthKeyInt = 6;
        }
        else if (monthKey == "july")
        {
            monthKeyInt = 7;
        }
        else if (monthKey == "august")
        {
            monthKeyInt = 8;
        }
        else if (monthKey == "september")
        {
            monthKeyInt = 9;
        }
        else if (monthKey == "october")
        {
            monthKeyInt = 10;
        }
        else if (monthKey == "november")
        {
            monthKeyInt = 11;
        }
        else if (monthKey == "december")
        {
            monthKeyInt = 12;
        }

        // If the year is 2021, add 12 to month value
        if (yearKey == "2021")
        {
            monthKeyInt = monthKeyInt + 12;
        }
    }
    // Else if month input already the month number
    else
    {
        // If the year is 2021, add 12 to it
        if (yearKey == "2021")
        {
            // Convert the month input into int and add 12
            monthKeyInt = stoi(monthKey) + 12;
        }
        else
        {
            // Convert the month input into int 
            monthKeyInt = stoi(monthKey);
        }
    }

    return monthKeyInt;
}

// Display for a particular month, the dates that each room is occupied
void ParticularDateHashTable::returnRoomsMonth(KeyType month, KeyType year) 
{
    // Get the hash for user input
    int hashKey = hashMonthWords(month, year);

    //Item
    ItemType1 item;
    vector< ItemType1 > arr;

    //Travelling linked list
    NodeDate* tempNode = items[hashKey];
    while (tempNode != NULL)
    {
        item = tempNode->item;
        arr.push_back(item);
        //Else move down the linked list
        tempNode = tempNode->next;
    }

    cout << "==== Bookings for the month: " << month << " ====" << endl;

    for (int i = 100; i <= 120; i++) 
    {
        for (int arrayCounter = 0; arrayCounter < arr.size(); arrayCounter++) 
        {
            Bookings pulledBooking = arr[arrayCounter];
            string roomNo = pulledBooking.getRoomNo();

            string delimiter = " ";
            size_t pos = 0;
            string token;
            int intRoomNo;
            while ((pos = roomNo.find(delimiter)) != string::npos)
            {
                intRoomNo = stoi(roomNo.erase(0, pos + delimiter.length()));
            }

            if (intRoomNo == i) 
            {
                cout << endl;
                cout << "==== Bookings for Room No: " << pulledBooking.getRoomNo() << " ====" << endl;
                cout << endl;
                cout << "==== " << "Booking ID: " << pulledBooking.getBookingID() << " ====" << endl;
                cout << endl;
                cout << "Guest Name: " << pulledBooking.getGuestName() << endl;
                cout << "Room Type: " << pulledBooking.getRoomType() << endl;
                cout << "Room No.: " << pulledBooking.getRoomNo() << endl;
                cout << "Number of Guests: " << pulledBooking.getNumberGuest() << endl;
                cout << "Check-in Date: " << pulledBooking.getCheckIn() << endl;
                cout << "Check-out Date: " << pulledBooking.getCheckOut() << endl;
                cout << "Status: " << pulledBooking.getRoomStatus() << endl;
                cout << "Date Booked: " << pulledBooking.getBookingDate() << endl;
            }
        }
    }
}

//vector<ItemType1> ParticularDateHashTable::get(KeyType key)
//{
//    //Initializing hash
//    int i = hash(key);
//
//    //Item
//    ItemType1 item;
//    vector< ItemType1 > arr;
//
//    //Travelling linked list
//    NodeDate* tempNode = items[i];
//    while (tempNode != NULL)
//    {
//        item = tempNode->item;
//        arr.push_back(item);
//        //If the current item's key matches what we want to find,
//        if (tempNode->key == key)
//        {
//            //Set the returning item to the tempNode's item
//            item = tempNode->item;
//            arr.push_back(item);
//        }
//        //Else move down the linked list
//        tempNode = tempNode->next;
//    }
//
//    //Return the item, item = "" if nothing found
//    return arr;
//}

//vector<ItemType1> ParticularDateHashTable::get(KeyType key)
//{
//    //Initializing hash
//    int i = hash(key);
//
//    //Item
//    ItemType1 item;
//    vector< ItemType1 > arr;
//
//    //Travelling linked list
//    NodeDate* tempNode = items[i];
//    while (tempNode != NULL)
//    {
//        item = tempNode->item;
//        arr.push_back(item);
//        //If the current item's key matches what we want to find,
//        if (tempNode->key == key)
//        {
//            //Set the returning item to the tempNode's item
//            item = tempNode->item;
//            arr.push_back(item);
//        }
//        //Else move down the linked list
//        tempNode = tempNode->next;
//    }
//
//    //Return the item, item = "" if nothing found
//    return arr;
//}

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
    for (int i = 0; i < MAX_SIZE_DATE; i++)
    {
        //If position is not NULL
        if (items[i] != NULL)
        {
            //Travel down the linked list
            NodeDate* tempNode = items[i];
            //If the current tempNode is not NULLm
            while (tempNode != NULL)
            {
                //Print item and key
                cout << tempNode->item.getCheckIn() << " | " << i << " | " << tempNode->key << endl;
                //Go to next node
                tempNode = tempNode->next;
            }
        }
    }
    cout << "The size of the dictionary is :" << size << endl;
}