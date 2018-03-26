# Data Science Project

Search data within San Francisco's Police Department Incidents dataset.

### Download the dataset

Click on this link: [Police Department Incidents](https://data.sfgov.org/api/views/gxxq-x39z/rows.tsv?accessType=DOWNLOAD).
It will download a TSV file with every data we need to make this work. This file weights 62 MiB. If you do not want to alter
the code, save this file into the proyect's folder, at the same level as souce codes.

### Compilation and dependencies

This project requires any C++ compiler which supports the C++11 standard.

To compile it, use the following command:

`$ g++ -std=c++11 main.cpp util.cpp util.h -o search`

### Usage

This program will allow you to search with one or two conditions. The general usage is:

`$ ./search column1 value1 [(and/or) column2 value2]`

**NOTE**: searches are case-insensitive.

### Examples

Search with one condition:

`$ ./search descript dog`

`$ ./search DAYOFWEEK MONDAY`

Search with condition1 and condition2:

`$ ./search descript dog and address lincoln`

`$ ./search DAYOFWEEK MONDAY and CATEGORY ASSAULT`

Search with condition1 or condition2:

`$ ./search descript dog or address lincoln`

`$ ./search DAYOFWEEK MONDAY or CATEGORY ASSAULT`
