// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
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
#include "ArrayList.h"
#include "ArrayListingBookings.h"

using namespace std;
 
void particularDateGuest(ParticularDateHashTable dateHashTable);
void Menu(BookingHashTable hashBookingTable, RoomsList finalRoomsList, ParticularDateHashTable dateHashTable);
void Checkinguest(BookingHashTable hashBookingTable, RoomsList finalRoomsList, ParticularDateHashTable dateHashTable);
void CreateBooking(BookingHashTable hashBookingTable, RoomsList finalRoomsList, ParticularDateHashTable dateHashTable);
void PrintBooking(BookingHashTable hashBookingTable);

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

	Menu(hashBookingTable,finalRoomsList,dateHashTable);
}

 //Displaying guests staying in the hotel on a particular date

void Menu(BookingHashTable hashBookingTable, RoomsList finalRoomsList, ParticularDateHashTable dateHashTable) {
	string input;
	string datetime;
	tm result{};
	cout << "============================Menu============================" << endl;
	cout << "1) Check in guest " << endl;
	cout << "2) Add a new booking for the hotel" << endl;
	cout << "3) Display guests staying in the hotel for a particular day" << endl;
	cout << "4) Display particular month dates each room is occupied" << endl;
	cout << "5) See the particular booking for guest using name" << endl;
	cout << "0) Exit Functions" << endl;
	cout << "============================================================"<< endl;
	cout << "Input options:" ;
	getline(cin, input);

	if (input =="1")
	{
		Checkinguest(hashBookingTable, finalRoomsList, dateHashTable);
		Menu(hashBookingTable, finalRoomsList, dateHashTable);
	}
	else if (input == "2")
	{   
		CreateBooking(hashBookingTable, finalRoomsList, dateHashTable);
		Menu(hashBookingTable, finalRoomsList, dateHashTable);
	}
	else if (input == "3") {
		particularDateGuest(dateHashTable);
		Menu(hashBookingTable, finalRoomsList, dateHashTable);
	}
	else if (input == "4") {
		string inputMonth;
		string inputYear;

		cout << "Enter month: ";
		getline(cin, inputMonth);
		cout << "Enter year: ";
		getline(cin, inputYear);
		dateHashTable.returnRoomsMonth(inputMonth, inputYear);
		Menu(hashBookingTable, finalRoomsList, dateHashTable);
	}
	else if (input == "5") {
		PrintBooking(hashBookingTable);
		Menu(hashBookingTable, finalRoomsList, dateHashTable);
	}
	else if (input == "0") {
		exit;
	}
	else {
		cout << "invalid input, Please try again!"<< endl;
		Menu(hashBookingTable, finalRoomsList, dateHashTable);
	}
}

void particularDateGuest(ParticularDateHashTable dateHashTable)
{

	cout << "==== " << "Guests staying at hotel on a particular date" << " ====" << endl;
	string desiredDate;
	string input;
	cout << "Enter date: ";
	getline(cin, desiredDate);
	dateHashTable.getParticularDate(desiredDate);
	/*ArrayListingBookings array = dateHashTable.getParticularDate(desiredDate);*/

	/*for (int i = 0; i < array.getLength(); i++)
	{
		Bookings pulledBooking = array.get(i);
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
	}*/
}
void Checkinguest(BookingHashTable hashBookingTable, RoomsList finalRoomsList, ParticularDateHashTable dateHashTable) {
	//declaring of variables
	string NameInput;
	string bookingInput;
	string datetime;
	tm result{};
	// Get the name value 
	cout << "Input name to be book:";
	getline(cin, NameInput);
	cout << endl;
	ArrayListingBookings array = hashBookingTable.get(NameInput);
	int bookingsCounter = 0;

	for (int i = 0; i < array.getLength();i++) {
		Bookings newbooking = array.get(i);
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

		for (int i = 0; i < array.getLength();i++)
		{
			if (array.get(i).getBookingID() == bookingInput)
			{
				for (int j = 0; j < finalRoomsList.getLength(); j++) {
					if (finalRoomsList.get(j).getRoom_Type() == array.get(i).getRoomType() && finalRoomsList.get(j).getStatus() == "No") {
						Bookings updatedBooking;
						updatedBooking.setBookingID(array.get(i).getBookingID());
						updatedBooking.setBookingDate(array.get(i).getBookingDate());
						updatedBooking.setGuestName(array.get(i).getGuestName());
						updatedBooking.setRoomNo(finalRoomsList.get(j).getRoom_number());
						updatedBooking.setRoomType(array.get(i).getRoomType());
						updatedBooking.setRoomStatus("Checked In");
						updatedBooking.setCheckIn(array.get(i).getCheckIn());
						updatedBooking.setCheckOut(array.get(i).getCheckOut());
						updatedBooking.setNumberGuest(array.get(i).getNumberGuest());
						updatedBooking.setSpecialRequest(array.get(i).getSpecialRequest());
						//Function to make object from BookingList
						hashBookingTable.remove(array.get(i).getGuestName(), array.get(i));
						hashBookingTable.add(array.get(i).getGuestName(), updatedBooking);
					    finalRoomsList.get(j).setStatus("Yes");
						break;
					}
				}
			}
		}

	}
}
void CreateBooking(BookingHashTable hashBookingTable, RoomsList finalRoomsList, ParticularDateHashTable dateHashTable) {
	string input;
	string name;
	Bookings CreateNewBooking;
	cout << "Input Name: ";
	getline(cin, name);
	CreateNewBooking.setGuestName(name);
	cout << "Input Booking Date: ";
	getline(cin, input);
	CreateNewBooking.setBookingDate(input);
	cout << "Input Room Type: ";
	getline(cin, input);
	CreateNewBooking.setRoomType(input);
	cout << "Input Check in date: ";
	getline(cin, input);
	CreateNewBooking.setCheckIn(input);
	cout << "Input Check out date: ";
	getline(cin, input);
	CreateNewBooking.setCheckOut(input);
	cout << "Input Number of guest: ";
	getline(cin, input);
	CreateNewBooking.setNumberGuest(input);
	cout << "Input Special Request (Leave empty if none): ";
	getline(cin, input);
	CreateNewBooking.setSpecialRequest(input);
	CreateNewBooking.setRoomStatus("Booked");
	CreateNewBooking.setRoomNo("");
	int size = hashBookingTable.getLength() + 1;
	stringstream ss;
	string BookingID="";
	ss << size;
	ss >> BookingID;
	CreateNewBooking.setBookingID(BookingID);
	hashBookingTable.add(name, CreateNewBooking);
	Menu(hashBookingTable,finalRoomsList,dateHashTable);
	cout << endl;

}
void PrintBooking(BookingHashTable hashBookingTable) {
	string NameInput;
	cout << "Input name: ";
	getline(cin, NameInput);
	ArrayListingBookings array = hashBookingTable.get(NameInput);
	for (int j = 0; j < array.getLength(); j++) {
		cout << "Booking ID: " << array.get(j).getBookingID() << endl;
		cout << "Booking Date: " << array.get(j).getBookingDate() << endl;
		cout << "Check In Date: " << array.get(j).getCheckIn() << endl;
		cout << "Booking Date: " << array.get(j).getRoomType() << endl;
		cout << "Booking Status: " << array.get(j).getRoomStatus() << endl << endl;
	}
}




