#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Chain
{

	int _d = 0;

public:
	vector<int> root_chain;

	int getLength()
	{
		return root_chain.size();

	}

	Chain() {

	}

	Chain(int n, int m)
	{
		int a = n;
		int module = pow(2, (round(m))) - 1;
		root_chain.push_back(a);
		while (true)
		{
			a = (a * 2) % module;
			if (a == n) break;
			root_chain.push_back(a);
		}
		sort(root_chain.begin(), root_chain.end());
		
	}

	friend Chain operator +(Chain& lhs, Chain& rhs)
	{
		lhs.root_chain.insert(lhs.root_chain.end(), rhs.root_chain.begin(), rhs.root_chain.end());
		sort(lhs.root_chain.begin(), lhs.root_chain.end());
		return lhs;
	}

	int GetD()
	{

	}

	~Chain()
	{
	}
	friend ostream& operator<<(ostream& os, const Chain& ch);
};

ostream& operator<<(ostream& os, const Chain& ch)
{
	for (int i = 0; i < ch.root_chain.size(); i++)
	{
		os << ch.root_chain[i] << " ";
	}
	os << endl;
	return os;
}
