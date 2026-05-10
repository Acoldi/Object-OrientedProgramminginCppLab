
#include <iostream>
#include <string.h>
#include "FirendFunctoins.h"
#include "VirtualPublic.h"
#include <cstring>

#include "Chapter11_VirtualFunctinos.h";
#include "Chapter12_SreamAndFiles.h";

using namespace std;



//int main()
//{
//#pragma region chapter 11 Virutual Functinos
//	//FirendFunctions::main();
//	//chapter11VirtualFunctions::frengl::main();
//	//chapter11VirtualFunctions::statfunc::main();
//	//chapter11VirtualFunctions::STRIMEM::main();
//	//chapter11VirtualFunctions::Exercise3::main();
//#pragma endregion
//#pragma region chapter 12 StreamsAndFIles
//
//	//chapter12_StreamAndfiles::Englerr::Main();
//	//chapter12_StreamAndfiles::Formatto::Main();
//	//chapter12_StreamAndfiles::Formati::Main();
//	//chapter12_StreamAndfiles::oline();
//	//chapter12_StreamAndfiles::iline();
//	//chapter12_StreamAndfiles::ichar2();
//	//chapter12_StreamAndfiles::binio();
//	//chapter12_StreamAndfiles::iopers();
//	//chapter12_StreamAndfiles::diskfun();
//	//chapter12_StreamAndfiles::seekg();
//	//chapter12_StreamAndfiles::REWOBJECT();
//	//chapter12_StreamAndfiles::empl_io::main();
//	//chapter12_StreamAndfiles::OSTRSTR();
//	chapter12_StreamAndfiles::comline::main(3, "u", "iii", "sdfd");
//
//#pragma endregion
//
//	return 0;
//}

#pragma region COMLINE
//int main(int argc, char * argv[])
//{
//	cout << "There are " << argc << " arguments\n";
//
//	for (int i = 0; i < argc; i++)
//	{
//		cout << "Argument " << i << " : " << argv[i] << endl;
//	}
//	return 0;
//}
#pragma endregion

#pragma region otype
int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: <PROGRAM NAME> filename";
		exit(1);
	}
	ifstream ifile(argv[1]);
	if (!ifile)
	{
		cerr << "Could not open file " << argv[1];
		exit(1);
	}

	//char ch;
	/*while (ifile)
	{	
		ifile.get(ch);
		cout << ch;
	}*/
	cout << ifile.rdbuf();
	return 0;
}
#pragma endregion