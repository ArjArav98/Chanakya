typedef vector<string> Keywords;

class TreeNode {

public:
	string id;
	string value;

	Keywords keywords;
	vector<TreeNode> children;	

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

	/*==================*/
	/* PUBLIC FUNCTIONS */
	/*==================*/

	/* We add a node with the given characteristics to a specified parent node. */
	void add(string parentId, string id, string value, Keywords keywords) {
		/* We first create a new node. */
		TreeNode temp;
		
		temp.id = id;
		temp.value = value;
		temp.keywords = keywords;

		/* We then 'get' the specified parent node. */
		TreeNode* parent = getNode(parentId, root);
		
		/* If the parent doesn't exist, we come out of the func. */
		if(parent == NULL) return;
		
		/* We then add the child to the children of the parent. */
		parent->children.push_back(temp);
	}


private:

	/*-------------------*/
	/* Utility Functions */
	/*-------------------*/

	/* We return the node with the given parent ID. */
	TreeNode* getNode(string id, TreeNode root) {
		
		if(root.id == id) {
			TreeNode* result = &root;
			return result;
		}
		else if(root.children.size() == 0);
		else if(root.children.size() != 0) {
	
			int childrenLength = root.children.size();
			for(int iter=0; iter<childrenLength; iter++) {
				TreeNode* result = getNode(id, root.children[iter]);
				if(result != NULL) return result;
			}

		}

		return NULL;

	}

};
