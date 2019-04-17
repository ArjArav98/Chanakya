class Node {
public:
	String value;
	Node* next;

	Node() {
		next = NULL;
	}

	Node(String passedValue) {
		value = passedValue;
		next = NULL;
	}

	bool isNotLast() {
		if(next == NULL) return false;
		else return true;
	}
};

class List {

	Node* head;
	Node* current;

public:

	/*==============================*/
	/* CONSTRUCTORS AND DESTRUCTORS */
	/*==============================*/

	List() {
		head = new Node;
		current = head;
	}

	~List() {
		thanosSnap();
		head = new Node;
	}

	/*================*/
	/* PUBLIC METHODS */
	/*================*/

	/* Add given value to end of list. */
	void add(String value) {

		Node* temp = new Node;
		temp->value = value;

		Node* pos = head;
		while(pos->next!=NULL) pos=pos->next;

		pos->next = temp;

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

	/* Destroys and erases all nodes. */
	void thanosSnap() {
		while(head!=NULL) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

};
