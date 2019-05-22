/*===================*/
/* UTILITY FUNCTIONS */
/*===================*/

/* Gets the value of the specified property from .config file. */
string getConfigProperty(string property) {

	fstream file("../config/prog.config");

	while(!file.eof()) {
		string temp;
		file >> temp;

		if(property == temp) {
			getline(file, temp);
			file.close();

			int len = temp.length();

			for(int iter=0; iter<len; iter++) {
				if(temp[iter]=='=') return temp.substr(iter+2, (len-2-(iter+2)));
			}

		}

	}

	file.close();
	return property; //If nothing else is returned.

}

/* Prints a menu with the name, field of chatbot. */
void menu() {

	//We retrieve the name from the config file.
	string name = getConfigProperty("name");
	
	//We retrieve the field from the config file an print it.
	cout<<endl<<name<<": Hey there! I'm "<<getConfigProperty("name")<<"!\n";
	cout<<"Ask me anything about '"<<getConfigProperty("field")<<"'!\n\n";

}
