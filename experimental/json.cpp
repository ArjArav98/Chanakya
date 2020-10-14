#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<array>
#include<stack>
using namespace std;

//let's implement just the brackets and the quote checking 

bool jsonValidator(string filename) {
	fstream jsonFile(filename);
	stack<char> bracketsStack;
	
	while(!jsonFile.eof()) {
		char character = jsonFile.get();

		if(character=='{' || character=='[') {
			bracketsStack.push(character);
		}
		else if(character=='}' || character==']') {	
			if(bracketsStack.top() != (character-2)) return false;
			bracketsStack.pop();
		}
		else if(character=='"') {
			if(bracketsStack.top() != '"') bracketsStack.push('"');
			else bracketsStack.pop();
		}
		else if(character==':') {
			if(bracketsStack.top() != ',')
		}
	}

	if(bracketsStack.size() != 0) return false;

	return true;
}

int main() {
	cout<<jsonValidator("test1.json");

	return 0;
}
