#pragma once
template <typename key_type, typename value_type>
class Leaf
{
public:
	Leaf(key_type key, value_type value, Leaf* parent = nullptr, Leaf* left_son = nullptr, Leaf* right_son = nullptr)
	{
		this->key = key;
		this->value = value;
		this->left_son = left_son;
		this->right_son = right_son;
		this->parent = parent;
		this->black = 0;
	};
	~Leaf() {};
	key_type key;
	value_type value;
	Leaf* left_son;
	Leaf* right_son;
	Leaf* parent;
	int black;
};