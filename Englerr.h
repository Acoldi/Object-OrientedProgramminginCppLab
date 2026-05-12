#pragma once
#include <iostream>
#include <string>
#include <cstdlib> //for atoi(), atof()
using namespace std;

namespace chapter12_StreamAndfiles
{
	namespace Englerr {

	int IsFeet(string);

	class Distance
	{
	private:
		float inches;
		int feet;
	public:
		Distance() : inches(0.0), feet(0)
		{
		}
		Distance(float inches, int Feets)
		{
			inches = inches;
			feet = Feets;
		}
		void SowDistance()
		{
			cout << feet << "\' - " << inches << '\"' << endl;
		}
		void Getdistance();
	};

	void Distance::Getdistance()
	{
		string sfeet;


		while (true)
		{
			cout << "Feet: ";
			cin.unsetf(ios::skipws);
			cin >> sfeet;
			if (IsFeet(sfeet))
			{
				cin.ignore(10, '\n');
				feet = atoi(sfeet.c_str());
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Try again" << endl;
		}
		while (true)
		{
			cout << endl << "Inches: ";
			cin.unsetf(ios::skipws);
			cin >> inches;
			if (inches > 12.0 || inches < 0.0)
			{
				cin.clear(ios::failbit);
			}
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
			cout << "try again" << endl;
		}


	};

	int IsFeet(string feet)
	{
		short lenght = feet.length();
		if (lenght == 0 || lenght > 5)
			return 0;

		for (short i = 0; i < feet.length(); i++)
		{
			if (feet[i] > '9' || feet[i] < '0')
				return 0;
		}
		double n = atof(feet.c_str());
		if (n > 999 || n < 0)
			return 0;
		return 1;
	}

	void Main()
	{
		Distance d; //make a Distance object
		char ans;
		do
		{
			d.Getdistance(); //get its value from user
			cout << "\nDistance = ";
			d.SowDistance(); //display it
			cout << "\nDo another(y / n) ? ";
			cin >> ans;
			cin.ignore(10, '\n'); //eat chars, including newline
		} while (ans != 'n'); //cycle until 'n'
	}
	}
}