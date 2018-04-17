# C++ Database Engine

### Download the dataset

Click on this link: [Police Department Incidents](https://mega.nz/#!KFYAmLSK!-9bbdMPe42uvn-pKVLyXnFUPkdaLa0EFobVu07TIxzw).
It will download a CSV file (semicolon separator) with every data we need to make this work. This file weights over 430 MiB.
If you do not want to alter the code, save this file into the proyect's folder, at the same level as the compiled application.

### Compilation and dependencies

This project requires any C++ compiler which supports the C++11 standard. It is highly recommended to use the -O3 flag to improve performance.

To compile it, use the following command:

`$ g++ -std=c++11 -O3 main.cpp util.cpp util.h -o search`

### Usage

This program will allow you to search with one or two conditions. The general usage is:

`$ ./search column1 value1 [(and|or) column2 value2]`

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

### Benchmark

For 2.18 million rows and -O3 flag, the results are:

* Simple query: *descript dog*

  `Matching rows: 3678; Finished in 4.47034 s.`

* AND query: *dayofweek monday and category assault*

  `Matching rows: 26175; Finished in 5.2775 s.`

* OR query: *dayofweek monday or category assault*

  `Matching rows: 465984; Finished in 4.77294 s.`
