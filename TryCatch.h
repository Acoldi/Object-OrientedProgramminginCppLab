#pragma once

#include <iostream>
using namespace std;

namespace chapter14
{
	namespace TryCatch
	{
		const int SIZE = 3;
		class Stack
		{
			int top = -1;
			int array[SIZE];
		public:
			class full
			{
			public:
				const char* message = "Index above range";
			};
			class empty
			{
			public:
				const char* message = "Index below range";
			};

			void Push(int v)
			{
				if (top + 1 == SIZE)
					throw full();
				array[++top] = v;
			}
			int Pop()
			{
				if (top - 1 < 0)
					throw empty();
				return array[top--];
			}
		};

		void main()
		{
			Stack s1;
			Stack s2;

			try
			{
				s1.Push(0);
				s1.Push(1);
				s1.Push(2);
				s1.Push(3);
			}
			catch (Stack::full fullExc)
			{
				cout << fullExc.message;
			}
			catch (Stack::empty emptyEx)
			{
				cout << emptyEx.message;
			}

		}
	}
}