#include <time.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#ifndef DATE_HPP
#define DATE_HPP

string int_to_string(int number) {
    ostringstream convert;
    convert << number;
    return convert.str();
}


class Date {
	private:
		int day, month, year;
	public:
		void update_current_date();
		void print_date();
		string get_date_string();
		int get_day();
		int get_month();
		int get_year(); 
};


void Date::update_current_date() {
	// Get current time
	time_t now = time(0);
	
	// Convert the time to a struct tm
	tm *ltm = localtime(&now);
	
	// Update date
	year  = ltm->tm_year + 1900;
	day   = ltm->tm_mday;
	month = ltm->tm_mon + 1; 
}

void Date::print_date() {
	update_current_date();
	cout << year << "-" << month << "-" << day << endl;
}

string Date::get_date_string() {
	update_current_date();
	string date = int_to_string(year) + "-" + int_to_string(month) + "-" + int_to_string(day);
	return date;
}

int Date::get_day() {
	return day;
}

int Date::get_month() {
	return month;
}

int Date::get_year() {
	return year;
}


#endif
