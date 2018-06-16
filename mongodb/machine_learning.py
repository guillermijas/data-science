#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import sys
sys.path.insert(0,'..')
import pymongo
from pymongo import MongoClient
from datetime import datetime
from statsmodels.tsa.seasonal import seasonal_decompose
from pyramid.arima import auto_arima

start_date = datetime(2017, 11, 1, 0, 0, 0)
end_date = datetime(2017, 12, 31, 0, 0, 0)

print('Mongo version', pymongo.__version__)
client = MongoClient('localhost', 27017)
db = client.datascience
collection = db.incidents

thefts_query = [{ 
        "$match": { "Category": {"$regex": ".*THEFT.*"}, 
                    "Date" : { "$lt" : "2018-02-01" }
        }}]

aggResult = collection.aggregate(thefts_query)
thefts = pd.DataFrame(list(aggResult))
print("Contador: ", thefts["_id"].size)

thefts_by_date = thefts.groupby('Date')._id.count()
thefts_by_date.head()

index = thefts_by_date.index
columns = ['Thefts']
df_data = thefts_by_date.values

data_clean = pd.DataFrame(df_data, index, columns)
data_clean.index = pd.to_datetime(data_clean.index) 

data = data_clean.groupby(pd.Grouper(freq='M')).sum()

data.plot(kind="line", grid=True, title="Thefts by day")

decomposition = seasonal_decompose(data, model="additive", freq=12)
decomposition.plot()

stepwise_model = auto_arima(data, start_p=1, start_q=1,
                            max_p=3, max_q=3, m=12,
                            start_P=0, seasonal=True,
                            d=1, D=1, trace=True,
                            error_action='ignore',
                            suppress_warnings=True,
                            stepwise=True )

print(stepwise_model.aic())

train = data.loc['2003-01-31':'2016-02-28']
test = data.loc['2016-03-31':'2018-01-31']

stepwise_model.fit(train)

future_forecast = stepwise_model.predict(n_periods=23)
print(future_forecast)

future_forecast = pd.DataFrame(future_forecast, index = test.index,
                               columns=['Prediction'])
pd.concat([test,future_forecast],axis=1).plot()
pd.concat([data,future_forecast],axis=1).plot()


