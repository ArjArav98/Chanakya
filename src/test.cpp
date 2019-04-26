#include<iostream>
#include<string>
#include<vector>
using namespace std;

#include"trees.h"
#include"stringmatcher.h"

int main(){

	Tree tree;

	tree.add("root","child","nothing");
	tree.add("root","child1","nothing");
	tree.add("root","child2","nothing");

	tree.print(tree.root);

	return 0;
}
