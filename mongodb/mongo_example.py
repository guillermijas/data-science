#Importing required packages

import pandas as pd
import sys
sys.path.insert(0,'..')
import pymongo
from pymongo import MongoClient

print('Mongo version', pymongo.__version__)
client = MongoClient('localhost', 27017)
db = client.datascience
collection = db.incidents

pipeline = [
  {"$match": {"Descript": {"$regex": ".*DOG.*"},
              "Resolution": "NONE"}},
]
aggResult = collection.aggregate(pipeline)
dog_no_res = pd.DataFrame(list(aggResult))
print("Contador: ", dog_no_res["_id"].size)
