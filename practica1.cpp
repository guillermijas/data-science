#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 3){
    cout << "Sintaxis: ./search columnName valueDesired" << endl;
  }else{
    int i = 0;
    vector<string> columns;
    string row, value, token;
    ifstream file("incidents.tsv");
   
    getline(file, row);
    istringstream ss(row);

	  while(getline(ss, token, '\t')) {
		  columns.push_back(token);
    }

    while(file.good()){
      getline(file, row);
      cout << string(row) << endl;
      break;
    }
  }
  return 0;
}
