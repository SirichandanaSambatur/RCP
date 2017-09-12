#pragma once

/////////////////////////////////////////////////////////////////////
//DBHelpher.h - Helper of the NoSql database                       //
// ver 1.0                                                         //
// Apllication: support for NoSqlDb, Spring 2017                   //
// Platform: Macbook Pro, Win 10, Visual Studio 2015               //
// Source:      Jim Fawcett, CST 4-187, 443-3948                   //
//              jfawcett@twcny.rr.com                              //
//Author: Siri Chandana S, ssambatu@syr.edu                        //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This is used to assist the user in performing various operations
* on the database like insertion, deletion, modification etc.
*
* It also wraps the contetns of the NoSqlDb and Elemnt class together
* so that they are not directly accesible to users. It basically provides the feature of encapsulation
*
* Required Files:
* ---------------
*   - NoSqlDb.h, NoSqlDb.cpp,
*   - DBHelper.h
*
* Build Process:
* --------------
* devenv CodeAnalyzer.sln /rebuild debug
*
* Maintenance History:
* --------------------
* Ver 1.0 : 7 Feb 2017
* - first release
*
*/
#include "NoSqlDb.h"

/////////////////////////////////////////////////////////////////////
// DBHelper class helps in performing basic operations on the DB
// - this class wraps both the contents of the element and nosqldb
// - it performs insertion,deletion,modifcation,addchildren 
//    and delete children on the database
//
template <typename Data>
class DBHelper {
public:
	using key = std::string;
	using Name = std::string;
	using Category = std::string;
	using TimeDate = std::string;
	using Description = std::string;
	using dataValue = Data;


	std::string msg;
	NoSqlDb<Data> dbptr;
	Element<Data> element;


public:
	DBHelper() {

	}
	DBHelper(NoSqlDb<Data> dbptr) {
		this->dbptr = dbptr;
	}
	std::string insertion(Name name, Category category, Description des, TimeDate timeDate, dataValue data);
	std::string deletion(Name name);
	std::string modifyInstance(key oldValue, Name name, Category category, Description des, TimeDate timeDate, dataValue data);
	std::string modify(key K, std::string Attribute, std::string newValue);
	std::string addChild(key parent, key child);
	std::string removeChild(key parent, key child);
	std::vector<std::string> getAllKeys();
	std::vector<std::string> getChildren(key val);
	void setFeature(bool time);
	NoSqlDb<Data> getDB();
	void display();
	int sizeofDB();
};

// insert a key/value pair into the database
template<typename Data>
std::string DBHelper<Data>::insertion(Name name, Category category, Description des, TimeDate timeDate, dataValue data)
{
	element.name = name;
	element.category = category;
	element.timeDate = timeDate;
	element.data = data;
	element.description = des;
	if (!(dbptr.save(element.name, element)))
		msg = "\n . . .Unsucessful insertion, Key exists. . .";
	else
		msg = "\n . . .Successful insertion. . .";
	return msg;
}

//delete key/value pair from the database
template<typename Data>
std::string  DBHelper<Data>::deletion(Name name)
{
	element.name = name;
	if (!(dbptr.remove(element.name)))
		msg = "\n . . .Unsucessful deletion, Key doesn't exists. . .";
	else
		msg = "\n . . .Successful deletion. . .";
	return msg;
}

//modifying an instance of the databse
template<typename Data>
std::string DBHelper<Data>::modifyInstance(key oldValue, Name name, Category category, Description des, TimeDate timeDate, dataValue data)
{
	element.name = name;
	element.category = category;
	element.timeDate = timeDate;
	element.data = data;
	if (!(dbptr.modify(oldValue, element)))
		msg = "\n . . .Unsucessful modification, Key doesn't exists. . .";
	else
		msg = "\n . . .Successful modification. . .";
	return msg;
}

//modifying an atrribute of the database
template<typename Data>
std::string DBHelper<Data>::modify(key K, std::string Attribute, std::string newValue)
{
	element = dbptr.value(K);

	if (Attribute == "name")
		element.name = newValue;
	else if (Attribute == "category")
		element.category = newValue;
	else if (Attribute == "description")
		element.description = newValue;
	dbptr.modify(K, element);
	return std::string();
}

//adding child relation
template<typename Data>
std::string DBHelper<Data>::addChild(key parent, key child)
{
	bool v = dbptr.addRelation(parent, child);
	if (v == true)
		msg = " \n . . . Succesfullly added child to parent relation . . .";
	else
		msg = " \n . . . Couldn't add child to parent relation . . .";
	return msg;
}

//removing child relation
template<typename Data>
inline std::string DBHelper<Data>::removeChild(key parent, key child)
{
	dbptr.removeRelation(parent, child);
	if (v == true)
		msg = " \n . . . Succesfullly removed child to parent relation . . .";
	else
		msg = " \n . . . Couldn't remove child to parent relation . . .";
	return msg;
}

//all the  keys present in the database returned
template<typename Data>
std::vector<std::string> DBHelper<Data>::getAllKeys()
{
	std::vector<key> temp;
	temp = dbptr.keys();
	return temp;
}

template<typename Data>
 std::vector<std::string> DBHelper<Data>::getChildren(key val)
{
	 std::vector<std::string> temp;
	 temp = dbptr.getChild(val);
	return temp;
}

template<typename Data>
 void DBHelper<Data>::setFeature(bool time)
{
	dbptr.setFeature(time);
}

//dbpointer can be accessed
template<typename Data>
NoSqlDb<Data> DBHelper<Data>::getDB()
{
	return dbptr;
}

//show the entries in the database
template<typename Data>
void DBHelper<Data>::display()
{
	NoSqlDb<Data>::Keys ikeys = dbptr.keys();
	for (NoSqlDb<Data>::Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << dbptr.value(key).show();
	}
	std::cout << "\n key/value pairs retrieved = " << dbptr.count() << "\n";
	std::cout << "\n\n";
}

//the size of the db
template<typename Data>
int DBHelper<Data>::sizeofDB()
{
	return dbptr.count();
}