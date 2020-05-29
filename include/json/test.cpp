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

    // bool stringsAreInQuotes(string filename) {

    //     ifstream jsonFile(filename);
    //     char currentChar, previousChar;

    //     while(true) {

    //     }

    // }

    public:
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
    cout<<json.extractFromFile("test.json", 120, 20);

    return 0;

}