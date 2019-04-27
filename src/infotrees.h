class TreeNode {
public:
	string id;
	string value;

	vector<string> keywords;
	vector<TreeNode> children;	

	/*==============*/
	/* CONSTRUCTORS */
	/*==============*/

	TreeNode() {}

	TreeNode(string passed_id) {
		id = passed_id;
	}

	/*================*/
	/* USER FUNCTIONS */
	/*================*/

	/* Adds a keyword to the keywords vector. */
	void addKeyword(string keyword) {
		keywords.push_back(keyword);
	}

	/*--------------------*/
	/* OPERATOR OVERLOADS */
	/*--------------------*/

	bool operator ==(TreeNode node) {
		if(id == node.id) return true;
		else return false;
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

	/* Sets value to node with given id. */
	void setValue(string id, string value) {
		TreeNode* parent = getNode(id, &root);
		if(parent == NULL) return;

		parent->value = value;
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

		for(int iter=0; iter<len; iter++) {
			print(passed_root.children[iter]);
		}

	}

};
