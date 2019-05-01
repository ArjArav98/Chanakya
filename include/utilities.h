/*===================*/
/* UTILITY FUNCTIONS */
/*===================*/

/* Gets the value of the specified property from .config file. */
string getConfigProperty(string property) {

	fstream filename("prog.config");

	while(!filename.eof()) {
		string temp;
		filename >> temp;

		if(property == temp) {
			filename >> temp; //The '=' operator.
			filename >> temp; //The property value.

			filename.close();
			return temp;
		}
	}

	filename.close();
	return property; //If nothing else is returned.

}
