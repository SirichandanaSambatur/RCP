#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
// PublishPage.h - Publish the given list of files as HTML files                       //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to publish various types of files in the package               //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package is used to publish every single file that ia present in the package. It
converts all the files to HTML files. It uses the HtmlDocument to convert the given 
list of files into Html pages and also links all the files, so that they can be published 
on the browser.


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
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_OBSOLETE_NO_WARNINGS
#include<iostream>
#include<sstream>
#include<fstream>
#include "../HtmlDocument/HtmlDocument.h"
#include<direct.h>
#include <windows.h>
namespace CodePublisher {
	class PublishHtmlPage {
	private:
		std::string htmlFilePath="HtmlFiles/mainPage.html";
		HtmlDocument hd;
		std::vector<std::string> csslist;
		std::vector<std::string> jslist;
		std::string js;
		std::string createHeader(std::string currentFile);
		std::string createMainContent(std::string content, std::vector<std::string> listOfFiles);
		std::string createFooter();
		std::string addDependancies(std::vector<std::string> listOfFiles);
		std::string createSections(std::string v);
		std::string createPrologue(std::string file);

	public:
		void createHtmlPage(std::string fileName, std::string content, std::vector<std::string> listOfFiles);
		void addCSS();
		void addJS();
		void showCSSFiles();
		void createMainPage(std::vector<std::string> files);

	};

	void PublishHtmlPage::createMainPage(std::vector<std::string> files) {
		std::ofstream file(htmlFilePath);
		std::string atag;
		std::string litag="";
		addCSS();
		std::string hContent= hd.createHtmlStartTag() + hd.createHeadSection(csslist,jslist)+ hd.createBodyStartTag() + createHeader("Main Page");
		std::string size = "The package consists of " + std::to_string(files.size()) + " files. Depandancy Analysis is performed on these files and the files have been published as an html file.<br>";
		size = size + "The following is the list of files that are present in the package-<br>";
		for (int i = 0; i < files.size(); i++) {
			std::size_t found =files[i].find_last_of("/\\");
			std::string currentPath = files[i].substr(0, found);
			std::string currentFile = files[i].substr(found + 1);
			std::string temp = currentFile + ".html";
			atag = hd.createAnchorTag("alink", currentFile, temp);
			litag += hd.createLiTag(atag);
		}
		std::string oltag = hd.createOLTag("A", "",litag);
		size += oltag;
		hContent += hd.createDivision("", "mainContent", size);
		std::string fContent = hd.createAnchorTag("acolor", "Return to main page", "mainPage.html");
		fContent += hd.createDivision("", "alignRight", "&copy;&nbsp;Copyright 2017. All rights reserved");
		std::string s = hd.createDivision("", "footer alignBottom", fContent);
		hContent += s+hd.createBodyEndTag();
		file << hContent;
		file.close();
	}

	std::string PublishHtmlPage::createPrologue(std::string file) {
		std::string content="<!---------------------------------------------------------------------\n File Name- "+file+"\nPublished- April 04, 2017, \nAuthor- Siri Chandana Sambatur, ssambatu@syr.edu\n ----------------------------------->\n ";
		return content;
	}
	void PublishHtmlPage::showCSSFiles() {
		std::cout << "Contents of HtmlFiles/HTMLDesign.css------------------\n";
		std::ifstream in("HtmlFiles/HTMLDesign.css");
		std::cout << in.rdbuf();
		std::cout << "\nContents of HtmlFiles/HideInformation.css------------------\n";
		std::ifstream in1("HtmlFiles/HideInformation.css");
		std::cout << in1.rdbuf();
	}

	void PublishHtmlPage::addCSS() {
		std::cout << "--------------------- Adding external Stylesheets- 'HtmlFiles/HideInformation.css' and 'HtmlFiles/HTMLDesign.css' -----------------------\n";
		csslist.push_back("HideInformation.css");
		csslist.push_back("HTMLDesign.css");
	}

	void PublishHtmlPage::addJS() {
		std::cout << "----------------- Adding external Java Script - 'HtmlFiles/HideInformation.js' ----------------\n";
		jslist.push_back("jquery-3.2.0.js");
		jslist.push_back("HideInformation.js");
	}
	//Header of the Html page according to design
	std::string PublishHtmlPage::createHeader(std::string currentFile) {
		std::string hContent = "Code Publisher - " + currentFile;
		std::string s = hd.createDivision("", "header", hContent);
		return s;
	}
	std::string PublishHtmlPage::createSections(std::string text) {
		std::string htmlContent = "";
		int count = 1;
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == '{') {
				htmlContent+=hd.createButton(std::to_string(count));
				htmlContent += hd.createDivIdStart(std::to_string(count)) + "{";
				count = count+1;
			}
			else if (text[i] == '}') {
				if (text[i + 1] == ';') {
					htmlContent += "};" + hd.createDivIdEnd();
					i = i + 1;
				}
				htmlContent +="}"+ hd.createDivIdEnd();
			}
			else
			 htmlContent += text[i];
		}
		return hd.createPreTag(htmlContent);
	}
	//main content of the Html page according to design
	std::string PublishHtmlPage::createMainContent(std::string content, std::vector<std::string> listOfFiles) {
		std::string hContent = addDependancies(listOfFiles) + hd.createDivision("code","","<br>Code present in the file is given below-<br>")+createSections(content);
		return hd.createDivision("","mainContent",hContent);
	}



	//footer of the Html page according to design
	std::string PublishHtmlPage::createFooter() {
		std::string fContent = hd.createAnchorTag("acolor", "Return to main page", "mainPage.html");
		fContent += hd.createDivision("", "alignRight", "&copy;&nbsp;Copyright 2017. All rights reserved");
		std::string s = hd.createDivision("", "footer", fContent);
		return s;
	}

	void PublishHtmlPage::createHtmlPage(std::string fileName, std::string content, std::vector<std::string> listOfFiles) {
		std::string Name= "HtmlFiles/"+fileName + ".html";
		std::string HtmlContent = "";
		try {
			std::cout << "\n----------------------------------------------------------------------------------------------------\n";
			std::cout << "Requirement 3------------------- Html file created- " << fileName << "-------------------\n";
			std::cout << "----------------------------------------------------------------------------------------------------\n";
			HtmlContent = createPrologue(fileName)+ hd.createHtmlStartTag()+hd.createHeadSection(csslist,jslist);
			HtmlContent = HtmlContent + hd.createBodyStartTag() + createHeader(fileName) +createMainContent(content,listOfFiles)+ createFooter() + hd.createBodyEndTag();
			std::ofstream file(Name);
			file << HtmlContent;
			file.close();
		}
		catch (std::exception& ex) {
			std::cout << "File Handling Error" << ex.what();
		}

	}

	std::string PublishHtmlPage::addDependancies(std::vector<std::string> listOfFiles) {
		std::cout << "Requirement 7---------------------- Adding the Dependancies----------------- \n";
			std::string tags = hd.createDivision("","dependancies","List Of Dependancies-<br>");
			std::string liTag;
			for (int i = 0; i < listOfFiles.size(); i++) {
				std::string temp=listOfFiles[i] + ".html";
				std::cout << temp << "\n";
				std::string atag= hd.createAnchorTag("", listOfFiles[i], temp);
				liTag += hd.createLiTag(atag);
			}

			tags += hd.createOLTag("1","alink",liTag);
			std::cout << "---------------------------------------------------------------------------------------------\n";
			std::cout << "\n\n";
			return tags;
		
	}
}