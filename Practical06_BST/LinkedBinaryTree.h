#ifndef LINKEDBINARYTREE_H
#define LINKEDBINARYTREE_H

// Forward references.
template <typename T, typename Iterator>class BinaryTree;
template <typename T>class BinaryTreeNode;
template <typename T>class Container;

template <typename T, typename Iterator>
class LinkedBinaryTree : public BinaryTree<T, Iterator> {      
public:       
    // LinkedBinaryTree specific member functions
    // Constructor          
    LinkedBinaryTree(T element);
    // Copy constructor
    LinkedBinaryTree(LinkedBinaryTree<T, Iterator> const & other) {
       copy(other);
    }
    // Destructor
    ~LinkedBinaryTree() {
       destroy();
    }
        
    // Generic container functions
    virtual int size() const;
    virtual bool isEmpty() const;          
    
    // Generic SimpleTree functions
    virtual Iterator root() const;
    virtual Iterator & parent(Iterator & position) const;  
    virtual bool isInternal(Iterator & position) const;
    virtual bool isExternal(Iterator & position) const;
    virtual bool isRoot(Iterator & position) const;   
    virtual void swap(Iterator & first, Iterator & second);
    virtual void replace(Iterator & position, T element);
	virtual int depth(Iterator & position) const;
	virtual int nonRecursiveDepth(Iterator & position) const;
    
    // BinaryTree functions
    virtual Iterator & leftChild(Iterator & position) const;
    virtual Iterator & rightChild(Iterator & position) const;
   
	// Functions to return tree iterators
	Iterator & begin();
	Iterator & end();

    // Binary search tree function - inserts 
	Iterator insertItem(T key, Iterator & iter, Iterator & iterParent);
	Iterator & treeSearch(T key, Iterator & iter);
	Iterator treeMinimum(Iterator & x) const;	
   
private:
    BinaryTreeNode<T>* m_pRoot;     // Pointer to the root node
    int d_count;                    // Number of nodes in the tree
        
    void copy(LinkedBinaryTree<T, Iterator> const & other);
    void destroy();
};

template <typename T, typename Iterator>
LinkedBinaryTree<T, Iterator>::LinkedBinaryTree(T element) : d_count(1) {
    m_pRoot = new BinaryTreeNode<T>(element, this, 0);    
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::copy(LinkedBinaryTree<T, Iterator> const & other) {
    m_pRoot = new BinaryTreeNode<T>(*(other.m_pRoot));        
    d_Count = other.d_Count;
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::destroy() {
   delete m_pRoot;
}


template <typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::size() const {
    return d_count;
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isEmpty() const {
    return (d_count == 0);
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::swap(Iterator & first, Iterator & second) {
   T temp = (*first);
   (*first) = (*second);
   (*second) = temp;   
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::replace(Iterator & position, T element) {
    (*position) = element;	
}

template <typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::depth(Iterator & position) const {
	// final level recursion, we have reached the root node
	if (position == m_pRoot) {
		return 0;
	}
	else {
		// call function again on parent of this node and add one
		Iterator parentNode = parent(position);
		return 1 + depth(parentNode);
	}
}

template <typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::nonRecursiveDepth(Iterator & position) const {
	int result = 0;
	Iterator current = position;
	// increment result while we have not yet reached the root
	while (current != m_pRoot) {
		result++;
		current = parent(current);
	}
	return result;
}

template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::root() const {
    return Iterator(m_pRoot);
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::parent(Iterator & position) const {     
	return position.node()->parent();
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isInternal(Iterator & position) const {	
	return ( position.node()->leftChild() != 0 || position.node()->rightChild() != 0);    
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isExternal(Iterator & position) const {
	return ( position.node()->leftChild() == 0 && position.node()->rightChild() == 0);    
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isRoot(Iterator & position) const {	
    return ( position == m_pRoot );
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::leftChild(Iterator & position) const {    	
	Iterator & iter = position;
	if ( position.node() != 0 ) {
		iter = position.node()->leftChild();
	}
	return iter;
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::rightChild(Iterator & position) const {    
    Iterator & iter = position;
	if ( position.node() != 0 ) {
		iter = position.node()->rightChild();
	}
	return iter;
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::treeSearch(T key, Iterator & iter) {
	/*if n is an external node and key(n) <> k then
  return NULL KEY
if k == key(n) then
  return n
else if k < key(n) then
  return treeSearch(k, T.leftChild(n))
else
  { we know that k > key(n) }
  return treeSearch(k, T.rightChild(n))*/
	if ( iter.node() == 0 || isExternal(iter) && (*iter) != key ) {
		return Iterator(0);
	}
	if ( key == (*iter) ) {
		return iter;
	}	
	else if ( key < (*iter) ) {
		return treeSearch( key, leftChild(iter) );
	}
	else {
		return treeSearch( key, rightChild(iter) );
	}
}


template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::insertItem(T key, Iterator & iter, 
													          Iterator & iterParent) {
    BinaryTreeNode<T> * pNode = iter.node();
	if ( pNode == 0) {       
       pNode = new BinaryTreeNode<T>(key, this);
       pNode->setLeftChild(0);
       pNode->setRightChild(0);
       pNode->setParent(iterParent.node());
	   d_count++;
    }
    else if (key < pNode->element()) {
       Iterator tempIter = insertItem(key, pNode->leftChild(), iter );
       pNode->setLeftChild( tempIter.node() );       
    }
    else if (key > pNode->element()) {
	   Iterator tempIter = insertItem(key, pNode->rightChild(), iter );
       pNode->setRightChild( tempIter.node() );              
    }
    
    return Iterator(pNode);    
}

template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::treeMinimum(Iterator & x) const{
	// starting node of our subtree
	BinaryTreeNode<T> * pNode = x.node();
	// continue down the left of the sub tree until we find a leaf node
	while (pNode->leftChild() != nullptr) {
		pNode = pNode->leftChild().node();
	}
	// return the left most node of our subtree
	return Iterator(pNode);
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::begin() {
	return Iterator(m_pRoot);	
}

template <typename T, typename Iterator>
Iterator & LinkedBinaryTree<T, Iterator>::end() {
	return m_pRoot->parent();	
}


	


#include "BinaryTree.h"
#include "BinaryTreeNode.h"

#endif
