/* Class which validates the config file. */
class ConfigValidator {

public:
	static int error_line;
	static string error_msg;

public:
	/*===========*/
	/* FUNCTIONS */
	/*===========*/

	static bool successfullyValidated() {
		if(!syntaxIsValid()) return false;
		else if(!allPropertiesPresent()) return false;
		else  if(!knowledgeFilePresent()) return false;
		else return true;
	}

	/* For logic explanation, refer knowledgeLinesAreValid() in KnowledgeValidate class. */
	static bool syntaxIsValid() {
		ifstream filename("../config/prog.config");
		string line;

		regex expression("(.)+( )+=( )+(.)+( )*");
		regex expression_two("( )*");

		getline(filename, line);

		while(true) {
			error_line++;
			if(!regex_match(line,expression)) {
				if(!regex_match(line,expression_two)) {
					filename.close();
					error_msg = "Syntax for config file is wrong";
					return false;
				}
			}
			getline(filename, line);
			if(filename.eof()) break;
		}

		filename.close();
		return true;

	}

	/* Checks if all properties are present in config file. */
	static bool allPropertiesPresent() {

		if(getConfigProperty("name") == "name") error_line = 1;
		else if(getConfigProperty("field") == "field") error_line = 2;
		else if(getConfigProperty("knowledge_file") == "knowledge_file") error_line = 3;
		else if(getConfigProperty("knowledge_type") == "knowledge_type") error_line = 4;
		else return true;

		error_msg = "Required properties are missing";
		return false;

	}

	/* Checks if knowledge file is present at path specified. */
	static bool knowledgeFilePresent() {
		try {
			ifstream file(getConfigProperty("knowledge_file"));
			if(!file.is_open()) throw -1;
			file.close();
		} 
		catch (const int exception) {
			error_line = 3;
			error_msg = "Cannot find knowledge file matching the name provided";
			return false;
		}

		return true;
	}

	static int errorLine() { return error_line; }
	static string errorMsg() { return error_msg; }

};

int ConfigValidator::error_line = 0;
string ConfigValidator::error_msg = "";