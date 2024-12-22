#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Information{
    int customer_id;
    string customer_name;
    string customer_city;
    string customer_state;
    string customer_country;
    string customer_phone;
    string customer_email;
};

// function prototypes
void create_output_screen_and_file();
void create_database(const string line, vector<Information> customer);
void create_table();
void insert_into_table();
void select_all_from_table_in_csv_mode(vector<Information> customer);

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

void create_database(const string line, vector<Information> customer) {
    outputFile << "> null " << ";" << endl;
    // Implementation here
    size_t values_pos = line.find("VALUES");

    string values_eli = line.substr(values_pos); // To remove the word "VALUES"
    string values_line = values_eli.substr(values_eli.find("(") + 1, values_eli.find(")") - values_eli.find("(") - 1); // To remove the parenthesis()

    //cout << values_line << endl;

    stringstream ss(values_line);
    string values_sep;
    vector<string> values;
    while ( getline(ss, values_sep, ',') ) // To separate a comma(,) between the data
    {
        values.push_back(values_sep);
    }

    Information customer_info;
    for (int i = 0; i < values.size(); i++)
    {
        if (values[i].find("'") != string::npos)
        {
            values[i] = values[i].substr(1, values[i].size() - 2); // To eliminate the single quote(')
            if (i == 1)
            {
                customer_info.customer_name = values[i]; // To collect the string data
            }
            else if (i == 2)
            {
                customer_info.customer_city = values[i];
            }
            else if (i == 3)
            {
                customer_info.customer_state = values[i];
            }
            else if (i == 4)
            {
                customer_info.customer_country = values[i];
            }
            else if (i == 5)
            {
                customer_info.customer_phone = values[i];
            }
            else if (i == 6)
            {
                customer_info.customer_email = values[i];
            }
        }
        else
        {
            int number = stoi(values[i]); // To convert string to integer
            if (i == 0)
            {
                customer_info.customer_id = number; // To collect the integer data
            }
        }
    }

    customer.push_back(customer_info); // Update the vector structure
    select_all_from_table_in_csv_mode(customer);
    //cout << customer_info.customer_id << customer_info.customer_name << customer_info.customer_city << customer_info.customer_state << customer_info.customer_country << customer_info.customer_phone << customer_info.customer_email << endl;

}

void create_table() {
    // Implementation here
}

void insert_into_table() {
    // Implementation here
}

void select_all_from_table_in_csv_mode(vector<Information> customer) {

    // Define sample table data using vectors
    /*vector<int> customer_id = {1, 2, 3, 4};
    vector<string> customer_name = {"name1", "name2", "name3", "name4"};
    vector<string> customer_city = {"city1", "city2", "city3", "city4"};
    vector<string> customer_state = {"state1", "state2", "state3", "state4"};
    vector<string> customer_country = {"country1", "country2", "country3", "country4"};
    vector<string> customer_phone = {"phone1", "phone2", "phone3", "phone4"};
    vector<string> customer_email = {"email1", "email2", "email3", "email4"};*/

    // Print table header in CSV format
    cout << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";
    outputFile << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";

    // Print table data in CSV format
    for (const auto& c : customer) {
        cout << c.customer_id << "," << c.customer_name << "," << c.customer_city << "," << c.customer_state << "," << c.customer_country << "," << c.customer_phone << "," << c.customer_email << "\n";
        outputFile << c.customer_id << "," << c.customer_name << "," << c.customer_city << "," << c.customer_state << "," << c.customer_country << "," << c.customer_phone << "," << c.customer_email << "\n";
    }
}


int main() {
    vector<Information> customer;

    ifstream fileInput;
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
    while (getline(fileInput, line))
        if (!line.empty())
        {
            if (line.find("CREATE TABLE") == 0)
            {
                //cout << line << endl;
            }
            else if (line.find("DATABASE") == 0)
            {
                //cout << line << endl;
            }
            else if (line.find("CREATE") == 0)
            {
                //cout << line << endl;
            }
            else if (line.find("INSERT INTO") == 0)
            {
                //cout << line << endl;
            }
            else if (line.find("VALUES") != string::npos)
            {
                create_database(line, customer);
            }
            else if (line.find("SELECT * FROM") == 0)
            {
                select_all_from_table_in_csv_mode(customer);
            }
            else
            {
                //cout << "no keyword" << endl;
            }
        }
        else
        {
            //cout << "----" << endl;
        }

    //create_output_screen_and_file();
    //create_database();

    fileInput.close();

    outputFile.close();

    //fileOutputName = "fileOutput1.txt"; //incorrect
    //fileInput.close(); CREATE fileOutputName << "";

    cout << "CREATE" << endl;
    cout << "DATABASES" << endl;

    return 0;
}
