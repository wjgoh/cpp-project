#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// function prototypes
void create_output_screen_and_file();
void create_database();
void create_table();
void insert_into_table();
void select_all_from_table_in_csv_mode();

int main() {
    fstream fileInput;
    string fileOutputName;

    string fileInputName = "C:\\yourname\\fileInput1.mdb";
    //string fileInputName = "C:\\yourname\\fileInput2.mdb";
    //string fileInputName = "C:\\yourname\\fileInput3.mdb";

    fileInput.open(fileInputName);

    if (!fileInput.is_open()) {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    string line;
    while (getline(fileInput, line)) {
        cout << line << endl;
    }
    fileInput.close();

    
    //fileOutputName = "fileOutput1.txt"; //incorrect
    //fileInput.close(); CREATE fileOutputName << "";
    
    cout << "CREATE" << endl;
    cout << "DATABASES" << endl;

    return 0;
}

// function definitions
void create_output_screen_and_file(const string& outputFileName) {
    // Implementation here
}

void create_database() {
    // Implementation here
}

void create_table() {
    // Implementation here
}

void insert_into_table() {
    // Implementation here
}

void select_all_from_table_in_csv_mode() {
    // Implementation here
    
}