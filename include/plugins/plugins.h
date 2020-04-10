#include"../../plugins/movies/movies-plugin.h"

class Plugins {

	Movies movies;

	public:
	void displayAnswers(vector<string> input, string name, bool pluginsOnly) {
		/* Plugin functions go here. */
		if(movies.getInputComparisonScore(input) == 1) movies.displayAnswer(input,name,pluginsOnly);
		else {
			if(pluginsOnly) cout<<name<<": Sorry, I couldn't find anything related to that!\n";
		}
	}

	bool areOffTopic(vector<string> input) {
		int size = input.size();
		for(int iter=0; iter<size; iter++) {
			if(input[iter] == "offtopic") return true;
		}
		return false;
	}

};
