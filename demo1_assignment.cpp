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

// Function Prototype
void output_screen_file();
void database(const string line, vector<Information> customer);
void create_table();
void insert_into_table();
void csv_mode();

void database(const string line, vector<Information> customer)
{
    size_t values_pos = line.find("VALUES");

    string values_eli = line.substr(values_pos);
    string values_line = values_eli.substr(values_eli.find("(") + 1, values_eli.find(")") - values_eli.find("(") - 1);

    //cout << values_line << endl;

    stringstream ss(values_line);
    string values_sep;
    vector<string> values;
    while ( getline(ss, values_sep, ',') )
    {
        values.push_back(values_sep);
    }

    Information customer_info;
    for (int i = 0; i < values.size(); i++)
    {
        if (values[i].find("'") != string::npos)
        {
            values[i] = values[i].substr(1, values[i].size() - 2);
            if (i == 1)
            {
                customer_info.customer_name = values[i];
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
            int number = stoi(values[i]);
            if (i == 0)
            {
                customer_info.customer_id = number;
            }
        }
    }

    cout << customer_info.customer_id << customer_info.customer_name << customer_info.customer_city << customer_info.customer_state << customer_info.customer_country << customer_info.customer_phone << customer_info.customer_email << endl;

    //insert_into_table(id, name, age, city, state, phone, email);

    /*if (values.size() == 7)
    {
        int id = stoi(values[0]);
        string name = values[1].substr(1, values[1].size() - 2);
        string city = stoi(values[2]);
        string state = values[3].substr(1, values[3].size() - 2);
        string country = values[4].substr(1, values[4].size() - 2);
        string phone = values[5].substr(1, values[5].size() - 2);
        string email = values[6].substr(1, values[6].size() - 2);

        Information customer_info;
        customer_info.customer_id = id;
        customer_info.customer_name = name;
        customer_info.customer_city = city;
        customer_info.customer_state = state;
        customer_info.customer_country = country;
        customer_info.customer_phone = phone;
        customer_info.customer_email = email;

        cout << id << name << city << state << country << phone << email << endl;
        //insert_into_table(id, name, city, state, country, phone, email);
    }*/
}

int main()
{
    vector<Information> customer;

    ifstream fileInput;

    string fileInputName = "data_input.mdb";

    fileInput.open("data_input.mdb");

    if ( !fileInput.is_open() )
    {
        cout << "File open failure!" << endl;
    }

    string line;
    while ( getline(fileInput, line) )
    {
        if (!line.empty())
        {
            if (line.find("CREATE TABLE") == 0)
            {
                cout << line << endl;
            }
            else if (line.find("DATABASE") == 0)
            {
                cout << line << endl;
            }
            else if (line.find("CREATE") == 0)
            {
                cout << line << endl;
            }
            else if (line.find("INSERT INTO") == 0)
            {
                cout << line << endl;
            }
            else if (line.find("VALUES") != string::npos)
            {
                database(line, customer);
            }
            else if (line.find("SELECT * FROM") == 0)
            {
                cout << line << endl;
            }
            else
            {
                cout << "no keyword" << endl;
            }
        }
        else
        {
            cout << "----" << endl;
        }
    }

    fileInput.close();
}
