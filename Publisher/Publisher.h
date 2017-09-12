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
void publishPackage(std::vector<std::string> files, DBHelper<std::string> sDB); //to publish the package given
void openBrowser(); //launch the default browser 

Build Process:
==============
Required files
ConvertType.h, PublishPage.h, DBHelpher.h

Build commands
devenv DependancyBasedCodePublisher.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 04 Apr 2017
- first release

*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<unordered_map>
#include<vector>
#include "../PublishPage/PublishPage.h"
#include "../ConvertType/ConvertType.h"
#include "../NoSqlDb/DBHelper.h"

using namespace std;

namespace CodePublisher {
	/////////////////////////////////////////////////////////////////////
	// Publisher class to publish the given pages
	// - all the files are published as html pages
	// - opens in the default browser
	//
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

	//open the html page with the default browser
	void Publisher::openBrowser() {
		std::string path = "HtmlFiles";
		_chdir(path.c_str());
		std::string htmlFilePath = "mainPage.html";
		std::cout <<"Launching the page from the folder- " <<path<<"\\"<<htmlFilePath;
		ShellExecuteA(GetDesktopWindow(), ("open"), LPCSTR(htmlFilePath.c_str()), NULL, NULL, SW_SHOWNORMAL);
	}

	void Publisher::SplitFilename(const std::string& str)
	{
		std::size_t found = str.find_last_of("/\\");
		currentPath = str.substr(0, found);
		currentFile = str.substr(found + 1);
	}


	//publish the packages by publishing all the files
	void Publisher::publishPackage(std::vector<std::string> files, DBHelper<std::string> sDB) {
		using Item = std::pair<string, vector<string>>;
		Convert c;
		std::cout << "Requirement 4- Implemented the hiding and unhiding feature using the CSS- 'HtmlFiles/HideInformation.css' and the JS- 'HtmlFiles/HideInformation.js'";
		std::cout << "\n------------------------------------------------------------------\n";
		std::cout << "Requirement 5- Displaying the contents of the CSS files that have been used------\n";
		p.showCSSFiles();
		std::cout << "\n------------------------------------------------------------------\n";
		std::cout << "Requirement 5- Displaying the contents of the JS file that have been used------\n";
		p.showJSFiles();
		std::cout << "\n------------------------------------------------------------------\n";
		std::cout << "\n--------------------Creating the main page----------------------\n";
		p.createMainPage(files);
		std::cout << "\n------------------------------------------------------------------\n";
		std::cout << "Requirement 6- Adding external links to all html files created in the head section\n";
		std::cout << "\n------------------------------------------------------------------\n";
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