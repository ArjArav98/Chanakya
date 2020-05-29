#include<iostream>
#include<stack>
#include<fstream>
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
};

int main() {
	JsonValidator json;
	cout<<json.bracketsAreMatched("test.json");
	return 0;
}