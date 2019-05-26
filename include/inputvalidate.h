/* Class which validates knowledge and config file syntax. */
class InputValidate {

	string filename;

public:
	bool inputIsValid;
	int file_line;

	InputValidate(string passed_filename) {
		file_line = 1;

		filename = passed_filename;
		inputIsValid = inputLinesAreValid();
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
			file_line++;
			if(file.eof()) break;
		}

		file.close();
		return true;

	}

};

class ConfigValidate {

public:
	bool configIsValid;
	int config_line;

	ConfigValidate() {
		config_line = 1;
		configIsValid = configLinesAreValid();
	}

private:
	/*===========*/
	/* FUNCTIONS */
	/*===========*/

	/* For logic explanation, refer inputLinesAreValid() in InputValidate class. */
	bool configLinesAreValid() {
		fstream filename("../config/prog.config");
		string line;

		regex expression("(.)+( )+=( )+(.)+( )+\\.");
		regex expression_two("( )*");

		getline(filename, line);

		while(true) {
			if(!regex_match(line,expression)) {
				if(!regex_match(line,expression_two)) {
					filename.close();
					return false;
				}
			}
			getline(filename, line);
			config_line++;
			if(filename.eof()) break;
		}

		filename.close();
		return true;

	}

};
