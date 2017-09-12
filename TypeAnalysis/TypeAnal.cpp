/////////////////////////////////////////////////////////////////////////////
// TypeAnal.cpp - Provides the type analysis to store in a type map        //
//  ver 1.0                                                                //
//  Language:      Visual C++ 2015                                         //
//  Platform:      Macbook Pro, Windows 10                                 //
//  Application:   Used to support dependancy analysis of the files        //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
#include "TypeAnal.h"
using namespace CodeAnalysis;

#ifdef TEST_TYPEANAL
int main() {
	TypeAnal t;
	std::cout << "TESTING- performing test analysis on files";
	t.doTypeAnal();
	std::cout << " The type table that is created";
	t.displayTypeTable();


}
#endif // TEST_TYPEANAL
