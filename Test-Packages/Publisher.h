#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
// Publisher.h - Publish the given list of files as HTML files on the browser          //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to publish various types of files in the package               //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package is used to publish all the files and insert links where they are necessary.
It uses the PublishPage package to make the files a list of Html files. So, these Html files
can finally be linked together as one and form a single website.


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
#include<unordered_map>
#include<vector>
#include "../PublishPage/PublishPage.h"
#include "../ConvertType/ConvertType.h"
#include "../NoSqlDb/DBHelper.h"

using namespace std;

namespace CodePublisher {

	class Publisher {
	public:
		void publishPackage(std::vector<std::string> files, DBHelper<std::string> sDB);
		void openBrowser();
	private:
		PublishHtmlPage p;
		std::string currentPath;
		std::string currentFile;
		void SplitFilename(const std::string& str);


	};
	void Publisher::openBrowser() {
		std::string htmlFilePath = "..\\Analyzer\\HtmlFiles\\mainPage.html";
		std::cout << htmlFilePath;
		ShellExecuteA(GetDesktopWindow(), ("open"), LPCSTR(htmlFilePath.c_str()), NULL, NULL, SW_SHOWNORMAL);
	}
	void Publisher::SplitFilename(const std::string& str)
	{
		std::size_t found = str.find_last_of("/\\");
		currentPath = str.substr(0, found);
		currentFile = str.substr(found + 1);
	}
	void Publisher::publishPackage(std::vector<std::string> files, DBHelper<std::string> sDB) {
		using Item = std::pair<string, vector<string>>;
		Convert c;
		std::cout << "Requirement 5- Display contents of the CSS files ------\n";
		p.showCSSFiles();
		std::cout << "--------------------Creating the main page----------------------\n\n";
		p.createMainPage(files);
		std::cout << "\n------------------------------------------------------------------\n";
		std::cout << "Requirement 6- Adding external links in the head section----------------\n";
		p.addCSS();
		p.addJS();
		for (int i = 0; i < files.size(); i++) {
			std::string temp = c.convertContent(files[i]);
			SplitFilename(files[i]);
			std::cout << "----------- Publishing the file " << currentFile << "------------------------\n";
			p.createHtmlPage(currentFile, temp, sDB.getChildren(currentFile));
		}
		
	}
}