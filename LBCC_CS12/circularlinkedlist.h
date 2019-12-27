#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

using namespace std;

// Original header file from Dr. Aziz
// Last modified by Nicole Pavlovich 05-26-19


// Basic node template
template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};

template <class Type>
class circularLinkedList
{
public:
	
	void initializeList();
		//Initializes the list to an empty state.
		//Postcondition: first = NULL, last = NULL, count = 0
	bool isEmptyList();
		//Function to determine whether the list is empty. 
		//Postcondition: Returns true if the list is empty; otherwise, returns false.
	void print() const;
	int length();
		//Function to return the number of nodes in the list.
		//Postcondition: The value of count is returned	
	void destroyList();
		//Function to delete all the nodes from the list.
		//Postcondition: first = NULL, last = NULL, 
	Type front();
		//Function to return the first element of the list.
		//Precondition: The list must exist and must not be empty.
		//Postcondition: If the list is empty, then the program terminates; otherwise, the first element of the list is returned.
	Type back();
		//Function to return the last element of the list.
		//Precondition: The list must exist and must not be empty.
		//Postcondition: If the list is empty, then the program terminates; otherwise, the last element of the list is returned.	
	bool search(const Type& searchItem);
		//Function to determine whether searchItem is in the list.		
		//Postcondition: Returns true if searchItem is found in the list; otherwise, it returns false.

	void insertNode(const Type& newitem);
	void deleteNode(const Type& deleteItem);
		//Function to delete deleteItem from the list.
		//Postcondition: If found, the node containing deleteItem is deleted from the list, first points to the first		
		//                node, and last points to the last node of the updated list. 
	circularLinkedList();
		//Default constructor
		//Initializes the list to an empty state. 		
		//Postcondition: first = NULL, last = NULL, count = 0    	 
	~circularLinkedList();
		//Destructor - Deletes all the nodes from the list
		//Postcondition: The list object is destroyed.

	void divideAt(circularLinkedList<Type> &secondList, const Type& item);
    //Divide the list at the node with the info item into two sublists.
    //Postcondition: first and last point to the first and last nodes of the first sublist.
    //               secondList.first and secondList.last point to the first and last nodes of the
    //               second sublist.

protected:
	int count;				//variable to store the number of elements in the list
	nodeType<Type> *first;	//pointer to the first node of the list
	nodeType<Type> *last;	//pointer to the last node of the list 

};


template <class Type>
void circularLinkedList<Type>::divideAt(circularLinkedList<Type> &secondList, const Type& searchItem){

	nodeType<Type> *current; 	// pointer to traverse the list
	bool found = false;			// flag

	// create the duplicate cut list
	if (first != NULL)
	{
		current = first->link;
		while (current != first && !found)
		{
			if (current->info >= searchItem) 
			{
				found = true;
				while ( current != first->link) {
					secondList.insertNode(current->info);
					current = current->link;		
				}
			}
			else
				current = current->link;
		}
	}

	// delete the nodes from the original list
	bool deletioncomplete = false;
    while (!deletioncomplete) {
        if (back() < searchItem) {
            deletioncomplete = true;
        }
        else {
            deleteNode(back());
        }
    }

}

template <class Type>
void circularLinkedList<Type>::initializeList()
{
	destroyList();
}

template <class Type>
bool circularLinkedList<Type>::isEmptyList()
{
	return (first == NULL);
}

template <class Type>
void circularLinkedList<Type>::print() const
{
	//pointer to traverse the list
	nodeType<Type> *current; 
	current = first->link;

	//while more data to print
	while (current != first) 
	{
		cout << current->info << " ";
		current = current->link;
	}

	cout << first->info << " ";
}

template <class Type>
int circularLinkedList<Type>::length()
{
	return count;
}

template <class Type>
void circularLinkedList<Type>::destroyList()
{
	nodeType<Type> *temp;
	nodeType<Type> *current = NULL;

	if (first != NULL)
	{
		current = first->link;
		first->link = NULL;
	}

	while (current != NULL)
	{
		temp = current;
		current = current->link;
		delete temp;
	}

	first = NULL;	//initialize last to NULL; first has already
					//been set to NULL by the while loop
	count = 0;
}

template <class Type>
Type circularLinkedList<Type>::front()
{
	//assert(first != NULL);
	return first->link->info; //return the info of the first node	
}

template <class Type>
Type circularLinkedList<Type>::back()
{
	//assert(first != NULL);
	return first->info; //return the info of the first node	
}

template <class Type>
bool circularLinkedList<Type>::search(const Type& searchItem)
{
	//pointer to traverse the list
	nodeType<Type> *current; 
	bool found = false;

	if (first != NULL)
	{
		current = first->link;

		while (current != first && !found)
		{
			if (current->info >= searchItem)
				found = true;
			else
				current = current->link;

			found = (current->info == searchItem);
		}
	}

	return found;
}

template <class Type>
void circularLinkedList<Type>::insertNode(const Type& newitem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent; //pointer just before current
	nodeType<Type> *newNode;  //pointer to create a node

	bool  found;

	newNode = new nodeType<Type>; //create the node

	newNode->info = newitem;   //store newitem in the node
	newNode->link = NULL;      //set the link field of the node
								//to NULL

	if (first == NULL)  //Case 1	e.g., 3
	{
		first = newNode;
		first->link = newNode;
		count++;
	}
	else
	{
		if (newitem >= first->info)//e.g., 25 > 3
		{
			newNode->link = first->link;
			first->link = newNode;
			first = newNode;
		}
		else
		{
			trailCurrent = first; //e.g., 1 < 3 
			current = first->link;
			found = false;

			while (current != first && !found)
				if (current->info >= newitem)
					found = true;
				else
				{
					trailCurrent = current;
					current = current->link;
				}

			trailCurrent->link = newNode;
			newNode->link = current;
		}

		count++;
	}//end else
}

template <class Type>
void circularLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	//pointer to traverse the list
	nodeType<Type> *current; 
	//pointer just before current
	nodeType<Type> *trailCurrent; 

	bool found;

	//Case 1; list is empty. 
	if (first == NULL)    
		cout << "Can not delete from an empty list." << endl;
	else
	{
		found = false;
		trailCurrent = first;
		current = first->link;

		while (current != first && !found)
			if (current->info >= deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}

		if (current == first)
		{
			if (first->info == deleteItem)
			{
				if (first == first->link)
					first = NULL;
				else
				{
					trailCurrent->link = current->link;
					first = trailCurrent;
				}
				delete current;

				count--;
			}
			else
				cout << "The item to be deleted is not in the list." << endl;
		}
		else
			if (current->info == deleteItem)
			{
				trailCurrent->link = current->link;
				count--;
				delete current;
			}
			else
				cout << "Item to be deleted is not in the list." << endl;
	} //end else
}

template <class Type>
circularLinkedList<Type>::circularLinkedList()
{
	first = NULL;
	count = 0;
}

template <class Type>
circularLinkedList<Type>::~circularLinkedList()
{
	destroyList();
}

#endif