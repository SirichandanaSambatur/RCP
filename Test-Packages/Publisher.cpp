/////////////////////////////////////////////////////////////////////////////////////////
// Publisher.h - Publish the given list of files as HTML files on the browser          //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to publish various types of files in the package               //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////
#include "Publisher.h"


using namespace CodePublisher;

#ifdef TEST_PUBLISHER
int main() {
	Publisher p;
	p.publishPackage();
}
#endif