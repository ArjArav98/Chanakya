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
				string keyword;
				file >> keyword;

				while(keyword != ".") {
					infotree.addKeyword(current_node, keyword);
					file >> keyword;
				}

			}
			/* If the operatore is '=', meaning assigning values. */
			else if(op == "=") {
				char character;
				string value = "";
				int iter = -1;
				
				while(true) {
					file >> character;
					if((character == '.') && (iter > -1) && (value[iter] == ' ')) break;
					
					value.push_back(character);
					iter++;
				}

				infotree.setValue(current_node,value);
			}

		}

		file.close();
		return infotree;

	}

};
