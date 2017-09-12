/////////////////////////////////////////////////////////////////////////////////////////
// PublishPage.cpp - Publish the given list of files as HTML files                     //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to publish various types of files in the package               //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEST_PUBLISHPAGE
#include "PublishPage.h"

using namespace CodePublisher;
int main() {
	PublishHtmlPage p;
	std::vector<std::string> listOfFiles;
	listOfFiles.push_back("link.html");
	listOfFiles.push_back("mainPage.html");
	std::vector<std::string> files;
	files.push_back("page1.html");
	files.push_back("page2.html");
	files.push_back("page3.html");
	files.push_back("page4.html");
	p.createMainPage(files);
	p.createHtmlPage("page1.html", "This is the first page to be created", listOfFiles);
	p.createHtmlPage("page2.html", "This is the second page to be created", listOfFiles);
	p.createHtmlPage("page3.html", "This is the third page to be created", listOfFiles);
	p.createHtmlPage("page4.html", "This is the fourth page to be created", listOfFiles);

}

#endif // !TEST_PUBLISHPAGE
