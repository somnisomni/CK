#pragma once

template <class T>
struct Node {
	public:
		T data;
		Node *next;

		Node(T item): data(item), next(nullptr) {}
};
