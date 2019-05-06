class InputValidate {

	string filename;
	string config_filename;

public:
	bool inputIsValid;
	bool configIsValid;

	InputValidate(string passed_filename) {
		filename = passed_filename;
		inputIsValid = inputLinesAreValid();

		config_filename = "../config/prog.config";
		configIsValid = configLinesAreValid();
	}

private:
	/*===========*/
	/* FUNCTIONS */
	/*===========*/

	/* Each input line is matched to 3 RegExps and is valid if even one matches. */
	/* If even one line is valid, this function returns true. */
	bool inputLinesAreValid() {

		fstream file(filename.c_str());
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
			if(file.eof()) break;
		}

		file.close();
		return true;

	}

	/* Similarly, we validate the config source file. */
	bool configLinesAreValid() {

		fstream filename(config_filename.c_str());
		string line;

		regex expression("[.]+( )+=( )+[.]+( )+\\.");
		regex expression_two("( )*");

		while(true) {
			if(!regex_match(line,expression)) {
				if(!regex_match(line,expression_two)) {
					filename.close();
					return false;
				}
			}
			getline(filename, line);
			if(filename.eof()) break;
		}

		filename.close();
		return true;

	}

};
