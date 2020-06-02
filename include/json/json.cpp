#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
using namespace std;

#include"dfa.h"

class JsonValidator {

	public:
	JsonValidator() {

		cout<<evaluateArray("test.json")<<endl;
		
	}

	bool evaluateArray(string filename) {

		Dfa dfa;

		/* We add the start node. */
		dfa.addNode("start","");

		/* We add the list nodes. */
		dfa.addNode("liststart","[");
		dfa.addNode("liststartspaces","\t ");
		dfa.addNode("liststartquotes","\"");
		dfa.addNode("listendquotes","\"");
		dfa.addNode("liststring","*");
		dfa.addNode("listendspaces","\t ");
		dfa.addNode("listcomma",",");
		dfa.addNode("listend","]");

		/* We link the start nodes. */
		dfa.addLink("start","liststart");

		/* We link the list nodes. */
		dfa.addLink("liststart","liststartspaces");
		dfa.addLink("liststart","liststartquotes");
		dfa.addLink("liststart","listend");

		dfa.addLink("liststartspaces","liststartspaces");
		dfa.addLink("liststartspaces","liststartquotes");
		dfa.addLink("liststartspaces","liststart");

		dfa.addLink("liststartquotes","listendquotes");
		dfa.addLink("liststartquotes","liststring");

		dfa.addLink("liststring","listendquotes");
		dfa.addLink("liststring","liststring");

		dfa.addLink("listendquotes","listendspaces");
		dfa.addLink("listendquotes","listcomma");
		dfa.addLink("listendquotes","listend");

		dfa.addLink("listendspaces","listendspaces");
		dfa.addLink("listendspaces","listcomma");
		dfa.addLink("listendspaces","listend");

		dfa.addLink("listcomma","liststartspaces");
		dfa.addLink("listcomma","liststartquotes");

		/* We set the starting and ending nodes. */
		dfa.setStartNode("start");
		dfa.addEndNode("listend");

		return dfa.matches(filename);

	}

};

int main() {
	JsonValidator json;
	return 0;
}