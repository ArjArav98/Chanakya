#include<iostream>
using namespace std;

//Take off the previous things before you make this as a header file.
//Include this after the normal iostream in the c++ file to compile correctly

class String {

	char* string;

public:
	String() {
		string = NULL;
	}

	String(const char* passedString) {
		string = passedString;
	}

	int length() {
		
	}

};
