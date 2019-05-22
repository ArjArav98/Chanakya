class TreeNode {
public:
	string id; //ID of the node.
	int valueIndex; //Index of required '=' sign.

	vector<string> keywords;
	vector<TreeNode> children;	

	/*==============*/
	/* CONSTRUCTORS */
	/*==============*/

	TreeNode() {}

	TreeNode(string passed_id) {
		id = passed_id;
	}

	/*--------------------*/
	/* OPERATOR OVERLOADS */
	/*--------------------*/

	bool operator ==(TreeNode node) {
		if(id == node.id) return true;
		else return false;
	}

	/*================*/
	/* USER FUNCTIONS */
	/*================*/


	/* This function extracts and returns node value with help of valueIndex. */
	string value() {

		/* We get the name of the knowledge file from the config file. */
		string filename = getConfigProperty("knowledge_file");

		/* We open the file in a stream. */
		fstream file(filename.c_str());
		int valueIter = 0; //To keep track of '=' encountered.
		string values = "";

		/* We read until the eof has been encountered. */
		while(!file.eof()) {
			string keyword;
			file >> keyword;

			/* If '=' is encountered.*/
			if(keyword == "=") {
				valueIter++;

				/* If this '=' number matches the one in valueIndex. */
				if(valueIter == valueIndex) {
					/* We append all strings read until dot in 'value'. */
					while(true) {
						file >> keyword;
						if(keyword == ".") break;

						values.append(keyword);
						values.push_back(' ');
					}

					values.pop_back();
					break;
				}

			}

		}

		file.close();
		return values; 

	}
};

class InformationTree {

public:

	TreeNode root;

	/*==============================*/
	/* CONSTRUCTORS AND DESTRUCTORS */
	/*==============================*/

	InformationTree() {
		root.id = "root";
	}

	/*================*/
	/* USER FUNCTIONS */
	/*================*/

	/* Creates a node with given id and adds to given parent node. */
	void add(string parentId, string id) {
		/* We first create a new node. */
		TreeNode temp(id);

		/* We then 'get' the specified parent node. */
		TreeNode* parent = getNode(parentId, &root);

		/* If the parent doesn't exist, we come out of the func. */
		if(parent == NULL) return;
		
		/* We then add the child to the children of the parent. */
		parent->children.push_back(temp);
	}

	/* Sets valueNumber to node with given id. */
	void setValue(string id, int valueIndex) {
		TreeNode* node = getNode(id, &root);
		if(node == NULL) return;

		node->valueIndex = valueIndex;
	}

	/* Adds a keyword to the node. */
	void addKeyword(string id, string keyword) {
		TreeNode* node = getNode(id, &root);
		if(node == NULL) return;

		node->keywords.push_back(keyword);
	}

	/*-------------------*/
	/* Utility Functions */
	/*-------------------*/

	/* We return the node with the given parent ID. */
	TreeNode* getNode(string id, TreeNode* passed_root) {
		
		if(passed_root->id == id) {
			return passed_root;
		}
		else if(passed_root->children.size() == 0);
		else if(passed_root->children.size() != 0) {
	
			int childrenLength = passed_root->children.size();
			for(int iter=0; iter<childrenLength; iter++) {
				TreeNode* result = getNode(id, &passed_root->children[iter]);
				if(result != NULL) return result;
			}

		}

		return NULL;

	}

	void print(TreeNode passed_root) {
		
		cout<<"The parent is "<<passed_root.id<<endl;
		cout<<"The children are :- ";

		int len = passed_root.children.size();
		if(len == 0) cout<<"none.\n\n";

		for(int iter=0; iter<len; iter++) {
			cout<<passed_root.children[iter].id<<", ";
		}

		if(len != 0) cout<<"\b\b.\n\n";

		cout<<"The keywords are :- ";
		int len1 = passed_root.keywords.size();
		if(len1 == 0) cout<<"none.\n\n";
		
		for(int iter=0; iter<len1; iter++) {
			cout<<passed_root.keywords[iter]<<", ";
		}

		if(len1 != 0) cout<<"\b\b.\n\n";

		for(int iter=0; iter<len; iter++) {
			print(passed_root.children[iter]);
		}

	}

};
