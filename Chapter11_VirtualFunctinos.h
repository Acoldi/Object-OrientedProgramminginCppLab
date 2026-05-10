#pragma once


#include <iostream>
#include <string.h>
#include "FirendFunctoins.h"
#include "VirtualPublic.h"
#include <cstring>


namespace chapter11VirtualFunctions
{
	namespace frengl
	{
		class distance
		{
		private:
			float inches;
			short feet;
		public:
			distance() : inches(0), feet(0) {}

			distance(float distance) {
				feet = (short)distance;
				inches = 12 * (distance - feet);
			}

			distance(float inches, short feet) {
				this->feet = feet;
				this->inches = inches;
			}

			void showdist() //display distance
			{
				cout << feet << "\' - " << inches << "\'";
			}

			distance operator + (distance d)
			{
				distance r;
				r.feet = feet + d.feet;
				r.inches = inches + d.inches;

				if (r.inches >= 12) {
					r.feet++;
					r.inches -= 12;
				}
				return r;
			}

			friend distance operator + (distance, distance);
		};

		distance operator + (distance a, distance b)
		{
			distance r;
			r.feet = a.feet + b.feet;
			r.inches = a.inches + b.inches;

			if (r.inches >= 12) {
				r.feet++;
				r.inches -= 12;
			}
			return r;
		}

		void main()
		{
			distance a(6, 12);
			distance b(6, 12);

			distance r = 12.7 + b;
			//distance r = a + b;

			r.showdist();
		}
	}

	namespace statfunc {
		class gamma
		{
		public:
			gamma()
			{
				total++;
				id = total;
			};
			~gamma()
			{
				total--;
				cout << "Id number: " << id << " destroyed\n";
			};

			static void showTotal() {
				cout << "total is: " << total << endl;
			}
			void showId() {
				cout << "ID is: " << id << endl;
			}

		private:
			static int total;
			int id;
		};
		int gamma::total = 0;

		void main()
		{
			gamma g1;
			gamma::showTotal();
			gamma* g2 = new gamma;
			gamma g3;

			//gamma::showTotal();
			g1.showTotal();
			g1.showId();
			g2->showId();
			g3.showId();

			cout << "----- (destroying object 2 manually) ---\n";
			delete g2;
			cout << "------------ End of program ----------\n";
		}
	}

	namespace STRIMEM {
		class strCount //keep track of number of unique strings
		{
		private:
			int count; //number of instances
			char* str; //pointer to string
			friend class String; //make ourselves available
			//member functions are private
			//--------------------------------------------------------------
			strCount(const char* s) //one-arg constructor
			{
				int length = strlen(s); //length of string argument
				str = new char[length + 1]; //get memory for string
				strcpy_s(str, length + 1, s); //copy argument to it
				count = 1; //start count at 1
			}
			//--------------------------------------------------------------
			~strCount() //destructor
			{
				delete[] str;
			} //delete the string
		};
		////////////////////////////////////////////////////////////////
		class String //String class
		{
		private:
			strCount* psc; //pointer to strCount
		public:
			String() //no-arg constructor
			{
				psc = new strCount("NULL");
			}
			//--------------------------------------------------------------
			String(const char* s) //1-arg constructor
			{
				psc = new strCount(s);
			}
			//--------------------------------------------------------------
			String(String& S) //copy constructor
			{
				psc = S.psc;
				(psc->count)++;
			}
			//--------------------------------------------------------------
			~String() //destructor
			{
				if (psc->count == 1) //if we are its last user,
					delete psc; // delete our strCount
				else // otherwise,
					(psc->count)--; // decrement its count
			}
			//--------------------------------------------------------------
			void display() //display the String
			{
				cout << psc->str; //print string
				cout << " (addr = " << psc << ")"; //print address
				cout << " (Count = " << psc->count << ")"; //print address
			}
			//--------------------------------------------------------------
			void operator = (String& S) //assign the string
			{
				if (psc->count == 1) //if we are its last user,
					delete psc; // delete our strCount
				else // otherwise,
					(psc->count)--; // decrement its count
				psc = S.psc; //use argument�s strCount
				(psc->count)++; //increment its count
			}
		};
		////////////////////////////////////////////////////////////////
		int main()
		{
			String s3 = "When the fox preaches, look to your geese.";
			cout << "\ns3 = "; s3.display(); //display s3
			String s1; //define String
			s1 = s3; //assign it another String
			cout << "\ns1 = "; s1.display(); //display it
			String s2(s3); //initialize with String
			cout << "\ns2 = "; s2.display(); //display it
			//string s4 = "Hello wold";
			cout << endl;
			return 0;
		}
	}

	namespace Exercise3
	{
		// clarray.cpp
		// creates array class
		using namespace std;
		////////////////////////////////////////////////////////////////
		class Array //models a normal C++ array
		{
		private:
			int* ptr; //pointer to Array contents
			int size; //size of Array
		public:
			Array(int s) //one-argument constructor
			{
				size = s; //argument is size of Array
				ptr = new int[s]; //make space for Array
			}
			~Array() //destructor
			{
				delete[] ptr;
			}
			int& operator [] (int j) //overloaded subscript operator
			{
				return *(ptr + j);
			}
			Array& operator = (Array& a)
			{
				delete[] ptr; // DELETE OLD PTR IF ANY

				ptr = new int[a.size];
				size = a.size;
				int j = 0;
				for (j; j < size; j++)
					*(ptr + j) = a[j]; // Or *(ptr+j) = *(a.ptr+j);

				return *this;
			}
			Array(Array& a)
			{
				ptr = new int[a.size];
				size = a.size;
				int j = 0;
				for (j; j < size; j++)
					*(ptr + j) = a[j];  // Or *(ptr+j) = *(a.ptr+j);
			}
		};
		////////////////////////////////////////////////////////////////
		int main()
		{
			const int ASIZE = 10; //size of array
			Array arr(ASIZE); //make an array
			int j = 0;
			for (j; j < ASIZE; j++) //fill it with squares
				arr[j] = j * j;
			Array arr2 = arr; // Assingment operator
			Array arr3(arr); // Copy constructor
			for (j = 0; j < ASIZE; j++) //display its contents
				cout << arr[j] << ' ';
			cout << endl;
			for (j = 0; j < ASIZE; j++)
				cout << arr2[j] << ' ';
			cout << endl;
			for (j = 0; j < ASIZE; j++)
				cout << arr3[j] << ' ';
			cout << endl;
			return 0;
		}
	}
}
