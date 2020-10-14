#include<iostream>
#include<vector>
#include<utility>
using namespace std;

class JsonValidator {

	struct Neighbour {
		vector<pair<char,char>> conditions;
		int id;
	};

	struct GraphNode {
		int id;
		vector<Neighbour> neighbours;
	};

	vector<GraphNode> dfa;

	JsonValidator() {
		dfa.
	}

};

int main() {

	return 0;
}
