#include<iostream>
#include<stack>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

class JsonValidator {

    ifstream jsonFile;

	public:
    JsonValidator(string filename) {
        jsonFile.open(filename);
        cout<<arraysAreFormattedProperly(0);
    }

    private:

	/* Checks if the [ and { have matching brackets. */
	bool bracketsAreMatched(string filename) {

		ifstream jsonFile(filename);
		stack<char> bracketStack;
        bool quotesNotOpen = true;

		while(true) {
			char character;
			jsonFile>>character;

			if(jsonFile.eof() ) break;
            if( character == '"' ) quotesNotOpen = !quotesNotOpen;

            {
                if( (character == '{' || character == '[') && quotesNotOpen) {
                    bracketStack.push(character);
                }
                else if ( (character == '}' || character == ']') && quotesNotOpen ) {
                    if(bracketStack.size() == 0) return false;

                    char topSymbol = bracketStack.top();
                    bracketStack.pop();

                    if(character == '}' && topSymbol == '{');
                    else if(character == ']' && topSymbol == '[');
                    else return false;
                }
            }
		}

		if(bracketStack.size() != 0) return false;

		return true;
	}

    /* We extract each string and see if it is formatted properly. */
    bool stringsAreFormattedProperly(string filename) {

        ifstream jsonFile(filename);

        long start, length = 0;
        bool stringHasStarted = false;
        bool quotesIsNotOpen = true;

        while(true) {
            char character = jsonFile.get();

            if(jsonFile.eof()) {
                if(stringHasStarted) {
                    length = jsonFile.tellg() - (long long) start;

                    if(stringIsEmpty(extractFromFile(filename,start-1,length)));
                    else if(stringNotEnclosedByQuotes(filename, start-1, length)) return false;
                }
                break;
            }

            if(character == '\\' && stringHasStarted) { /* Escaping characters. */
                jsonFile >> character;
                continue;
            }
            if( character == '"' || character == ',' ||
                character == ':' || character == '[' ||
                character == ']' || character == '{' || 
                character == '}' ) { /* Structural characters */

                if(stringHasStarted) {
                    stringHasStarted = false;
                    length = jsonFile.tellg() - (long long) start;

                    if(stringIsEmpty(extractFromFile(filename,start-1,length)));
                    else if(stringNotEnclosedByQuotes(filename, start-1, length)) return false;
                    
                    length = 0;
                }
            }
            else { /* Literally anything else. */
                if(!stringHasStarted) {
                    stringHasStarted = true;
                    start = jsonFile.tellg();
                }
            }
        }

        return true;
    }

    bool arraysAreFormattedProperly(long long cursor) {
        jsonFile.seekg(cursor);

        bool arrayHasStarted = false;
        bool stringHasStarted = false;
        bool commaNotEncountered = false; // Default value for first element.

        while(true) {
            char character = jsonFile.get();
            if(jsonFile.eof()) {
                if(arrayHasStarted) return false;
                break;
            }

            if(character == '\\') character = jsonFile.get();
            else if(character == '[') {
                if(!arrayHasStarted) {
                    arrayHasStarted = true;
                }
                else if(arrayHasStarted) {
                    if(arraysAreFormattedProperly(jsonFile.tellg() - (long long) 1) == 0)
                        return false;
                }
            }
            else if(character == '"') {
                if(arrayHasStarted) {
                    if(commaNotEncountered && !stringHasStarted) return false;
                    else if(!stringHasStarted) stringHasStarted = true;
                    else if(stringHasStarted) {
                        stringHasStarted = false;
                        commaNotEncountered = true;
                    }
                }
            }
            else if(character == ',') {
                if(!commaNotEncountered) return false;
                else if(arrayHasStarted && !stringHasStarted) commaNotEncountered = false;
            }
            else if(character == ']') {
                if(arrayHasStarted) {
                    if(stringHasStarted) return false;
                    arrayHasStarted = false;
                    return true;
                }
                else if(!arrayHasStarted) return false;
            }

        }

        return true;
    }

    /* SUPPORTING FUNCTIONS */

    /* We check if the given range is preceded by quotes. */
    bool stringNotEnclosedByQuotes(string filename, int start, int length) {
        ifstream file(filename);

        file.seekg(start-1);
        if(file.get() != 34) return true;

        file.seekg(start+length);
        if(file.get() != 34) return true;

        return false;
    }

    /* Extracts the requisite string from the filename given. */
    string extractFromFile(string filename, int start, int length) {
        ifstream file(filename);
        file.seekg(start);

        string str = "";

        for(int iter=0; iter<length; iter++) {
            char character = file.get();
            if(file.eof())  break;

            str += character;
        }
        
        return str;
    }

    bool stringIsEmpty(string input) {
        int length = input.length();
        
        for(int iter=0; iter<length; iter++) {
            if(!(input[iter] == ' ' || input[iter] == '\n' || input[iter] == '\r'))
                return false;
        }

        return true;
    }

    bool isANumber(string input) {
        int length = input.length();
        for(int iter=0; iter<length; iter++) {
            if(input[iter] >= '0' && input[iter] <= '9');
            else return false;
        }
        return true;
    }

    bool isABoolean(string input) {
        if(input == "true" || input=="false") return true;
        else return false;
    }

};

int main() {
	JsonValidator json("test.json");
    return 0;
}