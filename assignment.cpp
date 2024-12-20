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

    // Define sample table data using vectors
    vector<int> customer_id = {1, 2, 3, 4};
    vector<string> customer_name = {"name1", "name2", "name3", "name4"};
    vector<string> customer_city = {"city1", "city2", "city3", "city4"};
    vector<string> customer_state = {"state1", "state2", "state3", "state4"};
    vector<string> customer_country = {"country1", "country2", "country3", "country4"};
    vector<string> customer_phone = {"phone1", "phone2", "phone3", "phone4"};
    vector<string> customer_email = {"email1", "email2", "email3", "email4"};

    // Print table header in CSV format
    cout << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";
    outputFile << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";

    // Print table data in CSV format
    for (size_t i = 0; i < customer_id.size(); i++) {
        cout << customer_id[i] << "," << customer_name[i] << "," << customer_city[i] << ","
             << customer_state[i] << "," << customer_country[i] << "," << customer_phone[i] << ","
             << customer_email[i] << "\n";
        outputFile << customer_id[i] << "," << customer_name[i] << "," << customer_city[i] << ","
                   << customer_state[i] << "," << customer_country[i] << "," << customer_phone[i] << ","
                   << customer_email[i] << "\n";
    }
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
