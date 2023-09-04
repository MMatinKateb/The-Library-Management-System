#include <iostream>
#include <string.h>
using namespace std;

#ifndef STUDENT_HPP
#define STUDENT_HPP

class Student {
	private:
		bool isRegistered;
		string st_name, st_family, st_address;
		int st_num;
		
	public:
		Student();
		bool register_student(string name, string family, string address, int st_no);
		int get_stno();
		
};

Student::Student() {
	if (!isRegistered) {	// If is not registered.
		st_name = st_family = st_address = "";
		st_num = 0;
		isRegistered = false;
	}
}

bool Student::register_student(string name, string family, string address, int st_no) {
	st_name = name;
	st_family = family;
	st_address = address;
	st_num = st_no;
	isRegistered = true;
	return true;
}

int Student::get_stno() {
	return st_num;
}



#endif
