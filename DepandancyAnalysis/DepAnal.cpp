///////////////////////////////////////////////////////////////////////////////////////////
// DepAnal.cpp - Provides the depandancy analysis of files in specified collection       //
//  ver 1.0                                                                              //
//  Language:      Visual C++ 2015                                                       //
//  Platform:      Macbook Pro, Windows 10                                               //
//  Application:   Used to support strong components analysis of the files               //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University                           //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                              //
///////////////////////////////////////////////////////////////////////////////////////////

#include "DepAnal.h"
#include "../TypeAnalysis/TypeAnal.h"
using namespace CodeAnalysis;
#ifdef TEST_DEPANAL

int main()
{
	//Test stub for dependancy Analysis
	TypeAnal t;
	DepAnal d;
	std::cout << "performing type analysis";
	t.doTypeAnal();
	std::cout << "testing the dependancy analysis";
	d.checkDependancies(t);


}
#endif