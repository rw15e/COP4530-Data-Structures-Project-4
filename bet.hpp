// Assignment 4 COP4530
// Ryan Winter
// 11/8/17 (Fall 2017)

bool isOperand(string expression);
int checkPrecedence(string expression);

BET::BET(){ // default constructor
	start = new BinaryNode;
}

BET::BET(const string postfix){ // constructor that takes postfix and builds tree using it
	start = new BinaryNode;
	buildFromPostfix(postfix);
}

BET::BET(const BET& x){ // copy constructor
	start = clone(x.start);
}

BET::~BET(){ // destructor
	makeEmpty(start);
}

bool BET::buildFromPostfix(const string& postfix){ // build tree based on postfix expression
	string temp;
	string temp2;
	stack<BinaryNode*> myStack;
	stringstream s(postfix);
		
	int counter1 = 0;
	int counter2 = 0;

	if(postfix.empty() == true){
		cout << "Wrong postfix expression" << endl;
		start = nullptr;
		return false;
	}
	
	if(empty() == false)
		makeEmpty(start);
	
	bool flag = false;
	
	while(s >> temp){ // use stringstream to tokenize input
	
		// need to test here if there is a space entered (like there should be). should have a space inbetween always.. 
		// like 6 + should output wrong expression and ask for new expression
		
		//if(temp.size() > 1)
		//	return false;
			
		/*
		if(temp == " ")
			temp2 = " ";
		else
			temp2 = "string";
		*/
		//if(checkPrecedence(temp) != 0) // test if temp currently holds an operator
		//	counter1++;
		//if(isOperand(temp) == true)
		//	counter2++;
		
		BinaryNode *myNode = new BinaryNode(temp); // create a node to hold tokenized input
		
		if(isOperand(temp) == true){ // take all operands in and pushs to stack
			counter1++;
			myStack.push(myNode);	// push new node to stack
		}
		else if(checkPrecedence(temp) != 0){				// else if it is an operator (has precedence > 0)
			counter2++;
			if(counter1 == counter2){
				cout << "Wrong postfix expression" << endl;
				start = nullptr;
				return false;
			}
			else{
				myNode->left = myStack.top();
				myStack.pop();
				myNode->right = myStack.top();
				myStack.pop();
				myStack.push(myNode);
			}
		}		
	}

	if(counter1 != counter2)
		start = myStack.top();

	if(myStack.empty() == true){ // this stops a crash from trying to pop from empty stack
		cout << "Wrong postfix expression" << endl;
		start = nullptr;
		return false;
	}

	return true;
}

const BET & BET::operator=(const BET & x){ // assignment operator
	start = clone(x.start);
	return *this;
}

void BET::printInfixExpression(){ // print infix form (use private recursive function to help)
	printInfixExpression(start);
	cout << endl;
}

void BET::printPostfixExpression(){ // print postfix form (use private recursive function to help)
	printPostfixExpression(start);
	cout << endl;
}

size_t BET::size(){ // return the number of nodes in the tree
	return (size(start));
}

size_t BET::leaf_nodes(){  // return the number of leaf nodes in the tree
	return (leaf_nodes(start));
}
bool BET::empty(){ // return true if the tree is empty, else false
	if(start == nullptr) // if its an empty tree return true
		return true;
	return false;
}

void BET::printInfixExpression(BinaryNode *n){ // print infix expression (needs to handle adding parentheses)
	bool closeParentheses = false;
	
    if(n != nullptr){
        if(n->left == nullptr && n->right == nullptr) // if start node is valid, but has no children then just print it without any parentheses
            cout << n->data << " ";
        else{
            if(checkPrecedence(n->data) != 0 && checkPrecedence(n->right->data) != 0){	// test for operator. print right side first
                if(checkPrecedence(n->data) >= checkPrecedence(n->right->data)){
					if(checkPrecedence(n->data) == 2){
						cout << "( ";
						closeParentheses = true;
					}
				}
            }
            
            printInfixExpression(n->right);
			
            if(closeParentheses == true)
				cout << ") ";
            closeParentheses = false; // set closeParentheses back to false
            
            cout << n->data << " ";
            if(checkPrecedence(n->data) != 0 && checkPrecedence(n->left->data) != 0){	// test for operator. print left side next
				if(checkPrecedence(n->data) >= checkPrecedence(n->left->data)){
				    cout << "( ";
					closeParentheses = true;
				}
            }
            
            printInfixExpression(n->left);
            if(closeParentheses == true)
				cout << ") ";
			closeParentheses = false; // set closeParentheses back to false
        }
    }
}

void BET::makeEmpty(BinaryNode* &t){ // deletes all nodes in subtree pointed to by t
	if(t != nullptr){ // if it isnt empty then empty it
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
}

BET::BinaryNode * BET::clone(BinaryNode *t) const{ // clone all nodes in subtree pointed to by t
	if(t == nullptr)
		return nullptr;
    else
		return new BinaryNode(t->data, clone(t->left), clone(t->right));
}

void BET::printPostfixExpression(BinaryNode *n){ // print postfix expression
	if(size(n) == 0) // prevent segfault on empty tree
		return;
	else if(start->left == nullptr && start->right == nullptr)
		cout << start->data << endl;
	else{
		printPostfixExpression(n->right); // print right nodes first
		printPostfixExpression(n->left); // print left nodes next
		cout << n->data << " ";
	}
}

size_t BET::size(BinaryNode *t){ // returns number of nodes in subtree pointed to by t
	if(t == nullptr)
		return 0;
	else
		return(size(t->left) + size(t->right) + 1);
}

size_t BET::leaf_nodes(BinaryNode *t){ // return number of leaf nodes in the subtree pointed to by t
	if(t == nullptr)
		return 0;
	else if((t->left == nullptr) && (t->right == nullptr))
		return 1;
	else
		return (leaf_nodes(t->left) + leaf_nodes(t->right));
}

bool isOperand(const string str){ // test if operand
	for(int i = 0; i < int(str.size()); i++)
		if(isalnum(str[i]) == false) // check if alphanumeric 
			return false;
	return true;
}

int checkPrecedence(const string str){ // checks the precedence of given string
	if(str == "("|| str == ")")
		return (3);
	else if(str == "*" || str == "/")
		return (2);
	else if(str == "+" || str == "-")
		return (1);
	else
		return 0;
}