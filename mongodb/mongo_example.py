#Importing required packages

import pandas as pd
import sys
sys.path.insert(0,'..')
import pymongo
from pymongo import MongoClient
import folium
from folium import plugins

print('Mongo version', pymongo.__version__)
client = MongoClient('localhost', 27017)
db = client.datascience
collection = db.incidents

incid_by_district = [
    {"$group": {"_id": "$PdDistrict", "count": {"$sum": 1}}}
]

day_incidences = [
    {"$group": {"_id": "$DayOfWeek", "count": {"$sum": 1}}},
    {"$sort": { "count": -1 }}
]

incid_dogs = [
  {"$match": {"Descript": {"$regex": ".*DOG.*"}}}
]

common_categories = [
    {"$group": {"_id": "$Category", "count": {"$sum": 1}}},
    {"$sort": { "count": -1 }}
]

no_resolution = [
  {"$match": {"Resolution": "NONE"}}
]

aggResult = collection.aggregate(incid_by_district, allowDiskUse= True)
dist_count = pd.DataFrame(list(aggResult))
print("Contador: ", dist_count["_id"].size)

aggResult2 = collection.aggregate(day_incidences, allowDiskUse= True)
day_incid = pd.DataFrame(list(aggResult2))
print("Contador: ", day_incid["_id"].size)

aggResult3 = collection.aggregate(incid_dogs)
dog_no_res = pd.DataFrame(list(aggResult3))
print("Contador: ", dog_no_res["_id"].size)

aggResult4 = collection.aggregate(common_categories)
comm_categ = pd.DataFrame(list(aggResult4))
print("Contador: ", comm_categ["_id"].size)

aggResult5 = collection.aggregate(no_resolution)
no_res = pd.DataFrame(list(aggResult5))
print("Contador: ", no_res["_id"].size)

def mapa_calor(dataframe):
    mapa = folium.Map(location=[37.778254811523, -122.405834032593], tiles='openstreetmap')
    mapa.add_child(plugins.HeatMap([[row["Y"], row["X"]] for name, row in dataframe.iterrows()]))
    mapa.save('mapa_calor_incidencias.html')
    return mapa

mapa_calor(dog_no_res)