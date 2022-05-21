/* Pre-defined libraries. */
#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<array>
#include<fstream>
#include<regex>
using namespace std;

/* User-defined libraries. */
#include"../include/utilities/utilities.h"
#include"../include/knowledge-tree/infotrees.h"
#include"../include/knowledge-tree/stringmatcher.h"
#include"../include/knowledge-tree/treebuilder.h"
#include"../include/file-validation/knowledge-base/validate.h"
#include"../include/file-validation/config/validate.h"
#include"../include/user-input/inputscanner.h"
#include"../include/plugins/plugins.h"

int main(){

	/*-------------*/
	/* We validate the config file syntax. */
	if(!ConfigValidator::successfullyValidated()) { /* If invalid, we display an error. */
		cout	<<"Error: "<<ConfigValidator::errorMsg()<<" "
			<<"(Line "<<ConfigValidator::errorLine()<<").\n";
		return -1;
	}

	/*-------------*/
	/* We get the knowledge file and validate the syntax. */
	if(!KnowledgeBaseValidator::successfullyValidated()) { /* If not valid, we display an error. */
		cout	<<"Error: "<<KnowledgeBaseValidator::errorMsg()<<" "
			<<"(Line "<<KnowledgeBaseValidator::errorLine()<<").\n";
		return -1;
	}
	
	/*-------------*/
	/* We build the tree using the knowledge file. */
	InformationTree infotree = TreeBuilder::generateTree();
	TreeNode current_node = infotree.root;

	/*-------------*/
	/* We display the menu needed for the chatbot. */
	string name = getConfigProperty("name");
	menu();

	/***************/
	/* We declare the plugins modules. */
	Plugins plugins;

	/*-------------*/
	/* The loop for asking questions. */
	while(true) {

		/* We get the sentence as a vector of strings. */
		InputScanner in;
		cout<<"......\n\n";
		vector<string> sentence = in.getLine("You: ");

		/* If nothing is entered, we 'continue'. */
		/* If 'bye' is entered, we exit the loop. */
		if(sentence.size() == 0) continue;
		else if(sentence[0] == "bye") break;

		/*---------------*/
		/* The loop for searching for the node. */
		while(true) {

			/* We check if there is any plugin activity or not. */
			if(plugins.hasBeenMadeActive(sentence)) {
				plugins.areMainTopic = true;
				cout	<<name<<": You have enabled the secondary topics.\n"<<name<<": Ask me anything "
					<<"about movies, TV shows, the news and restaurants (and, hopefully, I can answer).\n\n";
				break;
			}
			else if(plugins.hasBeenMadeInactive(sentence)) {
				plugins.areMainTopic = false;
				cout	<<name<<": I've now updated my brain to the main topic, "
					<<"'"<<getConfigProperty("field")<<"', again. Let's do this!\n\n";
				break;
			}
			else if(plugins.areMainTopic) {
				plugins.displayAnswers(sentence,name,true);
				cout<<endl;
				break;
			}

			/* We iterate over the children in the current node. */
			int childrenLen = current_node.children.size();
			int maxScore = -1000;
			TreeNode temp_node;

			/* We get the comparisonScore for each node's keywords and the sentence. */
			for(int iter=0; iter<childrenLen; iter++) {
				int score = StringMatcher::getComparisonScore(current_node.children[iter].keywords(), sentence);
				if(score > maxScore) { 
					temp_node = current_node.children[iter];
					maxScore = score;
				}
			}

			current_node = temp_node;

			/* If the node has no children, then it is leaf node. */
			if(current_node.children.size() == 0) {
				cout<<name<<": "<<current_node.value()<<".\n"; /* Print the lead node value. */
				plugins.displayAnswers(sentence,name,false); /* Print plugins answer, if any. */
				cout<<endl;
				break;
			}

		}

		/* We reset the current_node to the infotree root. */
		current_node = infotree.root;

	}

	cout<<name<<": Okay, bye!\n\n";
	return 0;
}
