
/////////////////////////////////////////////////////////////////////////////////////
// TypeTable.cpp - Provides the type map where information of type is stored       //
//  ver 1.0                                                                        //
//  Language:      Visual C++ 2015                                                 //
//  Platform:      Macbook Pro, Windows 10                                         //
//  Application:   Used to support type analysis of the files                      //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                        //
/////////////////////////////////////////////////////////////////////////////////////

#include "TypeTable.h"
using namespace CodeAnalysis;
#ifdef TEST_TYPETABLE
int main() {
	typeTable t;
	std::cout << "inserting temporary values in the type table";
	t.addEntry("file.h", "code1", "class", "A");
	t.addEntry("file.h", "code", "function", "A");
	t.addEntry("file.h", "code", "function", "B");
	t.addEntry("file.h", "code", "function", "C");
	std::cout << "displaying the type table";
	t.display();

}
#endif // TEST_TYPETABLE
