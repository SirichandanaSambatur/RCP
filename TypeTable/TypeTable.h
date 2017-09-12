#pragma once
/////////////////////////////////////////////////////////////////////////////////////
// TypeTable.cpp - Provides the type map where information of type is stored       //
//  ver 1.0                                                                        //
//  Language:      Visual C++ 2015                                                 //
//  Platform:      Macbook Pro, Windows 10                                         //
//  Application:   Used to support type analysis of the files                      //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                        //
/////////////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package defines a type class and a type table class. The type table class holds 
the type map, while the type class contains information about each of these types.
These are used to assist type analysis

Public Interface:
=================
show()               //display the contents of type
getFileName()        // for the file name stored
getNamespace()       //for the namesapce stored
getType()           //for the type stored
addEntry()          //add entry into the type table
display()           //show the type table
getfiles()          // access files for given key

Build Process:
==============
Required files- TypeTable.h, TypeTable.cpp

Build commands
devenv DependancyBasedCodePublisher.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 05 Mar 2017
- first release

*/
#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
using namespace std;

namespace CodeAnalysis {
	/////////////////////////////////////////////////////////////////////
	// Type class is used to store the details of the declaration
	// - helps the type table class 
	//
	class type {
	private:
		string fileName;
		string kind;
		string ns;
	public:
		type(string n,string t, string k) {
			this->fileName = n;
			this->ns = t;
			this->kind = k;
		}
		string getFileName();
		string getNamespace();
		string getType();
		void show() {
			cout << "\n\t Value- ";
			if(fileName!="")
				cout << "file  = " << fileName <<"\t";
			cout << "type = " << kind<< "\t";
			if(ns!="")
				cout << "\tnamespace = " << ns << "\n";
		}
	};

	//return the file name 
	string type::getFileName() {
		return fileName;
	}

	//return the namespace
	string type::getNamespace() {
		return ns;
	}

	//return the type
	string type::getType() {
		return kind;
	}

	/////////////////////////////////////////////////////////////////////
	// typeTable class helps in creating the type table 
	// - this uses the type class for the value pair
	// - stores the type table as an unordered map of vectors
	//
	class typeTable {
	private:
		using Item = std::pair<string, vector<type>>;
		unordered_map<string,vector<type>> typeMap; // map in which the type table is stored
		bool checkDuplicate(string filename, string n, string t, string name);
	public:
		void addEntry(string filename,string n, string t, string name);
		void display();
		vector<std::string> getFiles(string tok, vector<string> ns);
	};

	//to avoid duplicate entries in the database
	bool typeTable::checkDuplicate(string filename, string n, string t, string name) {
			vector<type> temp = typeMap[name];
			for (int i = 0; i < temp.size(); i++) {
				if ((temp[i].getFileName() == filename) && (temp[i].getNamespace() == n)&&(temp[i].getType()==t))
					return true;
			}
		return false;
	}

	//add entry into the type table
	void typeTable::addEntry(string filename,string n, string t, string name) {
		bool check=checkDuplicate(filename,n,t, name);
		if (!check) {
			type t1(filename, n, t);
			typeMap[name].push_back(t1);
		}
	}

	//show the type table
	void typeTable::display() {
		for (Item it : typeMap) {
			std::cout << "key is " << it.first << "\n";
			vector<type> temp = it.second;
			for (int i = 0; i < temp.size(); i++) {
				temp[i].show();
			}
			std::cout << "\n-------------------------------------------------------------\n";
		}	
	}

	//retrieve the files 
	vector<std::string> typeTable::getFiles(string tok,vector<string> ns) {
		vector<std::string> files;
		vector<type> temp;
		if (typeMap.find(tok) == typeMap.end()) {
			return files;
		}
		temp = typeMap[tok];

		for (int i = 0; i < temp.size(); i++) {
			if (ns.empty()) {
				files.push_back(temp[i].getFileName());
			}
			else
			{
				string tempNS = temp[i].getNamespace();
				for(auto k=ns.begin();k <ns.end();k++)
				if (tempNS == *k) {
					files.push_back(temp[i].getFileName());
				}
			}
		}
		return files;
	}
}