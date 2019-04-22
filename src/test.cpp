#include<iostream>
#include<string>
#include<vector>
using namespace std;

#include"trees.h"

int main(){

	Tree tree;

	Keywords keywords;
	string name="arjun";
	keywords.push_back(name);

	tree.add("root","child","nothing",keywords);

	return 0;
}
