#include "Map.h"

template <typename key_type, typename value_type>
Leaf<key_type, value_type>* map<key_type, value_type>::contains(key_type key)
{
	Leaf<key_type, value_type>* current = root;
	if (root == nullptr) { return Null; }
	while (current != Null)
	{
		if (current->key == key) break;
		if (current->key < key)
			current = current->right_son;
		else
			current = current->left_son;
	}
	return current;
};

template <typename key_type, typename value_type>
Leaf<key_type, value_type>* map<key_type, value_type>::dtf_iterator::next()
{
	while (!((current->left_son == nullptr) && (current->right_son == nullptr)))
	{
		stack.push(current);
		current = current->left_son;
	}
	current = stack.pop();
	Leaf<key_type, value_type>* leaf = current;
	current = current->right_son;
	return leaf;
};

template <typename key_type, typename value_type>
bool map<key_type, value_type>::dtf_iterator::has_next()
{
	return ((stack.get_size() != 0) || !((current->left_son == nullptr) && (current->right_son == nullptr)));
};

template <typename key_type, typename value_type>
Leaf<key_type, value_type>* map<key_type, value_type>::get_grandfather(Leaf<key_type, value_type>* current)
{
	if ((current != Null) && (current->parent != nullptr))
		return current->parent->parent;
	else
		return nullptr;
};

template <typename key_type, typename value_type>
Leaf<key_type, value_type>* map<key_type, value_type>::get_uncle(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* grandfather = get_grandfather(current);
	if (grandfather == nullptr)
		return nullptr;
	if (current->parent == grandfather->left_son)
		return grandfather->right_son;
	else return grandfather->left_son;
};

template <typename key_type, typename value_type>
Leaf<key_type, value_type>* map<key_type, value_type>::get_sibling(Leaf<key_type, value_type>* current)
{
	if (current == current->parent->left_son)
		return current->parent->right_son;
	else
		return current->parent->left_son;
}

template <typename key_type, typename value_type>
void map<key_type, value_type>::rotate_to_the_left(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* pivot = current->right_son;
	pivot->parent = current->parent;
	if (root == current)
	{
		root = pivot;
	}
	if (current->parent != nullptr)
	{
		if (current->parent->left_son == current)
		{
			current->parent->left_son = pivot;
		}
		else
		{
			current->parent->right_son = pivot;
		}
	}
	current->right_son = pivot->left_son;
	if ((pivot->left_son != Null)/*&&(pivot->left_son!=nullptr)*/)
		pivot->left_son->parent = current;
	current->parent = pivot;
	pivot->left_son = current;
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::rotate_to_the_right(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* pivot = current->left_son;
	pivot->parent = current->parent;
	if (root == current)
	{
		root = pivot;
	}
	if (current->parent != nullptr)
	{
		if (current->parent->left_son == current)
		{
			current->parent->left_son = pivot;
		}
		else
		{
			current->parent->right_son = pivot;
		}
	}
	current->left_son = pivot->right_son;
	if (pivot->right_son != Null) 
	{
		pivot->right_son->parent = current;
	}
	current->parent = pivot;
	pivot->right_son = current;
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::insert1(Leaf<key_type, value_type>* current)
{
	if (current->parent == nullptr)
		current->black = 1;
	else
		insert2(current);
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::insert2(Leaf<key_type, value_type>* current)
{
	if (current->parent->black == 1)
		return;
	else
		insert3(current);
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::insert3(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* uncle = get_uncle(current);
	if ((uncle->black == 0) && (uncle != Null))
	{
		current->parent->black = 1;
		uncle->black = 1;
		Leaf<key_type, value_type>* grandfather = get_grandfather(current);
		grandfather->black = 0;
		insert1(grandfather);
	}
	else insert4(current);
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::insert4(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* grandfather = get_grandfather(current);
	if ((current == current->parent->right_son) && (current->parent == grandfather->left_son))
	{
		rotate_to_the_left(current->parent);
		current = current->left_son;
	}
	else if ((current == current->parent->left_son) && (current->parent == grandfather->right_son))
	{
		rotate_to_the_right(current->parent);
		current = current->right_son;
	}
	insert5(current);
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::insert5(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* grandfather = get_grandfather(current);
	current->parent->black = 1;
	grandfather->black = 0;
	if ((current = current->parent->left_son) && (current->parent = grandfather->left_son))
		rotate_to_the_right(grandfather);
	else
		rotate_to_the_left(grandfather);
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::remove1(Leaf<key_type, value_type>* current)
{
	if (current->parent != nullptr)
		remove2(current);
}

template <typename key_type, typename value_type>
void map<key_type, value_type>::remove2(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* sibling = get_sibling(current);
	if (sibling->black == 0)
	{
		current->parent->black = 0;
		sibling->black = 1;
		if (current == current->parent->left_son)
			rotate_to_the_left(current->parent);
		else
			rotate_to_the_right(current->parent);
	}
	remove3(current);
}

template <typename key_type, typename value_type>
void map<key_type, value_type>::remove3(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* sibling = get_sibling(current);
	if ((current->parent->black == 1)&&(sibling->black == 1) && (sibling->left_son->black == 1) && (sibling->right_son->black == 1))
	{
		sibling->black = 0;
		remove1(current->parent);
	}
	else
		remove4(current);
}

template <typename key_type, typename value_type>
void map<key_type, value_type>::remove4(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* sibling = get_sibling(current);
	if ((current->parent->black == 0) && (sibling->black == 1) && (sibling->left_son->black == 1) && (sibling->right_son->black == 1))
	{
		sibling->black = 0;
		current->parent->black = 1;
	}
	else
		remove5(current);
}

template <typename key_type, typename value_type>
void map<key_type, value_type>::remove5(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* sibling = get_sibling(current);
	if ((current == current->parent->left_son) && (sibling->right_son->black == 1))
	{
		sibling->black = 0;
		sibling->left_son->black = 1;
		rotate_to_the_right(sibling);
	}
	else if ((current == current->parent->right_son) && (sibling->left_son->black == 1))
	{
		sibling->black = 0;
		sibling->right_son->black = 1;
		rotate_to_the_left(sibling);
	}
		remove6(current);
}

template <typename key_type, typename value_type>
void map<key_type, value_type>::remove6(Leaf<key_type, value_type>* current)
{
	Leaf<key_type, value_type>* sibling = get_sibling(current);
	sibling->black = current->parent->black;
	current->parent->black = 1;
	if (current = current->parent->left_son)
	{
		sibling->right_son->black = 1;
		rotate_to_the_left(current->parent);
	}
	else
	{
		sibling->left_son->black = 1;
		rotate_to_the_right(current->parent);
	}
}

template <typename key_type, typename value_type>
map<key_type, value_type>::map()
{
	root = nullptr;
	Null = new Leaf<key_type, value_type>(0, 0);
	Null->black = 1;
};

template <typename key_type, typename value_type>
map<key_type, value_type>::~map()
{
	clear();
}

template <typename key_type, typename value_type>
void map<key_type, value_type>::insert(key_type key, value_type value)
{
	if (root == nullptr)
	{
		root = new Leaf<key_type, value_type>(key, value, nullptr, Null, Null);
		insert1(root);
	}
	else
	{
		if (contains(key) != Null)
		{
			try
			{
				throw exception("not a unique key");
			}
			catch (const exception & err)
			{
				cout << "The Map already contains this key";
				return;
			}
		}
		Leaf<key_type, value_type>* current = root;
		Leaf<key_type, value_type>* next = root;
		while (next != Null)
		{
			current = next;
			if (key < current->key)
				next = current->left_son;
			else
				next = current->right_son;
		}
		if (key < current->key)
		{
			current->left_son = new Leaf<key_type, value_type>(key, value, current, Null, Null);
			insert2(current->left_son);
		}
		else {
			current->right_son = new Leaf<key_type, value_type>(key, value, current, Null, Null);
			insert2(current->right_son);
		}
	}
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::remove(key_type key)
{
	if (root == nullptr)
	{
		try
		{
			throw exception("empty map");
		}
		catch (const exception & err)
		{
			cout << "Can't proceed with operation. The map is empty";
			return;
		}
	}
	Leaf<key_type, value_type>* to_remove = contains(key);
	if (to_remove == Null)
	{
		try
		{
			throw exception("not found");
		}
		catch (const exception & err)
		{
			cout << "Can't proceed with operation. The map doesn't contain this key";
			return;
		}
	}
	Leaf<key_type, value_type>* child;
	if ((to_remove->left_son != Null) && (to_remove->right_son != Null))
	{
		Leaf<key_type, value_type>* current = to_remove->left_son;
		Leaf<key_type, value_type>* next = current->right_son;
		Leaf<key_type, value_type>* child = Null;
		while (next != Null)
		{
			current = next;
			next = current->right_son;
		}
		to_remove->key = current->key;
		to_remove->value = current->value;
		to_remove = current;
	}
	if ((to_remove->left_son != Null)|| (to_remove->right_son != Null))
	{
		if (to_remove->left_son != Null)
		{
			child = to_remove->left_son;
		}
		else 
		{
			child = to_remove->right_son;
		}
		child->parent = to_remove->parent;
		if (to_remove == to_remove->parent->left_son)
		{
			to_remove->parent->left_son = child;
		}
		else
		{
			to_remove->parent->right_son = child;
		}
		if (to_remove->black == 1)
		{
			if (child->black == 0)
				child->black = 1;
			else
				remove1(child);
		}
		delete to_remove;
	}
		else
		{
		Leaf<key_type, value_type>* Null_ = new Leaf<key_type, value_type>(0, 0, to_remove->parent, Null, Null);
		Null_->black = 1;
		if (to_remove == to_remove->parent->left_son)
		{
			to_remove->parent->left_son = Null_;
		}
		else
		{
			to_remove->parent->right_son = Null_;
		}
		if (to_remove->black == 1)
		{
			remove1(Null_);
		}
		if (Null_ == Null_->parent->left_son)
			Null_->parent->left_son = Null;
		else
			Null_->parent->right_son = Null;
		delete to_remove;
		}
};


template <typename key_type, typename value_type>
void map<key_type, value_type>::clear()
{
	if (root == nullptr)
	{
		try
		{
			throw exception("empty map");
		}
		catch (const exception & err)
		{
			cout << "Can't proceed with operation. The map is empty";
			return;
		}
	}
	dtf_iterator* iterator = create_dtf_iterator();
	while (iterator->has_next())
	{
		Leaf<key_type, value_type>* current = iterator->next();
		delete current;
	}
	delete Null;
	root = nullptr;
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::get_keys()
{
	if (root == nullptr)
	{
		try
		{
			throw exception("empty map");
		}
		catch (const exception & err)
		{
			cout << "Can't proceed with operation. The map is empty";
			return;
		}
	}
	cout << '\n' << "the list of keys: ";
	dtf_iterator* iterator = create_dtf_iterator();
	while (iterator->has_next())
	{
		Leaf<key_type, value_type>* current = iterator->next();
		cout << current->key << " ";
	}
};

template <typename key_type, typename value_type>
void map<key_type, value_type>::get_values()
{
	if (root == nullptr)
	{
		try
		{
			throw exception("empty map");
		}
		catch (const exception & err)
		{
			cout << "Can't proceed with operation. The map is empty";
			return;
		}
	}
	cout << '\n' << "the list of values: ";
	dtf_iterator* iterator = create_dtf_iterator();
	while (iterator->has_next())
	{
		Leaf<key_type, value_type>* current = iterator->next();
		cout << current->value << " ";
	}
};


template <typename key_type, typename value_type>
void map<key_type, value_type>::print()
{
	if (root == nullptr)
	{
		try
		{
			throw exception("empty map");
		}
		catch (const exception & err)
		{
			cout << "Can't proceed with operation. The map is empty";
			return;
		}
	}
	cout << '\n' << "the map contains: " << '\n' << setw(10) << left << "key" << setw(10) << left << "value" << '\n';
	dtf_iterator* iterator = create_dtf_iterator();
	while (iterator->has_next())
	{
		Leaf<key_type, value_type>* current = iterator->next();
		cout << setw(10) << left << current->key << setw(10) << left << current->value << '\n';
	}
};

template <typename key_type, typename value_type>
Leaf<key_type, value_type>* map<key_type, value_type>::get_root()
{
	return root;
};