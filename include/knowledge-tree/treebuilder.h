/* Reads data from knowledge file and builds the tree.*/
class TreeBuilder {
	
	string filename;
	InformationTree infotree;

public:

	TreeBuilder(string passed_filename) {
		filename = passed_filename;
	}


	/*================*/
	/* USER FUNCTIONS */
	/*================*/

	/* Reads input file, generates tree with values and returns the tree. */
	InformationTree generateTree() {

		/* We open the file in a filestream. */
		fstream file(filename.c_str());

		/* Loop until file ends. */
		while(!file.eof()) {

			/* First string on line is node to be manipulated. */
			string current_node;
			file >> current_node;

			string op;
			file >> op;

			/* If the operator is '<', meaning adding nodes. */
			if(op == "<") {
				string parent;
				file >> parent;
				infotree.add(parent,current_node);
			}
			/* If the operator is ':', meaning adding keywords. */
			else if(op == ":") {
				
				/* Instead of storing keywords, we store file cursor pos. */
				/* We read file from this pos when retrieving keywords. */
				/* This saves memory! */

				int position = file.tellg();
				infotree.setKeywordPosition(current_node, position-1);

				/* We then have to navigate to the end of the line. */
				string word;
				file >> word;

				while(word != ".") file >> word;
			}
			/* If the operator is '=', meaning assigning values. */
			else if(op == "=") {	

				/* Instead of storing values, we store the file cursor pos. */
				/* We read file from this pos when retrieving values. */
				/* This saves memory! */

				int position = file.tellg();
				infotree.setValuePosition(current_node, position-1);

				/* We then have to navigate to the end of the line. */
				string word;
				file >> word;

				while(word != ".") file >> word; 
			}

		}

		file.close();
		return infotree;

	}

};
