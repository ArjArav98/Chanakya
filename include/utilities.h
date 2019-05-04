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

/* Prints a menu with the name, field of chatbot. */
void menu() {

	//We retrieve the name from the config file.
	string name = getConfigProperty("name");
	
	//We retrieve the field from the config file an print it.
	cout<<name<<": Hey there!\n";
	cout<<name<<": I'm "<<name<<" and I'm a chatbot designed to be an expert in the field of ";
	cout<<"'"<<getConfigProperty("field")<<"'. \n";
	cout<<name<<": Ask me anything!\n\n";

}
