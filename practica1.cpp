#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Para leer archivos
#include <sstream> // Para sacar cabeceras
#include <algorithm> // Para str_tolower
#include <chrono>
#include <ctime>

using namespace std;

const char* TSV_PATH = "incidents.tsv";


void search_data(string column, string value);
vector<string> tsv_header();
string str_tolower(string str);
void search_values(string search, int position);
bool str_contains(string str1, string str2);

int main(int argc, char* argv[]){
  if(argc != 3){
    cout << "Error. Try \"./search columnName valueDesired\"" << endl;
  }else{    
    search_data((string) argv[1], (string) argv[2]);
  }
  return 0;
}

void search_data(string column, string value){
  vector<string> headers = tsv_header();
  unsigned int i = 0;
  bool found = false;

  while(!found && i < headers.size()){
    found = str_tolower(column) == str_tolower(headers.at(i));
    i++;
  }
  
  if (found){
    search_values(value, i-1);
  }else{
    cout << "Column " << column << " not found." << endl;
  }
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

string str_tolower(string str) {
  transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c);});
  return str;
}

void search_values(string search, int position){
  cout << "Column found on position " << position << endl;
  
  string str, temp;
  vector<string> values;
  vector<string> data;
  ifstream file(TSV_PATH);
  
  auto start = std::chrono::system_clock::now();

  while(getline(file, str)) {
    values.clear();
    stringstream buffer(str);
    while(getline(buffer, temp, '\t')){
      values.push_back(str_tolower(temp));
    }
    
    if(str_contains(str_tolower(values.at(position)), str_tolower(search))){
      data.push_back(str);
      cout << data.back() << endl;
    }
  }  
  auto end = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;
  
  cout << "Process finished in " << elapsed_seconds.count() << " s." << endl;  
}

bool str_contains(string str1, string str2){
  return str1.find(str2) != string::npos;
}

