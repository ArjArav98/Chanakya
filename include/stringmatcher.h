typedef vector<string> Words;

class StringMatcher {

public:
	bool keywordHasAlternative(const string &keyword) {
		int len = keyword.length();
		for(int iter=0; iter<len; iter++) {
			if(keyword[iter]=='|') return true;
		}
		return false;
	}

	Words extractAlternatives(const string &keyword) {
		Words alternatives;
		int len = keyword.length();
		int start = 0;

		for(int iter=0; iter<len; iter++) {
			if(keyword[iter]=='|') {
				alternatives.push_back( keyword.substr(start,iter-start) );
				start = iter+1;
			}
		}

		alternatives.push_back( keyword.substr(start,len-start) );
		return alternatives;	
	}

	int getComparisonScore(const Words &node_keywords, const Words &sentence_words) {	
		int score = 0;

		int sentenceLen = sentence_words.size();
		int keywordsLen = node_keywords.size();

		/*=====================================*/
		/* Here, we iterate over the keywords. */
		for(int iter=0; iter<keywordsLen; iter++) {
		
			/*----------------------------------------------*/
			/* We check if there are alternatives. If no :- */
			Words alternatives;
			if (keywordHasAlternative(node_keywords[iter])) {
				
				alternatives = extractAlternatives(node_keywords[iter]);
				bool wordMatched = false;
				
				/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
				/* Here, we iterate over the alternatives. */
				int alternativesLen = alternatives.size();
				for(int jiter=0; jiter<alternativesLen; jiter++) {
					
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					/* Here, we iterate over the sentence and compare. */
					for (int kiter=0; kiter<sentenceLen; kiter++) {

						/* If matching, we inc score and return control to prev loop. */
						/* This is done so same word isn't matched twice incase present again. */
						if(alternatives[jiter] == sentence_words[kiter]) {
							score++;
							wordMatched = true;
							break;
						}
					}

					if(wordMatched) break;

				}
				
				if(wordMatched == false) score--;

			}

			/*------------------------------*/
			/* If there are no alternatives */
			else {

				bool wordMatched = false;
					
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				/* Here, we iterate over the sentence and compare. */
				for (int jiter=0; jiter<sentenceLen; jiter++) {

					/* Refer line 40 for expl. */
					if(node_keywords[iter] == sentence_words[jiter]) {
						score++;
						wordMatched = true;
						break;
					}
				}

				if(wordMatched == false) score--;

			}

		}

		return score;

	}

};

class error404 {

	/* Returns true if none of the children's keywords match with the sentence. */
	bool exists(TreeNode node, int finalScore) {

		int maxKeywords = -1;
		int childrenLen = node.children.size();

		/* We find out the max keywords present amongst the children nodes. */
		for(int iter=0; iter<childrenLen; iter++) {
			if(node.children[iter].keywords.size() > maxKeywords) {
				maxKeywords = node.children[iter].keywords.size();
			}
		}

		/* Since a non match is a negative, if no of negatives equal max keywords, then error. */
		if( (finalScore < 0) && ((-finalScore) >= maxKeywords) ) return true;
		else return false;

	}

};
