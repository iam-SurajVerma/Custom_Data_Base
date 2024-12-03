#include <iostream>  // For input/output operations
#include <vector>    // For using the vector container
#include <string>    // For string manipulation
#include <sstream>   // For parsing strings
#include <fstream>   // For file input/output

using namespace std;

// Define a class to represent a simple database
class Database {
public:
    // Constructor to initialize the Database object
    Database() {}

    // Create a new table with specified column names and types
    void createTable(const string& tableName, const vector<string>& columnNames, const vector<string>& columnTypes) {
        Table newTable;
        newTable.name = tableName;  // Assign the table name
        for (size_t i = 0; i < columnNames.size(); ++i) {
            // Add columns to the table
            newTable.columns.push_back({columnNames[i], columnTypes[i]});
        }
        // Add the new table to the list of tables in the database
        tables.push_back(newTable);
    }

    // Insert a new record (row) into a specified table
    void insertRecord(const string& tableName, const vector<string>& values) {
        for (Table& table : tables) {
            if (table.name == tableName) {
                // Ensure the number of values matches the number of columns
                if (values.size() != table.columns.size()) {
                    throw runtime_error("Invalid number of values for table: " + tableName);
                }
                // Add the new record to the table's data
                table.data.push_back(values);
                return;
            }
        }
        // Throw an error if the table is not found
        throw runtime_error("Table not found: " + tableName);
    }

    // Update a record in a specific table at a given row and column index
    void updateRecord(const string& tableName, int rowIndex, int columnIndex, const string& newValue) {
        for (Table& table : tables) {
            if (table.name == tableName) {
                // Validate row and column indices
                if (rowIndex >= 0 && rowIndex < table.data.size() && columnIndex >= 0 && columnIndex < table.columns.size()) {
                    // Update the specified value
                    table.data[rowIndex][columnIndex] = newValue;
                    return;
                }
                throw runtime_error("Invalid row or column index in table: " + tableName);
            }
        }
        // Throw an error if the table is not found
        throw runtime_error("Table not found: " + tableName);
    }

    // Delete a record (row) from a specific table
    void deleteRecord(const string& tableName, int rowIndex) {
        for (Table& table : tables) {
            if (table.name == tableName) {
                // Validate the row index
                if (rowIndex >= 0 && rowIndex < table.data.size()) {
                    // Remove the specified row
                    table.data.erase(table.data.begin() + rowIndex);
                    return;
                }
                throw runtime_error("Invalid row index in table: " + tableName);
            }
        }
        // Throw an error if the table is not found
        throw runtime_error("Table not found: " + tableName);
    }

    // Display all records in a specific table
    void viewRecords(const string& tableName) {
        for (Table& table : tables) {
            if (table.name == tableName) {
                cout << "Table: " << table.name << endl;
                cout << "\t";
                // Print column headers
                for (const Column& column : table.columns) {
                    cout << column.name << "\t";
                }
                cout << endl;
                // Print each row of data
                for (const vector<string>& row : table.data) {
                    cout << "\t";
                    for (const string& value : row) {
                        cout << value << "\t";
                    }
                    cout << endl;
                }
                return;
            }
        }
        // Throw an error if the table is not found
        throw runtime_error("Table not found: " + tableName);
    }

    // Save the entire database to a file
    void dumpToFile(const string& filename) {
        ofstream file(filename);
        // Check if the file can be opened
        if (!file.is_open()) {
            throw runtime_error("Failed to open file for writing: " + filename);
        }

        for (const Table& table : tables) {
            // Write table name
            file << "Table: " << table.name << endl;
            // Write column names and types
            for (const Column& column : table.columns) {
                file << "\t" << column.name << " (" << column.type << ")" << endl;
            }
            // Write table data (records)
            for (const vector<string>& row : table.data) {
                for (const string& value : row) {
                    file << value << "\t";
                }
                file << endl;
            }
            file << endl;
        }
        file.close();
    }

    // Load a database from a file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        // Check if the file can be opened
        if (!file.is_open()) {
            throw runtime_error("Failed to open file for reading: " + filename);
        }

        string line;
        while (getline(file, line)) {
            if (line.substr(0, 7) == "Table: ") {
                // Parse table name
                string tableName = line.substr(7);
                createTable(tableName, {}, {});  // Create an empty table initially
                while (getline(file, line) && !line.empty()) {
                    if (line.substr(0, 1) == "\t") {
                        // Parse column name and type
                        stringstream ss(line.substr(1));
                        string columnName, columnType;
                        ss >> columnName >> columnType;
                        tables.back().columns.push_back({columnName, columnType});
                    } else {
                        // Parse record data
                        stringstream ss(line);
                        vector<string> values;
                        string value;
                        while (ss >> value) {
                            values.push_back(value);
                        }
                        insertRecord(tableName, values);
                    }
                }
            }
        }
        file.close();
    }

private:
    // Define a structure to represent a column in a table
    struct Column {
        string name; // Column name
        string type; // Data type of the column
    };

    // Define a structure to represent a table
    struct Table {
        string name;                  // Table name
        vector<Column> columns;       // List of columns in the table
        vector<vector<string>> data;  // Table data (list of rows)
    };

    // List of tables in the database
    vector<Table> tables;
};

// Entry point of the program
int main() {
    Database db;                     // Create a database instance
    string studentsdb = "studentsdb.txt";

    // Uncomment to load database from a file
    // db.loadFromFile(studentsdb);

    // Create a new table named "students" with specified columns
    db.createTable("students", {"id", "name", "age"}, {"int", "string", "int"});

    // Insert multiple records into the "students" table
    db.insertRecord("students", {"1", "Alice", "20"});
    db.insertRecord("students", {"2", "Bob", "22"});
    db.insertRecord("students", {"3", "Charlie", "19"});
    db.insertRecord("students", {"4", "Diana", "23"});
    db.insertRecord("students", {"5", "Eve", "21"});

    // Display the records before making updates or deletions
    cout << "Initial Records:" << endl;
    db.viewRecords("students");

    // Update a record (change Diana's age to 24)
    db.updateRecord("students", 3, 2, "24");

    // Update another record (change Charlie's name to "Charles")
    db.updateRecord("students", 2, 1, "Charles");

    // Display the records after updates
    cout << "\nRecords After Updates:" << endl;
    db.viewRecords("students");

    // Delete a record (remove Eve's record)
    db.deleteRecord("students", 4);

    // Delete another record (remove Alice's record)
    db.deleteRecord("students", 0);

    // Display the records after deletions
    cout << "\nRecords After Deletions:" << endl;
    db.viewRecords("students");

    // Create another table named "courses" with specified columns
    db.createTable("courses", {"course_id", "course_name", "credits"}, {"int", "string", "int"});

    // Insert records into the "courses" table
    db.insertRecord("courses", {"101", "\tMathematics", "4"});
    db.insertRecord("courses", {"102", "\tPhysics", "\t3"});
    db.insertRecord("courses", {"103", "\tChemistry", "4"});
    db.insertRecord("courses", {"104", "\tBiology", "\t3"});

    // Display all records in the "courses" table
    cout << "\nRecords in Courses Table:" << endl;
    db.viewRecords("courses");

    // Create another table named "enrollment" with specified columns
    db.createTable("enrollment", {"student_id", "course_id", "semester"}, {"int", "int", "string"});

    // Insert records into the "enrollment" table
    db.insertRecord("enrollment", {"1", "101", "Fall\t\t2024"});
    db.insertRecord("enrollment", {"2", "102", "Spring\t\t2024"});
    db.insertRecord("enrollment", {"3", "103", "Fall\t\t2024"});
    db.insertRecord("enrollment", {"4", "104", "Spring\t\t2024"});

    // Display all records in the "enrollment" table
    cout << "\nRecords in Enrollment Table:" << endl;
    db.viewRecords("enrollment");

    // Save the database to a file
    db.dumpToFile(studentsdb);

    // Load the database back from the file to ensure persistence works
    Database db2;
    db2.loadFromFile(studentsdb);

    // Display the loaded database records to verify correctness
    cout << "\nRecords Loaded From File:" << endl;
    db2.viewRecords("students");
    db2.viewRecords("courses");
    db2.viewRecords("enrollment");

    return 0;
}


