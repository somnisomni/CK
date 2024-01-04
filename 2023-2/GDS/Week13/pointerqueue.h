#pragma once
#include "node.h"

template <class T>
class PointerQueue {
		Node<T> *m_front;
		Node<T> *m_rear;
		int m_size;
	public:
		PointerQueue(): m_front(nullptr), m_rear(nullptr), m_size(0) {}
		~PointerQueue() {
			while(!empty()) pop();
		}

		void push(T item);
		void pop();
		bool empty() { return m_size == 0; }
		T front() { return empty() ? T() : m_front->data; }
		int size() { return m_size; }
};

template<class T>
void PointerQueue<T>::push(T item) {
	Node<T> *inNode = new Node<T>(item);
	if(empty()) {
		m_front = inNode;
		m_rear = inNode;
	} else {
		m_rear->next = inNode;
		m_rear = inNode;
	}
	m_size++;
}

template<class T>
void PointerQueue<T>::pop() {
	if(empty()) return;

	Node<T> *delNode = m_front;
	m_front = m_front->next;
	delete delNode;
	m_size--;
}
