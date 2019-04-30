class InputValidate {

	string filename;

public:
	bool isValid;

	InputValidate(string passed_filename) {
		filename= passed_filename;
		isValid = linesAreValid();
	}

private:
	/*===========*/
	/* FUNCTIONS */
	/*===========*/

	/* Each line is matched to 3 RegExps and is invalid if even one doesn't  match. */
	/* If even one line is invalid, this function returns false. */
	bool linesAreValid() {

		fstream file(filename);
		string line;

		/* This expression checks for adding nodes and assigning values. */
		regex expression("[a-zA-Z0-9-_\\.]+( )+[<=]( )+[a-zA-Z0-9-_\\.]+( )*");
		/* This expression checks for adding keywords to nodes. */
		regex expression_two("[a-zA-Z0-9-_\\.]+( )+:(( )+.+)+( )+\\.( )*");
		/* This expression checks for an empty line. */
		regex expression_three("( )*");

		/* Gets a line from file and assigns to string. */
		getline(file, line);

		while(!file.eof()) {
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
		}

		file.close();
		return true;

	}

};
