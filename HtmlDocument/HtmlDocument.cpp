/////////////////////////////////////////////////////////////////////////////////////////
// HtmlDocument.cpp - Used for creating HTML pages and all the required tags           //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to convert existing files into html pages that are published   //                       
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEST_HTMLDOCUMENT

#include "HtmlDocument.h"

using namespace CodePublisher;
int main() {
	HtmlDocument h;
	std::string HtmlContent="";
	std::vector<std::string> cs;
	std::vector<std::string> js;
	cs.push_back("sample.css");
	js.push_back("sample.js");
	HtmlContent+= h.createPrologue("sample.html") + h.createHtmlStartTag() + h.createHeadSection(cs, js);
	HtmlContent += HtmlContent + h.createBodyStartTag()+h.createDivision("","sample","Test Html Page")+ h.createBodyEndTag();
	std::cout << HtmlContent;
}
#endif // !TEST_HTMLDOCUMENT