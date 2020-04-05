#pragma once
#include "Leaf.h";
#include "Stack.h";

template <typename key_type, typename value_type>
class map
{
private:
	Leaf<key_type, value_type>* contains(key_type key);
	Leaf<key_type, value_type>* root;
	Leaf<key_type, value_type>* Null;
	class dtf_iterator
	{
		Leaf<key_type, value_type>* current;
		Stack<key_type, value_type> stack;
	public:
		dtf_iterator(Leaf<key_type, value_type>* argroot)
		{
			current = argroot;
		}
		Leaf<key_type, value_type>* next();
		bool has_next();
	};
	dtf_iterator* create_dtf_iterator()
	{
		return new dtf_iterator(root);
	};
	Leaf<key_type, value_type>* get_grandfather(Leaf<key_type, value_type>* current);
	Leaf<key_type, value_type>* get_uncle(Leaf<key_type, value_type>* current);
	Leaf<key_type, value_type>* get_sibling(Leaf<key_type, value_type>* current);
	void rotate_to_the_left(Leaf<key_type, value_type>* current);
	void rotate_to_the_right(Leaf<key_type, value_type>* current);
	void insert1(Leaf<key_type, value_type>* current);
	void insert2(Leaf<key_type, value_type>* current);
	void insert3(Leaf<key_type, value_type>* current);
	void insert4(Leaf<key_type, value_type>* current);
	void insert5(Leaf<key_type, value_type>* current);
	void remove1(Leaf<key_type, value_type>* current);
	void remove2(Leaf<key_type, value_type>* current);
	void remove3(Leaf<key_type, value_type>* current);
	void remove4(Leaf<key_type, value_type>* current);
	void remove5(Leaf<key_type, value_type>* current);
	void remove6(Leaf<key_type, value_type>* current);
public:
	map();
	~map();
	Leaf<key_type, value_type>* get_root();
	void insert(key_type key, value_type value);
	void remove(key_type key);
	void clear();
	void get_keys();
	void get_values();
	void print();
};

#include "Map.inl";