/* Pre-defined libraries. */
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<regex>
using namespace std;

/* User-defined libraries. */
#include"../include/utilities.h"
#include"../include/infotrees.h"
#include"../include/stringmatcher.h"
#include"../include/treebuilder.h"
#include"../include/inputvalidate.h"
#include"../include/inputscanner.h"

int main(){

	/*-------------*/
	/* We validate the config file syntax. */
	ConfigValidate cf;

	if(!cf.configIsValid) { /* If invalid, we display an error. */
		cout<<"Error: Syntax for config file is wrong ";
		cout<<"(Line "<<cf.config_line<<").\n";
		return 0;
	}

	/*-------------*/
	/* We get the knowledge file and validate the syntax. */
	string knowledge_file = getConfigProperty("knowledge_file");
	InputValidate ip(knowledge_file);

	if(!ip.inputIsValid) { /* If not valid, we display an error. */
		cout<<"Error: Syntax for knowledge base is wrong ";
		cout<<"(Line "<<ip.file_line<<").\n";
		return 0;
	}
	
	/*-------------*/
	/* We build the tree using the knowledge file. */
	TreeBuilder tbuilder(knowledge_file);
	InformationTree infotree = tbuilder.generateTree();
	TreeNode current_node = infotree.root;

	/*-------------*/
	/* We display the menu needed for the chatbot. */
	string name = getConfigProperty("name");
	menu();

	/*-------------*/
	/* The loop for asking questions. */
	while(true) {

		//We get the sentence as a vector of strings.
		InputScanner in;
		vector<string> sentence = in.getLine("You: ");

		//We exit if 0th element of vector is exit.
		if(sentence[0] == "bye") break;

		/*---------------*/
		/* The loop for searching for the node. */
		while(true) {
			//We iterate over the children in the current node.
			int childrenLen = current_node.children.size();
			int maxScore = -1000;
			TreeNode temp_node;

			//We get the comparisonScore for each node's keywords and the sentence.
			for(int iter=0; iter<childrenLen; iter++) {
				StringMatcher sm;
				int score = sm.getComparisonScore(current_node.children[iter].keywords, sentence);
				if(score > maxScore) { 
					temp_node = current_node.children[iter];
					maxScore = score;
				}
			}

			current_node = temp_node;

			//If the node has no children, then it is leaf node.
			if(current_node.children.size() == 0) {
				cout<<name<<": "<<current_node.value()<<".\n\n";
				break;
			}

		}

		//We reset the current_node to the infotree root.
		current_node = infotree.root;

	}

	cout<<name<<": Bye!\n\n";
	return 0;
}
