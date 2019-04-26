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

class Tree {

public:

	TreeNode root;

	/*==============================*/
	/* CONSTRUCTORS AND DESTRUCTORS */
	/*==============================*/

	Tree() {
		root.id = "root";
	}

	/*================*/
	/* USER FUNCTIONS */
	/*================*/

	/* We add a node with the given characteristics to a specified parent node. */
	void add(string parentId, string id, string value) {
		/* We first create a new node. */
		TreeNode temp(id);
		temp.value = value;

		/* We then 'get' the specified parent node. */
		TreeNode* parent = getNode(parentId, root);

		/* If the parent doesn't exist, we come out of the func. */
		if(parent == NULL) return;
	
		/* We then add the child to the children of the parent. */
		parent->children.push_back(temp);
	}

	/*-------------------*/
	/* Utility Functions */
	/*-------------------*/

	/* We return the node with the given parent ID. */
	TreeNode* getNode(string id, TreeNode passed_root) {
		
		if(passed_root.id == id) {
			return &root;
		}
		else if(passed_root.children.size() == 0);
		else if(passed_root.children.size() != 0) {
	
			int childrenLength = passed_root.children.size();
			for(int iter=0; iter<childrenLength; iter++) {
				TreeNode* result = getNode(id, passed_root.children[iter]);
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
