/* Class which validates the config file. */
class ConfigValidator {

public:
	int config_line;

	ConfigValidate() {
		config_line = 1;
	}

private:
	/*===========*/
	/* FUNCTIONS */
	/*===========*/

	/* For logic explanation, refer knowledgeLinesAreValid() in KnowledgeValidate class. */
	bool successfullyValidates() {
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

    int getLine() {
        return config_line;
    }

};