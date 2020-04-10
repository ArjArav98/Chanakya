class Plugin {
	public:
	virtual int getInputComparisonScore(vector<string> input) = 0;
	virtual void displayAnswer(vector<string> input, string name, bool pluginsOnly) = 0;

	private:
	virtual vector<int> parseOptionsFromInput(vector<string> input) = 0;
	virtual string getRequestURL(vector<int> options) = 0;
	virtual void saveHTMLFromURL(string url) = 0;
	virtual vector<string> getDataFromHTML() = 0;
};
