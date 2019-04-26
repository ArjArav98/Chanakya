class TreeNode {
public:
	string id;
	string value;

	vector<string> keywords;
	vector<TreeNode> children;	

	TreeNode() {}

	TreeNode(string passed_id) {
		id = passed_id;
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

	/*==================*/
	/* PUBLIC FUNCTIONS */
	/*==================*/

	/* We add a node with the given characteristics to a specified parent node. */
	void add(string parentId, string id, string value) {
		/* We first create a new node. */
		TreeNode temp(id);
		temp.value = value;

		/* We then 'get' the specified parent node. */
		TreeNode parent = getNode(parentId, root);
		
		/* If the parent doesn't exist, we come out of the func. */
		if(parent.id == "NODE_IS_NULL") return;
		
		/* We then add the child to the children of the parent. */
		parent.children.push_back(temp);
	}


private:

	/*-------------------*/
	/* Utility Functions */
	/*-------------------*/

	/* We return the node with the given parent ID. */
	TreeNode getNode(string id, TreeNode root) {
		
		if(root.id == id) {
			return root;
		}
		else if(root.children.size() == 0);
		else if(root.children.size() != 0) {
	
			int childrenLength = root.children.size();
			for(int iter=0; iter<childrenLength; iter++) {
				TreeNode result = getNode(id, root.children[iter]);
				if(result.id != "NODE_IS_NULL") return result;
			}

		}

		TreeNode temp("NODE_IS_NULL");
		return temp;

	}

};
