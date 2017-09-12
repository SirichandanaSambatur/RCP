#pragma once
/////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database                   //
// ver 1.0                                                         //
// Apllication: support for NoSqlDb, Spring 2017                   //
// Platform: Macbook Pro, Win 10, Visual Studio 2015               //
// Source:      Jim Fawcett, CST 4-187, 443-3948                   //
//              jfawcett@twcny.rr.com                              //
// Author: Siri Chandana S, ssambatu@syr.edu                       //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is used to manage a database. The database holds 
* key/value pairs.
*
* It consists of the Element class that is used to implement the 
* metadata of value.
*
* An unordered map data structure is used to store the key/value pairs.
* This unordered map is a part of the NosqlDb Class.
*
* Required Files:
* ---------------
*  NoSqlDb.h, NoSqlDb.cpp
*  DBhelper.h
*  CppProperties.h
*
* Build Process:
* --------------
*   devenv CodeAnalyzer.sln /rebuild debug
*
* Maintenance History:
* --------------------
* Ver 1.0 : 7 Feb 2017
* - first release
*
*/

#include <unordered_map>
#include <string>
#include <sstream> 
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "../CppProperties/CppProperties.h"

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
// - it needs to store child data, something for you to implement
//
template<typename Data>
class Element
{
public:
	using Key = std::string;
	using Name = std::string;
	using Category = std::string;
	using TimeDate = std::string;
	using Description = std::string;
	using Children = std::string;

	Property<Name> name;            // metadata
	Property<Description> description;//metadata
	Property<Category> category;    // metadata
	Property<TimeDate> timeDate;    // metadata
	std::vector<Children> children;
	Property<Data> data;            // data

	std::string show();

};

template<typename Data>
std::string Element<Data>::show()
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "description" << " : " << description;
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n    " << std::setw(8) << "data" << " : " << data;
	out << "\n    " << std::setw(8) << "children" << " : ";

	for (auto i = children.begin(); i != children.end(); i++)
		out << *i << "	";
	out << "\n";
	return out.str();
}


/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
// - you will need to add query capability
//   That should probably be another class that uses NoSqlDb
//
template<typename Data>
class NoSqlDb
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;

	Keys keys();
	bool save(Key key, Element<Data> elem);
	bool remove(Key key);
	bool modify(Key key, Element<Data> elem);
	Element<Data> value(Key key);
	bool addRelation(Key parent, Key child);
	bool removeRelation(Key parent, Key child);
	void setFeature(bool timeOn);
	bool getFeature();
	std::vector<Key> getChild(Key key);
	size_t count();
private:
	using Item = std::pair<Key, Element<Data>>;
	bool timer;
	std::unordered_map<Key, Element<Data>> store;
};

//returns the keys present in the database
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}

//if the key and value given doesnt exist in the databse then insert them into the database
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	return true;
}

//return the children of a given key
template<typename Data>
std::vector<std::string> NoSqlDb<Data>::getChild(Key key) {
	std::vector<Key> temp;
	temp = value(key).children;
	return temp;

}
//remove the  key given from the databases and all its references to the database
template<typename Data>
bool NoSqlDb<Data>::remove(Key key)
{
	if (store.find(key) == store.end())
		return false;
	std::vector<Key> allKeys = keys();
	for (auto j = allKeys.begin(); j != allKeys.end(); j++) {
		removeRelation(*j, key);
	}
	store.erase(key);
	return true;
}

//return the value when the key is given from the database
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}

//creating a parent child relation between keys in the database
template<typename Data>
bool NoSqlDb<Data>::addRelation(Key parent, Key child)
{
	if (store.find(parent) == store.end() || store.find(child) == store.end())
		return false;
	Element<Data> parentElem;
	parentElem = value(parent);
	parentElem.children.push_back(child);
	store[parent] = parentElem;
	return true;
}

//removing a parent child relation between keys in the database
template<typename Data>
bool NoSqlDb<Data>::removeRelation(Key parent, Key child)
{
	Element<Data> parentElem;
	parentElem = value(parent);
	std::vector<Key> copyChildren = parentElem.children;
	copyChildren.erase(std::remove(copyChildren.begin(), copyChildren.end(), child), copyChildren.end());
	parentElem.children = copyChildren;
	store[parent] = parentElem;
	return true;
}

//set the timer on for persisting the database contents into the file
template<typename Data>
void NoSqlDb<Data>::setFeature(bool timeOn)
{
	this->timer= timeOn;
}

//checking the value of the timer
template<typename Data>
bool NoSqlDb<Data>::getFeature()
{
	return timer;
}

//total number of elements in the database
template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}

//updating the existing values in the database
template<typename Data>
bool NoSqlDb<Data>::modify(Key key, Element<Data> elem)
{
	if (store.find(key) == store.end())
		return false;
	store[key] = elem;
	return true;
}
