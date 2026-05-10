#pragma once
#include "FirendFunctoins.h"
using namespace std;

namespace fireinds
{
	class a
	{
	public:
		int data;
	};
	class child1 : virtual public a
	{
	};
	class child2 : virtual public a
	{
	};
	class GrandChild2 : public child1, public child2
	{
		int Alldata()
		{
			return data;
		}
	};
}