#include<iostream>
#include<stack>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

class JsonValidator {

    ifstream jsonFile;
    string filenamestring;

    int line;

	public:
    JsonValidator(string filename) {
    }

    private:

	/* Checks if the [ and { have matching brackets. */
	bool bracketsAreMatched() {

		stack<char> bracketStack;
        bool quotesNotOpen = true;

		while(true) {
			char character = jsonFile.get();

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
    bool stringsAreFormattedProperly() {

        long start, length = 0;
        bool stringHasStarted = false;
        bool quotesIsNotOpen = true;

        while(true) {
            char character = jsonFile.get();

            if(jsonFile.eof()) {
                if(stringHasStarted) {
                    length = jsonFile.tellg() - (long long) start;

                    if(stringIsEmpty(extractFromFile(start-1,length)));
                    else if(stringNotEnclosedByQuotes(start-1, length)) return false;
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

                    if(stringIsEmpty(extractFromFile(start-1,length)));
                    else if(stringNotEnclosedByQuotes(start-1, length)) return false;
                    
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

            if(character == '\\') {
                if(stringHasStarted) character = jsonFile.get();
                else return false;
            }
            else if(character == '[') {
                if(!arrayHasStarted) {
                    arrayHasStarted = true;
                }
                else if(arrayHasStarted) {
                    if(arraysAreFormattedProperly(jsonFile.tellg() - (long long) 1)) 
                        commaNotEncountered = true;
                    else return false;
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
            else if(character == '{'){
                return mapsAreFormattedProperly(jsonFile.tellg() - (long long) 1);
            }
            else {
                if(!stringHasStarted && (character == ' ' || character == '\n' || character == '\r'));
                else if(stringHasStarted);
                else return false;
            }

        }

        return true;
    }

    bool mapsAreFormattedProperly(long long cursor) {
        jsonFile.seekg(cursor);

        bool mapHasStarted = false;
        bool stringHasStarted = false;
        bool commaEncountered = true;
        bool colonEncountered = false;
        int stringNum = 0;

        while(true) {
            char character = jsonFile.get();
            if(jsonFile.eof()) break;
            
            if(character == '\\') {
                if(stringHasStarted) character = jsonFile.get();
                else return false;
            }
            else if(character == '{') {
                if(!mapHasStarted) mapHasStarted = true;
                else {
                    if(stringNum == 0) return false;

                    bool dummy = true;
                    if(mapsAreFormattedProperly(jsonFile.tellg() - (long long) 1)) stringNum = 2;
                    else return false;

                }
            }
            else if(character == '"') {
                if(!stringHasStarted) {
                    stringHasStarted = true;
                    if(stringNum == 0 && commaEncountered) commaEncountered = false;
                    else if(stringNum == 1 && !colonEncountered) return false;
                    else if(stringNum >= 2) return false;
                }
                else {
                    stringHasStarted = false;
                    stringNum++;
                }
            }
            else if(character == ':') {
                if(!stringHasStarted && stringNum == 1) {
                    if(!colonEncountered) colonEncountered = true;
                    else return false;
                }
                else return false;
            }
            else if(character == ',') {
                if(!stringHasStarted && stringNum == 2) {
                    commaEncountered = true;
                    stringNum = 0;
                    colonEncountered = false;
                }
                else return false;
            }
            else if(character == '}') {
                if(mapHasStarted && stringNum == 2 && !commaEncountered) break;
                else return false;
            }
            else if(character == '[') {
                return arraysAreFormattedProperly(jsonFile.tellg() - (long long) 1);
            }
            else {
                if(!stringHasStarted && (character == ' ' || character == '\n' || character == '\r'));
                else if(stringHasStarted);
                else return false;
            }
        }

        return true;
    }

    /* SUPPORTING FUNCTIONS */

    /* We check if the given range is preceded by quotes. */
    bool stringNotEnclosedByQuotes(int start, int length) {
        ifstream file(filenamestring);

        file.seekg(start-1);
        if(file.get() != 34) return true;

        file.seekg(start+length);
        if(file.get() != 34) return true;

        return false;
    }

    /* Extracts the requisite string from the filename given. */
    string extractFromFile(int start, int length) {
        ifstream file(filenamestring);
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

};

int main() {
	JsonValidator json("test.json");
    return 0;
}