#include<iostream>
#include<stack>
#include<fstream>
#include<string>
using namespace std;

class JsonValidator {

	public:
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
        int start, length = 0;
        bool stringHasStarted = false;
        bool quotesIsNotOpen = true;

        while(true) {
            char character;
            jsonFile >> character;

            if(jsonFile.eof()) {
                if(stringHasStarted && stringNotEnclosedByQuotes(filename, start-1, length))
                    return false;
                break;
            }

            if(character == '\\' && stringHasStarted) { /* Escaping characters. */
                length+=2;
                jsonFile >> character;
                continue;
            }
            if( character == '"' || character == ',' ||
                character == ':' || character == '[' ||
                character == ']' || character == '{' || 
                character == '}' ) { /* Structural characters */

                if(stringHasStarted) {
                    stringHasStarted = false;
                    if(stringNotEnclosedByQuotes(filename, start-1, length)) return false;
                    length = 0;
                }
            }
            else { /* Literally anything else. */
                if(!stringHasStarted) {
                    stringHasStarted = true;
                    start = jsonFile.tellg();
                }
                length++;
            }
        }

        return true;
    }

    /* We check if the given range is preceded by quotes. */
    bool stringNotEnclosedByQuotes(string filename, int start, int length) {
        ifstream file(filename);
        char character;

        file.seekg(start-1);
        if(file.get() != 34) return true;

        for(int iter=start; iter<(start+length+1); iter++) file >> character;
        if(character != '"') return true;

        return false;
    }

    private:
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

    private:
    /* Extracts the requisite string from the filename given. */
    string extractFromFile(string filename, int start, int length) {
        ifstream file(filename);
        file.seekg(start);

        string str = "";

        for(int iter=0; iter<length; iter++) {
            char character;
            file >> character;

            if(file.eof())  break;

            str += character;
        }
        
        return str;
    }
};

int main() {
	JsonValidator json;
    cout<<json.stringsAreFormattedProperly("test.json")<<endl;

    return 0;

}