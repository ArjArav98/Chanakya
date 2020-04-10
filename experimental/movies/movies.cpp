#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<fstream>
using namespace std;

#include"plugins.h"

class Movies: Plugin {

	public:
	v

	private:
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

};

int main() {

	vector<int> options;
	
	int option;
	cin>>option;

	int year = 2020;

	if(option == 19) {
		cin>>year;
	}

	options.push_back(option);
	options.push_back(year);

	Movies movies;

	movies.saveHTMLFromURL(movies.getRequestURL(options));
	vector<string> results = movies.getDataFromHTML();
	int size = results.size();

	for(int i=0; i<size; i++) {
		cout<<results[i]<<endl;
	}

	return 0;
}
