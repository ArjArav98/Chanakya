#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<fstream>
using namespace std;

string getMoviesRequestURL(int option, string year) {

	if(option == 1) return "https://www.rottentomatoes.com/top/bestofrt/top_100_action__adventure_movies/";
	else if(option == 2) return "https://www.rottentomatoes.com/top/bestofrt/top_100_animation_movies/";
	else if(option == 3) return "https://www.rottentomatoes.com/top/bestofrt/top_100_art_house__international_movies/";
	else if(option == 4) return "https://www.rottentomatoes.com/top/bestofrt/top_100_classics_movies/";
	else if(option == 5) return "https://www.rottentomatoes.com/top/bestofrt/top_100_comedy_movies/";
	else if(option == 6) return "https://www.rottentomatoes.com/top/bestofrt/top_100_documentary_movies/";
	else if(option == 7) return "https://www.rottentomatoes.com/top/bestofrt/top_100_drama_movies/";
	else if(option == 8) return "https://www.rottentomatoes.com/top/bestofrt/top_100_horror_movies/";
	else if(option == 9) return "https://www.rottentomatoes.com/top/bestofrt/top_100_kids__family_movies/";
	else if(option == 10) return "https://www.rottentomatoes.com/top/bestofrt/top_100_musical__performing_arts_movies/";
	else if(option == 11) return "https://www.rottentomatoes.com/top/bestofrt/top_100_mystery__suspense_movies/";
	else if(option == 12) return "https://www.rottentomatoes.com/top/bestofrt/top_100_romance_movies/";
	else if(option == 13) return "https://www.rottentomatoes.com/top/bestofrt/top_100_science_fiction__fantasy_movies/";
	else if(option == 14) return "https://www.rottentomatoes.com/top/bestofrt/top_100_special_interest_movies/";
	else if(option == 15) return "https://www.rottentomatoes.com/top/bestofrt/top_100_sports__fitness_movies/";
	else if(option == 16) return "https://www.rottentomatoes.com/top/bestofrt/top_100_television_movies/";
	else if(option == 17) return "https://www.rottentomatoes.com/top/bestofrt/top_100_western_movies/";
	else if(option == 18) return "https://www.rottentomatoes.com/top/bestofrt/";
	else if(option == 19) return "https://www.rottentomatoes.com/top/bestofrt/?year="+year;

}

void saveMoviesToHTMLFromURL(string url) {
	string cmd = "curl -s " + url + " >> movies.txt";
	system(cmd.c_str());
}

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

vector<string> getMoviesFromHTML() {

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

int main() {

	int option;
	cin>>option;

	string year = "2020";

	if(option == 19) {
		cin>>year;
	}

	saveMoviesToHTMLFromURL(getMoviesRequestURL(option, year));
	vector<string> movies = getMoviesFromHTML();
	int size = movies.size();

	for(int i=0; i<size; i++) {
		cout<<movies[i]<<endl;
	}

	return 0;
}
