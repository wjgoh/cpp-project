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
#include <cctype>
using namespace std;

// function prototypes
void create_output_screen_and_file(const string &line);
void create_database(const string line, vector<vector<string>> &temporary_data, vector<vector<string>> &rows_data); // fixed
void create_table(const vector<string> column_lines, string &tableName, vector<string> &table_Column, vector<string> &data_type);
void insert_into_table(const string &line, const string tableName, const vector<vector<string>> temporary_data, const vector<string> data_type, ofstream &outputFile);
void select_all_from_table_in_csv_mode(const string &line, const string &tableName, const vector<string> &table_Column, const vector<vector<string>> &rows_data, ofstream &outputFile);
void update_data_from_table(const string &line, const vector<string> &table_Column, vector<vector<string>> &rows_data, ofstream &outputFile);
void delete_from_table(const string &line, const string &tableName, const vector<string> &table_Column, vector<vector<string>> &rows_data, ofstream &outputFile);
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

void create_database(const string line, vector<vector<string>> &temporary_data, vector<vector<string>> &rows_data)
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
    temporary_data.push_back(values);

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
    rows_data.push_back(rows_values); // Update vector rows_data
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

void insert_into_table(const string &line, const string tableName, const vector<vector<string>> temporary_data, const vector<string> data_type, ofstream &outputFile)
{
    size_t tableName_end = line.find("(");
    string check_tableName = line.substr(0, tableName_end);

    if (check_tableName == tableName) // Verify table name
    {
        for (int i = 0; i < temporary_data.size(); i++)
        {
            for (int j = 0; j < temporary_data[i].size(); j++)
            {
                if (data_type[j] == "INT") // If table column is an INT data type
                {
                    for (char ch : temporary_data[i][j])
                    {
                        if ( !isdigit(ch) || temporary_data[i][j].find("'") != string::npos ) // Check if the data is not a digit or numeric data
                        {
                            cerr << "Warning - " << temporary_data[i][j] << " not match with the data type INT!!" << endl;
                            break;
                        }
                    }
                }
                else if (data_type[j] == "TEXT") // If table column is a TEXT data type
                {
                    if (temporary_data[i][j].find("'") == string::npos) // Check if the data is not a string
                        cerr << "Warning - " << temporary_data[i][j] << " not match with the data type TEXT!!" << endl;
                }
            }
        }
    }
    else
    {
        cerr << "Warning - table " << check_tableName << " not found!!" << endl;
    }
}

void select_all_from_table_in_csv_mode(const string &line, const string &tableName, const vector<string> &table_Column, const vector<vector<string>> &rows_data, ofstream &outputFile)
{
    size_t tableName_begin = line.find("FROM") + 5;
    size_t tableName_end = line.find(";", tableName_begin);
    string check_tableName = line.substr(tableName_begin, tableName_end - tableName_begin);


    if (check_tableName == tableName)
    {

        for (size_t i = 0; i < table_Column.size(); ++i)
        {
            cout << table_Column[i];
            outputFile << table_Column[i];
            if (i < table_Column.size() - 1)
            {
                cout << ",";
                outputFile << ",";
            }
        }
        cout << endl;
        outputFile << endl;
        for (const auto &row : rows_data)
        {
            for (size_t i = 0; i < row.size(); ++i)
            {
                cout << row[i];
                outputFile << row[i];
                if (i < row.size() - 1)
                {
                    cout << ",";
                    outputFile << ",";
                }
            }
            cout << endl;
            outputFile << endl;
        }

    }
}
void update_data_from_table(const string &line,const string &tableName, const vector<string> &table_Column, vector<vector<string>> &rows_data, ofstream &outputFile)
{
   // Find the positions of SET and WHERE
     size_t set_pos = line.find("SET");
     size_t where_pos = line.find("WHERE");

    // Extract SET and WHERE commands
     string set_command = set_command.substr(set_pos + 4,where_pos-(set_pos + 4)-1);
     string where_command = line.substr(where_pos + 6, line.find(";") - (where_pos + 6));

    // Extract column and value for SET
     size_t set_equal_pos = set_command.find("=");
     string set_col = set_command.substr(0, set_equal_pos);
     string set_data = set_command.substr(set_equal_pos + 1);

   // Extract column and value for WHERE
     size_t where_equal_pos = where_command.find("=");
     string where_col = where_command.substr(0, where_equal_pos);
     string where_data = where_command.substr(where_equal_pos + 1);

    //Remove quotes ("'") from SET and WHERE
    if (set_data.find("'") != string::npos)
    {
        size_t quote_pos = set_data.find("'");
        set_data = set_data.substr(quote_pos + 1, set_data.size() - 2);
        //cout << set_data << endl;
    }
    if (set_data.find("'") != string::npos)
    {
        size_t quote_pos = set_data.find("'");
        set_data = set_data.substr(quote_pos + 1, set_data.size() - 2);
        //cout << set_data << endl;
    }


    int set_col_index;
    int where_col_index;


      for (int i = 0; i < table_Column.size(); i++)
      {
        if (where_col == table_Column[i])
            where_col_index = i;
            /*for (int j = 0; j < rows_data.size(); j++)
            {
                if (where_data == rows_data[j][i])
                    where_data_index = j;
            }*/
        if (set_col == table_Column[i])
             set_col_index = i;
            /*for (int j = 0; j < rows_data.size(); j++)
            {
                if (set_data == rows_data[j][i])
                    set_data_index = j;
            }*/
      }

      for (auto& row : rows_data)
    {
        if (row[where_col_index] == where_data)
            row[set_col_index] = set_data;
    }
}


void delete_from_table(const string &line, const string &tableName, const vector<string> &table_Column, vector<vector<string>> &rows_data, ofstream &outputFile)
{
    size_t tableName_begin = line.find("FROM") + 5;
    size_t tableName_end = line.find("WHERE");
    string check_tableName = line.substr(tableName_begin, tableName_end - 1 - tableName_begin);

    if (check_tableName == tableName)
    {
        cout << "> "<< line << endl;
        outputFile << "> " << line << endl;

        size_t where_pos = line.find("WHERE");
        string where_command = line.substr(where_pos + 6, line.find(";") - (where_pos + 6));
        //cout << where_command << endl;

        size_t where_equal_pos = where_command.find("=");
        string where_col = where_command.substr(0, where_equal_pos);
        string where_data = where_command.substr(where_equal_pos + 1);
        //cout << where_col << endl << where_data << endl;

        int where_col_index;
        int where_data_index;
        for (int i = 0; i < table_Column.size(); i++)
        {
            if(where_col == table_Column[i])
                where_col_index = i;
                break;
        }

        vector<vector<string>> update_row;
        for (int i = 0; i < rows_data.size(); i++)
        {
            if (rows_data[i][where_col_index] != where_data)
                update_row.push_back(rows_data[i]);
        }
        rows_data = update_row;
    }
    else
    {
        cerr << "Warning - table not found!!" << endl;
    }
}


void count_tableRow(const vector<vector<string>> &rows_data, ofstream &outputFile)
{
    cout << rows_data.size() << endl;
    outputFile << rows_data.size() << endl;
}



int main()
{

    //string fileInputName = "fileInput1.mdb";
    string fileInputName = "fileInput1.mdb"; // with path name
    //string fileInputName = "fileInput2.mdb";
    //string fileInputName = "fileInput3.mdb";

    ifstream fileInput;
    string fileOutputName;

    fileInput.open(fileInputName);

    if (!fileInput.is_open())
    {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    vector<vector<string>> rows_data;
    vector<vector<string>> temporary_data;
    vector<string> data_type;
    vector<string> table_Column;
    string tableName;

    string line;
    while (getline(fileInput, line))
        if (!line.empty())
        {
            if (line.find("CREATE TABLE") == 0)
            {
                cout << "> " << line << endl;
                outputFile << "> " << line << endl;
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
                cout << "> " << line << endl;
                outputFile << "> " << line << endl;
            }
            else if (line.find("VALUES") != string::npos)
            {
                cout << line << endl;
                outputFile << line << endl;
                create_database(line, temporary_data, rows_data);
                insert_into_table(line, tableName, temporary_data, data_type, outputFile);
            }
            else if (line.find("SELECT * FROM") == 0)
            {
                cout << "> " << line << endl;
                outputFile << "> " << line << endl;
                select_all_from_table_in_csv_mode(line, tableName, table_Column, rows_data, outputFile);
            }
            else if (line.find("DELETE FROM") == 0)
            {
                delete_from_table(line, tableName, table_Column, rows_data, outputFile);
            }
            else if (line.find("SELECT COUNT(*) FROM") == 0)
            {
                cout << "> " << line << endl;
                outputFile << "> " << line << endl;
                count_tableRow(rows_data, outputFile);
            }
        }



    fileInput.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }

    return 0;
}
