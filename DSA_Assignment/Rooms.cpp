#include "Rooms.h"

Rooms::Rooms() {}
Rooms::Rooms(string roomNumber, string roomType, string CostPerNight, string status)
{
	Room_number = roomNumber;
	Room_Type = roomType;
	Cost_per_night = CostPerNight;
	Status = status;
}
void Rooms::setRoom_number(string roomNum) 
{
	Room_number = roomNum;
}
void Rooms::setRoom_Type(string roomType)
{
	Room_Type = roomType;
}
void Rooms::setCost_per_night(string CostPerNight)
{
	Cost_per_night = CostPerNight;
}
void Rooms::setStatus(string status) {
	Status = status;
}
string Rooms::getRoom_number()
{
	return Room_number;
}
string Rooms::getRoom_Type()
{
	return Room_Type;
}
string Rooms::getCost_per_night()
{
	return Cost_per_night;
}
string Rooms::getStatus()
{
	return Status;
}

