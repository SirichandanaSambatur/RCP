#pragma once
#define _CRT_SECURE_NO_WARNINGS
////////////////////////////////////////////////////////////////////////////////////////////
// Display.h - Helper class that is use to show the analysis that is being performed      //
//  ver 1.0                                                                               //
//  Language:      Visual C++ 2015                                                        //
//  Platform:      Macbook Pro, Windows 10                                                //
//  Application:   Used to support analysis of the files                                  //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                               //
////////////////////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package is used to display the various analysis that has been performed on the file
collection that is given to us. 

Public Interface:
=================
typeAnalysis()      //perform type Analysis
depAnalysis()       //perform dependancy analysis
depDatabase()       //insert dependancy analysis into the databaase
strongComponents()  // finding the strongly connected components
XMLformat()         //store the analysis as an XML file

Build Process:
==============
Required files -
TypeAnal.h, DepAnal.h, DBHelper.h, Component.h, Persistance.h

Build commands 
devenv CodeAnalyzer.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 05 Mar 2017
- first release

*/
#include "../TypeAnalysis/TypeAnal.h"
#include "../DepandancyAnalysis/DepAnal.h"
#include "../NoSqlDb/DBHelper.h"
#include "../Publisher/Publisher.h"
#include<chrono>
#include<ctime> 
#include<unordered_map>

namespace CodeAnalysis {
	/////////////////////////////////////////////////////////////////////////////
	// Display class helps in performing augmentation of database
	// - this class performs all the various analysis to be performed 
	//    on the file collection that is provided
	// - it uses the NoSql Data base to store the analysis that it has performed
	//

	using namespace CodePublisher;
	class Display {
	private:
		TypeAnal ta;
		DepAnal dp;
		Publisher p;
		DBHelper<std::string> sDB;
		DBHelper<std::string> connect;
		unordered_map<std::string, int> mapping;//data structure to store mapping the files to index
		using item = std::pair<std::string, int>;
		bool checkInMap(std::string s);
		void insertMap(std::string s);
		void createMap();
		std::string msg;
		std::string getTimeDate();

	public: 
		void typeAnalysis();
		void depAnalysis();
		void depDatabase();
		void publishFiles();
	};

	//checking if a file is already mapped
 bool  Display::checkInMap(std::string s) {
		for (item i : mapping) {
			if (i.first == s) {
				return true;
			}
		}
		return false;
	}
	//extract the current time and date function
std::string Display::getTimeDate() {
		std::string time="";
		std::chrono::time_point<std::chrono::system_clock> current_time;
		current_time = std::chrono::system_clock::now();
		std::time_t current = std::chrono::system_clock::to_time_t(current_time);
		time = std::ctime(&current);
		return time;
	}
	//inserting file into the map
 void Display::insertMap(std::string s) {
		static int count = 0;
		if (!checkInMap(s)) {
			mapping[s] = count;
			count++;
		}

	}
	//performing type analysis
 void  Display::typeAnalysis() {
		ta.doTypeAnal();
		//ta.displayTypeTable();
	}

	//perform depandancy analysis
void Display::depAnalysis() {
		dp.checkDependancies(ta);
		dp.checkDependentFiles(ta);
		//dp.showDependancy();
	}

	//inserting depandancy into the database
 void Display::depDatabase() {
		unordered_map<string, vector<string>> fileDependancies = dp.getDependancy();
		using Item = std::pair<string, vector<string>>;
		for (Item it : fileDependancies)
		{
			msg=sDB.insertion(it.first,"file","this is parent file",getTimeDate(),"Dependancy Analysis in Data Base");
			vector<string> temp = it.second;
			for (int i = 0; i < temp.size(); i++) {
				msg = sDB.insertion(temp[i], "file", "this is a file", getTimeDate(), "Dependendancy Analysis in Data Base");
				msg= sDB.addChild(it.first, temp[i]);
			}
		}
		//sDB.display();
	}

	//create a map of files with unique id(int) for graph
void Display::createMap() {
		unordered_map<string, vector<string>> fileDependancies = dp.getDependancy();
		using Item = std::pair<string, vector<string>>;
		for (Item it : fileDependancies)
		{
			insertMap(it.first);
			vector<string> temp = it.second;
			for (int i = 0; i < temp.size(); i++) {
				insertMap(temp[i]);
			}
		}
	}



	//publishing the html files
	void Display::publishFiles() {
		std::cout << "\n-------------Publisher to publish the files in the package------------\n\n";
		vector<std::string> files = ta.getFiles();
		p.publishPackage(files,sDB);
		p.openBrowser();
	}
}