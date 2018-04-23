#!/usr/bin/env python
import os
from pymongo import MongoClient
import pandas as pd
import json
import progressbar

STEP = 200


def import_content():
    client = MongoClient()
    db = client['datascience']
    incid = db.incidents
    incid.remove()
    csv = pd.read_csv('/home/guillermo/data-science/cpp_db/incidents.csv', sep=';')

    bar = progressbar.ProgressBar()
    for start in bar(range(0, len(csv.index), STEP)):
        partial_csv = csv.ix[start:(start + STEP), :]
        csv_to_json = json.loads(partial_csv.to_json(orient='records'))
        incid.insert(csv_to_json)
        del partial_csv
        del csv_to_json

if __name__ == "__main__":
    import_content()