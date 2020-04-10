class Plugin {
	public:
	virtual int getInputComparisonScore(vector<string> input) = 0;
	//virtual string getAnswer(string input) = 0;
	
	private:
	virtual string getRequestURL(vector<int> options) = 0;
	virtual void saveHTMLFromURL(string url) = 0;
	virtual vector<string> getDataFromHTML() = 0;
};

class Plugins {

	public:
	virtual void displayAnswers(vector<string> input) = 0;

	private:
	virtual bool pluginsExist(vector<string> input) = 0;

};
