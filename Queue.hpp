#ifndef QUEUE_HPP
#define  QUEUE_HPP
#include <iostream>
#include <ostream>
using namespace std;
using namespace cop4530;

template<typename T> 
Queue<T>::Queue()
{
	//already zero
}
template <typename T>
Queue<T>::~Queue()
{
	
}
template <typename T>
Queue<T>::Queue(const Queue& rhs)
{
	Queue CP = rhs;
	swap(*this, CP);
}

template <typename T>
Queue<T>::Queue(Queue&& rhs)
{
	thequeue = rhs.thequeue;
	rhs.thequeue = nullptr;
}
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& rhs)
{
	thequeue = rhs.thequeue;
	rhs.thequeue = thequeue;
	
}
template<typename T> 
Queue<T>& Queue<T>::operator=(Queue&& rhs)
{
	swap(thequeue, rhs.thequeue);
	return *this;

}
template <typename T> 
T& Queue<T>::back()
{
	return thequeue.back();
}
template <typename T>
const T& Queue<T>::back() const
{
	return thequeue.back();
}
template <typename T>
bool Queue<T>::empty() const
{
	if (thequeue.begin() == thequeue.end())
		return true;
	if (thequeue.empty())
		return true;
	else
		return false;
}
template <typename T>
T& Queue<T>::front()
{
	return thequeue.front();
}
template <typename T>
const T& Queue<T>::front() const
{
	return thequeue.front();
}
template <typename T>
void Queue<T>::pop()
{
	thequeue.pop_front();
}
template <typename T>
void Queue<T>::push(const T& val)
{
	thequeue.push_back(val);
}
template <typename T>
void Queue<T>::push(T&& val)
{
	thequeue.push_back(val);
}

template <typename T>
int Queue<T>::size()
{
	return thequeue.size();
}
#endif /* VECTOR_HPP */