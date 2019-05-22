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

		/* This keeps track of number of '=' signs in the file. */
		/* This will act as a sort of index to retrieve the node values. */
		int valueIndex = 0;

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
				string keyword;
				file >> keyword;

				while(keyword != ".") {
					infotree.addKeyword(current_node, keyword);
					file >> keyword;
				}

			}
			/* If the operator is '=', meaning assigning values. */
			else if(op == "=") {	

				/* Instead of retrieving values, we store only the '=' number, */
				/* so that we can come back to the required '=' later and retrieve */
				/* the actual values. This is done to save memory. */

				valueIndex++;
				infotree.setValue(current_node,valueIndex);

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
