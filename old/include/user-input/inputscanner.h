/* Class which reads input from the user and sanitises it. */
class InputScanner {

	/* Removes punctuation and redundant spaces in the string. */
	string removePunctuation(string original_question) {
		string new_question;
		int originalLen = original_question.length();

		for(int iter=0; iter<originalLen; iter++) {
			char current = original_question[iter];
	
			/* We remove punctuation and redundant spaces. */
			if(current == ' ' && original_question[iter-1] == ' ');
			else if(current == '"') new_question.push_back(current);
			else if(current >= '!' && current <= '/');
			else if(current >= ':' && current <= '@');
			else if(current >= '[' && current <= '`');
			else if(current >= '{' && current <= '~');
			else new_question.push_back(current);
		}
		
		return new_question;
	}

	/* Checks if there are upper-case characters. */
	bool upperCaseExists(string original) {
		int len = original.length();

		for(int iter=0; iter<len; iter++) {
			if(original[iter] >= 'A' && original[iter] <= 'Z') return true;
		}

		return false;
	}

	/* Makes every character lower-case. */
	string toLowerCase(string original_question) {
		
		if(upperCaseExists(original_question)) {
			
			int len = original_question.length();
			int difference = 'a' - 'A';
			string new_question;

			for(int iter=0;iter<len; iter++) {
				/* If uppercase, we add the difference and push to new string. */
				if(original_question[iter] >= 'A' && original_question[iter] <= 'Z') {
					new_question.push_back(original_question[iter] + difference);
				}
				else new_question.push_back(original_question[iter]);
			}

			return new_question;

		}

		return original_question;
	}

	/*===================*/
	/* UTILITY FUNCTIONS */
	/*===================*/

	/* Removes leading and trailing whitespaces from strings. */
	string trimString(string original_question) {
		string new_string;
		int originalLen = original_question.length();
		
		bool leadingSpaceExists = original_question[0] == ' ';
		bool trailingSpaceExists = original_question[originalLen-1] == ' ';

		if(leadingSpaceExists || trailingSpaceExists) {
			
			for(int iter=0; iter<originalLen; iter++) {
				if(iter==0 && leadingSpaceExists) continue;
				else if(iter==(originalLen-1) && trailingSpaceExists) continue;
				else new_string.push_back( original_question[iter] );
			}

			return new_string;

		}
		else return original_question;

	}

public:

	/*================*/
	/* USER FUNCTIONS */
	/*================*/

	/* Gets the string and then splits it into a vector of words. */
	vector<string> getLine(string statement) {
		
		string question;
		vector<string> questionSplit;

		cout<<statement;
		getline(cin, question);

		if(question.empty()) return questionSplit;
	
		question.assign(trimString(question));
		question.assign(removePunctuation(question));
		question.assign(toLowerCase(question));

		int start=0, len=question.length();

		for(int iter=0; iter<len; iter++) {

			if(question[iter] == ' ') {
				questionSplit.push_back( question.substr(start,iter-start) );
				start = iter+1;
			}

		}

		questionSplit.push_back( question.substr(start,len-start) );	
		return questionSplit;

	}

};
