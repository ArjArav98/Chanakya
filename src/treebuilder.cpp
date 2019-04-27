#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

#include"infotrees.h"

class TreeBuilder {
	InformationTree infotree;
public:
	void generateTree(string filename) {

		/* We open the file in a filestream. */
		fstream file(filename);
		
		/* Loop until file ends. */
		while(!file.eof()) {

			/* First string on line is node to be manipulated. */
			string current_node;
			file >> current_node;

			/* If the next string is '<' (adding branch). */
			string op;
			file >> op;

			if(op == "<") {
				string parent;
				file >> parent;
				infotree.add(parent,current_node);
			}
			else if(op == "=") {
				string value;
				file >> value;
				infotree.setValue(current_node,value);
			}

		}

	}

};

int main() {

	TreeBuilder tb;
	tb.generateTree("hello.txt");

	return 0;
}
