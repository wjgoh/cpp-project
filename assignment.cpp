//*******************************************************************************************
//Program: Bachelor of Computer Science
//Course: CPP6114 Programming Fundamentals
//Lecture Class: TC2L
//Tutorial Class: TT4L
//Trimester: 2430
//Member_1: ID | NAME | EMAIL | PHONE
//Member_2: ID | NAME | EMAIL | PHONE
//Member_3: ID | NAME | EMAIL | PHONE
//Member_4: 242UC244S3 | TENG MING HEIN | TENG.MING.HEIN@student.mmu.edu.my | 016-7831558
//*******************************************************************************************
//Task Distribution
//Member_1:
//Member_2:
//Member_3:
//Member_4:
//*******************************************************************************************
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Information
{
    int customer_id;
    string customer_name;
    string customer_city;
    string customer_state;
    string customer_country;
    string customer_phone;
    string customer_email;
};

// function prototypes
void create_output_screen_and_file(const string &line);
void create_database(const string &line, vector<Information> &customer);
void create_table(const string& line, const string &command);
void insert_into_table();
void select_all_from_table_in_csv_mode(const vector<Information> &customer);

// function definitions
// string outputFileName = "outputfile1.txt";
ofstream outputFile;
bool headerPrinted = false;

void create_output_screen_and_file(const string &line)
{
    size_t file_begin = line.find(" ") + 1;                                 // Get the start position of output file name
    size_t file_end = line.find(";");                                       // Get the end position of output file name
    string outputFileName = line.substr(file_begin, file_end - file_begin); // Get the output file name

    outputFile.open(outputFileName);

    if (!outputFile.is_open())
    {
        cout << "Unable to create output file" << endl;
        return;
    }

    // cout << "> CREATE " << outputFileName << ";" << endl;
    cout << "> " << line << endl;
    // outputFile << "> CREATE " << outputFileName << ";" << endl;
    outputFile << "> " << line << endl;
}

void create_database(const string &line, vector<Information> &customer)
{
    size_t values_pos = line.find("VALUES");

    string values_eli = line.substr(values_pos);                                                                       // To remove the word "VALUES"
    string values_line = values_eli.substr(values_eli.find("(") + 1, values_eli.find(")") - values_eli.find("(") - 1); // To remove the parenthesis()

    stringstream ss(values_line);
    string values_sep;
    vector<string> values;
    while (getline(ss, values_sep, ',')) // To separate a comma(,) between the data
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
}

void create_table(const string& line, const string &command) {
    /*cout << "> CREATE TABLE customer:" << endl;
    outputFile << "> CREATE TABLE customer:" << endl;

    string headers[] = {
        "customer_id",
        "customer_name",
        "customer_city",
        "customer_state",
        "customer_country",
        "customer_phone",
        "customer_email",
    };

    // Initialize constants

    const int numColumn = sizeof(headers) / sizeof(headers[0]); // Number of columns


// print column names
    for (int i = 0; i < numColumn; i++) {
        cout  << headers[i] <<endl;
        outputFile << headers[i]<< endl;


*/
    size_t tableName_begin = line.find("TABLE") + 6;
    size_t tableName_end = line.find("(");
    string tableName = line.substr(tableName_begin, tableName_end - tableName_begin);

    size_t header_begin = command.find("(") + 1;
    size_t header_end = command.find(")");
    string header_line = command.substr(header_begin, header_end - header_begin);

    stringstream ss(header_line);
    string header_sep;
    vector<string> columns;

    while ( getline(ss, header_sep, ',') )
    {
        string header_name = header_sep.substr(0, header_sep.find(" "));
        string data_type = header_sep.substr(header_sep.find(" ") + 1);

        string column = header_name + " " + data_type;

        columns.push_back(column);
    }

    for (size_t i = 0; i < columns.size(); i++)
    {
        if (i == columns.size() - 1)
        {
            cout << columns[i] << endl;
        }
        else
        {
            cout << columns[i] << "," << endl;
        }
    }

}

void insert_into_table(const string &line, vector<Information> &customer)
{
    // Extract values inside parentheses
    size_t start = line.find("(") + 1;
    size_t end = line.find(")");
    string values = line.substr(start, end - start);

    // Remove single quotes and split by commas
    for (char &c : values)
    {
        if (c == '\'')
            c = ' ';
    }
    stringstream ss(values);
    vector<string> fields;
    string field;

    while (getline(ss, field, ','))
    {
        fields.push_back(field);
    }

    // Create a new customer and populate fields
    Information newCustomer;
    newCustomer.customer_id = stoi(fields[0]);
    newCustomer.customer_name = fields[1];
    newCustomer.customer_city = fields[2];
    newCustomer.customer_state = fields[3];
    newCustomer.customer_country = fields[4];
    newCustomer.customer_phone = fields[5];
    newCustomer.customer_email = fields[6];

    // Add to the customer vector
    customer.push_back(newCustomer);

    // Output for confirmation
    cout << "> " << line << endl;
    outputFile << "> " << line << endl;
}

void select_all_from_table_in_csv_mode(const vector<Information> &customer)
{
    if (!headerPrinted)
    {
        // Print table header in CSV format
        cout << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";
        outputFile << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";
        headerPrinted = true;
    }

    // Print table data in CSV format
    for (const auto &c : customer)
    {
        cout << c.customer_id << "," << c.customer_name << "," << c.customer_city << "," << c.customer_state << "," << c.customer_country << "," << c.customer_phone << "," << c.customer_email << "\n";
        outputFile << c.customer_id << "," << c.customer_name << "," << c.customer_city << "," << c.customer_state << "," << c.customer_country << "," << c.customer_phone << "," << c.customer_email << "\n";
    }
}

int main()
{
    vector<Information> customer;

    ifstream fileInput;
    string fileOutputName;

    string fileInputName = "fileInput1.mdb";

    fileInput.open(fileInputName);

    if (!fileInput.is_open())
    {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    // create_output_screen_and_file();

    string line;
    while (getline(fileInput, line))
        if (!line.empty())
        {
            if (line.find("CREATE TABLE") == 0)
            {
                string command;
                while (getline(fileInput, command))
                {
                    if (command.find("INT") != string::npos || command.find("TEXT") != string::npos)
                    {
                        create_table(line, command);
                    }
                    else if (command.find(");"))
                    {
                        break;
                    }
                }
            }
            else if (line.find("DATABASE") == 0)
            {
                // cout << line << endl;
            }
            else if (line.find("CREATE") == 0)
            {
                create_output_screen_and_file(line);
            }
            else if (line.find("INSERT INTO") == 0)
            {
                // cout << line << endl;
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
                // cout << "no keyword" << endl;
            }
        }
        else
        {
            // cout << "----" << endl;
        }

    fileInput.close();
    outputFile.close();

    // Print the customer data in CSV format once
    select_all_from_table_in_csv_mode(customer);

    cout << "CREATE" << endl;
    cout << "DATABASES" << endl;

    return 0;
}
