#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
// HtmlDocument.h - Used for creating HTML pages and all the required tags             //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to convert existing files into html pages that are published   //                       
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package is used to create HTML pages, that can be viewed on browser.
It consists of all the methods that help in creating the required tags of HTML. It will
also include the required CSS and JS for the HTML files.

Public Interface:
=================
createHtmlStartTag();
createHeadSection();
createBodyStartTag();
createBodyEndTag();
createAnchorTag();
createHtmlEndTag();
createPreTag();
createScriptTag();
createDivision();
createLiTag();
createOLTag();
createButton();
createDivIdStart();
createDivIdEnd();

Build Process:
==============
Required files
HtmlDocument.h, HtmlDocument.cpp


Build commands
devenv DependancyBasedCodePublisher.sln /rebuild debug

Maintenance History:
====================
ver 1.0 :  04 Apr 2017
- first release

*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include <chrono>
#include <ctime>


namespace CodePublisher {
	/////////////////////////////////////////////////////////////////////////////////////////
	// HtmlDocument class helps creating Html pages that follow the Html syntax and semantics
	// - this class is used to create various Html tags (start and end)
	// - it factilates in creating the html file structure
	//

	class HtmlDocument {
	private:
		std::string getTimeDate();
	public:
		std::string createHtmlStartTag();
		std::string createHeadSection(std::vector<std::string> cssList, std::vector<std::string> jsList);
		std::string createBodyStartTag();
		std::string createBodyEndTag();
		std::string createAnchorTag(std::string className, std::string name, std::string link);
		std::string createHtmlEndTag();
		std::string createPreTag(std::string content);
		std::string createScriptTag(std::string name);
		std::string createDivision(std::string id, std::string className, std::string bodyDiv);
		std::string createLiTag(std::string t);
		std::string createOLTag(std::string t, std::string className, std::string n);
		std::string createButton(std::string var);
		std::string createDivIdStart(std::string v);
		std::string createDivIdEnd();
		std::string createPrologue(std::string file);
	};
	std::string HtmlDocument::getTimeDate() {
		std::string time;
		//Accesing the system clock
		std::chrono::time_point<std::chrono::system_clock> current_time;
		current_time = std::chrono::system_clock::now();
		std::time_t current = std::chrono::system_clock::to_time_t(current_time);
		time = std::ctime(&current);
		return time;
	}
	//creating the prologues for the html pages
	std::string HtmlDocument::createPrologue(std::string file) {
		std::string content = "<!---------------------------------------------------------------------\n File Name- " + file + "\nPublished"+getTimeDate() +"\nAuthor- Siri Chandana Sambatur, ssambatu@syr.edu\n ----------------------------------->\n ";
		return content;
	}

	//start div tag
	std::string HtmlDocument::createDivIdStart(std::string v) {
		return "<div id = \"collapsible" + v + "\">";
	}

	//end div tag
	std::string HtmlDocument::createDivIdEnd() {
		return "</div>";
	}
	//creating Html button
	std::string HtmlDocument::createButton(std::string var) {
		std::string content="<button id=\"collapseInfo\" onclick =\"myFunction('collapsible"+var+"')\">show</button>";
		return content;
	}
	//creating html start tag
	std::string HtmlDocument::createHtmlStartTag() {
		return "<!DOCTYPE html><br><html>";
	}

	//html end tag
	std::string HtmlDocument::createHtmlEndTag() {
		return "</html>";
	}

	//head section and include all necessary links to external files
	std::string HtmlDocument::createHeadSection(std::vector<std::string> cssList, std::vector<std::string> jsList) {
		std::string headContent = "<head>";
		for (int i = 0; i < cssList.size(); i++) {
			headContent += "<link rel='stylesheet' type='text/css' href='" + cssList[i] + "'>\n";
		}
		for (int j = 0; j < jsList.size(); j++) {
			headContent += createScriptTag(jsList[j]);
		}
		headContent += "</head>";
		return headContent;
	}

	//body tag and necessary feature if any
	std::string HtmlDocument::createBodyStartTag() {
		return "<body>";
	}

	//end the body section of html file
	std::string HtmlDocument::createBodyEndTag() {
		return "</body>";
	}

	//create the necessary links
	std::string HtmlDocument::createAnchorTag(std::string className, std::string name, std::string link) {
		std::string tag = "";
		tag = "<a ";
		if (className != "")
			tag += "class='" + className + "'";
		tag += "href='" + link + "'>" + name;
		tag = tag + "</a>";
		return tag;
	}

	//creating pre tag of html files
	std::string HtmlDocument::createPreTag(std::string content) {
		std::string tag = "<pre>" + content + "</pre>";
		return tag;
	}

	//creating script tag to add any js functions or external js files
	std::string HtmlDocument::createScriptTag(std::string name) {
		std::string tag = "<script src='" + name + "'></script>";
		return tag;
	}

	//creating a division with certain requirements
	std::string HtmlDocument::createDivision(std::string id, std::string className, std::string bodyDiv) {
		std::string tag = "<div ";
		if (id != "") {
			tag = tag + "id='" + id + "'";
		}
		if (className != "") {
			tag = tag + "class='" + className + "'";
		}
		tag = tag + ">" + bodyDiv + "</div>";
		return tag;
	}

	//create list tag 
	std::string HtmlDocument::createLiTag(std::string t) {
		std::string ol = "<li>" + t + "</li>";
		return ol;
	}

	//creating the ordered lists
	std::string HtmlDocument::createOLTag(std::string t, std::string className, std::string n) {
		std::string ol = "<ol class='" + className;
		ol += "' type='" + t + "'>" + n + "</ol>";
		return ol;
	}
}