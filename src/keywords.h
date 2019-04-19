class Node {
public:
	String value;
	Node* next;

	Node() {
		next = NULL;
	}

	bool isNotLast() {
		if(next == NULL) return false;
		else return true;
	}
};

/*==========*/
/* Keywords */
/*==========*/

/* Keywords is a list data-structure which holds the list of keywords. */

class Keywords {

	Node* head;
	Node* current;

public:

	/*==============================*/
	/* CONSTRUCTORS AND DESTRUCTORS */
	/*==============================*/

	Keywords() {
		head = new Node;
		current = head;
	}

	~Keywords() {
		thanosSnap();
	}

	/*==================*/
	/* PUBLIC FUNCTIONS */
	/*==================*/

	/* Add given value to end of list. */
	void add(String value) {
		Node* temp = new Node;
		temp->value = *value;

		Node* pos = head;
		while(pos->next!=NULL) pos=pos->next;
		pos->next = temp;
	}

	void add(const char* value) {
		Node* temp = new Node;
		temp->value = value;

		Node* pos = head;
		while(pos->next!=NULL) pos=pos->next;
		pos->next = temp;
	}


	/* Searches for given value in list of keywords. */
	Node* search(String value) {

		Node* pos = head->next;

		while(pos!=NULL) {
			if(pos->value == value) return pos;
			pos = pos->next;
		}

		return NULL;

	}

	void copy(Keywords keywords) {
		thanosSnap();
		head = new Node;

		while(keywords.iterates()) {
			String value = keywords.currentValue();
			add(value);
		}
	}

	/*---------------------*/
	/* Iteration Functions */
	/*---------------------*/

	/* Iterates over the list when used in a loop. */
	bool iterates() {
		if(current->isNotLast()) {
			current = current->next;
			return true;
		}
		else {
			current = head;
			return false;
		}
	}

	String currentValue() {
		return current->value;	
	}
	
	/*------------------*/
	/* Utility Functions*/
	/*------------------*/

private:
	/* Destroys and erases all nodes. */
	void thanosSnap() {
		while(head!=NULL) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		current = head = NULL;
	}

};
