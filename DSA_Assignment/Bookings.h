#pragma once
#include <iostream>

using namespace std;


class Bookings {
private:
	string BookingID;
	string BookingDate;
	string GuestName;
	string RoomNo;
	string RoomType;
	string Status;
	string CheckIn;
	string CheckOut;
	string Guest;
	string SpecialRequest;
public:
	Bookings();
	Bookings(string, string, string, string, string, string, string, string, string, string);
	void setBookingID(string);
	void setBookingDate(string);
	void setGuestName(string);
	void setRoomNo(string);
	void setRoomType(string);
	void setRoomStatus(string);
	void setCheckIn(string);
	void setCheckOut(string);
	void setNumberGuest(string);
	void setSpecialRequest(string);
	string getBookingID();
	string getBookingDate();
	string getGuestName();
	string getRoomNo();
	string getRoomType();
	string getRoomStatus();
	string getCheckIn();
	string getCheckOut();
	string getNumberGuest();
	string getSpecialRequest();
};