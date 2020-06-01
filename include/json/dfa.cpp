#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
using namespace std;

class DfaNode {

	string nodeName;
	string dfaPattern;
	vector<string> nodeLinks;

	public:
	DfaNode(string name, string thisPattern) {
		nodeName = name;
		dfaPattern = thisPattern;
	}

	DfaNode(){}

	bool match(char character) {
		if(dfaPattern.length() == 1 && dfaPattern[0] == '*') return true;
		else if(dfaPattern.length() == 1 && dfaPattern[0] == character) return true;
		else if(dfaPattern.length() == 2) {
			if(character >= dfaPattern[0] && character <= dfaPattern[1]) return true;
			else return false;
		}
		else if(dfaPattern.length() == 3) {
			if(character < dfaPattern[1] || character > dfaPattern[2]) return true;
			else return false;
		}
		else return false;
	}

	void addLink(string nodeName) {
		nodeLinks.push_back(nodeName);
	}

	vector<string>& links() {
		return nodeLinks;
	}

	string pattern() {
		return dfaPattern;
	}

	string name() {
		return nodeName;
	}

	bool operator==(DfaNode node) {
		if(nodeName == node.name()) return true;
		else return false;
	}

	void operator=(DfaNode node) {
		nodeName = node.name();
		nodeLinks = node.links();
		dfaPattern = node.pattern();
	}
};

class Dfa {

	map<string,DfaNode> nodeMap;
	string startNode;
	vector<string> endNodes;

	public:
	void addNode(string name, string pattern) {
		DfaNode node(name, pattern);
		nodeMap.insert( pair<string, DfaNode>(name, node));
	}

	void addLink(string source, string destination) {
		nodeMap.at(source).addLink(destination);
	}

	void setStartNode(string name) {
		startNode = name;
	}

	void addEndNode(string name) {
		endNodes.push_back(name);
	}

	bool matches(string filename) {
		ifstream file(filename);
		string currentNode = startNode;

		while(true) {
			/* We get the character. */
			char character = file.get();
			if(file.eof()) break;

			/* We see if the current node has any linkings which match. */
			vector<string> nodeLinks;

			try {
				nodeLinks = nodeMap.at(currentNode).links();
			} catch (exception e) {
				cout<<"does it come here";
				break;
			}
			
			vector<string>::iterator iter;
			bool matchFlag = false;

			for(iter = nodeLinks.begin(); iter != nodeLinks.end(); ++iter) {
				DfaNode node;
				node = nodeMap.at(*iter);
				cout<<"The name of the node is "<<node.name()<<" and character is "<<character<<endl;
				if(node.match(character)) {
					currentNode = node.name();
					cout<<"yeah this happened";
					matchFlag = true;
					break;
				}
			}

			cout<<"The character is "<<character<<" and the node is "<<currentNode<<endl;
			if(!matchFlag) break;
			cout<<"it came here"<<endl;
		}

		vector<string>::iterator iter;
		for(iter = endNodes.begin(); iter != endNodes.end(); ++iter) {
			if(currentNode == *iter) return true;
		}

		return false;
	}
};