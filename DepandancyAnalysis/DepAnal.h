#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
// DepAnal.h - Provides the depandancy analysis of files in specified collection       //
//  ver 1.0                                                                            //
//  Language:      Visual C++ 2015                                                     //
//  Platform:      Macbook Pro, Windows 10                                             //
//  Application:   Used to support strong components analysis of the files             //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University                         //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                            //
/////////////////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package is used to perform depandancy analysis on the files. With the help of the 
depandancy analysis of files, the strong components can be found and relations between
the various files in the file collection

Public Interface:
=================
checkDependancies() //checks the dependacies using the type table 
showDependancy()    //display the dependancies in type table
getDependancy()     //to get the dependancy map

Build Process:
==============
Required files
- Tokenizer.h ,ActionsAndRules.h, TypeAnal.h

Build commands 
devenv DependancyBasedCodePublisher.sln /rebuild debug

Maintenance History:
====================
ver 1.1: 04 Apr 2017
- modifying the dependancies to handle missing dependancies

ver 1.0 : 05 Mar 2017
- first release

*/
#include "../Tokenizer/Tokenizer.h"
#include "../Parser/ActionsAndRules.h"
#include "../TypeAnalysis/TypeAnal.h"
#include <iostream>
#include<unordered_map>
#include<set>

namespace CodeAnalysis
{
	////////////////////////////////////////////////////////////////////////////
	// DepAnal class helps in performing dependancy analysis of file collection
	// - this class uses the Tokenizer to extract tokens
	// - ifile Dependancies are stored as an map of vectors
	//

	class DepAnal {
	private:
		using Item = std::pair<string, vector<string>>;
		unordered_map<string, vector<string>> fileDependancy;
		AbstrSynTree& ASTref_;
		ScopeStack<ASTNode*> scopeStack_;
		Scanner::Toker toker_;
		TypeAnal ta;
		std::set<char> delimiters{ '\\' };
		std::vector<std::string> splitpath(const std::string& str);
		bool checkDuplicate(string file1, string file2);
		bool checkIfExist(vector<std::string> files,string file);
		std::string retrieveFiles(std::string val);

	public:
		DepAnal();
		void checkDependancies(TypeAnal ta);
		void showDependancy();
		void checkDependentFiles(TypeAnal ta);
		unordered_map<string, vector<string>> getDependancy();

	};

	 DepAnal::DepAnal() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack())
	{
	}
	//extract files from the path given
	std::vector<std::string> DepAnal::splitpath(const std::string& str)
	{
		std::vector<std::string> result;

		char const* pch = str.c_str();
		char const* start = pch;
		for (; *pch; ++pch)
		{
			if (delimiters.find(*pch) != delimiters.end())
			{
				if (start != pch)
				{
					std::string str(start, pch);
					result.push_back(str);
				}
				else
				{
					result.push_back("");
				}
				start = pch + 1;
			}
		}
		result.push_back(start);

		return result;
	}

	//check files before inserting to avoid adding duplicates
	 bool DepAnal::checkDuplicate(string f,string file) {
			vector<string> temp = fileDependancy[f];
			for (int i = 0; i < temp.size(); i++) {
				if (temp[i] == file)
					return true;
			}
		return false;
	}
	 bool DepAnal::checkIfExist(vector<std::string> files,string file) {
		 bool flag = false;
		 for (int i = 0; i < files.size(); i++) {
			 std::vector<std::string> file1 = splitpath(files[i]);
			 if (file1.back() == file)
				 flag=true;
		 }
		 return flag;
	 }
	//check all the file dependancies from the type table
void  DepAnal::checkDependancies(TypeAnal ta) {
		vector<std::string> files = ta.getFiles();
		for (int i = 0; i < files.size(); i++) {
			std::ifstream in(files[i]);
			if (!in.good())
			{
				std::cout << "\n  can't open " << files[i] << "\n\n";
			}
			std::string newSpecialChars = "., :, +, +=, \n { }";
			Scanner::Toker toker_;
			toker_.attach(&in);
			toker_.returnComments();
			std::vector<std::string> file = splitpath(files[i]);
			std::vector<std::string> cur_namespace;
			do
			{
				std::string tok = toker_.getTok();
				if (tok == "using") {
					tok = toker_.getTok();
					if (tok == "namespace") {
						cur_namespace.push_back(toker_.getTok());
					}
				}
				vector<string> dFiles = ta.getDependancy(tok,cur_namespace);
				if (dFiles.empty())
					continue;
				for (int j = 0; j < dFiles.size(); j++) {
					bool check= checkDuplicate(file.back(),dFiles[j]);
				if (dFiles[j] != file.back()&&!check) {
					fileDependancy[file.back()].push_back(dFiles[j]);
					}	
				}
			} while (in.good());
		}
	}

//extract file from the header
std::string DepAnal::retrieveFiles(std::string temp) {
	std::string list="";
	if (temp.find("<") != std::string::npos)
		return list;
	size_t c = temp.find("\"");
	if ( c!= std::string::npos) {
		size_t i = temp.find_last_of("/");
		size_t j = temp.find_last_of("\"");
		if (i == std::string::npos) {
			list = temp.substr(c + 1, j -c-1);
			return list;
		}
		list = temp.substr(i + 1, j - i - 1);
		return list;
	}
	size_t slash= temp.find("\\");
	if (slash != std::string::npos) {
		size_t j = temp.find_last_of("\"");
		list = temp.substr(slash + 1, j - c - 1);
		return list;
	}
	return list;
}

//validate dependancies through headers
void DepAnal::checkDependentFiles(TypeAnal ta) {
	vector<std::string> files = ta.getFiles();
	for (int i = 0; i < files.size(); i++) {
		std::vector<std::string> listInFile;
		std::ifstream in(files[i]);
		if (!in.good())
		{
			std::cout << "\n  can't open " << files[i] << "\n\n";
		}
		std::vector<std::string> file = splitpath(files[i]);
		std::string line;
		while (in.good()) {
		getline(in, line);
		if (line.find("#include") != std::string::npos) {
			std::string filename = retrieveFiles(line);
			if (filename != "")
				listInFile.push_back(filename);
		}
		for (int k = 0; k < listInFile.size(); k++) {
			bool check = checkDuplicate(file.back(), listInFile[k]);
			bool val = checkIfExist(files,listInFile[k]);
			if (val) {
				if (!check) {
					fileDependancy[file.back()].push_back(listInFile[k]);
				}
			}
		}
	}
	}
}
	//display the various dependacies of the file dependancy map
	void DepAnal::showDependancy() {
		for (Item it : fileDependancy)
		{
			std::cout << "\n'" << it.first << "' depends on ";
			vector<string> temp = it.second;
			for (int i = 0; i < temp.size(); i++) {
				std::cout << "'" << temp[i] << "'\t";
			}
			std::cout << "\n";
		}

	}

	//to get the file dependancy map
	 unordered_map<string, vector<string>> DepAnal::getDependancy() {
		return fileDependancy;
	}
}