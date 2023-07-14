#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

class BinaryTrie
{
private:
	struct node
	{
		node *left;
		node *right;
		ll cnt;
	};
	node *root;

public:
	BinaryTrie()
	{
		root = create();
	}
	node *create()
	{
		node *Node = new node;
		Node->left = NULL;
		Node->right = NULL;
		Node->cnt = 0;
		return Node;
	}
	void add(ll num)
	{
		bitset<32> bs(num);
		node *curr = root;
		for (ll i = 31; i >= 0; i--)
		{
			curr->cnt = curr->cnt + 1;
			if (bs[i] == 1)
			{
				if (curr->right == NULL)
				{
					curr->right = create();
				}
				curr = curr->right;
			}
			else
			{
				if (curr->left == NULL)
				{
					curr->left = create();
				}
				curr = curr->left;
			}
		}
		curr->cnt = curr->cnt + 1;
	}
	void erase(ll num)
	{
		bitset<32> bs(num);
		node *curr = root;
		for (ll i = 31; i >= 0; i--)
		{
			curr->cnt = curr->cnt - 1;
			if (bs[i] == 1)
			{
				curr = curr->right;
			}
			else
			{
				curr = curr->left;
			}
		}
		curr->cnt = curr->cnt - 1;
	}
	ll queryMAX(ll num)
	{
		bitset<32> bs(num);
		node *curr = root;
		ll mx = 0;
		for (ll i = 31; i >= 0; i--)
		{
			ll mask = (1LL << i);
			if (bs[i] == 1)
			{
				if (curr->left != NULL && curr->left->cnt != 0)
				{
					curr = curr->left;
				}
				else if (curr->right != NULL && curr->right->cnt != 0)
				{
					mx = mx | mask;
					curr = curr->right;
				}
			}
			else
			{
				if (curr->right != NULL && curr->right->cnt != 0)
				{
					mx = mx | mask;
					curr = curr->right;
				}
				else if (curr->left != NULL && curr->left->cnt != 0)
					curr = curr->left;
			}
		}
		return num ^ mx;
	}
};

int main(){

    return 0;
}