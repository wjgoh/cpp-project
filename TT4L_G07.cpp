//*******************************************************************************************
// Program: Bachelor of Computer Science
// Course: CPP6114 Programming Fundamentals
// Lecture Class: TC2L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 242UC244S9 | GOH WEI JING | goh.wei.jing@student.mmu.edu.my | 011-10872022
// Member_2: 242UC244SJ | Khoo Shen Zhi | khoo.shen.zhi@student.mmu.edu.my | 011-36735033
// Member_3: 242UC244K7 | CHIN KUAN SIING | CHIN.KUAN.SIING@student.mmu.edu.my |011-54070928
// Member_4: 242UC244S3 | TENG MING HEIN | TENG.MING.HEIN@student.mmu.edu.my | 016-7831558
//*******************************************************************************************
// Task Distribution
// Member_1: create_output_screen_and_file, create_table function, select_all_from_table_in_csv_mode
// Member_2: error_handling, flowchart, strecture diagram
// Member_3: create_insert_into_table,create_table function
// Member_4: create_database function, create_table function
//*******************************************************************************************
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


//string fileInputName = "fileInput1.mdb";
string fileInputName = "C:\\Users\\user\\CPP Assignment\\cpp-project\\fileInput1.mdb"; // with path name
//string fileInputName = "fileInput2.mdb";
//string fileInputName = "fileInput3.mdb";

struct Row
{
    int num_Row;
};

// function prototypes
void create_output_screen_and_file(const string &line);
void create_database(const string line, vector<vector<string>> &rows_data); // fixed
void create_table(const vector<string> column_lines, string &tableName, vector<string> &table_Column, vector<string> &data_type);
void insert_into_table(const string &line, vector<Row> &table_Row);
void select_all_from_table_in_csv_mode(const vector<Information> &customer);
void count_tableRow(const vector<vector<string>> &rows_data);

// function definitions, no global variables
ofstream outputFile;
bool headerPrinted = false;

void create_output_screen_and_file(const string &line)
{
    size_t file_begin = line.find(" ") + 1;
    size_t file_end = line.find(";");
    string outputFileName = line.substr(file_begin, file_end - file_begin);

    outputFile.open(outputFileName);

    if ( !outputFile.is_open() )
    {
        cout << "Unable to create output file" << endl;
        return;
    }

    cout << "> CREATE " << outputFileName << ";" << endl;
    outputFile << "> CREATE " << outputFileName << ";" << endl;
}

void create_database(const string line, vector<vector<string>> &rows_data)
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

    vector<string> rows_values;
    for (int i = 0; i < values.size(); i++)
    {
        if (values[i].find("'") != string::npos)
        {
            values[i] = values[i].substr(1, values[i].size() - 2); // To eliminate the single quote(')
            rows_values.push_back(values[i]);
        }
        else
        {
            rows_values.push_back(values[i]);
        }
    }
    rows_data.push_back(rows_values); // Update the vector structure
}

void create_table(const vector<string> column_lines, string &tableName, vector<string> &table_Column, vector<string> &data_type)
{
    for (const string& command : column_lines)
    {
        string line = command;

        if (line.find("CREATE TABLE") != string::npos)
        {
            // Get the table name
            size_t tableName_begin = line.find("TABLE") + 6;
            size_t tableName_end = line.find("(");
            tableName = line.substr(tableName_begin, tableName_end - tableName_begin);
        }
        else if (line.find("INT") != string::npos || line.find("TEXT") != string::npos)
        {
            // Get the column name
            size_t blank = line.find(' ');
            string col_name = line.substr(0, blank);
            table_Column.push_back(col_name);

            // Get the data type
            size_t comma_pos = line.find(",");
            string dtName = line.substr(blank + 1, comma_pos - blank - 1);
            data_type.push_back(dtName);
        }
    }
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

void select_all_from_table_in_csv_mode(const vector<Information> &customer) //wrong
{
    cout << "> SELECT FROM * " << tableName << ";" << endl;
    outputFile << "> SELECT FROM * " << tableName << ";" << endl;

    if (!headerPrinted)
    {
        // Print table header in CSV format, wrong
        cout << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";
        outputFile << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email\n";
        headerPrinted = true;
    }

    // Print table data in CSV view format, wrong
    for (const auto &c : customer)
    {
        cout << c.customer_id << "," << c.customer_name << "," << c.customer_city << "," << c.customer_state << "," << c.customer_country << "," << c.customer_phone << "," << c.customer_email << "\n";
        outputFile << c.customer_id << "," << c.customer_name << "," << c.customer_city << "," << c.customer_state << "," << c.customer_country << "," << c.customer_phone << "," << c.customer_email << "\n";
    }
}

void delete_from_table(const string &line, vector<Information> &customer) {
    size_t where_pos = line.find("WHERE");
    size_t equals_pos = line.find("=", where_pos);
    int customer_id = stoi(line.substr(equals_pos + 1));

    customer.erase(remove_if(customer.begin(), customer.end(), [customer_id](const Information &c) {
        return c.customer_id == customer_id;
    }), customer.end());

    cout << "> " << line << endl;
    outputFile << "> " << line << endl;
}

void count_tableRow(const vector<vector<string>> &rows_data);
{
    cout << rows_data.size() << endl;
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

    vector<vector<string>> &rows_data; // fixed
    vector<string> data_type;
    vector<string> table_Column;
    vector<Row> table_Row;
    string tableName;

    string line;
    while (getline(fileInput, line))
        if (!line.empty())
        {
            if (line.find("CREATE TABLE") == 0)
            {
                cout << "> " << line << endl;
                vector<string> column_lines;

                column_lines.push_back(line); // Add the "CREATE TABLE" line
                string command;
                while (getline(fileInput, command) && command.find(");") == string::npos)
                {
                    column_lines.push_back(command);
                    cout << command << endl;
                    outputFile << command << endl;
                }
                column_lines.push_back(command); // Add the final line with ");"

                cout << command << endl; // Print the final line
                outputFile << command << endl;

                create_table(column_lines, tableName, table_Column, data_type);
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
                create_database(line, rows_data);
            }
            else if (line.find("SELECT * FROM") == 0)
            {
                select_all_from_table_in_csv_mode(customer);
            }
            else if (line.find("DELETE FROM") == 0)
            {
                delete_from_table(line, customer);
            }
        }



    fileInput.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    return 0;
}
