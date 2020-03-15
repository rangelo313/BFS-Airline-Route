#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <stdexcept>

namespace cop4530 {

	template <typename T>
	class Queue
	{
	public:
		Queue();				//Default constructor
		~Queue();				//default destructor
		Queue(const Queue& rhs);		//copy constructor
		Queue(Queue&& rhs);		//move constructor. Create the new queue with the elements of an existing queue rhs.
		Queue& operator=(const Queue& rhs);	//copy assignment operator
		Queue& operator=(Queue&& rhs); //move assignment operator.
		T& back();				//return a reference to the last element in the queue
		const T& back() const;			//
		bool empty() const;			//return true if there is no element in the queue
		T& front();				//return a reference to the first term
		const T& front() const;			//
		void pop();				//remove the first element in the queue and discard it
		void push(const T& val);		//add a new element val into the queue
		void push(T&& val);
		int size();				//return the number of elements in the queue


	private:
		std::deque <T> thequeue;			//dynamic stores element
	};
#include "Queue.hpp"
}
#endif
