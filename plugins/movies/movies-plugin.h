#include"../../include/plugins/plugin.h"

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
			vector<string> unfilteredFilms = getDataFromHTML();

			/* We will filter according to year, if option is present. */
			vector<string> films;
			if(options[1] != 0) { /* if a year is present. */
				int noOfFilms = unfilteredFilms.size();
				for(int iter=0; iter<noOfFilms; iter++) {
					/* if a year is found....*/
					if(unfilteredFilms[iter].find(to_string(options[1])) != string::npos) {
						films.push_back(unfilteredFilms[iter]);
					}
				}
			}
			else films = unfilteredFilms;

			/* We format the starting according to the given mode. */
			if(onlyPlugins) cout<<name<<": The top films in the ";
			else cout<<"\n"<<name<<": Additionally, according to Rotten Tomatoes, these are the top films in the ";

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
			else if(options[0] == 21) cout<<"'Best Picture - Oscars'";
			else if(ootions[0] == 22) cout<<"'Tamil'";
			else;

			/* If year is present, we fill in the year. */
			if(options[1] != 0) cout<<" genre from the year "+to_string(options[1])+" are shown below. ";
			else cout<<" genre are shown below, along with the year of their release. ";

			cout<<"Information is sourced live from Rotten Tomatoes.\n";

			formatTextIntoCols(2,films);
			cout<<"\n";
		}

	}

	private:
	vector<int> parseOptionsFromInput(vector<string> input) {

		/* The first option is genre (awards are genres too). Second option is year. */

		string genres[] = {"adventure","action", "animation","art","international","classic","comedy","documentary","drama","horror","kids","family","musical","dance","music","mystery","suspense","thriller","romance","science","sci","fantasy","special","sports","fitness","game","television","western","all","oscars","oscar","award","awards","tamil","kollywood"};
		int genreOptions[] = {1,1,2,3,3,4,5,6,7,8,9,9,10,10,10,11,11,11,12,13,13,13,14,15,15,15,16,17,18,21,21,21,21,22,22};
		int noOfGenres = 35;

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
			if (options.size() != 0) break; /* If a genre exists, then break. */
		}

		if(options.size() == 0) options.push_back(18); /* If no genres, then we suggest 'all'. */

		/* If no genre existed, then we search for the year. */
		for(int iter=0; iter<size; iter++) {
			if(isYear(input[iter])) {
				options.push_back(stoi(input[iter]));
				return options;
			}
		}

		if(options.size() == 1) options.push_back(0); /* If no year, then we suggest all. */
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
		else if(options[0] == 21) return "https://www.criticker.com/films/?filter=e3139zod";
		else if(options[0] == 22) return "'https://www.criticker.com/films/?filter=e3075&p=1' 'https://www.criticker.com/films/?filter=e3075&p=2' 'https://www.criticker.com/films/?filter=e3075&p=3' 'https://www.criticker.com/films/?filter=e3075&p=4'";

		return "";
	}

	void saveHTMLFromURL(string url) {
		string cmd = "curl -s " + url + " > data.txt";
		system(cmd.c_str());
	}	

	vector<string> getDataFromHTML() {
		
		ifstream file("data.txt");
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
			else if(word == "class='fl_titlelist_link'") {

				int flag = 0;
				char character;

				while(true) {
					file.get(character);
					if(character == '<') break;
					if(flag == 1) movie.push_back(character);
					if(character == '>') flag = 1;	
				}

				movies.push_back(movie);
				movie = "";
			
			}

		}
		
		file.close();
		return movies;
	}

};
