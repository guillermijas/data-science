# MongoDB


### MongoDB and Compass installation

To begin with, we will go to MongoDB's website and look for "Getting started" guides. In this case, we will use MongoDB 3.6.3 and Compass 0.12.7, as GUI and search tool.

The following installation steps have been taken from [MongoDB Docs](https://docs.mongodb.com/manual/tutorial/install-mongodb-on-ubuntu/):

`$ sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 2930ADAE8CAF5059EE73BB4B58712A2291FA4AD5`
`$ echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.6 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.6.list`
`$ sudo apt update`
`$ sudo apt install mongodb-org`

And now Mongo should be installed. We can launch it with the next command:

`$ sudo service mongod start`

It will open the port 27017 and start listening to requests. Next step is installing [MongoDB Compass](https://www.mongodb.com/download-center?filter=enterprise#compass) and we will be ready to import our first dataset.


### Import data with mongoimport

Compared to the other techonologies, data importation in MongoDB is quite simple and easily customizable. We will use **mongoimport**, the built-in tool which allows us to transform a downloaded TSV into a collection.

The command we will use is:

`$ mongoimport -d 'datascience' -c 'incidents' --type tsv --headerline --file incidents.tsv`

And those options mean:
&nbsp;&nbsp;&nbsp;&nbsp;-d 'datascience': use "datascience" database.
&nbsp;&nbsp;&nbsp;&nbsp;-c 'incidents': every row will be added to "incidents" collection, equivalent to a SQL table.
&nbsp;&nbsp;&nbsp;&nbsp;--type tsv: self explanatory. We could also have used a .csv file
&nbsp;&nbsp;&nbsp;&nbsp;--headerline: the first row contains column's names
&nbsp;&nbsp;&nbsp;&nbsp;--file incidents.tsv: this is the file wich contains the data

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
