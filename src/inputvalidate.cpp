#include<iostream>
#include<fstream>
#include<regex>
using namespace std;

class InputValidate {

	string filename;

public:
	InputValidate(string passed_filename) {
		filename = passed_filename;
	}

	bool linesAreValid() {

		fstream file(filename);
		string line;
		regex expression("([a-zA-z0-9-_]+  *[<=:]( *[^(\t)(\n)(\r)(\r\n)(\v)]{2,})+ *~{1})*");

		getline(file, line);

		while(!file.eof()) {
			if(!regex_match(line,expression)) {
				file.close();
				return false;
			}
			getline(file, line);
		}

		file.close();
		return true;

	}

	bool twoDotsInLine() {

		fstream file(filename);
		char character;

		while(!file.eof()) {

			file >> character;
			
			/* If a dot is encountered. */
			if(character == '.') {

				while(!file.eof()) {
					/* If another dot is encountered. */
					if(character == '.') {
						file.close();
						return true;
					}
					/* If another operator is encountered. */
					else if(character == ':' || character == '<' || character == '=') {
						file.close();
						return false;
					}
				}

			}
		}

		return true;

	}

	bool fileIsValid() {
		return !twoDotsInLine() && linesAreValid();
	}

};

int main() {

	InputValidate in("hello.txt");
	if(in.fileIsValid()) cout<<"it's valid!\n";
	else cout<<"it is not valid!\n";

	return 0;
}
