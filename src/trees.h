class TreeNode {

public:
	String id;
	String value;

	Keywords keywords;
	
	TreeNode* children;
	TreeNode* next;

	TreeNode() {
		children = NULL;
		next = NULL;
	}

};

class Tree {

public:

	TreeNode* root;

	/*==============================*/
	/* CONSTRUCTORS AND DESTRUCTORS */
	/*==============================*/

	Tree() {
		root = new TreeNode;
		root->id = "root";
	}

	~Tree() {
		thanosSnap(root);
		root = NULL;
	}

	/*==================*/
	/* PUBLIC FUNCTIONS */
	/*==================*/

	/* We add a node with the given characteristics to a specified parent node. */
	void add(String parentId, String id, String value, Keywords keywords) {
		cout<<"this is workkkinnggg\n";
		/* We first create a new node. */
		TreeNode* temp = new TreeNode;
		
		temp->id = id;
		temp->value = value;
		cout<<"this is working\n";
		temp->keywords.copy(keywords);

		cout<<"this is working1234\n";
		/* We then 'get' the specified parent node. */
		TreeNode* parent = getNode(parentId);
		cout<<"this is working2\n";
		
		/* If the parent doesn't exist, we come out of the func. */
		if(parent == NULL) return;
		
		/* We check for children and then add the child node. */
		if(parent->children == NULL) {
			parent->children = temp;
		}
		else {
			TreeNode* pos = parent->children;
			while(pos->next!=NULL) pos = pos->next;
			pos->next = temp;
		}

	}


private:

	/*-------------------*/
	/* Utility Functions */
	/*-------------------*/

	/* We return the node with the given parent ID. */
	TreeNode* getNode(String id) {
		
		TreeNode* current = root;

		if(current->id == id) return current;
		if(current->children != NULL) {
			TreeNode* temp = getNode(current->children->id);
			if(temp != NULL) return temp;
		}
		if(current->next != NULL) {
			TreeNode* temp = getNode(current->next->id);
			if(temp != NULL) return temp;
		}
		
		return NULL;

	}

	/* We destroy all the nodes in the tree. */
	void thanosSnap(TreeNode* root) {
		if(root->children != NULL) thanosSnap(root->children);
		if(root->next != NULL) thanosSnap(root->next);
	
		delete root;
	}
	

};
