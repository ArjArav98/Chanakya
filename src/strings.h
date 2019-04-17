#define STRSIZE 50

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
		return getLength(string);
	}

	/* OPERATOR OVERLOADING */

	void operator =(const char* passedString) {
		eraseString();
		string = (char*) passedString;
	}

	char operator [](int index) {
		return string[index];
	}

	bool operator ==(const char* passedString) {
		
		//We first get the length of the first string.
		int len1 = getLength( (char*) passedString);

		//We now compare the two lengths.
		if(length() != len1) return false;
		else {
			//We now compare each character in both strings.
			int iter;

			for(iter=0; iter<len1; iter++) {
				if(passedString[iter] != string[iter]) return false;
			}
			
			return true;
		}

	}

	bool operator ==(String str) {
	
		//We first get the length of the first string.
		int len1 = str.length();

		//We now compare the two lengths.
		if(length() != len1) return false;
		else {
			//We now compare each character in both strings.
			int iter;

			for(iter=0; iter<len1; iter++) {
				if(str[iter] != string[iter]) return false;
			}

			return true;
		}

	}

	friend ostream &operator <<(ostream &out, String &str);
	friend istream &operator >>(istream &in, String &str);

	/* PRIVATE METHODS */

	int getLength(char* string) {

		int iter;
		for(iter=0; string[iter]!='\0'; iter++);
		return iter;
	}

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

istream &operator >>(istream &in, String &str) {

	char* new_str = new char[STRSIZE];
	cin.getline(new_str, STRSIZE);

	str.eraseString();
	str.string = new_str;
	str.allocated = true;

	return in;
}
