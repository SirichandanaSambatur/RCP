/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                 //
// ver 1.0                                                         //
// Apllication: support for NoSqlDb, Spring 2017                   //
//Platform: Macbook Pro, Win 10, Visual Studio 2015                //
// Source:      Jim Fawcett, CST 4-187, 443-3948                   //
//              jfawcett@twcny.rr.com                              //
//Author: Siri Chandana S, ssambatu@syr.edu                        //
/////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "NoSqlDb.h"
#include "DBHelper.h"
#include <iostream>
#include <chrono>
#include <ctime>

#ifdef TEST_NOSQLDB

using StrData = std::string;
using intData = int;


//------- test stub ---------
int main()
{
	std::string time;
	std::string msg;
	//Accesing the system clock
	std::chrono::time_point<std::chrono::system_clock> current_time;
	current_time = std::chrono::system_clock::now();
	std::time_t current = std::chrono::system_clock::to_time_t(current_time);
	time = std::ctime(&current);
	std::cout << "\n  Demonstrating NoSql Helper Code";
	std::cout << "\n =================================\n";
	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";
	DBHelper<StrData> db;
	msg = db.insertion("elem1", "test", "string type database first element.", time, "elem1's StrData");
	std::cout << "\n" << msg << "\n";
	msg = db.insertion("elem2", "test1", "string type database second element.", time, "elem2's StrData");
	std::cout << "\n" << msg << "\n";
	msg = db.insertion("elem3", "test1", "string type database third element.", time, "elem3's StrData");
	std::cout << "\n" << msg << "\n";
	msg = db.insertion("elem4", "sub", "inserted this element fourth", time, "elem4's StrData");
	std::cout << "\n" << msg << "\n";
	msg = db.insertion("elem5", "sub", "this element is a part of the sub category.", time, "elem5's StrData");
	std::cout << "\n" << msg << "\n";
	msg = db.insertion("elem6", "item", " string type database sixth element.", time, "elem6's StrData");
	std::cout << "\n" << msg << "\n";

	std::cout << "\n Adding Relations to NoSqlDb<string>";
	std::cout << "\n ---------------------------------------\n";
	msg = db.addChild("elem1", "elem2");
	std::cout << "\n" << msg << "\n";
	msg = db.addChild("elem1", "elem3");
	std::cout << "\n" << msg << "\n";

	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";
	db.display();

	std::cout << "\n Deleting the element3 with key - 'elem3' ";
	std::cout << "\n ---------------------------------------\n";
	msg = db.deletion("elem3");
	std::cout << "\n" << msg << "\n";

	std::cout << "\n  Retrieving elements from NoSqlDb<int> after deletion";
	std::cout << "\n ---------------------------------------\n";
	db.display();

	std::cout << "\n  Creating and saving NoSqlDb elements with int data";
	std::cout << "\n ----------------------------------------------------\n";

	DBHelper<intData> idb;
	msg = idb.insertion("elem1", "test1", "iinteger type database first element.", time, 1);
	std::cout << "\n" << msg << "\n";
	msg = idb.insertion("elem2", "test1", "integer type database second element.", time, 2);
	std::cout << "\n" << msg << "\n";
	msg = idb.insertion("item6", "sub", "integer type database third element.", time, 67);
	std::cout << "\n" << msg << "\n";
	msg = idb.insertion("item3", "test", "integer type database third item.", time, 656);
	std::cout << "\n" << msg << "\n";
	msg = idb.insertion("elem3", "test", "integer type database third element.", time, 39);
	std::cout << "\n" << msg << "\n";
	msg = idb.insertion("elem4", "sub", "integer type database fourth element.", time, 9);
	std::cout << "\n" << msg << "\n";
	msg = idb.insertion("elem5", "example", "integer type database fifth element of example.", time, 5);
	std::cout << "\n" << msg << "\n";
	msg = idb.insertion("elem6", "example", "integer database has sixth element", time, 6);
	std::cout << "\n" << msg << "\n";

	std::cout << "\n Adding Relations to NoSqlDb<int>";
	std::cout << "\n ---------------------------------------\n";
	msg = idb.addChild("elem1", "elem2");
	std::cout << "\n" << msg << "\n";
	msg = idb.addChild("elem1", "elem5");
	std::cout << "\n" << msg << "\n";
	msg = idb.addChild("elem1", "elem6");
	std::cout << "\n" << msg << "\n";
	msg = idb.addChild("elem5", "elem2");
	std::cout << "\n" << msg << "\n";
	msg = idb.addChild("elem6", "elem2");
	std::cout << "\n" << msg << "\n";

	std::cout << "\n  Retrieving elements from NoSqlDb<int>";
	std::cout << "\n ---------------------------------------\n";
	idb.display();

	std::cout << "\n Modifying the element2 instance with key - 'elem2' ";
	std::cout << "\n ---------------------------------------\n";
	msg = idb.modifyInstance("elem2", "elem7", "test", " ", time, 5);
	std::cout << "\n" << msg << "\n";

	std::cout << "\n  Retrieving elements from NoSqlDb<int> after modification";
	std::cout << "\n ---------------------------------------\n";
	idb.display();

	DBHelper<double> dbh;
	std::cout << "\n  Creating and saving NoSqlDb elements with double data";
	std::cout << "\n -------------------------------------------------------\n";


	msg = dbh.insertion("e1", "xyz", " ", time, 3.45);
	std::cout << "\n" << msg << "\n";
	msg = dbh.insertion("e2", "xyz", " ", time, 5.45);
	std::cout << "\n" << msg << "\n";
	msg = dbh.insertion("e3", "xyz", " ", time, 3.4);
	std::cout << "\n" << msg << "\n";
	msg = dbh.insertion("e4", "xyz", " ", time, 8.45);
	std::cout << "\n" << msg << "\n";
	msg = dbh.insertion("e5", "xyz", " ", time, 9.45);
	std::cout << "\n" << msg << "\n";

	std::cout << "\n  Retrieving elements from NoSqlDb<double> after insertion";
	std::cout << "\n ---------------------------------------\n";
	dbh.display();

	std::cout << "\n Modification of element1 instance with key= 'e1' ";
	std::cout << "\n ---------------------------------------\n";
	msg = dbh.modifyInstance("e1", "e6", "jkil", " ", time, 5.5555);
	std::cout << "\n" << msg << "\n";

	std::cout << "\n  Retrieving elements from NoSqlDb<double> after modification";
	std::cout << "\n ---------------------------------------\n";
	dbh.display();

	std::cout << "\n Deletion of element1 with key= 'e1' ";
	std::cout << "\n ---------------------------------------\n";
	msg = dbh.deletion("e1");
	std::cout << "\n" << msg << "\n";
	std::cout << "\n  Retrieving elements from NoSqlDb<double> after deletion";
	std::cout << "\n ---------------------------------------\n";
	dbh.display();
}
#endif


