#include<iostream>
using namespace std;

//Take off the previous things before you make this as a header file.
//Include this after the normal iostream in the c++ file to compile correctly

class String {

	char* string;
	bool allocated;

public:
	String() {
		string = NULL;
		allocated = false;
	}

	String(const char* passedString) {
		string = (char*) passedString;
		allocated = false;
	}

	/* PUBLIC METHODS */

	int length() {
		int count=0;
		for(count=0; string[count]!='\0'; count++);
		return count;
	}

	/* OPERATOR OVERLOADING */

	void operator =(const char* passedString) {
		eraseString();
		string = (char*) passedString;
	}

	friend ostream &operator <<(ostream &out, String &str);
	friend istream &operator >>(istream &in, String &str);

	/* PRIVATE METHODS */

	void eraseString() {
		if(allocated == true) {
			delete string;
			allocated = false;
		}
	}

};

ostream &operator <<(ostream &out, String &str) {

	for(int iter=0; iter<str.length(); iter++) {
		out<<str.string[iter];
	}

	return out;

}

int main() {

	String hello = "hello";
	cout<<hello.length();

	cout<<hello;

	return 0;
}
