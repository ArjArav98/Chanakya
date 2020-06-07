/* Class which validates a .chat file. */
class ChatValidator {

	int file_line;
	string filenamestring;

	public:
	ChatValidator(string filename) {
		filenamestring = filename;
		file_line = 1;
	}

	/*===========*/
	/* FUNCTIONS */
	/*===========*/

	/* Each input line is matched to 3 RegExps and is valid if even one matches. */
	/* If even one line is valid, this function returns true. */
	bool knowledgeBaseValid() {

		fstream file(filenamestring.c_str());
		string line;

		/* This expression checks for adding nodes and assigning values. */
		regex expression("[a-zA-Z0-9-_\\.]+( )+<( )+[a-zA-Z0-9-_\\.]+( )*");
		/* This expression checks for adding keywords to nodes. */
		regex expression_two("[a-zA-Z0-9-_\\.]+( )+[:=](( )+.+)+( )+\\.( )*");
		/* This expression checks for an empty line. */
		regex expression_three("( )*");

		/* Gets a line from file and assigns to string. */
		getline(file, line);

		while(true) {
			/* We check each of the three RegExps. */
			if(!regex_match(line,expression)) {
				if(!regex_match(line,expression_two)) {
					if(!regex_match(line,expression_three)) {
						file.close();
						return false;
					}
				}
			}
			getline(file, line);
			file_line++;
			if(file.eof()) break;
		}

		file.close();
		return true;

	}

	int getLine() {
		return file_line;
	}
};

/* Class which validates a .json file.  */
class JsonValidator {

	ifstream jsonFile;
	string filenamestring;

	int file_line;

	public:
	JsonValidator(string filename) {
		file_line = 1;
		filenamestring = filename;
	}

	bool knowledgeBaseValid() {
		jsonFile.open(filenamestring);

		if( bracketsAreMatched() == false ) {
			jsonFile.close();
			return false;
		}
		file_line = 1;
		jsonFile.seekg(0);

		if( stringsAreFormattedProperly() == false ) {
			jsonFile.close();
			return false;
		}
		file_line = 1;
		jsonFile.seekg(0);

		if( mapsAreFormattedProperly(0) == false ) {
			jsonFile.close();
			return false;
		}

		jsonFile.close();
		return true;
	}

	int getLine() {
		return file_line;
	}

	private:
	/*************/
	/* FUNCTIONS */
	/*************/

	/* Validates whether all brackets in file are matching. */
	bool bracketsAreMatched() {

		stack<char> bracketStack;
		bool quotesNotOpen = true;

		while(true) {
			char character = jsonFile.get();

			if(jsonFile.eof() ) break;
			if( character == '"' ) quotesNotOpen = !quotesNotOpen;

			{
				if( (character == '{' || character == '[') && quotesNotOpen) {
					bracketStack.push(character);
				}
				else if ( (character == '}' || character == ']') && quotesNotOpen ) {
					if(bracketStack.size() == 0) return false;

					char topSymbol = bracketStack.top();
					bracketStack.pop();

					if(character == '}' && topSymbol == '{');
					else if(character == ']' && topSymbol == '[');
					else return false;
				}
				else if( character == '\n' || character == '\r' ) file_line++;
			}
		}

		if(bracketStack.size() != 0) return false;

		return true;
	}

	/* Validates whether each string is formatted properly. */
	bool stringsAreFormattedProperly() {

		long start, length = 0;
		bool stringHasStarted = false;
		bool quotesIsNotOpen = true;

		while(true) {
			char character = jsonFile.get();

			if(jsonFile.eof()) {
				if(stringHasStarted) {
					length = jsonFile.tellg() - (long long) start;

					if(stringIsEmpty(extractFromFile(start-1,length)));
					else if(stringNotEnclosedByQuotes(start-1, length)) return false;
				}
				break;
			}
			else if( character == '\\' && stringHasStarted ) { /* Escaping characters. */
				character = jsonFile.get();
				continue;
			}
			else if( character == '"' || character == ',' ||
				character == ':' || character == '[' ||
				character == ']' || character == '{' || 
				character == '}' ) { /* Structural characters */

				if(stringHasStarted) {
					stringHasStarted = false;
					length = jsonFile.tellg() - (long long) start;

					if(stringIsEmpty(extractFromFile(start-1,length)));
					else if(stringNotEnclosedByQuotes(start-1, length)) return false;
					
					length = 0;
				}
			}
			else if( character == '\n' || character == '\r' ) file_line++;
			else { /* Literally anything else. */
				if(!stringHasStarted) {
					stringHasStarted = true;
					start = jsonFile.tellg();
				}
			}
		}

		return true;
	}

	/* Validates whether every array in the file is formatted properly. */
	bool arraysAreFormattedProperly(long long cursor) {
		jsonFile.seekg(cursor);

		bool arrayHasStarted = false;
		bool stringHasStarted = false;
		bool commaNotEncountered = false; // Default value for first element.

		while(true) {
			char character = jsonFile.get();
			if(jsonFile.eof()) {
				if(arrayHasStarted) return false;
				break;
			}

			if( character == '\\' ) {
				if(stringHasStarted) character = jsonFile.get();
				else return false;
			}
			else if( character == '[' ) {
				if(!arrayHasStarted) {
					arrayHasStarted = true;
				}
				else if( arrayHasStarted ) {
					if( arraysAreFormattedProperly(jsonFile.tellg() - (long long) 1) ) 
						commaNotEncountered = true;
					else return false;
				}
			}
			else if( character == '"' ) {
				if( arrayHasStarted ) {
					if( commaNotEncountered && !stringHasStarted ) return false;
					else if( !stringHasStarted ) stringHasStarted = true;
					else if( stringHasStarted ) {
						stringHasStarted = false;
						commaNotEncountered = true;
					}
				}
			} 
			else if( character == ',' ) {
				if( !commaNotEncountered ) return false;
				else if( arrayHasStarted && !stringHasStarted ) commaNotEncountered = false;
			}
			else if( character == ']' ) {
				if( arrayHasStarted ) {
					if( stringHasStarted ) return false;
					arrayHasStarted = false;
					return true;
				}
				else return false;
			}
			else if( character == '{' ){
				return mapsAreFormattedProperly(jsonFile.tellg() - (long long) 1);
			}
			else if(character == '\n' || character == '\r') file_line++;
			else {
				if( character == ' ' );
				else return false;
			}

		}

		return true;
	}

	/* Validates whether every map in the array is formatted properly. */
	bool mapsAreFormattedProperly(long long cursor) {
		jsonFile.seekg(cursor);

		bool mapHasStarted = false;
		bool stringHasStarted = false;
		bool commaEncountered = true;
		bool colonEncountered = false;
		int stringNum = 0;

		while(true) {
			char character = jsonFile.get();
			if(jsonFile.eof()) break;
			
			if( character == '\\' ) {
				if(stringHasStarted) character = jsonFile.get();
				else return false;
			}
			else if( character == '{' ) {
				if( !mapHasStarted ) mapHasStarted = true;
				else {
					if( stringNum == 0 ) return false;

					bool dummy = true;
					if( mapsAreFormattedProperly(jsonFile.tellg() - (long long) 1) ) stringNum = 2;
					else return false;

				}
			}
			else if(character == '"') {
				if( !stringHasStarted ) {
					stringHasStarted = true;
					if( stringNum == 0 && commaEncountered ) commaEncountered = false;
					else if( stringNum == 1 && !colonEncountered ) return false;
					else if( stringNum >= 2 ) return false;
				}
				else {
					stringHasStarted = false;
					stringNum++;
				}
			}
			else if( character == ':' ) {
				if( !stringHasStarted && stringNum == 1 ) {
					if( !colonEncountered ) colonEncountered = true;
					else return false;
				}
				else return false;
			}
			else if( character == ',' ) {
				if( !stringHasStarted && stringNum == 2 ) {
					commaEncountered = true;
					stringNum = 0;
					colonEncountered = false;
				}
				else return false;
			}
			else if( character == '}' ) {
				if( mapHasStarted && stringNum == 2 && !commaEncountered ) break;
				else return false;
			}
			else if( character == '[' ) {
				return arraysAreFormattedProperly(jsonFile.tellg() - (long long) 1);
			}
			else if( character == '\n' || character == '\r') file_line++;
			else {
				if( character == ' ' );
				else return false;
			}
		}

		return true;
	}

	/************************/
	/* SUPPORTING FUNCTIONS */
	/************************/

	/* We check if the given range is preceded by quotes. */
	bool stringNotEnclosedByQuotes(int start, int length) {
		ifstream file(filenamestring);

		file.seekg(start-1);
		if(file.get() != 34) return true;

		file.seekg(start+length);
		if(file.get() != 34) return true;

		return false;
	}

	/* Extracts the requisite string from the filename given. */
	string extractFromFile(int start, int length) {
		ifstream file(filenamestring);
		file.seekg(start);

		string str = "";

		for(int iter=0; iter<length; iter++) {
			char character = file.get();
			if(file.eof())  break;

			str += character;
		}
		
		return str;
	}

	/* Checks whether a string is empty (contains only space characters). */
	bool stringIsEmpty(string input) {
		int length = input.length();
		
		for(int iter=0; iter<length; iter++) {
			if(!(input[iter] == ' ' || input[iter] == '\n' || input[iter] == '\r'))
				return false;
		}

		return true;
	}

};

/* Class which validates knowledge file syntax. */
class KnowledgeBaseValidator {

public:

	static int error_line;
	static string error_msg;

	static bool successfullyValidated() {
		
		string filename = getConfigProperty("knowledge_file");
		string filetype = getConfigProperty("knowledge_type");
		
		if(filetype == "chat") {
			ChatValidator chatfile(filename);
			bool valid = chatfile.knowledgeBaseValid();
			error_line = chatfile.getLine();

			return valid;
		}
		if(filetype == "json") {
			JsonValidator jsonfile(filename);
			bool valid = jsonfile.knowledgeBaseValid();
			error_line = jsonfile.getLine();

			return valid;
		}
		else return false;

	}

	static int errorLine() { return error_line; }
	static string errorMsg() { return error_msg; }

};

int KnowledgeBaseValidator::error_line = 1;
string KnowledgeBaseValidator::error_msg = "";