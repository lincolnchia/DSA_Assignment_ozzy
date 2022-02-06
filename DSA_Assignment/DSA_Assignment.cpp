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
#include "ParticularDateHashTable.h"
 
using namespace std;
 
int sscanf_s();
void Menu(BookingHashTable hashBookingTable);
void particularDateGuest(ParticularDateHashTable dateHashTable);

int main()
{
	List bookingList;
	BookingHashTable hashBookingTable;
	hashBookingTable.~BookingHashTable();
	ParticularDateHashTable dateHashTable;
	dateHashTable.~ParticularDateHashTable();
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
					// dateHashTable stores Bookings objects by their checkin date
					dateHashTable.add(bookingList.get(6), newBooking);
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

	particularDateGuest(dateHashTable);

	//Menu(hashBookingTable);
}

 //Displaying guests staying in the hotel on a particular date
void particularDateGuest(ParticularDateHashTable dateHashTable) 
{

	cout << "====" << "Guests staying at hotel on a particular date" << "====" << endl;
	string desiredDate;
	string input;
	cout << "Enter date: ";
	getline(cin, desiredDate);

	vector<ItemType1> array = dateHashTable.getParticularDate(desiredDate);

	for (int i = 0; i < array.size(); i++)
	{
		Bookings pulledBooking = array[i];
		cout << endl;
		cout << "====" << "Booking ID: " << pulledBooking.getBookingID() << "====" << endl;
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

void Menu(BookingHashTable hashBookingTable) {
	string input;
	string datetime;
	char aString[20];
	tm result{};
	cout << "Input name to be booked:" ;
	getline(cin, input);
	vector<ItemType1> array = hashBookingTable.get	(input);
	for (int i = 0; i < array.size();i++) {
		Bookings newbooking = array[i];
		cout << newbooking.getBookingID() << endl;
		datetime = newbooking.getCheckIn();
		strcpy_s(aString, datetime.c_str());
		sscanf_s(aString, "%d/%d/%4d  %d:%d:%d", &result.tm_mday, &result.tm_mon, &result.tm_year, &result.tm_hour, &result.tm_min, &result.tm_sec);
		result.tm_year = result.tm_year - 1900;
		result.tm_mon = result.tm_mon - 1;
		time_t t = mktime(&result);
	}
}



