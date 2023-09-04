#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include "Student.hpp"
#include "Book.hpp"
#include "Date.hpp"
#include "Log.hpp"
using namespace std;

/*
	Author: Negin Heidari
	The Library Management System
*/

Book* find_book_by_id(Book arr[], int id) {
	int i;
	for (i=0; i<5; i++)
		if (arr[i].get_bookid() == id)
			return &arr[i];
}


bool book_exists(int bookid, Book arr[]) {
	int i;
	for (i=0; i<5; i++)
		if (arr[i].get_bookid() == bookid)
			return true;	// Book exists
	return false;			// Book does not exist
}

bool student_exists(int stnum, Student arr[]) {
	int i = 5;
	for (i=0; i<5; i++)
		if (arr[i].get_stno() == stnum && stnum != 0)
			return true;	// Student exists
	return false;			// Student does not exist
}


void press_key() {
	cout << "Press any key to continue...\n";
	getch();
}


// Show Menu
void show_menu() {
	cout << "[ Enter a number according to the options below ]\n";
	cout << "1 - Register Student\n";
	cout << "2 - Show List of Books\n";
	cout << "3 - Issue Book\n";
	cout << "4 - Return a Book\n";
	cout << "5 - Report\n";
	cout << "6 - Exit Program\n\n";
}

bool has_duplicates(Student arr[], int st_no, int st_counter) {

    for (int i=0; i<5; i++) {   // Check for duplicate student numbers
        if (i == st_counter + 1)
            continue;

        else if (arr[i].get_stno() == st_no) {
            cout << "[!!!] Student already exists.\n";
            press_key();
            return true;
        }
    }

    return false;
}


int main() {
	
	Student st[5];
	Book bk[5];
	Date dt;
	
	int st_counter = -1;    // Keep track of number of students

	// Define available books
	bk[0].register_book("Adams     ", "Mathematics               ", 1111111);
	bk[1].register_book("Tannenbaum", "Operating Systems         ", 2222222);
	bk[2].register_book("Russle    ", "Artificial Intelligence   ", 3333333);
	bk[3].register_book("Ross      ", "Computer Networks         ", 4444444);
	bk[4].register_book("CLRS      ", "Introduction to Algorithms", 5555555);
	
	// check/create Report.txt file
	fstream file;
	if (!report_file_exists()) { // If file does not exist
		create_report_file();
		file.open("Report.txt", fstream::in | fstream::app);
	} else
		file.open("Report.txt", fstream::in | fstream::app);
	


	while (true) {
		system("CLS");
		
		// Re-open file
		file.close();
		file.open("Report.txt", fstream::in | fstream::app);
		
		int option;
		cout << "\t\t\t### Library Management System ###\n";
		cout << "\t\t\t### Today\'s date: " << dt.get_date_string() << "\n";
		cout << "\t\t\t### Author: Mohammad Matin Kateb\n\n\n";
		show_menu();
		cout << "Enter a number: ";
		cin >> option;
		

		if (option == 1) {
			// Registering student
			int st_no; 
			string st_name, st_family, st_address;

			cout << "Enter student name: ";
			cin >> st_name;
			cout << "Enter student family: ";
			cin >> st_family;
			cout << "Enter student address: ";
			cin >> st_address;
			cout << "Enter student number: ";
			cin >> st_no;

			if (has_duplicates(st, st_no, st_counter)) {
				continue;
			} else if (st_counter >= 4) {
				cout << "[!!!] Maximum capacity for number of students reached.\n";
				press_key();
				continue;
			} else {    //  Register student
				st_counter++;
				if ( st[st_counter].register_student(st_name, st_family, st_address, st_no) ) {
					cout << "New student registered successfully.\n";
					string report = "[" + dt.get_date_string() + "] " + "New student with StudentNO-" + int_to_string(st_no) + " registered.";
					file << report << endl;
					press_key();
				}
			}
		} else if (option == 2) {
			// Show list of books
			cout << "\n\n\t\t### List of Books:\n\n";
			cout << "Author     " << "\t\t|\t\t" << "Title                     " << "\t\t|\t\t" << "Book ID" << "\t\t|\t\t" << "Available" << "\n";
			for (int i=0; i<5; i++)
				bk[i].display();
			press_key();
			continue;
		} else if (option == 3) {
			// Issue Book
			int st_id, book_id;
			cout << "\n\t\t###Book Issue\n";
			cout << "Enter student number: ";
			cin >> st_id;
			cout << "Enter book ID: ";
			cin >> book_id;
			if ( student_exists(st_id, st) && book_exists(book_id, bk) ) {
				// find the book
				Book *book = find_book_by_id(bk, book_id);
				if (!book->is_available()) { // if book is NOT available
					cout << "[!!!] Sorry, the book is not available.\n";
					press_key();
					continue;
				} else {	// Book is available
					cout << "Issuing book-" << book_id << " for stundet-" << st_id << endl;
					book->issue_book(st_id);
					string report = "[" + dt.get_date_string() + "] " + "Issuing book-" + int_to_string(book_id) + " for student-" + int_to_string(st_id);
					file << report << endl;
					cout << "Book-" << book_id << " successfully issued for student-" << st_id << endl;
					press_key();
					continue;
				}
			} else {
				cout << "[!!!] Invalid Information\n";
				press_key();
				continue;
			}
		} else if (option == 4) {
			// Return a book
			cout << "\t\t\t### Return Book\n\n";
			int book_id, stu_id;
			cout << "Enter book ID to return: ";
			cin >> book_id;
			cout << "Enter studentNO: ";
			cin >> stu_id;
			Book *book = find_book_by_id(bk, book_id);
			if (book->is_available() || !student_exists(stu_id, st) || !book_exists(book_id, bk) || 
				book->get_issued_student() != stu_id) {
				cout << "[!!!] Invalid Information.\n";
				press_key();
				continue;
			} else {
				if (!book->return_book(stu_id)) {
					cout << "[!!!] Invalid Information.\n";
					press_key();
					continue;
				} else {
					string report = "[" + dt.get_date_string() + "]" + " Book-" + int_to_string(book_id) + " returned by student-" + int_to_string(stu_id);
					file << report << endl;
					cout << "Book-" << book_id << " returned by student-" << stu_id << endl;
					press_key();
					continue;
				}
			}
		} else if (option == 5) {
			// Report
			cout << "\n\n\t\t## Report:\n\n";
			string line;
			while (getline(file, line))
				cout << line << endl;
			cout << endl;
			press_key();
			continue;
		} else if (option == 6) {
			// Exit
			cout << "Exiting...\n";
			press_key();
			file.close();
			exit(0);
		} else {
			cout << "[!!!] Invalid Input\n\n";
			press_key();
			continue;
		}
		
	}

    return 0;
}
