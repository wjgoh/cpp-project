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

// function definitions
string outputFileName = "outputfile1.txt";
ofstream outputFile(outputFileName);

void create_output_screen_and_file() {
   
    
    if (!outputFile.is_open()) {
        cout << "Unable to create output file" << endl;
        return;
    }
    
    cout << "> CREATE " << outputFileName << ";" << endl;
    outputFile << "> CREATE " << outputFileName << ";" << endl;
    

    
}

void create_database() {
    outputFile << "> null " << ";" << endl;
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

int main() {
    fstream fileInput;
    string fileOutputName;

    string fileInputName = "fileInput1.mdb";
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
    

    create_output_screen_and_file();
    create_database();

    fileInput.close();

    outputFile.close();


    

    //fileOutputName = "fileOutput1.txt"; //incorrect
    //fileInput.close(); CREATE fileOutputName << "";
    
    cout << "CREATE" << endl;
    cout << "DATABASES" << endl;

    return 0;
}