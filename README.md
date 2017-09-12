# Dependancy Based Remote Code Publisher

The type of database used for this project is a NOSQL database and the contents of this database are persisted with XML format. The project performs Type Based Dependancy Analysis.In this project we will develop means to display source code files as web pages with embedded child links. Each link refers to a code file that the displayed code file depends on.
The created HTML files will be present in the HTMLFiles folder. The 'mainpage.html' is the index file that is created for all the other files.
The following are the main packages developed in this project-

1) TypeTable:
Provides a container class that stores type information needed for dependency analysis.
2) TypeAnalysis:
Finds all the types and global functions defined in each of a collection of C++ source files. It does this by building rules to detect:
type definitions - a) classes, structs, enums, typedefs, and aliases b)global function definitions c) global data definitions and capture their fully qualified names and the files where they are defined. It uses the TypeTable package to store that information.
3) DependencyAnalysis:
Finds, for each file in a specified file collection, all other files from the file collection on which they depend. File A depends on file B, if and only if, it uses the name of any type or global function or global data defined in file B. It might do that by calling a function or method of a type or by inheriting the type. Note that this intentionally does not record dependencies of a file on files outside the file set, e.g., language and platform libraries.
4) Strong Components:
A strong component is the largest set of files that are all mutually dependent. That is, all the files which can be reached from any other file in the set by following direct or transitive dependency links. The term "Strong Component" comes from the theory of directed graphs. There are a number of algorithms for finding strong components in graphs. My favorite is the Tarjan Algorithm, nicely described here: Tarjan Algorithm description and pseudo code. You will need a graph class to implement this. You will find one in the Repository: C++ graph class.
5) Display:
Uses information in the Analyzer's AST and TypeTable to build an effective display of the dependency relationships between all files in the selected file set.
6) NoSqlDb:
Stores and retrieves dependency information in a NoSqlDb<std::string>, you developed in Project #1. Here, child relationships denote compile dependencies.


The following are the features of the project-
1) Dependency analysis of the C++ source code files you will publish, using a Code Analyzer.
2) The ability to specify, on the command line, files to be published, by providing command line arguments for path and file patterns.
3) The ability to display any file cited on the command line, by starting a process that runs a browser of your choice, naming the specification of the file you want to display.

## Running the project-
Visual Studio Native Command Tools is required to run the project. From the root directory, execute the compile.bat and then run.bat. The project can also be run using Microsoft Visual Studio. 
The project is test on the Test-Packages folder. To publish other packages modify the run.bat file with root folder name and the type of files to be published.



Credits-
This project was developed for the Object Oriented Design course with guidance from Dr. Jim Fawcett. 
