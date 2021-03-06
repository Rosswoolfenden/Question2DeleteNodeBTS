// deleteBSTnode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;
class BinTreeNode {
public:
	BinTreeNode(int value) {
		this->value = value;
		this->left = NULL;
		this->right = NULL;
	}
	int value;
	BinTreeNode* left;
	BinTreeNode* right;
	BinTreeNode* parent;

};
 //GIVEN FUNCTION
BinTreeNode* tree_insert(BinTreeNode* tree, int item) {
	if (tree == NULL) {

	
		tree = new BinTreeNode(item);}
	else {
		if (item < tree->value) {
			if (tree->left == NULL) {
				tree->left = new BinTreeNode(item);
				tree->left->parent = tree;
			}

			else {
				tree_insert(tree->left, item);
			}
		}
		else {
			if (tree->right == NULL) {
				tree->right = new BinTreeNode(item);
				tree->right->parent = tree;
			}
			else {
				tree_insert(tree->right, item);
			}
		}
	}
	return tree;

}
//GIVEN FUNCTION

void postorder(BinTreeNode* tree) {
	if (tree->left != NULL)
		postorder(tree->left);
	if (tree->right != NULL)
		postorder(tree->right);
	cout << tree->value << endl;

}
//GIVEN FUNCTION

void in_order(BinTreeNode* tree) {
	if (tree->left != NULL)
		in_order(tree->left);
	cout << tree->value << endl;
	if (tree->right != NULL)
		in_order(tree->right);
}
BinTreeNode* findN(BinTreeNode* tree, int target) {
	if (tree != NULL) { // if we are not at the end of a branch
		if (tree->value == target) { //base case- if current node is the one looking for -- or if you are at the end of a branch.
		
			return tree;
		}
		else if (target < tree->value) { // ir target is less than current node 
			return findN(tree->left, target); // recusive call with the left child node 
		}
		else {
			return findN(tree->right, target);  // recusive call with the right child node 
		}
	}
	cout << "NODE DOES NOT EXITS SORRY ";
	return tree;
}
 
int count_child_nodes(BinTreeNode* node) {
	int child_count = 0; // sets the child count to zero

	if (node->left != NULL) {  // if the left child pointer is not empty
		child_count = child_count + 1;  // add to the child count 
	}
	if (node->right != NULL) {
		child_count = child_count + 1;
	}

	return child_count;

}
	
	

	
BinTreeNode* FindMax(BinTreeNode* node) {
	BinTreeNode* current = node; //points at current 
	while (current->right != NULL)// while there is somthing to the right child slot of the node
	{
		current = current->right; // moves to the right child slot
	}
	return current; //retutrns the value of the right most child- the maximine value 

}
BinTreeNode* FindMin(BinTreeNode* node) {
	BinTreeNode* current = node; //points at current 
	while (current->left != NULL) { // while the left child is not empty
		current = current->left; //move to the left child untill there is no left child- means you have found min
	}
	return current;// returns the value of the less most node

}
BinTreeNode* del_node(BinTreeNode* tree, int node) {
	BinTreeNode* n;
	n = findN(tree, node);
	int childCount = count_child_nodes(n);
	BinTreeNode* parentNode= n->parent;
	
	if (childCount == 0) {
		if (n->value < parentNode->value) {  // if the node is a left child
			parentNode->left = NULL;   //erases the parents link
		}
		else {
			parentNode->right = NULL;  //does the same if its a right child 

		}
		delete n; //deletes the node
	}
	else if (childCount == 1) {
		if (n->right != NULL) {
			if (n->value < parentNode->value) { // if the node is the left child of its parent
				parentNode->left = n->right;  //swaps the parent link to ns child
			}
			else {
				parentNode->right = n->right;
			}

		}
		else {
			if (n->value < parentNode->value) { // if the node is the left child of its parent
				parentNode->left = n->left;
			}
			else {
				parentNode->right = n->left;
			}
		}
		delete n;
	}
	else {
		BinTreeNode* maxLeft = FindMax(n->left);    // finds the max leaf which will replace
		n->value = maxLeft->value;    // sets the leaf node as the new node.
		//delete (FindMax(n->left));
		
		if (maxLeft->value < maxLeft->parent->value) {
			maxLeft->parent->left = NULL;  //deletes  the leaf node which has been moved to the root
		}
		else {
			maxLeft->parent->right = NULL;
		}
	}

	return tree;
}




int main(int argc, char *argv[])
{

	// needs to be a balanced graph
	BinTreeNode* t = tree_insert(0, 5);
	tree_insert(t, 3);
	tree_insert(t, 7);
	tree_insert(t, 2);
	tree_insert(t, 4);
	tree_insert(t, 6);
	tree_insert(t, 8);
	//findN(t, 5);
	
	in_order(t);
	cout << " " << endl;

	del_node(t, 5);


	in_order(t);
	return 0;

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
