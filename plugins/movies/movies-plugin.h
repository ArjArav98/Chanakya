#include"../../include/plugins/plugin.h"

/* Movies implements the Plugin abstract class. */
class Movies: Plugin {

	private:
	string movieName;

	public:
	string getName() {
		return "Movies";
	}

	/***************/
	/* We basically check whether this plugin can give an answer or not. */
	bool canGiveAnAnswer(vector<string> input) {
		int length = input.size();

		for(int iter=0; iter<length; iter++) {
			if(input[iter] == "movies" || input[iter] == "movie") return true;
			else if(input[iter] == "films" || input[iter] == "film") return true;
		}
		return false;
	}

	/***************/
	/* Takes the data (movies vector) given and displays it in a formatted way. */
	void displayAnswer(vector<string> input, string name, bool onlyPlugins) {

		/* We get the parameter options from the input. */
		vector<int> options = parseOptionsFromInput(input);
	
		/* We firct check if an answer is possible. */
		if(!canGiveAnAnswer(input) && options[1]==0 && options[2]==0)
			cout<<name<<": Sorry, I'm not able to answer that. Try to give more details.\n\n";

		/* If yes, then we download the data and all that. */
		saveHTMLFromURL(getRequestURL(options));
		vector<string> results = getDataFromHTML();

		/* We check if it is a question about a movie. */
		if(options[2] > 0) {
			if(options[2] == 1) {
				cout<<name<<": The details of the movie you asked for are as follows:-\n\n";
				formatTextIntoCols(-1,results); /* No formatting here. */				
			}
			else if(options[2] == 2) cout<<name<<" If you were trying to search for details about a particular movie, make sure you enclose the name of the movie in doublequotes (\").\n\n";
			return;
		}	

		/* We format the starting according to the given mode. */
		if(onlyPlugins) cout<<name<<": The top films in the ";
		else cout<<"\n"<<name<<": Additionally, according to Rotten Tomatoes, these are the top ";

		/* We fill in the genres. */
		switch(options[0]) {
			case 1: cout<<"'Adventure & Action'"; break;
			case 2: cout<<"'Animation'"; break;
			case 3: cout<<"'Comedy'"; break;
			case 4: cout<<"'Drama'"; break;
			case 5: cout<<"'Horror'"; break;
			case 6: cout<<"'Kids & Family'"; break;
			case 7: cout<<"'Music & Musicals'"; break;
			case 8: cout<<"'Mystery'"; break;
			case 9: cout<<"'Suspense & Thriller'"; break;
			case 10: cout<<"'Romance'"; break;
			case 11: cout<<"'Sci-Fi'"; break;
			case 12: cout<<"'Sports'"; break;
			case 13: cout<<"'War'"; break;
			case 16: cout<<"'All'"; break;
			case 14: cout<<"'Oscar-Winning - Best Feature Film' genre. These films would have won only the year later, as the Academy Awards mostly feature films made the previous year. Movies from this "; break;
			case 15: cout<<"'Kollywood/Tamil'"; break;
			case 17: cout<<"'BAFTA-Winning - Best Feature Film'"; break;
			case 18: cout<<"'Disney Original Movies'"; break;
			case 19: cout<<"'Malayalam'"; break;
		}
		
		/* Further printing... */
		if(options[1] != 0) { /* If a year is requested, then print that. */
			cout<<" genre from the year "+to_string(options[1])+" are shown below. ";
			cout<<" Information is sourced live from criticker.com!\n";
			formatTextIntoCols(2,results); /* We format the movie titles into two columns. */
		}
		else if(options[0] != 20) { /* Every genre, other than news... */
			cout<<" genre are shown below, along with the year of their release. ";
			cout<<" Information is sourced live from criticker.com!\n";
			formatTextIntoCols(2,results); /* We format the movie titles into two columns. */
		}
		else if(options[0] == 20) { /* The news genre... */
			cout<<" updates and news from the world of movies and entertainment. ";
			cout<<" Information is sources live from hollywoodreporter.com!\n\n";
			formatTextIntoCols(-1,results); /* No formatting here. */
		}
	
		cout<<endl<<"Feel free to ask me more questions about movie recommendations ";
		cout<<"(you can even specify the genre and year), individual movie details and even movie news!\n\n";
	}

	private:
	
	/***************/
	/* Given the vector input, we parse options (parameters) for the URL requests. */
	vector<int> parseOptionsFromInput(vector<string> input) {

		/*------*/
		/* The first option is genre (awards are genres too). Second option is year. */
		array<string,38> genres = {"adventure","action", "animation","comedy","drama","horror","kids","family","musical","music","mystery","suspense","thriller","romance","romantic","science","sci","fantasy","sports","fitness","game","war","oscars","oscar","award","awards","tamil","kollywood","bafta","disney","plus","malayalam","mallu","mollywood","news","updates","update","all"};
		array<int,38> genreOptions = {1,1,2,3,4,5,6,6,7,7,8,9,9,10,10,11,11,11,12,12,12,13,14,14,14,14,15,15,17,18,18,19,19,19,20,20,20,16};
		int noOfGenres = genreOptions.size();

		vector<int> options(3,0); /* 3 elements with value 0. */

		/* We shall first try and see if a genre exists in the sentence. */
		int size = input.size();
		for(int iter=0; iter<size; iter++) {
			for(int jiter=0; jiter<noOfGenres; jiter++) {
				if(input[iter].find(genres[jiter]) != string::npos){ 
					options[0] = genreOptions[jiter];
					break;
				}
			}
			if (options[0] != 0) break; /* If a genre exists, then break. */
		}
		if(options[0] == 0) options[0] = 16; /* If no genres, then we suggest 'all'. */

		/*-----*/
		/* We now search to see if a year exists. */
		for(int iter=0; iter<size; iter++) {
			if(isYear(input[iter])) {
				options[1] = stoi(input[iter]);
			}
		}
	
		/*-----*/
		/* We now search to see if a movie name exists in between doublequotes. */
		int flag = 0;

		// We search for doublequotes.
		for(int iter=0; iter<size; iter++) {
			// We iterate over the string characters themselves.
			for(int jiter=0; jiter<input[iter].length(); jiter++) {
				if(input[iter][jiter]=='"' && flag==0) flag = 1;
				else if(input[iter][jiter]=='"' && flag==1) {
					options[2] = 1;
					flag = 0;
					break;
				}
				else if(flag == 1) movieName.push_back(input[iter][jiter]);	
			}
			if(flag == 1) movieName.push_back('+');
		}
		
		// If no doublequotes and if user is asking about a movie maybe, we record this.
		if(options[2] == 0) {
			for(int iter=0; iter<size; iter++) {
				if(input[iter]=="plot" || input[iter]=="story" || input[iter]=="details") options[2]=2;
				else if(input[iter]=="detail" || input[iter]=="details" || input[iter]=="info") options[2]=2;
				else if(input[iter]=="information") options[2]=2;
			}
		}

		return options;
	}

	/***************/
	/* Using the options (parameters) given, we formulate the request URL. */
	string getRequestURL(vector<int> options) {

		string baseURL = "'https://www.criticker.com/films/?filter=";

		if(options[2] == 1) return "'https://www.criticker.com/?search="+movieName+"&type=films'";

		switch(options[0]) {
			case 1: baseURL.append("gy12x13zi1zf1900zt2030zor'"); break; //action
			case 2: baseURL.append("gy18zi1zf1900zt2030zor'"); break; //animated
			case 3: baseURL.append("gy2zi1zf1900zt2030zor'"); break; //comedy
			case 4: baseURL.append("gy3zi1zf1900zt2030zor'"); break; //drama
			case 5: baseURL.append("gy15zi1zf1900zt2030zor'"); break; //horror
			case 6: baseURL.append("gy10zi1zf1900zt2030zor'"); break; //kids
			case 7: baseURL.append("gy41x9zi1zf1900zt2030zor'"); break; //music
			case 8: baseURL.append("gy17zi1zf1900zt2030zor'"); break; //mystery
			case 9: baseURL.append("gy6zi1zf1900zt2030zor'"); break; //thriller/suspense
			case 10: baseURL.append("gy1zi1zf1900zt2030zor'"); break; //romance
			case 11: baseURL.append("gy5zi1zf1900zt2030zor'"); break; //scifi
			case 12: baseURL.append("gy34zi1zf1900zt2030zor'"); break; //sport
			case 13: baseURL.append("gy14zi1zf1900zt2030zor'"); break; //war
			case 14: baseURL.append("f1900zt2030ze3139zod'"); break; //oscar
			case 15: baseURL.append("f1900zt2030ze3075zor'"); break; //tamil
			case 16: baseURL.append("i1zf1900zt2030zor'"); break; //all
			case 17: baseURL.append("f1900zt2030ze10797zod'"); break; //bafta
			case 18: baseURL.append("f1900zt2030ze42853zor'"); break; //disney/disney+
			case 19: baseURL.append("f1900zt2030ze2908zor'"); break; //malayalam
			case 20: baseURL = "'https://www.hollywoodreporter.com/topic/movies'"; break; //news
		}

		/* For year, we replace year in URL with our own. */
		if(options[1] != 0 && options[0] == 14) { /* For Oscars, +1 year as award is presented next year only. */
			baseURL.replace(baseURL.find("1900"),4,to_string(options[1]-1));
			baseURL.replace(baseURL.find("2030"),4,to_string(options[1]-1));
		}
		else if(options[1] != 0 && options[0] != 20) { /* No year replace for news results. */
			baseURL.replace(baseURL.find("1900"),4,to_string(options[1]));
			baseURL.replace(baseURL.find("2030"),4,to_string(options[1]));
		}

		return baseURL;
	}

	/***************/
	/* We save the request response HTML to a file. */
	void saveHTMLFromURL(string url) {
		string cmd = "curl -s " + url + " > data.txt";
		system(cmd.c_str()); /* Downloading file from URL. */

		cmd = " cat data.txt | sed 's/&quot;/\"/g' | sed \"s/&#039;/'/g\" > tempdata.txt";
		system(cmd.c_str()); /* Replacing &quot; with ". */

		cmd = "cat tempdata.txt > data.txt; rm tempdata.txt";
		system(cmd.c_str()); /* Replacing &#039; with '. */
	}	

	/****************/
	/* We parse the response HTML in the file to get our data (movie vectors). */
	vector<string> getDataFromHTML() {
		
		ifstream file("data.txt");
		string word;
		string movie = "";
		movieName = "";

		vector<string> movies;

		while(!file.eof()) {
			file>>word;
		
			/* Web-Scraping Movies from Criticker.com */
			if(word == "class='fl_titlelist_link'") {

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
			/* Web-Scraping News from hollywoodreporter.com. */
			else if(word == "class=\"topic-card__headline") {
				
				int flag = 0;
				char character;

				while(true) {
					file.get(character);
					if(character == '<') break;
					if(flag == 1) movie.push_back(character);
					if(character == '>') {
						flag = 1;
						movie.append("--> ");
					}
				}

				movies.push_back(movie);
				movie = "";
			}
			/* Web-Scraping movie name from criticker.com search. */
			else if(word == "class='titlerow_name'><a") {
				int flag = 0;
				char character;

				while(true) {
					file.get(character);
					if(character == '<') break;
					if(flag == 1) movie.push_back(character);
					if(character == '>') flag = 1;	
				}

				movie.push_back('\n');
				movie.append("Summary: ");
			}
			/* Web-Scraping movie summary from criticker.com search. */
			else if(word == "class='titlerow_summary'") {
				int flag = 0;
				char character;

				while(true) {
					file.get(character);
					if(character == '<') break;
					if(flag == 1) movie.push_back(character);
					if(character == '>') flag = 1;	
				}

				movies.push_back(movie);
				movie="";
				break;
			}
		}

		file.close();
		return movies;
	}

};
