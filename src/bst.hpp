#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h> 
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);

    // Destructor for the BST class, destroys the tree
    ~BST(void);

    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);

    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);

    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T>* inorder(void);

    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T>* postorder(void);

    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T>* preorder(void);

    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T>* search(T);

    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);

    // Find minimum node for use in the remove() function.
    Node<T>* minNode(Node<T>*);

private:
    // the root node of the tree
    Node<T>* root;
    // the number of nodes in the tree
    int node_count;

    // Helper function for insert(). Hides detail from called function.
    Node<T>* insertHelper(int, Node<T>*);

    // Helper function for remove(). Hides detail from called function.
    Node<T>* removeHelper(T, Node<T>*);

    // Helper function for inorder(). Hides detail from called function.
    void inorderHelper(std::vector<T>*, Node<T>*);

    // Helper function for postorder(). Hides detail from called function.
    void postorderHelper(std::vector<T>*, Node<T>*);

    // Helper function for preorder(). Hides detail from called function.
    void preorderHelper(std::vector<T>*, Node<T>*);

    // Helper function for search(). Hides detail from called function.
    Node<T>* searchHelper(T, Node<T>*);

    // Inorder Node - function to return inorder node for use in removing nodes with two children.
    Node<T>* inorderNode(Node<T>*);
	
 };

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
std::vector<T>* BST<T>::inorder()
{
    std::vector<T>* save_vector = new std::vector<T>;                   // Stores the tree as we walk it.
	
    inorderHelper(save_vector, root);
	
	return save_vector;
}

template<class T>
void BST<T>::inorderHelper(std::vector<T>* in_vector, Node<T>* incoming_node)
{   if (incoming_node == NULL) {                                        // If incoming_node is NULL you don't traverse because there is no tree!
        return;
    }
    else {
        inorderHelper(in_vector, incoming_node->get_left());
        in_vector->push_back(incoming_node->get_data());
        inorderHelper(in_vector, incoming_node->get_right());
    }
}


template<class T>
std::vector<T>* BST<T>::preorder()
{
    std::vector<T> *save_vector = new std::vector<T>;

    preorderHelper(save_vector, root);

    return save_vector;
}

template<class T>
void BST<T>::preorderHelper(std::vector<T>* in_vector, Node<T>* incoming_node)
{
    if (incoming_node == NULL) {                                        // Again, signifies empty list and we return since we can't traverse.
        return;
    }
    else {
       in_vector->push_back(incoming_node->get_data());
       preorderHelper(in_vector, incoming_node->get_left());
       preorderHelper(in_vector, incoming_node->get_right());
    }
}


template<class T>
std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *save_vector = new std::vector<T>;

    postorderHelper(save_vector, root);

    return save_vector;
}

template<class T>
void BST<T>::postorderHelper(std::vector<T>* in_vector, Node<T>* incoming_node)
{
    if (incoming_node == NULL) {
        return;
    }
    else {
        postorderHelper(in_vector, incoming_node->get_left());
        postorderHelper(in_vector, incoming_node->get_right());
        in_vector->push_back(incoming_node->get_data());
    }
}

template<class T>
void BST<T>::insert(T new_data)
{
    root = insertHelper(new_data, root);
    std::cout << "Node count: " << node_count << std::endl;
}

template<class T>
Node<T>* BST<T>::insertHelper(int data, Node<T>* incoming_node)
{
    if (incoming_node == NULL) {                                                    // If the node is NULL, this means create a new tree.
        Node<T>* newNode = new Node<T>;
        newNode->set_data(data);
        newNode->set_left(NULL);
        newNode->set_right(NULL);
        node_count++;
        return newNode;
    }
    else
    if (incoming_node->get_data() > data) {                                         // If not NULL, we need to check if the node should go left or right and insert accordingly.
        incoming_node->set_left(insertHelper(data, incoming_node->get_left()));     // If less, go down the left tree.
    }
    else {                                                                          // Go down the right tree if not less (all other cases).
            incoming_node->set_right(insertHelper(data, incoming_node->get_right()));
    }

    return incoming_node;
}


template<class T>
Node<T> *BST<T>::search(T val)
{
    return searchHelper(val, root);
}

template<class T>
Node<T>* BST<T>::searchHelper(T in_data, Node<T>* incoming_node)
{
    if (incoming_node == NULL || incoming_node->get_data() == in_data) {
        return incoming_node;
    }
    else
    if (incoming_node->get_data() < in_data) {
        return searchHelper(in_data, incoming_node->get_left());
    }
    else {
        return searchHelper(in_data, incoming_node->get_right());
    }
}

template<class T>
void BST<T>::remove(T in_val)
{
	root = removeHelper(in_val, root);
}

template<class T>
Node<T>* BST<T>::removeHelper(T in_data, Node<T>* in_node)
{
    if (root == NULL) {                                
		return NULL;
	}
	else 
	if (in_node->get_data() > in_data) {
		in_node->set_left(removeHelper(in_data, in_node->get_left()));
	}
	else
	if (in_node->get_data() < in_data) {
		in_node->set_right(removeHelper(in_data, in_node->get_right()));
	}
	else {
		if (in_node->get_left() == NULL && in_node->get_right() == NULL) {	// No children
			delete in_node;
			in_node == NULL;
		}
		else
		if (in_node->get_left() == NULL) {									// Right child
			Node<T> * temp = in_node;
			in_node = in_node->get_right();
			delete temp;
		}
		else
		if (in_node->get_right() == NULL) {									// Left child
			Node<T> * temp = in_node;
			in_node = in_node->get_left();
			delete temp;
		}
		else {
			Node<T>* temp;
			int new_data;
			
			temp = minNode(in_node->get_right());
			new_data = temp->get_data();
			in_node->set_data(new_data);
			in_node->set_right(removeHelper(temp->get_data(), in_node->get_right()));
		}
		
	}
	
	return in_node;
}

template<class T>
Node<T>* BST<T>::minNode(Node<T>* incoming_node)
{
    while ( incoming_node->get_left() != NULL) {
        incoming_node = incoming_node->get_left();
    }

    return incoming_node;
}


template<class T>
int BST<T>::get_size()
{
    return node_count;
}
