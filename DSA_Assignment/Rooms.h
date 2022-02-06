#pragma once
#include <iostream>

using namespace std;


class Rooms {
private:
	string Room_number;
	string Room_Type;
	string Cost_per_night;
	string Status;
public:
	Rooms();
	Rooms(string, string, string, string);
	void setRoom_number(string);
	void setRoom_Type(string);
	void setCost_per_night(string);
	void setStatus(string);
	string getRoom_number();
	string getRoom_Type();
	string getCost_per_night();
	string getStatus();
};