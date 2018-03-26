#include <iostream>
#include <vector>
#include <fstream> // Para leer/escribir archivos
#include <sstream> // Para sacar cabeceras
#include <chrono>
#include "util.h"

using namespace std;
const char* TSV_PATH = "../incidents.tsv";

void search_data(const string &column, const string &value);
vector<string> tsv_header();
void search_values(const string &search, unsigned long position);


void save_results(vector<string> vector);

int main(int argc, char* argv[]){
  if(argc != 3)
    cout << "Error. Try \"./search descript dog\"" << endl;
  else
    search_data((string) argv[1], (string) argv[2]);

  return 0;
}

void search_data(const string &column, const string &value){
  vector<string> headers = tsv_header();
  unsigned int i = 0;
  bool found = false;

  while(!found && i < headers.size()){
    found = util::str_tolower(column) == util::str_tolower(headers.at(i));
    i++;
  }

  if (found)
    search_values(value, i-1);
  else
    cout << "Column " << column << " not found." << endl;
}

vector<string> tsv_header(){
  vector<string> columns;
  string row, value, token;
  ifstream file(TSV_PATH);

  getline(file, row);
  istringstream first_row(row);

  while(getline(first_row, token, '\t'))
    columns.push_back(token);

  return columns;
}



void search_values(const string &search, unsigned long position){
  string str, temp;
  vector<string> values;
  vector<string> matching_rows;
  ifstream file(TSV_PATH);

  auto start = chrono::system_clock::now();

  // Insert headers first
  getline(file, str);
  matching_rows.push_back(str);

  // Insert matching data
  while(getline(file, str)) {
    values.clear();
    stringstream buffer(str);
    while(getline(buffer, temp, '\t'))
      values.push_back(util::str_tolower(temp));

    if(util::str_contains_lower(values.at(position), search))
      matching_rows.push_back(str);
  }

  util::save_results(matching_rows);

  auto end = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;

  cout << matching_rows.size() <<" rows found in " << elapsed_seconds.count() << " s." << endl;
  cout << "You can see the results in 'incidents_found.tsv'" << endl;
}

