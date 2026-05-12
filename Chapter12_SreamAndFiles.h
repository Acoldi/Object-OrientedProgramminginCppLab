#pragma once


#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include "Englerr.h"


using namespace std;

namespace chapter12_StreamAndfiles
{
	namespace Formatto
	{
		inline void Main()
		{
			string h = "Hello";
			string w = "World";
			double d = 100.3;
			int i = 9;

			ofstream file("Text.txt");
			file << h << ' ' << w << ' ' << d << ' ' << i;
		}
	}
	namespace Formati
	{
		inline void Main(){
			ifstream file("Text.txt");
			string h;
			string w;
			double d;
			int i;

			file >> h >> w >> d >> i;

			cout << "h: " << h << endl;
			cout << "w: " << w << endl;
			cout << "d: " << d << endl;
			cout << "i: " << i << endl;
			cout << "i + 2: " << i + 2 << endl;
		}
	}

	inline void oline() {
		ofstream file("Text.txt");
		file << "Hello world\n";
		file << "This is A world where you can write into files\n";
	}
	inline void iline() {
		const int Max = 100;
		char buffer[Max];
		ifstream file("Text.txt");
		while (file.good()) {
			file.getline(buffer, Max);
			cout << buffer << endl;
		}
	}
	inline void ichar2()
	{
		ifstream file("Text.txt");
		cout << file.rdbuf();
	}
	inline void binio() {
		const int SIZE = 100;
		int buff[SIZE];

		for (short i = 0; i < SIZE; i++)
			buff[i] = i;

		ofstream file("edata.dat", ios::binary);
		file.write(reinterpret_cast<char*>(buff), SIZE * sizeof(int));
		file.close();

		for (short i = 0; i < SIZE; i++)
			buff[i] = 0;

		ifstream ifile("edata.dat", ios::binary);
		ifile.read(reinterpret_cast<char *>(buff), SIZE * sizeof(int));

		for (short i = 0; i < SIZE; i++)
		{
			cout << buff[i] + 100 << " ";
			if (buff[i] != i) {
				cout << "data is incorrect";
				return;
			}
			
		}
		cout << "data is correct";
	}
	inline void iopers() {
		class person {
		private:
			short age;
			char name[80];
			//string name;
		public:
			void getdata()
			{
				cout << "age: "; cin >> age; cout << endl;
				cout << "name: "; cin >> name; cout << endl;
			}
			void showdata()
			{
				cout << "name: "; cout << name << endl;
				cout << "age: "; cout << age << endl;
			}
		};

		person per;
		per.getdata();

		//ofstream opersondata("Objects/PERSON.DAT", ios::binary);
		ofstream opersondata("PERSON.DAT", ios::binary);
		opersondata.write(reinterpret_cast<char*>(&per), sizeof(per));
		opersondata.close();

		person rper;
		ifstream ipersondata("PERSON.DAT", ios::binary);
		ipersondata.read(reinterpret_cast<char*>(&rper), sizeof(person));
		rper.showdata();
		ipersondata.close();
	}
	class person {
	private:
		short age;
		char name[80];
	public:
		void getdata()
		{
			string sage = "";
			cin.unsetf(ios::skipws);
			cout << "age: ";
			cin >> age;
			while (!cin.good())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "age: ";
				cin >> age;
				};
			cin.ignore(100, '\n');
			cout << "name: "; cin >> name;
			cin.ignore(20, '\n');
			cin.clear();
		}
		void showdata()
		{
			cout << "\nname: "; cout << name << endl;
			cout << "age: "; cout << age << endl;
		}
		void diskOut();
		void diskIn(int);
		static int diskCount();
	private:
		bool IsNumber(string num)
		{
			for (short i = 0; i < num.length(); i++)
			{
				if (num[i] > '9' || num[i] < '0')
					return 0;
			}
			return 1;
		}
	};
	const string persFileDat = "PERSFILE.DAT";
	void person::diskOut()
	{
		ofstream os;
		os.open(persFileDat, ios::app | ios::binary);
		os.write((char*)this, sizeof(*this));
	}
	void person::diskIn(int i)
	{
		ifstream is;
		is.open(persFileDat, ios::binary);
		is.seekg(i * sizeof(*this));
		is.read((char*)this, sizeof(*this));
	}
	int person::diskCount()
	{
		ifstream is;
		is.open(persFileDat, ios::binary);
		is.seekg(0, ios::_Seekend);
		int count = is.tellg() / sizeof(person);
		return count;
	}

	inline void DISKFUN()
	{
		person per;
		char ans = 'y';
		fstream file;
		file.open("GROUP.DAT", ios::app | ios::out | ios::in | ios::binary);
		do
		{
			cout << "Enter person data:\n";
			per.getdata();
			file.write(reinterpret_cast<char*>(&per), sizeof(person));

			cin.setf(ios::skipws);
			cout << "\nEnter another person? (y, n)\n- "; cin >> ans;
			cin.ignore(10, '\n');
		
		} while (tolower(ans) == 'y');

		cout << endl;
		file.seekg(0);
		while (file.good())
		{
			cout << "person:\n";
			per.showdata();
			file.read(reinterpret_cast<char*>(&per), sizeof(person));
		}
		file.close();
	}

	person getPersonAt(int i);
	inline void seekg()
	{
		person per;
		cout << "Index of person: ";
		short i; cin >> i;
		per = getPersonAt(i);
		per.showdata();
	}
	person getPersonAt(int i)
	{
		i--;
		ifstream file;
		file.open("GROUP.DAT", ios::in);

		file.seekg(0, file._Seekend);
		int count = file.tellg() / sizeof(person);
		file.clear();

		if (i > count || i < 0)
		{
			cerr << "Out of index";
			exit(1);
		}

		person per;
		file.seekg(i * sizeof(person));
		file.read((char*)&per, sizeof(per));

		return per;
	}
	inline void REWOBJECT()
	{
		person per;
		while (true)
		{
			per.getdata();
			per.diskOut();
			cout << "Do another?\n";
			char ans; cin >> ans;
			cin.ignore(10, '\n');
			if (ans == 'n')
				break;
		}
		short count = per.diskCount() ;
		cout << "There are " << count << " Persons\n";
		for (short i = 1; i <= count; i++)
		{
			per.diskIn(i - 1);
			per.showdata();
			cout << endl;
		}
	}
	namespace empl_io
	{
		#include <typeinfo>

		const int LEN = 32;
		const int MAXEM = 100;
		string fileName = "EMPLOY.DAT";
		enum employee_type { tmanager, tscientist, tlaborer };
		////////////////////////////////////////////////////////////////
		class employee //employee class
		{
		protected:
			char name[LEN];
			static int n;
			static employee* arrayp[]; 
		public:
			unsigned long number;
			virtual void getdata()
			{
				cout << " Enter last name : "; cin >> name;
				cout << " Enter number : "; cin >> number;
			}
			virtual void putdata()
			{
				cout << "\n Name : " << name;
				cout << "\n Number : " << number;
			}
			virtual employee_type getType();
			static void add();
			static void display();
			static void read();
			static void write();
		};

		class manager : public employee
		{
		private:
			char title[LEN];
			double dues;
		public:
			void getdata()
			{
				employee::getdata();
				cout << " Enter title : "; cin >> title;
				cout << " Enter golf club dues : "; cin >> dues;
			}
			void putdata()
			{
				employee::putdata();
				cout << "\n Title : " << title;
				cout << "\n Golf club dues : " << dues;
			}
		};
		
		class scientist : public employee
		{
		private:
			int pubs;
		public:
			void getdata()
			{
				employee::getdata();
				cout << " Enter number of pubs : "; cin >> pubs;
			}
			void putdata()
			{
				employee::putdata();
				cout << "\n Number of publications : " << pubs;
			}
		};
		class laborer : public employee
		{
		};

		int employee::n = 0;
		employee* employee::arrayp[MAXEM];
		employee_type employee::getType()
		{
			if (typeid(*this) == typeid(manager)) return tmanager;
			else if (typeid(*this) == typeid(laborer)) return tlaborer;
			else if (typeid(*this) == typeid(scientist)) return tscientist;
			else { cout << "Wrong employee type\n"; exit(1); };
		}
		void employee::add()
		{
			employee* per;
			char ans;
			cout << " \'m' -- to add a manager\n";
			cout << " \'s' -- to add a scientist\n";
			cout << " \'l' -- to add a laborer\n";
			while (true)
			{
				cout << "\nEnter selection: ";
				cin >> ans;
				if (ans == 'm' || ans == 's' || ans == 'l')
					break;
			}

			switch (ans)
			{
			case 'm':
				arrayp[n] = new manager();
				break;
			case 's':
				arrayp[n] = new scientist();
				break;
			case 'l':
				arrayp[n] = new laborer();
				break;
			}

			arrayp[n]->getdata();
			n++;
		}
		void employee::display()
		{
			for (int i = 0; i < n; i++)
			{
				cout << "( " << i + 1 << " ). ";
				employee_type type = arrayp[i]->getType();
				switch (type)
				{
				case chapter12_StreamAndfiles::empl_io::tmanager:
					cout << "Manager:";
					break;
				case chapter12_StreamAndfiles::empl_io::tscientist:
					cout << "Scientist:";
					break;
				case chapter12_StreamAndfiles::empl_io::tlaborer:
					cout << "Laborer:";
					break;
				}
				arrayp[i]->putdata();
				cout << endl;
			}
		}
		void employee::read()
		{
			employee_type type;
			int size = 0;
			ifstream inf(fileName, ios::binary);
			if (!inf)
			{
				cerr << fileName << " File not open.";
				return;
			}
			n = 0;
			while (true)
			{
			inf.read((char*)&type, sizeof(type));
			if (inf.eof()) break;
			switch (type)
			{
			case chapter12_StreamAndfiles::empl_io::tmanager:
				arrayp[n] = new manager;
				size = sizeof(manager);
				break;
			case chapter12_StreamAndfiles::empl_io::tscientist:
				arrayp[n] = new scientist;
				size = sizeof(scientist);
				break;
			case chapter12_StreamAndfiles::empl_io::tlaborer:
				size = sizeof(laborer);
				arrayp[n] = new laborer;
				break;
			default:
				cerr << "UNKOWN TYPE IN FILE"; return;
			}
			inf.read((char*)arrayp[n], size);
			if (!inf)
			{
				cerr << "Can't read form file: " << fileName;
				return;
			}
			n++;



			//int size; //size of employee object
			//employee_type etype; //type of employee
			//ifstream inf; //open ifstream in binary
			//inf.open("EMPLOY.DAT", ios::binary);
			//if (!inf)
			//{
			//	cout << "\nCan’t open file\n"; return;
			//}
			//n = 0; //no employees in memory yet
			//while (true)
			//{ //read type of next employee
			//	inf.read((char*)&etype, sizeof(etype));
			//	if (inf.eof()) //quit loop on eof
			//		break;
			//	if (!inf) //error reading type
			//	{
			//		cout << "\nCan’t read type from file\n"; return;
			//	}
			//	switch (etype)
			//	{ //make new employee
			//	case tmanager: //of correct type
			//		arrayp[n] = new manager;
			//		size = sizeof(manager);
			//		break;
			//	case tscientist:
			//		arrayp[n] = new scientist;
			//		size = sizeof(scientist);
			//		break;
			//	case tlaborer:
			//		arrayp[n] = new laborer;
			//		size = sizeof(laborer);
			//		break;
			//	default: cout << "\nUnknown type in file\n"; return;
			//	} //read data from file into it
			//	inf.read((char*)arrayp[n], size);
			//	if (!inf) //error but not eof
			//	{
			//		cout << "\nCan’t read data from file\n"; return;
			//	}
			//	n++; //count employee
			}
		}

		void employee::write()
		{
			int size = 0;
			employee_type type;
			cout << "Writing " << n << " employees\n";
			ofstream os(fileName, ios::trunc | ios::binary);
			if (!os)
			{
				cout << fileName << " can't open\n";
				return;
			}

			for (int i = 0; i < n; i++)
			{
				type = arrayp[i]->getType();
				os.write((char*)&type, sizeof(type));
				switch (type)
				{
				case chapter12_StreamAndfiles::empl_io::tmanager:
					size = sizeof(manager);
					break;
				case chapter12_StreamAndfiles::empl_io::tscientist:
					size = sizeof(scientist);
					break;
				case chapter12_StreamAndfiles::empl_io::tlaborer:
					size = sizeof(laborer);
					break;
				default:
					cerr << "Unknown type";
					return;
				}
				os.write((char*)arrayp[i], size);
				if (!os)
				{
					cerr << "Can't write to file: " << fileName;
					return;
				}
			}

		}

		inline void main()
		{
			char ch;
			while (true)
			{
				cout << "\n'a' -- add data for an employee"
					"\n'd' -- display data for all employees"
					"\n'w' -- write all employee data to file"
					"\n'r' -- read all employee data from file"
					"\n'x' -- exit"
					"\nEnter selection : ";
				cin >> ch;
				switch (ch)
				{
				case 'a':
					employee::add(); break;
				case 'd':
					employee::display(); break;
				case 'w': 
					employee::write(); break;
				case 'r': 
					employee::read(); break;
				case 'x': exit(0);
				default: cout << "\nUnknown command";
				}
			}
		}
	}
	void OSTRSTR()
	{
		const int maxbuff = 80;
		char buff [maxbuff];

		ostrstream omem(buff, maxbuff);
		
		char ch = 'x'; //test data
		int j = 77;
		double d = 67890.12345;
		char str1[] = "Kafka";
		char str2[] = "frued";

		omem << "ch= " << ch << endl
			<< "j= " << j << endl
			<< setiosflags(ios::fixed) << setprecision(2)
			<< d << endl
			<< "str1= " << str1 << endl
			<< "str2= " << str2 << endl
			<< '\0';


		cout << buff;
	}

	namespace Exercises
	{
		void e1()
		{
			Englerr::Distance dis;
			char ans = 'y';
			fstream file;
			file.open("DISTSNCES.DAT", ios::app | ios::out | ios::in | ios::binary);
			do
			{
				cout << "Enter a distance data:\n";
				dis.Getdistance();
				file.write(reinterpret_cast<char*>(&dis), sizeof(dis));

				cin.setf(ios::skipws);
				cout << "\nEnter another distance? (y, n)\n- "; cin >> ans;
				cin.ignore(10, '\n');

			} while (tolower(ans) == 'y');

			cout << endl;
			file.seekg(0, file._Seekend);
			int n = file.tellg() / sizeof(dis);
			cout << "Number of distances: " << n << endl;

			file.seekg(0);
			while (true)
			{
				file.read(reinterpret_cast<char*>(&dis), sizeof(dis));
				if (!file)
					break;
				cout << "\nDistance:";
				dis.SowDistance();
			}
			file.close();
		}

		namespace e4
		{
			void e4()
			{
				string name;
				string middlename;
				string lastname;
				unsigned int employeeNumber;
				ofstream outnamedata("NAMEDATA.txt", ios::trunc);
				if (!outnamedata) {
					cerr << "Could not open file NAMEDATA.txt";
					return;
				}
				while (true)
				{
					cout << "Name: ";  cin >> name;
					cout << "MiddleName: "; cin >> middlename;
					cout << "LastName: "; cin >> lastname;
					cout << "employee number: "; cin >> employeeNumber;
					outnamedata << name << ' ';
					outnamedata << middlename << ' ';
					outnamedata << lastname << ' ';
					outnamedata << employeeNumber << ' ';

					char a = 'y';
					cout << "\nAnother? "; cin >> a;
					if (a != 'y')
						break;
				}

				ifstream ifile("NAMEDATA.txt");
				if (!ifile) {
					cerr << "Could not open file NAMEDATA.txt";
					return;
				}

				while (ifile)
				{
					ifile >> name >> middlename >> lastname >> employeeNumber;
					cout << name << ' ' << middlename << ' ' << lastname << ' ' << employeeNumber;
				}

			}
		}

		namespace e6
		{
			const string filename = "E6_name.txt";
			class Name
			{
				string name;
				string middlename;
				string lastname;
				unsigned int employeeNumber;
			public:
				void getData()
				{
					cout << "Name: ";  cin >> name;
					cout << "MiddleName: "; cin >> middlename;
					cout << "LastName: "; cin >> lastname;
					cout << "employee number: "; cin >> employeeNumber;
				}
				void showData()
				{
					cout << name << ' ' << middlename << ' ' << lastname << ' ' << employeeNumber;
				}
				bool read(int index)
				{
					ifstream ifile(filename);
					if (!ifile) return 0;

					for (int i = 0; ifile || i <= index; i++)
					{
						ifile >> name >> middlename >> lastname >> employeeNumber;
					}
				}

				bool write()
				{
					ofstream ofile(filename, ios::app);
					if (!ofile) return 0;
					ofile << name << ' ' << middlename << ' ' << lastname << ' ' << employeeNumber << '\r\n';
				}

			};

			void e6()
			{
				Name n;
				char a = 'y';
				do
				{
					n.getData();
					n.write();
					cout << "Anotehr?(y/n)\n\t-"; cin >> a;
				} while (a == 'y');

				ifstream ifile(filename);
				if (!ifile)
				{
					cout << "Cannot open file " << filename; return;
				}

				cout << ifile.rdbuf();
			}
		}

		namespace e7
		{
			const string filename = "E7_name.txt";
			class Name
			{
				string name;
				string middlename;
				string lastname;
				unsigned int employeeNumber;
			public:
				static fstream file;
				inline static void openStream()
				{
					file.open(filename, ios::app | ios::in | ios::out);
				}
				inline static void resetStream()
				{
					file.seekg(0);
				}

				void getData()
				{
					cout << "Name: ";  cin >> name;
					cout << "MiddleName: "; cin >> middlename;
					cout << "LastName: "; cin >> lastname;
					cout << "employee number: "; cin >> employeeNumber;
				}
				void showData()
				{
					cout << name << ' ' << middlename << ' ' << lastname << ' ' << employeeNumber;
				}
				bool read(int index)
				{
					if (file) return 0;

					for (int i = 0; file || i <= index; i++)
					{
						file >> name >> middlename >> lastname >> employeeNumber;
					}
				}

				bool write()
				{
					if (!file) return 0;
					file << name << ' ' << middlename << ' ' << lastname << ' ' << employeeNumber << '\n';
					return 1;
				}

			};

			std::fstream e7::Name::file;
			void e7()
			{
				Name n;
				char a = 'y';
				Name::openStream();
				do
				{
					n.getData();
					n.write();
					cout << "Anotehr?(y/n)\n\t-"; cin >> a;
				} while (a == 'y');

				Name::resetStream();

				cout << Name::file.rdbuf();
			}
		}
		namespace e12
		{
			#include <typeinfo>

			const int LEN = 32;
			const int MAXEM = 100;
			string fileName = "E12_Employee.find.DAT";
			enum employee_type { tmanager, tscientist, tlaborer };
			////////////////////////////////////////////////////////////////
			class employee
			{
			protected:
				char name[LEN];
				static int n;
				static employee* arrayp[];
			public:
				unsigned long number;
				virtual void getdata()
				{
					cout << " Enter last name : "; cin >> name;
					cout << " Enter number : "; cin >> number;
				}
				virtual void putdata()
				{
					cout << "\n Name : " << name;
					cout << "\n Number : " << number;
				}
				virtual employee_type getType();
				static void add();
				static void display();
				static void read();
				static void write();
				static void find();
			};

			class manager : public employee
			{
			private:
				char title[LEN];
				double dues;
			public:
				void getdata()
				{
					employee::getdata();
					cout << " Enter title : "; cin >> title;
					cout << " Enter golf club dues : "; cin >> dues;
				}
				void putdata()
				{
					employee::putdata();
					cout << "\n Title : " << title;
					cout << "\n Golf club dues : " << dues;
				}
			};

			class scientist : public employee
			{
			private:
				int pubs;
			public:
				void getdata()
				{
					employee::getdata();
					cout << " Enter number of pubs : "; cin >> pubs;
				}
				void putdata()
				{
					employee::putdata();
					cout << "\n Number of publications : " << pubs;
				}
			};
			class laborer : public employee
			{
			};

			int employee::n = 0;
			employee* employee::arrayp[MAXEM];
			employee_type employee::getType()
			{
				if (typeid(*this) == typeid(manager)) return tmanager;
				else if (typeid(*this) == typeid(laborer)) return tlaborer;
				else if (typeid(*this) == typeid(scientist)) return tscientist;
				else { cout << "Wrong employee type\n"; exit(1); };
			}
			void employee::add()
			{
				employee* per;
				char ans;
				cout << " \'m' -- to add a manager\n";
				cout << " \'s' -- to add a scientist\n";
				cout << " \'l' -- to add a laborer\n";
				while (true)
				{
					cout << "\nEnter selection: ";
					cin >> ans;
					if (ans == 'm' || ans == 's' || ans == 'l')
						break;
				}

				switch (ans)
				{
				case 'm':
					arrayp[n] = new manager();
					break;
				case 's':
					arrayp[n] = new scientist();
					break;
				case 'l':
					arrayp[n] = new laborer();
					break;
				}

				arrayp[n]->getdata();
				n++;
			}
			void employee::display()
			{
				///Your code writes and reads polymorphic objects by doing os.write((char*)arrayp[i], sizeof(derived)) and inf.read((char*)arrayp[n], size). That copies the entire object memory, including the compiler-generated vtable pointer, into the file and later back into a newly allocated object. When read back the saved vptr values point into the old process memory layout (or file garbage), not the current valid vtable, so RTTI/virtual dispatch (used by typeid / getType) dereferences an invalid pointer and crashes. The debugger showed valid heap object addresses and names, but their __vfptr pointed into invalid memory near the crash address — classic vptr corruption from raw binary object I/O.
				//Fix(recommended) Stop writing raw object memory for polymorphic objects.Serialize only the logical data members.Example pattern :
				
				for (int i = 0; i < n; i++)
				{
					cout << "( " << i + 1 << " ). ";
					employee_type type = arrayp[i]->getType();
					switch (type)
					{
					case chapter12_StreamAndfiles::empl_io::tmanager:
						cout << "Manager:";
						break;
					case chapter12_StreamAndfiles::empl_io::tscientist:
						cout << "Scientist:";
						break;
					case chapter12_StreamAndfiles::empl_io::tlaborer:
						cout << "Laborer:";
						break;
					}
					arrayp[i]->putdata();
					cout << endl;
				}
			}
			void employee::read()
			{
				employee_type type;
				int size = 0;
				ifstream inf(fileName, ios::binary);
				if (!inf)
				{
					cerr << fileName << " File not open.";
					return;
				}
				n = 0;
				while (true)
				{
					inf.read((char*)&type, sizeof(type));
					if (inf.eof()) break;
					switch (type)
					{
					case chapter12_StreamAndfiles::empl_io::tmanager:
						arrayp[n] = new manager;
						size = sizeof(manager);
						break;
					case chapter12_StreamAndfiles::empl_io::tscientist:
						arrayp[n] = new scientist;
						size = sizeof(scientist);
						break;
					case chapter12_StreamAndfiles::empl_io::tlaborer:
						size = sizeof(laborer);
						arrayp[n] = new laborer;
						break;
					default:
						cerr << "UNKOWN TYPE IN FILE"; return;
					}
					inf.read((char*)arrayp[n], size);
					if (!inf)
					{
						cerr << "Can't read form file: " << fileName;
						return;
					}
					n++;



					//int size; //size of employee object
					//employee_type etype; //type of employee
					//ifstream inf; //open ifstream in binary
					//inf.open("EMPLOY.DAT", ios::binary);
					//if (!inf)
					//{
					//	cout << "\nCan’t open file\n"; return;
					//}
					//n = 0; //no employees in memory yet
					//while (true)
					//{ //read type of next employee
					//	inf.read((char*)&etype, sizeof(etype));
					//	if (inf.eof()) //quit loop on eof
					//		break;
					//	if (!inf) //error reading type
					//	{
					//		cout << "\nCan’t read type from file\n"; return;
					//	}
					//	switch (etype)
					//	{ //make new employee
					//	case tmanager: //of correct type
					//		arrayp[n] = new manager;
					//		size = sizeof(manager);
					//		break;
					//	case tscientist:
					//		arrayp[n] = new scientist;
					//		size = sizeof(scientist);
					//		break;
					//	case tlaborer:
					//		arrayp[n] = new laborer;
					//		size = sizeof(laborer);
					//		break;
					//	default: cout << "\nUnknown type in file\n"; return;
					//	} //read data from file into it
					//	inf.read((char*)arrayp[n], size);
					//	if (!inf) //error but not eof
					//	{
					//		cout << "\nCan’t read data from file\n"; return;
					//	}
					//	n++; //count employee
				}
			}
			void employee::write()
			{
				int size = 0;
				employee_type type;
				cout << "Writing " << n << " employees\n";
				ofstream os(fileName, ios::trunc | ios::binary);
				if (!os)
				{
					cout << fileName << " can't open\n";
					return;
				}

				for (int i = 0; i < n; i++)
				{
					type = arrayp[i]->getType();
					os.write((char*)&type, sizeof(type));
					switch (type)
					{
					case chapter12_StreamAndfiles::empl_io::tmanager:
						size = sizeof(manager);
						break;
					case chapter12_StreamAndfiles::empl_io::tscientist:
						size = sizeof(scientist);
						break;
					case chapter12_StreamAndfiles::empl_io::tlaborer:
						size = sizeof(laborer);
						break;
					default:
						cerr << "Unknown type";
						return;
					}
					os.write((char*)arrayp[i], size);
					if (!os)
					{
						cerr << "Can't write to file: " << fileName;
						return;
					}
				}

			}
			void employee::find()
			{
				unsigned long empn = 0;
				cout << "Enter Employee Number: ";
				cin >> empn;
				int size;
				employee_type type;
				employee* emp = NULL;
				ifstream ifile(fileName, ios::binary);
				if (!ifile)
					return;
				while (ifile)
				{
					ifile.read((char*)&type, sizeof(type));
					switch (type)
					{
					case chapter12_StreamAndfiles::empl_io::tmanager:
						emp = new manager;
						size = sizeof(manager);
						break;
					case chapter12_StreamAndfiles::empl_io::tscientist:
						emp = new scientist;
						size = sizeof(scientist);
						break;
					case chapter12_StreamAndfiles::empl_io::tlaborer:
						size = sizeof(laborer);
						emp = new laborer;
						break;
					default:
						cerr << "UNKOWN TYPE IN FILE"; return;
					}
					ifile.read((char*)emp, size);
					if (emp->number == empn)
					{
						emp->putdata();
						return;
					}
				}
			}
			inline void e12()
			{
				char ch;
				while (true)
				{
					cout << "\n'a' -- add data for an employee"
						"\n'd' -- display data for all employees"
						"\n'w' -- write all employee data to file"
						"\n'r' -- read all employee data from file"
						"\n'f' -- read all employee data from file"
						"\n'x' -- exit"
						"\nEnter selection : ";
					cin >> ch;
					switch (ch)
					{
					case 'a':
						employee::add(); break;
					case 'd':
						employee::display(); break;
					case 'w':
						employee::write(); break;
					case 'r':
						employee::read(); break;
					case 'f':
						employee::find(); break;
					case 'x': exit(0);
					default: cout << "\nUnknown command";
					}
				}
			}
		}
	}
}

