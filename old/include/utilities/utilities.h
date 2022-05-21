/*===================*/
/* UTILITY FUNCTIONS */
/*===================*/

/* Gets the value of the specified property from .config file. */
string getConfigProperty(string property) {

	fstream file("../config/prog.config");

	while(!file.eof()) {
		string temp;
		file >> temp;

		if(property == temp) {
			getline(file, temp);
			file.close();

			int len = temp.length();

			for(int iter=0; iter<len; iter++) {
				if(temp[iter] == '=') return temp.substr(iter+2, (len-(iter+2)));
			}

		}

	}

	file.close();
	return property; //If nothing else is returned.

}

string getKnowledgeBaseFileName() {
	return "../data/knowledgebase.chat";
}

/* Prints a menu with the name, field of chatbot. */
void menu() {

	//We retrieve the name from the config file.
	string name = getConfigProperty("name");
	
	//We retrieve the field from the config file an print it.
	cout<<endl<<name<<": Hey there! I'm "<<getConfigProperty("name")<<"!\n";
	cout<<"Enter 'help' for assistance. Ask me anything about '"<<getConfigProperty("field")<<"'!\n\n";
	cout<<name<<": For information about a host of secondary topics such as movies, TV shows, news updates and restaurants, enter 'offtopic'. To come back to the main topic, enter 'ontopic'.\n\n";
	cout<<name<<": When you're done, enter 'bye'!\n\n";

}

/* Checks if a string is a year or not. */
bool isYear(string word) {
	if(word.length() != 4) return false;
	else {
		for(int iter=0; iter<4; iter++) {
			if((word[iter] < '0') || (word[iter] > '9')) return false;
		}
		return true;
	}
}

/* Removes any HTML tags from a given text. */
string removeHTMLTagsFromText(string text) {
		
	int length = text.length();
	int flag = 0;

	string newWord = "";

	for(int iter=0; iter<length; iter++) {
		if(flag == 2) flag = 0;
		if(text[iter] == '<') flag = 1;
		if(text[iter] == '>') flag = 2;
		if(flag == 0) newWord += text[iter];
		else if(flag == 1){ }
	}

	return newWord;
}	

/* We can display strings into a number of columns or a table. */
void formatTextIntoCols(int columns, vector<string> input) {

	if(columns == -1) { /* No formatting into columns. */
		int size = input.size();
		for(int iter=0; iter<size; iter++) cout<<input[iter]<<endl;
		return;
	}

	/* We declare the largestLengths and init to 0. */
	int* largestLengths = new int[columns];
	for(int iter=0; iter<columns; iter++) largestLengths[iter] = 0;

	int colIter = 0;
	int size = input.size();

	/* We get the largest lengths for all the columns. */
	for(int iter=0; iter<size; iter++, colIter++) {
		if(input[iter].length() > largestLengths[colIter]) largestLengths[colIter] = input[iter].length();
		if(colIter == (columns-1)) colIter = -1;
	}

	/* We make every length larger by 2 for padding. */
	for(int iter=0; iter<columns; iter++) largestLengths[iter] += 2;

	/* We now do the printing. */
	colIter = 0;
	cout<<"\n";

	for(int iter=0; iter<size; iter++, colIter++) {
		
		cout<<" "<<input[iter]; /* We print the text. */
		
		int remainingSpaces = largestLengths[colIter] - input[iter].length();
		for(int jiter=0; jiter<remainingSpaces; jiter++) cout<<" "; /* We print the spaces. */

		if(colIter == (columns-1)) {
			colIter = -1;
			cout<<endl;
		}
	}

	delete[] largestLengths;
}
