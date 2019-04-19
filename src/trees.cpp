#include<iostream>
using namespace std;

#include"strings.h"
#include"lists.h"

//We need to remove this before we make this into a library.

// The tree must have these following things
// A unique name (string)
// value (only if lead node)
// leaf node or not (boolean)
// A list of keywords with which to identify it
// A list of children which might lead to other branches

class TreeNode {

public:
	String id;
	String value;

	bool isLeaf;
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
	void add(String parentId, String id, String value, bool isLeaf, Keywords keywords) {

		/* We first create a new node. */
		TreeNode* temp = new TreeNode;
		
		temp->id = id;
		temp->value = value;
		temp->isLeaf = isLeaf;
		temp->keywords = keywords;

		/* We then 'get' the specified parent node. */
		TreeNode* parent = getNode(parentId);
	
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

	/*===================*/
	/* PRIVATE FUNCTIONS */
	/*===================*/

	/*-------------------*/
	/* Utility Functions */
	/*-------------------*/

	/* We return the node with the given parent ID. */
	TreeNode* getNode(String id) {
		
		TreeNode* current = root;

		if(current->id == id) return current;
		else if(current->children != NULL) {
			TreeNode* temp = getNode(current->children->id);
			if(temp != NULL) return temp;
		}
		else if(current->next != NULL) {
			TreeNode* temp = getNode(current->next->id);
			if(temp != NULL) return temp;
		}
		
		return NULL;

	}

	/* We destroy all the nodes in the tree. */
	void thanosSnap(TreeNode* root) {
		if(root->children != NULL) thanosSnap(root->children);
		else if(root->next != NULL) thanosSnap(root->next);
		else delete root;
	}
	

};

int main() {	

	Tree tree;

	cout<<tree

	return 0;
}
