#include "LinkedBinaryTree.h"
#include "BinaryTreeIterator.h"

#include <iostream>

using namespace std;


int main() {	

	LinkedBinaryTree<int, BinaryTreeIterator<int>> myTree(10);

	myTree.insertItem(5, myTree.root(), myTree.parent(myTree.root()) );
	myTree.insertItem(15, myTree.root(), myTree.parent(myTree.root()) );
	myTree.insertItem(25, myTree.root(), myTree.parent(myTree.root()) );
	myTree.insertItem(35, myTree.root(), myTree.parent(myTree.root()) );
	myTree.insertItem(14, myTree.root(), myTree.parent(myTree.root()));
	myTree.insertItem(13, myTree.root(), myTree.parent(myTree.root())); 
	myTree.insertItem(12, myTree.root(), myTree.parent(myTree.root()));
	myTree.insertItem(3, myTree.root(), myTree.parent(myTree.root()));
	myTree.insertItem(1, myTree.root(), myTree.parent(myTree.root()));
	myTree.insertItem(2, myTree.root(), myTree.parent(myTree.root()));
	myTree.insertItem(4, myTree.root(), myTree.parent(myTree.root()));
    

	BinaryTreeIterator<int> iter = myTree.root();
	
	//iter.downRight();
	//iter.downRight();
	//iter.downRight();
	
	cout << myTree.nonRecursiveDepth(iter) << endl;
	cout << myTree.treeMinimum(iter).node()->element() << endl;
	system("PAUSE");
	
}