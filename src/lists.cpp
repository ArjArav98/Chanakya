#include<iostream>
using namespace std;

#include"strings.h"

//Delete everything before this before we make this into a header file.

class Node {
public:
	String value;
	Node* next;

	Node() {
		next = NULL;
	}

	Node(String passedValue) {
		value = passedValue;
	}
};

class List {

	Node<NodeValue>* head;

public:
	List() {
		head = new Node;
	}

};

int main(){ 

	return 0;
}
