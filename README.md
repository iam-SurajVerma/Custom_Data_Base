../
└── DatabaseProject/
    ├── CMakeLists.txt
    ├── main.cpp
    ├── include/
    │   ├── Database.h
    │   ├── Table.h
    │   └── Utility.h
    └── src/
        ├── Database.cpp
        ├── Table.cpp
        └── Utility.cpp
Simple In-Memory Database System

This project implements a simple in-memory database system using C++. It provides basic functionality to manage tables, insert, update, delete records, and save/load data to/from a file. This lightweight project demonstrates core database operations and is an excellent learning tool for beginners in software development.

Features

Create Tables: Define tables with customizable column names and types.

Insert Records: Add rows of data to tables.

Update Records: Modify existing data by specifying row and column indices.

Delete Records: Remove specific rows from a table.

View Records: Display all data in a table.

Save to File: Persist the database state by saving it to a file.

Load from File: Reconstruct the database from a saved file.

Technologies Used

Programming Language: C++

Concepts: Object-Oriented Programming (OOP), STL (Standard Template Library)

File Handling: Save and load data for persistence

Development Environment: Any C++ compiler (e.g., GCC, Clang, Visual Studio)

Skills Highlighted

OOP design principles

Data structures like vectors for dynamic storage

Error handling using exceptions

File I/O for data persistence
