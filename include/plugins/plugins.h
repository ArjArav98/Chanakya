#include"../../plugins/movies/movies-plugin.h"

class Plugins {

	Movies movies;

	public:
	bool areMainTopic;
	int previousTopic;

	Plugins() { areMainTopic = false; previousTopic = -1; }

	void displayAnswers(vector<string> input, string name, bool pluginsOnly) {
		/* Plugin functions go here. */
		if(movies.canGiveAnAnswer(input) == 1) {
			movies.displayAnswer(input,name,pluginsOnly);
			previousTopic = 1;
		}
		else {
			if(previousTopic == 1) movies.displayAnswer(input,name,pluginsOnly);
			else {
				if(pluginsOnly) cout<<name<<": Sorry, I couldn't find anything related to that!\n";
			}
		}
	}

	bool hasBeenMadeActive(vector<string> input) {
		int size = input.size();
		for(int iter=0; iter<size; iter++) {
			if(input[iter] == "offtopic") return true;
		}
		return false;
	}

	bool hasBeenMadeInactive(vector<string> input) {
		int size = input.size();
		for(int iter=0; iter<size; iter++) {
			if(input[iter] == "ontopic") return true;
		}
		return false;
	}

};
