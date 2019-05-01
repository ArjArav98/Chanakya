/*===================*/
/* UTILITY FUNCTIONS */
/*===================*/

/* Gets the value of the specified property from .config file. */
string getConfigProperty(string property) {

	fstream filename("../config/prog.config");

	while(!filename.eof()) {
		string temp;
		filename >> temp;

		if(property == temp) {

			getline(filename, temp);
			filename.close();

			int len = temp.length();

			for(int iter=0; iter<len; iter++) {
				if(temp[iter]=='=') return temp.substr(iter+2, (len-2-(iter+2)));
			}

		}

	}

	filename.close();
	return property; //If nothing else is returned.

}

void menu() {

	cout<<"==============\n";
	cout<<"   CHANAKYA\n";
	cout<<"==============\n\n";

	cout<<"";

}
