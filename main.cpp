#include <iostream>
#include <vector>
#include <fstream> // Para leer/escribir archivos
#include <sstream> // Para sacar cabeceras
#include <chrono>
#include "util.h"

using namespace std;
const char* TSV_PATH = "incidents.tsv";
const char* TSV_RESULT_PATH = "incidents_found.tsv";

void simple_search(const string &column, const string &value, const string &tsv_path = TSV_PATH);
int column_position(const string &column);
vector<string> tsv_header();
void search_value(const string &value, int position, const string &tsv_path);
void intersection_search(const vector<string> &params);
void union_search(const vector<string> &params);
void search_multiple_values(const string &first_value, int first_pos, const string &second_value, int second_pos);

int main(int argc, char* argv[]){
  auto start = chrono::system_clock::now();

  vector<string> params(argv + 1, argv + argc);
  if (params.size() == 2)
    simple_search(params.at(0), params.at(1));
  else if (params.size() == 5 && params.at(2) == "or")
    union_search(params);
  else if (params.size() == 5 && params.at(2) == "and")
    intersection_search(params);
  else
    cout << "Error. Usage: \"" << argv[0] << " column1 value1 [(and/or) column2 value2]\"" << endl;

  auto end = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;
  cout << "Finished in " << elapsed_seconds.count() << " s." << endl;
  cout << "You can see the results in 'incidents_found.tsv'" << endl;

  return 0;
}


void simple_search(const string &column, const string &value, const string &tsv_path){
  int column_pos = column_position(column);
  if (column_pos > -1){
    search_value(value, column_pos, tsv_path);
  }else
    cout << "Column " << column << " not found." << endl;
}

int column_position(const string &column) {
  vector<string> headers = tsv_header();
  int i = 0;
  bool found = false;

  while(!found && i < headers.size()){
    found = util::str_tolower(column) == util::str_tolower(headers[i]);
    i++;
  }

  i = found ? i-1 : -1;
  return i;
}

vector<string> tsv_header() {
  vector<string> columns;
  string row, value, token;
  ifstream file(TSV_PATH);

  getline(file, row);
  istringstream first_row(row);

  while(getline(first_row, token, '\t'))
    columns.push_back(token);

  return columns;
}


void search_value(const string &value, int position, const string &tsv_path) {
  string tsv_row, row_elem;
  vector<string> vect_row;
  vector<string> matching_rows;
  ifstream file(tsv_path);
  int rows_ctr = 0;

  // Insert header first
  getline(file, tsv_row);
  matching_rows.push_back(tsv_row);

  // Insert matching data
  while(getline(file, tsv_row)) {
    vect_row.clear();
    stringstream buffer(tsv_row);
    while(getline(buffer, row_elem, '\t'))
      vect_row.push_back(util::str_tolower(row_elem));

    if(util::str_contains_lower(vect_row[position], value))
      matching_rows.push_back(tsv_row);

    rows_ctr++;
  }

  util::save_results(matching_rows);

  cout << "Processed rows: " << rows_ctr << endl;
  cout << "Matching rows: " << matching_rows.size() << endl;
}

void intersection_search(const vector<string> &params) {
  cout << "First condition: " << params[0] << " " << params[1] << endl;
  simple_search(params[0], params[1]);
  cout << "Second condition: " << params[3] << " " << params[4] << endl;
  simple_search(params[3], params[4], TSV_RESULT_PATH);
}

void union_search(const vector<string> &params) {
  int first_column_pos = column_position(params[0]);
  int second_column_pos = column_position(params[3]);
  if (first_column_pos > -1 && second_column_pos > -1){
    search_multiple_values(params[1], first_column_pos, params[4], second_column_pos);
  }else
    cout << "Column " << params[0] << " or " << params[3] <<" not found." << endl;
}

void search_multiple_values(const string &first_value, int first_pos, const string &second_value, int second_pos) {
  string tsv_row, row_elem;
  vector<string> vect_row;
  vector<string> matching_rows;
  ifstream file(TSV_PATH);
  int rows_ctr = 0;

  // Insert header first
  getline(file, tsv_row);
  matching_rows.push_back(tsv_row);

  // Insert matching data
  while(getline(file, tsv_row)) {
    vect_row.clear();
    stringstream buffer(tsv_row);
    while(getline(buffer, row_elem, '\t'))
      vect_row.push_back(util::str_tolower(row_elem));

    if(util::str_contains_lower(vect_row[first_pos], first_value) || util::str_contains_lower(vect_row[second_pos], second_value))
      matching_rows.push_back(tsv_row);

    rows_ctr++;
  }

  util::save_results(matching_rows);

  cout << "Processed rows: " << rows_ctr << endl;
  cout << "Matching rows: " << matching_rows.size() << endl;
}
