#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
// ConvertType.h - To convert a file in the Html format                                //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to convert a given list of files in .html files                //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package is used to convert the type of each given file as an html file.
This conversion helps keep the content as it is in the new Html pages. It also performs 
any syntacitically changes of content that needs to be made on the existing file. So, that 
when the file is converted to .html, there is no loss of data. It helps in preserving 
the contents of the existing files.


Public Interface:
=================


Build Process:
==============
Required files


Build commands
devenv CodeAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 02 Apr 2017
- first release

*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

namespace CodePublisher {
	class Convert {
	private:

	public:
		std::string convertContent(std::string fname);
	};

	std::string Convert::convertContent(std::string fname) {
		std::string temp = "";
		std::string content = "";
		std::ifstream in(fname);
		if (!in.good())
			throw(std::exception(("can't open source file " + fname).c_str()));
		std::ostringstream out;
		out << in.rdbuf();
		temp = out.str();
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] == '<') {
				content = content + "&lt;";
			}
			else if (temp[i] == '>') {
				content = content + "&gt;";
			}
			else
				content = content + temp[i];
		}
		return content;
	}
}