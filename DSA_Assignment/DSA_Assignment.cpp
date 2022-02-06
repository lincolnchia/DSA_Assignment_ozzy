// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
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
#include "Rooms.h"
#include "RoomsList.h"
#include <stdio.h>      
#include <time.h>
#include <iomanip>
#include "ParticularDateHashTable.h"
 
using namespace std;
 
int sscanf_s();
void Menu(BookingHashTable hashBookingTable);
void particularDateGuest(ParticularDateHashTable dateHashTable);
void Menu(BookingHashTable hashBookingTable, RoomsList roomsList);

int main()
{
	List bookingList;
	List roomsList;
	RoomsList finalRoomsList;
	BookingHashTable hashBookingTable;
	hashBookingTable.~BookingHashTable();
	ParticularDateHashTable dateHashTable;
	dateHashTable.~ParticularDateHashTable();
	ifstream myFile;
	myFile.open("BookingsAssignment.csv");

	ifstream nextFile;
	nextFile.open("Rooms.csv");

	//Loading in Rooms file
	while (nextFile.good())
	{
		string line;
		getline(nextFile, line, ',');
		if (line.find("\n") != string::npos)
		{
			string delimiter = "\n";
			size_t pos = 0;
			string token;
			//finding the point at which we want to split the string
			while ((pos = line.find(delimiter)) != string::npos)
			{
				//saving the first half of the string
				Rooms newRoom;
				token = line.substr(0, pos);
				roomsList.add(token);
				if (roomsList.get(2) != "Cost per night") {
					newRoom.setRoom_number(roomsList.get(0));
					newRoom.setRoom_Type(roomsList.get(1));
					newRoom.setCost_per_night(roomsList.get(2));
					newRoom.setStatus("No");
					finalRoomsList.add(newRoom);
				}

				for (int i = 0; i < 4;i++) {
					roomsList.remove(0);
				}

				//saving the second half of the string
				line.erase(0, pos + delimiter.length());
				roomsList.add(line);
			}
		}
		//adding the lines regularly
		else {
			roomsList.add(line);
		}
	}

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
					//Adding status to the rooms 
					if (bookingList.get(5) == "Checked In")
					{
						//Runs through the final rooms list 
						for (int i = 0; i < finalRoomsList.getLength(); i++) {
							//Checks that newbookings room is the same as in room
							if (bookingList.get(3) == finalRoomsList.get(i).getRoom_number()) {
								Rooms newRoom;
								newRoom.setRoom_number(finalRoomsList.get(i).getRoom_number());
								newRoom.setCost_per_night(finalRoomsList.get(i).getCost_per_night());
								newRoom.setRoom_Type(finalRoomsList.get(i).getRoom_Type());
								newRoom.setStatus("True");
								finalRoomsList.remove(i);
								finalRoomsList.add(i, newRoom);
							}
						}
					}
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

	cout << "==== " << "Guests staying at hotel on a particular date" << " ====" << endl;
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

void Menu(BookingHashTable hashBookingTable, RoomsList finalRoomsList) {
	string input;
	string NameInput;
	string bookingInput;
	string datetime;
	char aString[20];
	tm result{};
	cout << "==========Menu==========" << endl;
	cout << "1) Check In guest " << endl;
	cout << "2) Add a new booking for the hotel" << endl;
	cout << "========================"<< endl;
	cout << "Input options:" ;
	getline(cin, input);

	if (input =="1")
	{
		//declaring of variables
		string datetime;
		char aString[20];
		tm result{};
		// Get the name value 
		cout << "Input name to be book:";
		getline(cin, NameInput);
		cout << endl;
		vector<ItemType1> array = hashBookingTable.get(NameInput);
		int bookingsCounter = 0;

		for (int i = 0; i < array.size();i++) {
			Bookings newbooking = array[i];
			if (newbooking.getRoomStatus() != "Checked Out" && newbooking.getRoomStatus() != "Checked In") {
				cout << "Booking ID: " << newbooking.getBookingID() << " ";
				cout << "Check In date: " << newbooking.getCheckIn() << " " << endl;
				//adding to the size of the bookings
				bookingsCounter++;
			}
		}

		// Checking if there are any bookings
		if (bookingsCounter == 0) 
		{
			cout << "There are no bookings" << endl << endl;
		}

		//asking for which booking to enter
		else {
			cout << "Which Booking would you like to book in for: ";
			getline(cin, bookingInput);
			cin.clear();
			int intbookingInput;
			stringstream ss;
			ss << bookingInput;
			ss >> intbookingInput;

			for (int i = 0; i < array.size();i++) 
			{
				if (array[i].getBookingID() == bookingInput)
				{
					for (int j = 0; j < finalRoomsList.getLength(); j++) {
						if (finalRoomsList.get(j).getRoom_Type() == array[i].getRoomType() && finalRoomsList.get(j).getStatus() == "No") {
							Bookings updatedBooking;
							updatedBooking.setBookingID(array[i].getBookingID());
							updatedBooking.setBookingDate(array[i].getBookingDate());
							updatedBooking.setGuestName(array[i].getGuestName());
							updatedBooking.setRoomNo(finalRoomsList.get(j).getRoom_number());
							updatedBooking.setRoomType(array[i].getRoomType());
							updatedBooking.setRoomStatus("Checked In");
							updatedBooking.setCheckIn(array[i].getCheckIn());
							updatedBooking.setCheckOut(array[i].getCheckOut());
							updatedBooking.setNumberGuest(array[i].getNumberGuest());
							updatedBooking.setSpecialRequest(array[i].getSpecialRequest());
							//Function to make object from BookingList
							hashBookingTable.remove(array[i].getGuestName(),array[i]);
							hashBookingTable.add(array[i].getGuestName(), updatedBooking);
							break;
						}
					}
				}
			}

		}
		Menu(hashBookingTable, finalRoomsList);
	}
	else if (input == "2")
	{   
		Menu(hashBookingTable, finalRoomsList);
	}
}




