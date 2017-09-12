////////////////////////////////////////////////////////////////////////////////////////////
// Display.cpp - Helper class that is use to show the analysis that is being performed    //
//  ver 1.0                                                                               //
//  Language:      Visual C++ 2015                                                        //
//  Platform:      Macbook Pro, Windows 10                                                //
//  Application:   Used to support analysis of the files                                  //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                               //
////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "Display.h"
using namespace CodeAnalysis;
#ifdef TEST_DISPLAY
int main() {
	Display d;
	std::cout << "Testing type Anaylsis";
	d.typeAnalysis();
	std::cout<<"testing dependancy analysis"
	d.depAnalysis();

	std::cout << "inserting the dependancy into the database";
	d.depDatabase();
	std::cout << "testing to check strongly connected components";
	d.strongComponents();

	std::cout << 'testing to output as a XML file";
	if (XMLfile == "")
		XMLfile = "defaultXML.xml";
	d.XMLFormat(XMLfile);
}

#endif // TEST_DISPLAY