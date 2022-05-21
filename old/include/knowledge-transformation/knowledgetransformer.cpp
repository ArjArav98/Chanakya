#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class KnowledgeTransformer {

public:
	static void transformData() {
		string filename = "../../data/chennai.json";
		string filetype = "json";

		if(filetype == "chat") ChatTransformer::transformData();
		else if(filetype == "json") JsonTransformer::transformData();
	}

};

class ChatTransformer {

public:
	static void transformData() {
		string filename = "../../data/chennaisuperkings.chat";
		ifstream original_file(filename);

		ofstream new_file("../../data/knowledgebase.chat");
		new_file << original_file.rdbuf();

		original_file.close();
		new_file.close();
	}

};

class JsonTransformer {

public:
	static void transformData() {
		/*
		if its the first string and its not a keyword, then its a node name.
		if its the first string and its a keyword, then its okay.

		the string encountered after the first string is the result we want.
		we need to set the parent node for every iteration and a current node also.
		
		once we encounter the children keyword, we change
		*/
	}

};

int main() {

	KnowledgeTransformer::transformData();

	return 0;
}