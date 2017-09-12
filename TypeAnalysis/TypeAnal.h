#pragma once
/////////////////////////////////////////////////////////////////////////////
// TypeAnal.h - Provides the type analysis to store in a type map          //
//  ver 1.0                                                                //
//  Language:      Visual C++ 2015                                         //
//  Platform:      Macbook Pro, Windows 10                                 //
//  Application:   Used to support dependancy analysis of the files        //
//  Author:        Siri Chandana Sambatur, ssambatu@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
==================
This package is used to perform type analysis using the type map that the 
type table class constructs. It has access to the Abstract Syntax tree, 
tokenizer and scopestack. It uses the rules and actions defined for each 
type of the variable.

Public Interface:
=================
getFiles()               //extract all the files
getDependancy()          //extract the dependancy
doTypeAnal()             //perform type analysis using type table
displayTypeTable()       //showing the type table
checkFile()              //to avoid duplicates
using SPtr

Build Process:
==============
Required files - ActionsAndrules.h, TypeTable.h

Build commands 
devenv DependancyBasedCodePublisher.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 05 Mar 2017
- first release

*/
#include "../Parser/ActionsAndRules.h"
#include "../TypeTable/TypeTable.h"
#include<iostream>
namespace CodeAnalysis {
	//////////////////////////////////////////////////////////////////////////
	//TypeAnal class helps in performing type anaylsis on file collection
	// - this class wuses the type table created
	// - DFS is used to traverse through the Abstract Syntax Tree
	//
	class TypeAnal
	{
	public:
		using SPtr = std::shared_ptr<ASTNode*>;
		TypeAnal();
		void doTypeAnal();
		vector<std::string> getFiles();
		vector<std::string> getDependancy(std::string tok, std::vector<std::string> ns);
		void displayTypeTable();
		bool checkFile(std::string file);

	private:
		void DFS(ASTNode* pNode);
		typeTable map;
		vector<string> fileTable;//store the files
		AbstrSynTree& ASTref_;
		ScopeStack<ASTNode*> scopeStack_;
		Scanner::Toker& toker_;
	};

TypeAnal::TypeAnal() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{
	}

	//to avoid adding duplicates in the filetable
 bool TypeAnal::checkFile(std::string file) {
		for (auto i = fileTable.begin(); i < fileTable.end(); i++) {
			if (*i == file)
				return true;
		}
		return false;
	}

	//perform DFS on the root of AST
void TypeAnal::DFS(ASTNode* pNode)
	{
		static std::string path = "";
		static std::string c_ns = "";
		if (pNode->path_ != path)
		{
			std::string filePath = pNode->path_;
			if(!checkFile(filePath))
				fileTable.push_back(filePath);
			c_ns = "";
			path = pNode->path_;
		}
		if (pNode->type_ == "namespace"&& pNode->name_ != c_ns) {
			c_ns = pNode->name_;
		}
		else if(pNode->type_ == "class"||pNode->type_=="enum" || pNode->type_=="function" || pNode->type_=="struct" ||pNode->type_=="interface" || pNode->type_=="lambda") {
			map.addEntry(pNode->package_, c_ns,pNode->type_, pNode->name_);
		}
		for (auto pChild : pNode->children_)
			DFS(pChild);
	}

	//Analysis of the files using the DFS
	 void TypeAnal::doTypeAnal()
	{
		ASTNode* pRoot = ASTref_.root();
		DFS(pRoot);
	}

	//extracting the files
	 vector<std::string> TypeAnal::getFiles() {
		return fileTable;
	}

	//extracting the dependancies
	 vector<std::string> TypeAnal::getDependancy(std::string tok, std::vector<std::string> ns) {
		vector<std::string> file = map.getFiles(tok,ns);
		return file;
	}

	//to display the typetable
	 void TypeAnal::displayTypeTable() {
		map.display();
	}
}