/* Class definition for each individual node in the tree. */
class TreeNode {

public:
	int valuePosition; //Position of value in file.
	int keywordPosition; //Position of keywords in file.

	string id; //ID of this node.
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
		fstream file(filename.c_str());
		
		/* One string for storing values and another for reading. */
		string values = "";
		string keyword;

		/* The cursor is set at position where value is present in file.*/
		file.seekg(valuePosition);
		file >> keyword;

		/* The loop iterates until a dot is read. */
		while(true) {
			file >> keyword;
			if(keyword == ".") break;

			values.append(keyword); /* String appended to values string. */
			values.push_back(' '); /* We add a space after each word. */
		}

		values.pop_back(); /* We pop out trailing space character. */

		file.close();
		return values; 

	}

	vector<string> keywords() {

		/* We get the name of the knowledge file from the config file. */
		string filename = getConfigProperty("knowledge_file");
		fstream file(filename.c_str());
		
		/* Vector for storing values and string for reading. */
		vector<string> node_keywords;
		string keyword;

		/* The cursor is set at position where value is present in file.*/
		file.seekg(keywordPosition);
		file >> keyword;

		/* The loop iterates until a dot is read. */
		while(true) {
			file >> keyword;
			if(keyword == ".") break;

			node_keywords.push_back(keyword);
		}

		file.close();
		return node_keywords;

	}

};

/* Class definiton for the tree itself. */
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

	/* Sets valuePosition to position in file. */
	void setValuePosition(string id, int valuePosition) {
		TreeNode* node = getNode(id, &root);
		if(node == NULL) return;

		node->valuePosition = valuePosition;
	}

	/* Sets keywordPosition to position in file. */
	void setKeywordPosition(string id, int keywordPosition) {
		TreeNode* node = getNode(id, &root);
		if(node == NULL) return;

		node->keywordPosition = keywordPosition;
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

	/* Debugging function. */
	/* void print(TreeNode passed_root) {
		
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

	} */

};
