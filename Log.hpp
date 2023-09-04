#include <fstream>
#include <iostream>
using namespace std;

#ifndef LOG_HPP
#define LOG_HPP

bool report_file_exists() {
	ifstream file("Report.txt");
	if (file)
		return true;	// Report file exists in directory
	else
		return false;
}

void create_report_file() {
    ofstream file("Report.txt");
    file.close();
}


//void write_to_report_file(ofstream file, string text) {
//	if (file.is_open())
//		file << text << endl;
//	else 
//		cout << "Unable to open the file." << endl;
//}
//
//void read_from_report_file(ifstream file) {
//	cout << "\n\n\t\t## Report:\n\n";
//	if (file.is_open()) {
//		string line;
//		while (getline(file, line)) {
//			cout << line << endl;
//		}
//	} else {
//		cout << "Unable to open the file." << endl;
//	}
//}

#endif
