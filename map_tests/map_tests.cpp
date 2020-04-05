#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "../Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace maptests
{
	TEST_CLASS(maptests)
	{
	public:
		TEST_METHOD(insert0)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			try
			{
				Map.insert(3, 1);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("not a unique key", e.what());
			}
		}

		TEST_METHOD(insert1)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Leaf<int, int>* root = Map.get_root();
			Assert::AreEqual(root->black, 1);
			Assert::AreEqual(root->key, 3);
			Assert::AreEqual(root->value, 5);
			Assert::AreEqual(root->left_son->key, 0);
			Assert::AreEqual(root->right_son->key, 0);


		}

		TEST_METHOD(insert2)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Map.insert(2, 6);
			Leaf<int, int>* root = Map.get_root();
			Assert::AreEqual(root->black, 1);
			Assert::AreEqual(root->key, 3);
			Assert::AreEqual(root->value, 5);
			Assert::AreEqual(root->left_son->black, 0);
			Assert::AreEqual(root->left_son->key, 2);
			Assert::AreEqual(root->left_son->value, 6);
			Assert::AreEqual(root->right_son->key, 0);
			Assert::AreEqual(root->left_son->left_son->key, 0);
			Assert::AreEqual(root->left_son->right_son->key, 0);
		}

		TEST_METHOD(insert3)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Map.insert(2, 6);
			Map.insert(4, 7);
			Map.insert(-1, 8);
			Leaf<int, int>* root = Map.get_root();
			Assert::AreEqual(root->black, 1);
			Assert::AreEqual(root->key, 3);
			Assert::AreEqual(root->left_son->black, 1);
			Assert::AreEqual(root->left_son->key, 2);
			Assert::AreEqual(root->right_son->black, 1);
			Assert::AreEqual(root->right_son->key, 4);
			Assert::AreEqual(root->left_son->left_son->black, 0);
			Assert::AreEqual(root->left_son->left_son->key, -1);
			Assert::AreEqual(root->left_son->right_son->key, 0);
			Assert::AreEqual(root->left_son->left_son->left_son->key, 0);
			Assert::AreEqual(root->left_son->left_son->right_son->key, 0);
			Assert::AreEqual(root->right_son->right_son->key, 0);
			Assert::AreEqual(root->right_son->left_son->key, 0);
		}

		TEST_METHOD(insert4_5)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Map.insert(2, 6);
			Map.insert(4, 7);
			Map.insert(-1, 8);
			Map.insert(1, 5);
			Leaf<int, int>* root = Map.get_root();
			Assert::AreEqual(root->black, 1);
			Assert::AreEqual(root->key, 3);
			Assert::AreEqual(root->left_son->black, 1);
			Assert::AreEqual(root->left_son->key, 1);
			Assert::AreEqual(root->right_son->black, 1);
			Assert::AreEqual(root->right_son->key, 4);
			Assert::AreEqual(root->left_son->left_son->black, 0);
			Assert::AreEqual(root->left_son->left_son->key, -1);
			Assert::AreEqual(root->left_son->right_son->black, 0);
			Assert::AreEqual(root->left_son->right_son->key, 2);
			Assert::AreEqual(root->left_son->left_son->left_son->key, 0);
			Assert::AreEqual(root->left_son->left_son->right_son->key, 0);
			Assert::AreEqual(root->left_son->right_son->left_son->key, 0);
			Assert::AreEqual(root->left_son->right_son->right_son->key, 0);
			Assert::AreEqual(root->right_son->right_son->key, 0);
			Assert::AreEqual(root->right_son->left_son->key, 0);
		}

		TEST_METHOD(remove0)
		{
			map<int, int> Map;
			try
			{
				Map.remove(5);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("empty map", e.what());
			}
		}

		TEST_METHOD(remove01)
		{
			map<int, int> Map;
			Map.insert(2, 2);
			try
			{
				Map.remove(7);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("not found", e.what());
			}
		}

		TEST_METHOD(remove1)
		{
			map<int, int> Map;
			Map.insert(2, 2);
			Map.insert(1, 4);
			Map.insert(3, 4);
			Map.remove(2);
			Assert::AreEqual(Map.get_root()->key, 1);
			Assert::AreEqual(Map.get_root()->black, 1);
			Assert::AreEqual(Map.get_root()->right_son->key, 3);
			Assert::AreEqual(Map.get_root()->right_son->black, 0);
			Assert::AreEqual(Map.get_root()->left_son->key, 0);
		}

		TEST_METHOD(remove2)
		{
			map<int, int> Map;
			Map.insert(5, 2);
			Map.insert(3, 4);
			Map.insert(7, 4);
			Map.insert(1, 4);
			Map.insert(4, 4);
			Map.insert(6, 4);
			Map.insert(8, 4);
			Map.insert(0, 4);
			Map.remove(0);
			Map.remove(6);
			Map.remove(8);
			Map.remove(7);
			Assert::AreEqual(Map.get_root()->key, 3);
			Assert::AreEqual(Map.get_root()->black, 1);
			Assert::AreEqual(Map.get_root()->right_son->key, 5);
			Assert::AreEqual(Map.get_root()->right_son->black, 1);
			Assert::AreEqual(Map.get_root()->left_son->key, 1);
			Assert::AreEqual(Map.get_root()->left_son->black, 1);
			Assert::AreEqual(Map.get_root()->right_son->right_son->key, 0);
			Assert::AreEqual(Map.get_root()->right_son->left_son->key, 4);
			Assert::AreEqual(Map.get_root()->right_son->left_son->black, 0);
			Assert::AreEqual(Map.get_root()->right_son->left_son->left_son->key, 0);
			Assert::AreEqual(Map.get_root()->right_son->left_son->right_son->key, 0);
			Assert::AreEqual(Map.get_root()->right_son->right_son->key, 0);
			Assert::AreEqual(Map.get_root()->left_son->right_son->key, 0);
			Assert::AreEqual(Map.get_root()->left_son->left_son->key, 0);

		}

		TEST_METHOD(remove3)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Map.insert(2, 6);
			Map.insert(4, 7);
			Map.insert(-1, 8);
			Map.remove(-1);
			Map.remove(2);
			Assert::AreEqual(Map.get_root()->key, 3);
			Assert::AreEqual(Map.get_root()->black, 1);
			Assert::AreEqual(Map.get_root()->right_son->key, 4);
			Assert::AreEqual(Map.get_root()->right_son->black, 0);
			Assert::AreEqual(Map.get_root()->left_son->key, 0);
		}

		TEST_METHOD(remove4)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Map.insert(1, 6);
			Map.insert(5, 7);
			Map.insert(-1, 8);
			Map.remove(-1);
			Map.insert(2, 5);
			Map.insert(-1, 7);
			Map.insert(4, 5);
			Map.insert(6, 7);
			Map.insert(-7, 7);
			Map.remove(-7);
			Map.remove(-1);
			Assert::AreEqual(Map.get_root()->key, 3);
			Assert::AreEqual(Map.get_root()->black, 1);
			Assert::AreEqual(Map.get_root()->right_son->key, 5);
			Assert::AreEqual(Map.get_root()->right_son->black, 1);
			Assert::AreEqual(Map.get_root()->left_son->key, 1);
			Assert::AreEqual(Map.get_root()->left_son->black, 1);
			Assert::AreEqual(Map.get_root()->left_son->left_son->key, 0);
			Assert::AreEqual(Map.get_root()->left_son->right_son->key, 2);
			Assert::AreEqual(Map.get_root()->left_son->right_son->black, 0);
			Assert::AreEqual(Map.get_root()->left_son->right_son->black, 0);
		}

		TEST_METHOD(remove5_6)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Map.insert(1, 6);
			Map.insert(5, 7);
			Map.insert(-1, 8);
			Map.remove(-1);
			Map.insert(2, 5);
			Map.insert(-1, 7);
			Map.insert(4, 5);
			Map.insert(6, 7);
			Map.insert(-7, 7);
			Map.remove(-7);
			Map.remove(-1);
			Map.remove(4);
			Map.remove(6);
			Map.remove(5);
			Leaf<int, int>* root = Map.get_root();
			Assert::AreEqual(root->black, 1);
			Assert::AreEqual(root->key, 2);
			Assert::AreEqual(root->left_son->black, 1);
			Assert::AreEqual(root->left_son->key, 1);
			Assert::AreEqual(root->right_son->black, 1);
			Assert::AreEqual(root->right_son->key, 3);
			Assert::AreEqual(root->left_son->left_son->key, 0);
			Assert::AreEqual(root->left_son->right_son->key, 0);
			Assert::AreEqual(root->right_son->right_son->key, 0);
			Assert::AreEqual(root->right_son->left_son->key, 0);
		}

		TEST_METHOD(clear0)
		{
			map<int, int> Map;
			try
			{
				Map.clear();
			}
			catch (std::exception e)
			{
				Assert::AreEqual("not found", e.what());
			}
		}

		TEST_METHOD(clear1)
		{
			map<int, int> Map;
			Map.insert(3, 5);
			Map.insert(2, 6);
			Map.insert(4, 7);
			Map.insert(-1, 8);
			Map.insert(1, 5);
			Map.clear();
			Leaf<int, int>* root = Map.get_root();
			Leaf<int, int>* control = nullptr;
			Assert::AreEqual(root, control);
		}

		TEST_METHOD(clear2)
		{
			map<int, int> Map;
			try
			{
				Map.clear();
			}
			catch (std::exception e)
			{
				Assert::AreEqual("empty map", e.what());
			}
		}

		TEST_METHOD(get_keys)
		{
			map<int, int> Map;
			try
			{
				Map.get_keys();
			}
			catch (std::exception e)
			{
				Assert::AreEqual("empty map", e.what());
			}
		}

		TEST_METHOD(get_values)
		{
			map<int, int> Map;
			try
			{
				Map.get_values();
			}
			catch (std::exception e)
			{
				Assert::AreEqual("empty map", e.what());
			}
		}

		TEST_METHOD(print)
		{
			map<int, int> Map;
			try
			{
				Map.print();
			}
			catch (std::exception e)
			{
				Assert::AreEqual("empty map", e.what());
			}
		}

	};

}
