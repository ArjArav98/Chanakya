#include<iostream>
#include<string>
#include<vector>
using namespace std;

class InputScanner {

public:
	string removePunctuation(string original_question) {
		string new_question;
		int originalLen = original_question.length();

		for(int iter=0; iter<originalLen; iter++) {
			char current = original_question[iter];

			if(current >= '!' && current <= '/') break;
			else if(current >= ':' && current <= '@') break;
			else if(current >= '[' && current <= '`') break;
			else if(current >= '{' && current <= '~') break;
			else new_question.push_back(current);
		}

		return new_question;
	}

	string trimString(string original_question) {
		string new_string;
		int originalLen = original_question.length();
		
		bool leadingSpaceExists = original_question[0] == ' ';
		bool trailingSpaceExists = original_question[originalLen-1] == ' ';

		if(leadingSpaceExists || trailingSpaceExists) {
			
			for(int iter=0; iter<originalLen; iter++) {
				if(iter!=0 && iter!=(originalLen-1)) {
					new_string.push_back( original_question[iter] );
				}
				if(iter==0 && leadingSpaceExists) continue;
				else if(iter==(originalLen-1) && trailingSpaceExists) continue;
			}

		}

		return new_string;
	}

	vector<string> getLine(string statement) {
		
		string question;
		vector<string> questionSplit;

		cout<<statement;
		getline(cin, question);

		if(question.empty()) return questionSplit;
		
		question.assign(removePunctuation(question));
		//question.assign(trimString(question));

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

int main(){ 

	InputScanner in;
	vector<string> words = in.getLine("Question --> ");
	
	int len = words.size();

	for(int iter=0; iter<len; iter++)
		cout<<words[iter]<<endl;

	return 0;
}
