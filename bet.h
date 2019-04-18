// Assignment 4 COP4530
// Ryan Winter
// 11/8/17 (Fall 2017)

#ifndef BET_H
#define BET_H
#include <iostream>
#include <sstream>  
#include <stack>

using namespace std;

class BET
{		
	struct BinaryNode{		// struct must be called BinaryNode and contain all node-related information. (such as elements and pointers to children nodes)
		string data;
		BinaryNode *left; 		// pointer to left node
		BinaryNode *right; 		// pointer to right node
		BinaryNode(const string & d = string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr) : data{d}, left{l}, right{r} {}
	};
	
	public:		
		BET();										 // default constructor (build empty tree)
		BET(const string postfix);					 // constructor that builds tree based on postfix expression
		BET(const BET&);							 // copy constructor
		~BET();										 // destructor
		bool buildFromPostfix(const string& postfix); // build tree based on postfix expression
		const BET & operator=(const BET &);			 // assignment operator
		void printInfixExpression();				 // print infix form (use private recursive function to help)
		void printPostfixExpression();				 // print postfix form (use private recursive function to help)
		size_t size();								 // return the number of nodes in the tree (use private recursive function to help)
		size_t leaf_nodes();						 // return the number of leaf nodes in the tree (use private recursive function to help)
		bool empty();								 // return true if the tree is empty, else false

	private:
		void printInfixExpression(BinaryNode *n);	 // print infix expression (needs to handle adding parentheses)
		void makeEmpty(BinaryNode* &t);				 // deletes all nodes in subtree pointed to by t
		BinaryNode * clone(BinaryNode *t) const;	 // clone all nodes in subtree pointed to by t
		void printPostfixExpression(BinaryNode *n);  // print postfix expression
		size_t size(BinaryNode *t);					 // returns number of nodes in subtree pointed to by t
		size_t leaf_nodes(BinaryNode *t);			 // return number of leaf nodes in the subtree pointed to by t
		BinaryNode *start;							 // pointer to start of tree
};

#include "bet.hpp"
#endif