#include "mylist.h"
#include "flighthashtable.h"


//============================================================
template <typename T>
MyList<T>::MyList ()
{
	size = 0;
	head = new Node<T>; 
	tail= new Node<T>; 
	head->next = tail;
    tail->prev = head;
}
//============================================================
template <typename T>
MyList<T>::~MyList () // destructor to clean up all nodes
{
	while (!empty())
	{
		removeFront();
	}
	delete head;
	delete tail;
}
//============================================================
template <typename T>
bool MyList<T>::empty() const // is list empty?
{
	if (head->next == tail)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
//============================================================
template <typename T>
const T& MyList<T>::front() const // get front element
{
	if(empty()) 
	{
        throw runtime_error("List is empty..!");
    }
	else
	{
		return head->next->elem;
	}
    
}
//============================================================
template <typename T>
const T& MyList<T>::back() const // get front element
{
	if(empty()) 
	{
        throw runtime_error("List is empty..!");
    }
	else
	{
		return tail->prev->elem;
	}
}
//============================================================
template <typename T>
void MyList<T>::addBefore(Node<T> *ptr, const T& elem)
{
	Node<T>* creatednode = new Node<T>(elem);
    creatednode->next = ptr;
    ptr->prev->next = creatednode;
	creatednode->prev = ptr->prev;
    ptr->prev = creatednode;
}
//============================================================
template <typename T>
void MyList<T>::addFront(const T& elem) // add to front of list
{
	addBefore(head->next, elem);
	size++;
}
//============================================================
template <typename T>
void MyList<T>::addBack(const T& elem) // add to Back of the list
{
	addBefore(tail, elem);
	size++;
}
//============================================================
template <typename T>
void MyList<T>::removeFront() // remove front item from list
{
	if(empty()) 
	{
        throw runtime_error("List is empty..!");
    }
	else
	{
		Node<T>* delnode= head->next;
		delnode->next->prev = head;
    	head->next = delnode->next;
    	delete delnode;
		size--;
	}
}
//============================================================
template <typename T>
void MyList<T>::removeBack() // remove last item from list
{
	if(empty()) 
	{
        throw runtime_error("List is empty..!");
    }
	else
	{
		Node<T>* delnode = tail->prev;
		tail->prev = delnode->prev;
		delnode->prev->next = tail;
		delete delnode;
		size--;
	}
}
//============================================================
template <typename T>
void MyList<T>::erase(MyList<T>::iterator itr)
{
    if (itr == end() or itr.v == NULL) // iterator points to tail or NUll, cannot erase
    {
        throw runtime_error("Cannot erase");
    }
	else
	{
		Node<T>* delnode = itr.v; 

		// Update links
		delnode->prev->next = delnode->next;
		delnode->next->prev = delnode->prev;

		// Delete node and decrement size
		delete delnode;
		size--;
	}
}


template class MyList<HashNode>;