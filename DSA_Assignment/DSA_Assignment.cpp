// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <string.h>
#include "list.h"
#include "Bookings.h"
#include "BookingHashTable.h"
 
using namespace std;
 
int sscanf_s();
void Menu(BookingHashTable hashBookingTable);

int main()
{
	List bookingList;
	BookingHashTable hashBookingTable;
	hashBookingTable.~BookingHashTable();
	ifstream myFile;
	myFile.open("BookingsAssignment.csv");
	
	//Adding the Bookings CSV into Linked List
	while (myFile.good()) 
	{
		string line;
		getline(myFile, line, ',');
		if (line.find("\n") != string::npos) 
		{
			string delimiter = "\n";
			size_t pos = 0;
			string token;
			int i = 0;
			Bookings newBooking;
			//Bookings bookingObject;
			//Bookings* bookingPointer = &bookingObject;
			/*Removing \n and , from the list*/
			while ((pos = line.find(delimiter)) != string::npos)
			{

				token = line.substr(0, pos);

				bookingList.add(token);
				
				if (bookingList.get(2) != "Guest Name") 
				{
					newBooking.setBookingID(bookingList.get(0));
					newBooking.setBookingDate(bookingList.get(1));
					newBooking.setGuestName(bookingList.get(2));
					newBooking.setRoomNo(bookingList.get(3));
					newBooking.setRoomType(bookingList.get(4));
					newBooking.setRoomStatus(bookingList.get(5));
					newBooking.setCheckIn(bookingList.get(6));
					newBooking.setCheckOut(bookingList.get(7));
					newBooking.setNumberGuest(bookingList.get(8));
					newBooking.setSpecialRequest(bookingList.get(9));
					//Function to make object from BookingList
					hashBookingTable.add(bookingList.get(2), newBooking);
				}
				

				//Wipe BookingList
				for (int i = 0; i < 10;i++) {
					bookingList.remove(0);
				}

				line.erase(0, pos + delimiter.length());

				bookingList.add(line);

			}

		}
		//If string does not have \n in it, just add to linked list
		else
			bookingList.add(line);
	}
	Menu(hashBookingTable);
}

void Menu(BookingHashTable hashBookingTable) {
	string input;
	cout << "Input name to be book:" ;
	getline(cin, input);
	vector<ItemType1> array = hashBookingTable.get(input);
	for (int i = 0; i < array.size();i++) {
		Bookings newbooking = array[i];
		cout << newbooking.getBookingID() << endl;
		string Date = newbooking.getCheckIn();
	}
}

//int sscanf_s(char aString[])
//{   // https://www.cplusplus.com/reference/ctime/tm/ for info about time structure (tm)
//	tm result;
//	char aString[] = "03/04/2020  06:09:02";
//	sscanf_s(aString, "%d/%d/%4d  %d:%d:%d",
//	&result.tm_mday, &result.tm_mon, &result.tm_year, &result.tm_hour, &result.tm_min, &result.tm_sec);
//	printf("tm_hour:  %d\n", result.tm_hour);
//	printf("tm_min:  %d\n", result.tm_min);
//	printf("tm_sec:  %d\n", result.tm_sec);
//	printf("tm_mday:  %d\n", result.tm_mday);
//	printf("tm_mon:  %d\n", result.tm_mon);
//	printf("tm_year:  %d\n", result.tm_year);
//	return 0;
//}

