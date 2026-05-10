#pragma once
#include <iostream>

using namespace std;
namespace FirendFunctions
{
	class b;
	class a
	{
	public:
		a() : data(9) {}
	private:
		int data;

		friend int totalsum(a, b);
	};
	class b
	{
	public:
		b() : data(9) {}
	private:
		int data;

		friend int totalsum(a, b);
	};
	int totalsum(a a, b b)
	{
		return a.data + b.data;
	}

	void main()
	{
		a a;
		b b;

		cout << totalsum(a, b);
	}
}