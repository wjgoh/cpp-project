//*******************************************************************************************
// Program: Bachelor of Computer Science
// Course: CPP6114 Programming Fundamentals
// Lecture Class: TC2L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 242UC244S9 | GOH WEI JING | goh.wei.jing@student.mmu.edu.my | 011-10872022
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: 242UC244K7 | CHIN KUAN SIING | CHIN.KUAN.SIING@student.mmu.edu.my |011-54070928
// Member_4: 242UC244S3 | TENG MING HEIN | TENG.MING.HEIN@student.mmu.edu.my | 016-7831558
//*******************************************************************************************
// Task Distribution
// Member_1: create_output_screen_and_file, create_table function, select_all_from_table_in_csv_mode
// Member_2:
// Member_3:create_insert_into_table,create_table function
// Member_4: create_database function, create_table function
//*******************************************************************************************
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string fileInputName = "fileInput1.mdb"; // File name

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

struct Row
{
    int num_Row;
};

// function prototypes
void create_output_screen_and_file(const string &line);
void create_database(const string &line, vector<Information> &customer);
void create_table(const string &line);
void insert_into_table(const string &line, vector<Row> &table_Row);
void select_all_from_table_in_csv_mode(const vector<Information> &customer);

// function definitions
ofstream outputFile;
bool headerPrinted = false;
string tableName;

void create_output_screen_and_file(const string &line)
{
    size_t file_begin = line.find(" ") + 1;
    size_t file_end = line.find(";");
    string outputFileName = line.substr(file_begin, file_end - file_begin);

    outputFile.open(outputFileName);

    if (!outputFile.is_open())
    {
        cout << "Unable to create output file" << endl;
        return;
    }

    cout << "> CREATE " << outputFileName << ";" << endl;
    outputFile << "> CREATE " << outputFileName << ";" << endl;
}

void create_database(const string &line, vector<Information> &customer)
{
    size_t values_pos = line.find("VALUES");

    string values_eli = line.substr(values_pos);                                                                       // To remove the word "VALUES"
    string values_line = values_eli.substr(values_eli.find("(") + 1, values_eli.find(")") - values_eli.find("(") - 1); // To remove the parenthesis()

    stringstream ss(values_line);
    string values_sep;
    vector<string> values;
    while (getline(ss, values_sep, ','))
    { // To separate a comma(,) between the data
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

void create_table(const string &line)
{
    size_t tableName_begin = line.find("TABLE") + 6;
    size_t tableName_end = line.find("(");
    tableName = line.substr(tableName_begin, tableName_end - tableName_begin); // Get table name

    string headers[] = {
        "customer_id INT,",
        "customer_name TEXT,",
        "customer_city TEXT,",
        "customer_state TEXT,",
        "customer_country TEXT,",
        "customer_phone TEXT,",
        "customer_email TEXT",
    };

    // Initialize table row and column
    const int table_Col = sizeof(headers) / sizeof(headers[0]); // Number of columns

    cout << "> CREATE TABLE " << tableName << "(" << endl;
    outputFile << "> CREATE TABLE " << tableName << "(" << endl;

    // Print column names
    for (int i = 0; i < table_Col; i++)
    {
        cout << headers[i] << endl;
        outputFile << headers[i] << endl;
    }

    cout << ");" << endl;
    outputFile << ");" << endl;
}

void insert_into_table(const string &line, vector<Row> &table_Row)
{
    Row row;
    row.num_Row = table_Row.size() + 1; // Update the table row while "INSERT INTO" is found
    table_Row.push_back(row);

    // Output for confirmation
    cout << "> " << line << endl;
    outputFile << "> " << line << endl;
}

void select_all_from_table_in_csv_mode(const vector<Information> &customer)
{
    cout << "> SELECT FROM * " << tableName << ";" << endl;
    outputFile << "> SELECT FROM * " << tableName << ";" << endl;

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
    ifstream fileInput;
    string fileOutputName;

    fileInput.open(fileInputName);

    if (!fileInput.is_open())
    {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    vector<Information> customer;
    vector<Row> table_Row;

    string line;
    while (getline(fileInput, line))
        if (!line.empty())
        {
            if (line.find("CREATE TABLE") == 0)
            {
                create_table(line);
            }
            else if (line.find("DATABASE") == 0)
            {
                cout << "> " << line << endl;
                outputFile << "> " << line << endl;
                cout << fileInputName << endl;
                outputFile << fileInputName << endl;
            }
            else if (line.find("CREATE") == 0)
            {
                create_output_screen_and_file(line);
            }
            else if (line.find("TABLE") == 0)
            {
                cout << "> " << line << endl;
                outputFile << "> " << line << endl;
                cout << tableName << endl;
                outputFile << tableName << endl;
            }
            else if (line.find("INSERT INTO") == 0)
            {
                insert_into_table(line, table_Row);
            }
            else if (line.find("VALUES") != string::npos)
            {
                cout << line << endl;
                outputFile << line << endl;
                create_database(line, customer);
            }
            else if (line.find("SELECT * FROM") == 0)
            {
                select_all_from_table_in_csv_mode(customer);
            }
        }

    fileInput.close();
    outputFile.close();

    return 0;
}
