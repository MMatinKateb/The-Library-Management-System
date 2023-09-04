#include <iostream>
#include <string>
#include "Student.hpp"
using namespace std;

#ifndef BOOK_HPP
#define BOOK_HPP


class Book {
    private:
        string author, title;
        int book_id, issued_by;
        bool available;
        

    public:
        void register_book(string auth, string titl, int id);
        void display();
        int get_bookid();
        bool is_available();
        void issue_book(int st_no);
        bool return_book(int sno);
        int get_issued_student();
};

void Book::register_book(string auth, string titl, int id) {
    author = auth;
    title = titl;
    book_id = id;
    available = true;
}

void Book::display() {
    cout << author << "\t\t|\t\t" << title << "\t\t|\t\t" << book_id << "\t\t|\t\t" << available << "        " << "\n";
}

int Book::get_bookid() {
	return book_id;
}

bool Book::is_available() {
	if (available)	return true;
	else			return false;
}

void Book::issue_book(int st_no) {
	available = false;
	issued_by = st_no;
}

bool Book::return_book(int sno) {
	if (issued_by != sno) 
		return false;
	available = true;
	issued_by = 0;
	return true;
}

int Book::get_issued_student() {
	return issued_by;
}


#endif
