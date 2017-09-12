/////////////////////////////////////////////////////////////////////////////////////////
// ConvertType.h - To convert a file in the Html format                                //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to convert a given list of files in .html files                //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEST_CONVERTTYPE
#include "ConvertType.h"
using namespace CodePublisher;

int main() {
	Convert c;
	std::cout << "Testing if a sample file is converting its contents according to html syntaxes.";
	std::string temp = c.convertContent("Test.cpp");
	std::cout << temp;
}
#endif // !TEST_CONVERTTYPE
