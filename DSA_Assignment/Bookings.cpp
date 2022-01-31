#include "Bookings.h"



Bookings::Bookings(){}
Bookings::Bookings(string id, string bookdate, string gname, string roomno, string type, string status, string chkin, string chkout, string noguest, string srequest) 
{
	BookingID = id;
	BookingDate = bookdate;
	GuestName = gname;
	RoomNo = roomno;
	RoomType = type;
	Status = status;
	CheckIn = chkin;
	CheckOut = chkout;
	Guest = noguest;
	SpecialRequest = srequest;
}

void Bookings::setBookingID( string bookingid) { BookingID = bookingid; }
void Bookings::setBookingDate(string bookingdate) { BookingDate = bookingdate; }
void Bookings::setGuestName(string guestname) { GuestName = guestname; }
void Bookings::setRoomNo(string roomno) { RoomNo = roomno; }
void Bookings::setRoomType(string roomtype) { RoomType = roomtype; }
void Bookings::setRoomStatus(string status) { Status = status; }
void Bookings::setCheckIn(string chkin) { CheckIn = chkin; }
void Bookings::setCheckOut(string chkout) { CheckOut = chkout; }
void Bookings::setNumberGuest(string noguest) { Guest = noguest; }
void Bookings::setSpecialRequest(string srequest) { SpecialRequest = srequest; }
string Bookings::getBookingID() { return BookingID; }
string Bookings::getBookingDate() { return BookingDate; }
string Bookings::getGuestName() { return GuestName; }
string Bookings::getRoomNo() { return RoomNo; }
string Bookings::getRoomType() { return RoomType; }
string Bookings::getRoomStatus() { return Status; }
string Bookings::getCheckIn() { return CheckIn; }
string Bookings::getCheckOut() { return CheckOut; }
string Bookings::getNumberGuest() { return Guest; }
string Bookings::getSpecialRequest() { return SpecialRequest; }
