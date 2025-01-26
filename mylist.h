#ifndef myLIST_H
#define myLIST_H


#include<iostream>
#include<iomanip>
#include<string>

using namespace std;


template <typename T>
class Node
{
	private:
		T elem; //data element (type string in this case)
		Node<T>* next; //Link (pointer) to the next Node
		Node<T>* prev; //Link (pointer) to the previous Node
		template<class U> friend class MyList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(T elem) : elem(elem),next(NULL), prev(NULL)
		{}
		friend class FlightHASHTABLE;
};

template <typename T>
class MyList
{
	private:
		int size;
		Node<T>* head; 	// pointer to the head of List
		Node<T>* tail; 	// pointer to the tail of List
	public:
		MyList (); // constructor to create dummy head and tail nodes
		~MyList (); // destructor to clean up all nodes
		bool empty() const; // return true if the list is empty
		const T& front() const; // returns the const reference of the element from the first valid Node of list, throw an exception if the list is empty
		const T& back() const;  // returns the const reference of the element from last valid Node of the list, throw an exception if the list is empty
		void addBefore(Node<T> *ptr, const T& elem);	 //add a new node before a node pointed by ptr
		void addFront(const T& elem); // add a new node to the front of list (after head)
		void addBack(const T & elem); //add a new node to the back of the list (before tail)
		void removeFront(); // remove front node from list, throw an exception if the list is empty
		void removeBack();  // remove last node from list, throw an exception if the list is empty
		

		class iterator
		{
		private:
			Node<T>* v;
			iterator(Node<T>* node)
			{
				v = node;
			}
		public:
			using iterator_category = bidirectional_iterator_tag;
			using difference_type   = ptrdiff_t;
			using value_type        = T;
			using pointer           = Node<T>*;
			using reference         = Node<T>&;
			T operator*()
			{
				return v->elem;
			}
			iterator& operator++()
			{
				v = v->next;
				return *this;
			}
			iterator& operator--()
			{
				v = v->prev;
				return *this;
			}
			bool operator==(const iterator& other) const
			{
				return v == other.v;
			}
			bool operator!=(const iterator& other) const
			{
				return v != other.v;
			}
			Node<T>* getnode()
			{
				return v;
			}
			friend class MyList;

		};
		
		// add begin() and end() methods
		iterator begin() 
		{
        	return iterator(head->next);
    	}
    	iterator end() 
		{
        	return iterator(tail);
    	}
		void erase(MyList<T>::iterator itr);
		friend class FlightHASHTABLE;
};


#endif