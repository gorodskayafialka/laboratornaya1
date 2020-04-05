#pragma once
#include "Leaf.h"
template <typename key_type, typename value_type>
class Node
{
public:
	Node(Leaf<key_type, value_type>* data, Node* next = nullptr)
	{
		this->data = data;
		this->next = next;
	};
	~Node() {};
	Leaf<key_type, value_type>* data;
	Node* next;
};

template <typename key_type, typename value_type>
class Stack
{
	void reset()
	{
		head = nullptr;
		tail = nullptr;
	}
	Node<key_type, value_type>* head;
	Node<key_type, value_type>* tail;
	size_t size;
public:
	Stack()
	{
		reset();
		size = 0;
	};
	~Stack()
	{
		Node<key_type, value_type>* current = head;
		Node<key_type, value_type>* prev;
		while (current != tail)
		{
			prev = current;
			current = current->next;
			delete prev;
			size--;
		}
		delete current;
		size--;
		reset();
	};
	void push(Leaf<key_type, value_type>* new_element)
	{
		if (size == 0)
		{
			head = new Node<key_type, value_type>(new_element);
			tail = head;
		}
		else
		{
			Node<key_type, value_type>* current = new Node<key_type, value_type>(new_element);
			current->next = head;
			head = current;
		}
		size++;
	}
	Leaf<key_type, value_type>* pop()
	{
		if (size == 0)
		{
			throw exception("The queue is empty");
		}
		else
		{
			Leaf<key_type, value_type>* element = head->data;
			Node<key_type, value_type>* current = head;
			head = head->next;
			delete current;
			size--;
			if (size == 0) reset();
			return (element);
		}
	}
	size_t get_size()
	{
		return size;
	}
};