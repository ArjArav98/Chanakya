#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<fstream>
using namespace std;

#include"plugin.h"

class Movies: Plugin {

	public:
	int getInputComparisonScore(vector<string> input) {
		int length = input.size();

		for(int iter=0; iter<length; iter++) {
			if(input[iter] == "movies" || input[iter] == "movie") return 1;
			else if(input[iter] == "films" || input[iter] == "film") return 1;
		}
		return 0;
	}

	void displayAnswer(vector<string> input, string name, bool onlyPlugins) {

		vector<int> options = parseOptionsFromInput(input);
		
		if(options[0] != 20) { /* If there is a valid answer... */
			
			saveHTMLFromURL(getRequestURL(options));
			vector<string> films = getDataFromHTML();

			/* We format the starting according to the given mode. */
			if(onlyPlugins) cout<<name<<": The top films in the ";
			else cout<<name<<": Additionally, according to Rotten Tomatoes, these are the top films in the ";

			/* We fill in the genres. */
			if(options[0] == 1) cout<<"'Adventure & Action'";
			else if(options[0] == 2) cout<<"'Animation'";
			else if(options[0] == 3) cout<<"'Art House and International'";
			else if(options[0] == 4) cout<<"'Classics'";
			else if(options[0] == 5) cout<<"'Comedy'";
			else if(options[0] == 6) cout<<"'Documentary'";
			else if(options[0] == 7) cout<<"'Drama'";
			else if(options[0] == 8) cout<<"'Horror'";
			else if(options[0] == 9) cout<<"'Kids & Family'";
			else if(options[0] == 10) cout<<"'Musicals and Performing Arts'";
			else if(options[0] == 11) cout<<"'Mystery, Suspense and Thriller'";
			else if(options[0] == 12) cout<<"'Romance'";
			else if(options[0] == 13) cout<<"'Sci-Fi & Fantasy'";
			else if(options[0] == 14) cout<<"'Special Interests'";
			else if(options[0] == 15) cout<<"'Sports & Fitness'";
			else if(options[0] == 16) cout<<"'Television Movies'";
			else if(options[0] == 17) cout<<"'Western'";
			else if(options[0] == 18) cout<<"'All'";
			else if(options[0] == 19) cout<<("year "+to_string(options[1]));

			cout<<" are shown below, along with the year of their release. Information is sourced live from Rotten Tomatoes.\n";

			int noOfFilms = films.size();
			for(int iter=0; iter<noOfFilms; iter++) {
				cout<<endl<<films[iter];
			}

			cout<<"\n";
		}

	}

	private:
	vector<int> parseOptionsFromInput(vector<string> input) {
		
		string genres[] = {"adventure","action", "animation","art","international","classic","comedy","documentary","drama","horror","kids","family","musical","dance","music","mystery","suspense","thriller","romance","science","sci","fantasy","special","sports","fitness","game","television","western","all"};
		int genreOptions[] = {1,1,2,3,3,4,5,6,7,8,9,9,10,10,10,11,11,11,12,13,13,13,14,15,15,15,16,17,18};
		int noOfGenres = 29;

		vector<int> options;

		/* We shall first try and see if a genre exists in the sentence. */
		int size = input.size();
		for(int iter=0; iter<size; iter++) {
			for(int jiter=0; jiter<noOfGenres; jiter++) {
				if(input[iter].find(genres[jiter]) != string::npos){ 
					options.push_back(genreOptions[jiter]);
					break;
				}
			}
			if (options.size() != 0) { /* If a genre exists, then return the options. */
				options.push_back(2020);
				return options;
			}
		}

		/* If no genre existed, then we search for the year. */
		for(int iter=0; iter<size; iter++) {
			if(isYear(input[iter])) {
				options.push_back(19);
				options.push_back(stoi(input[iter]));
				return options;
			}
		}

		/* If no year or genre is present, then we give a no-result. */
		options.push_back(20);
		options.push_back(2020);

		return options;
	}

	string getRequestURL(vector<int> options) {

		if(options[0] == 1) return "https://www.rottentomatoes.com/top/bestofrt/top_100_action__adventure_movies/";
		else if(options[0] == 2) return "https://www.rottentomatoes.com/top/bestofrt/top_100_animation_movies/";
		else if(options[0] == 3) return "https://www.rottentomatoes.com/top/bestofrt/top_100_art_house__international_movies/";
		else if(options[0] == 4) return "https://www.rottentomatoes.com/top/bestofrt/top_100_classics_movies/";
		else if(options[0] == 5) return "https://www.rottentomatoes.com/top/bestofrt/top_100_comedy_movies/";
		else if(options[0] == 6) return "https://www.rottentomatoes.com/top/bestofrt/top_100_documentary_movies/";
		else if(options[0] == 7) return "https://www.rottentomatoes.com/top/bestofrt/top_100_drama_movies/";
		else if(options[0] == 8) return "https://www.rottentomatoes.com/top/bestofrt/top_100_horror_movies/";
		else if(options[0] == 9) return "https://www.rottentomatoes.com/top/bestofrt/top_100_kids__family_movies/";
		else if(options[0] == 10) return "https://www.rottentomatoes.com/top/bestofrt/top_100_musical__performing_arts_movies/";
		else if(options[0] == 11) return "https://www.rottentomatoes.com/top/bestofrt/top_100_mystery__suspense_movies/";
		else if(options[0] == 12) return "https://www.rottentomatoes.com/top/bestofrt/top_100_romance_movies/";
		else if(options[0] == 13) return "https://www.rottentomatoes.com/top/bestofrt/top_100_science_fiction__fantasy_movies/";
		else if(options[0] == 14) return "https://www.rottentomatoes.com/top/bestofrt/top_100_special_interest_movies/";
		else if(options[0] == 15) return "https://www.rottentomatoes.com/top/bestofrt/top_100_sports__fitness_movies/";
		else if(options[0] == 16) return "https://www.rottentomatoes.com/top/bestofrt/top_100_television_movies/";
		else if(options[0] == 17) return "https://www.rottentomatoes.com/top/bestofrt/top_100_western_movies/";
		else if(options[0] == 18) return "https://www.rottentomatoes.com/top/bestofrt/";
		else if(options[0] == 19) return "https://www.rottentomatoes.com/top/bestofrt/?year="+to_string(options[1]);

}

	void saveHTMLFromURL(string url) {
		string cmd = "curl -s " + url + " >> movies.txt";
		system(cmd.c_str());
	}	

	vector<string> getDataFromHTML() {
		
		ifstream file("movies.txt");
		string word;
		string movie = "";

		vector<string> movies;

		while(!file.eof()) {
			file>>word;
			
			if(word == "articleLink\">") {

				file>>word;
				movie += word + " ";
				
				while(!file.eof() && word != "</td>") {	
					file>>word;
					movie += word + " ";
				}

				movies.push_back(removeHTMLTagsFromText(movie));
				movie = "";
			}
		}
		
		file.close();
		return movies;
	}

	/* UTILITIES FUNCTIONS */

	private:
	string removeHTMLTagsFromText(string text) {
		
		int length = text.length();
		int flag = 0;

		string newWord = "";

		for(int iter=0; iter<length; iter++) {
			if(flag == 2) flag = 0;
			if(text[iter] == '<') flag = 1;
			if(text[iter] == '>') flag = 2;
			if(flag == 0) newWord += text[iter];
			else if(flag == 1);
		}

		return newWord;
	}

	bool isYear(string word) {
		if(word.length() != 4) return false;
		else {
			for(int iter=0; iter<4; iter++) {
				if((word[iter] < '0') || (word[iter] > '9')) return false;
			}
			return true;
		}
	}

};

int main() {

	vector<string> input;
	input.push_back("tell");
	input.push_back("me");
	input.push_back("some");
	input.push_back("good");
	input.push_back("action");
	input.push_back("films");
	/*input.push_back("");
	input.push_back("");
	input.push_back("");
	input.push_back("");*/

	Movies movies;
	movies.displayAnswer(input,"Chanakya",true);
	
	return 0;
}
