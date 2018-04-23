
<h1>Neo4J y Python</h1>

<p>Para conectar Neo4J con Python se ha optado por utilizar la librería Py2neo. En primer lugar, se instala mediante el siguiente comando: <br><br>
<b>$ pip install py2neo</b> <br>
El siguiente paso es importar las librerías necesarias para realizar las consultas a Neo4J y para mostrar los datos:<br>
<ul>
    <li>
        <b>py2neo:</b> instalada anteriormente. Es el conector entre Python y Neo4J, las consultas a la base de datos se realizan gracias a él.
    </li>
    <li>
        <b>numpy: </b>necesaria para manejar Arrays en Python entre otras funciones.</li>
    <li>
        <b>pandas: </b>proporciona herramientas para el análisis de datos.
    </li>
    <li>
        <b>matplotlib: </b>utiliza los datos obtenidos para generar diferentes gráficas.
    </li>
</ul>

Se utiliza la función <i>authenticate</i> de Py2neo para especificar el usuario y contraseña necesarios para acceder a la base de datos. Además se genera un objeto Graph, mediante el cual se realizarán las consultas.

</p>


```python
from py2neo import Graph, authenticate
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
authenticate("localhost:7474", "neo4j", "1234")
graph = Graph()
```

<h3>Consulta simple</h3>

Comenzamos con una consulta simple, obtener 20 incidentes que impliquen a un perro. La consulta se hace utilizando el método <i>data</i> del objeto <i>graph</i> que devuelve una lista. A continuación, nos ayudamos de DataFrame que pertenece a la librería <i>pandas</i> para mostrar los datos de una forma mas sencilla y visual.


```python
result = pd.DataFrame(list(graph.data("MATCH (i:Incident) WHERE i.descript CONTAINS 'DOG' RETURN i.incidntNum as Incident, i.descript as Description LIMIT 15")))
result

```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>Description</th>
      <th>Incident</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150098630</td>
    </tr>
    <tr>
      <th>1</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150113539</td>
    </tr>
    <tr>
      <th>2</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150122295</td>
    </tr>
    <tr>
      <th>3</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150123817</td>
    </tr>
    <tr>
      <th>4</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150132153</td>
    </tr>
    <tr>
      <th>5</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150141154</td>
    </tr>
    <tr>
      <th>6</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150143984</td>
    </tr>
    <tr>
      <th>7</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150150939</td>
    </tr>
    <tr>
      <th>8</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150151200</td>
    </tr>
    <tr>
      <th>9</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150151266</td>
    </tr>
    <tr>
      <th>10</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150153109</td>
    </tr>
    <tr>
      <th>11</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150157311</td>
    </tr>
    <tr>
      <th>12</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150163142</td>
    </tr>
    <tr>
      <th>13</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150166011</td>
    </tr>
    <tr>
      <th>14</th>
      <td>AIDED CASE, DOG BITE</td>
      <td>150170539</td>
    </tr>
  </tbody>
</table>
</div>



<h3>Creación de gráficas</h3><br>
En la siguiente consulta se obtiene el número de incidentes que ocurren cada día de la semana ordenados de mayor a menor, de forma que conocemos los días más conflictivos. Se utiliza la función <i>count()</i> de Neo4J para contar el número de accidentes por cada día.


```python
result1= pd.DataFrame(list(graph.data("MATCH (i:Incident)-[:OCURRED_ON]-(d:DayOfWeek) RETURN d.dayOfWeek as DayOfWeek, count(i) as Incidents ORDER BY Incidents DESC")))
result1
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>DayOfWeek</th>
      <th>Incidents</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Friday</td>
      <td>333229</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Wednesday</td>
      <td>319625</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Saturday</td>
      <td>316115</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Thursday</td>
      <td>311795</td>
    </tr>
    <tr>
      <th>4</th>
      <td>Tuesday</td>
      <td>311106</td>
    </tr>
    <tr>
      <th>5</th>
      <td>Monday</td>
      <td>302540</td>
    </tr>
    <tr>
      <th>6</th>
      <td>Sunday</td>
      <td>290627</td>
    </tr>
  </tbody>
</table>
</div>



Utilizando el ejemplo anterior, se va a generar un gráfico de barras para visualizar los datos utilizando la 
librería <b>matplotlib</b>. Para ello, es necesario separar el resultado de la consulta en dos arrays, uno contiene
los días de la semana y el otro el número de incidentes. El manejo de arrays es posible gracias a la librería 
<b>numpy</b>.


```python
days = result1['DayOfWeek']
incidents = result1['Incidents']

index = np.arange(len(days))
plt.bar(index, incidents)
plt.xlabel('Day Of Week', fontsize=10)
plt.ylabel('nº of incidents', fontsize=7)
plt.xticks(index, days, fontsize=7, rotation=30)
plt.title('Incidents/Day of Week')
plt.show()
```


![png](output_7_0.png)


<h3>Distritos más conflictivos</h3>


```python
result2 = pd.DataFrame(list(graph.data("MATCH (i:Incident)-[:OCURRED_IN]-(d:District) RETURN d.PdDistrict as District, count(i) as Incidents ORDER BY Incidents DESC LIMIT 5")))
result2


```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>District</th>
      <th>Incidents</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>SOUTHERN</td>
      <td>394099</td>
    </tr>
    <tr>
      <th>1</th>
      <td>MISSION</td>
      <td>295781</td>
    </tr>
    <tr>
      <th>2</th>
      <td>NORTHERN</td>
      <td>268877</td>
    </tr>
    <tr>
      <th>3</th>
      <td>CENTRAL</td>
      <td>222253</td>
    </tr>
    <tr>
      <th>4</th>
      <td>BAYVIEW</td>
      <td>218462</td>
    </tr>
  </tbody>
</table>
</div>




```python
districts = result2['District']
incidents = result2['Incidents']

index = np.arange(len(districts))
plt.bar(index, incidents)
plt.xlabel('Districts', fontsize=10)
plt.ylabel('nº of incidents', fontsize=7)
plt.xticks(index, districts, fontsize=7, rotation=30)
plt.title('5 distrítos más problemáticos')
plt.show()
```


![png](output_10_0.png)


<h3>Incidentes más comunes</h3>


```python
result3 = pd.DataFrame(list(graph.data("MATCH (i:Incident)-[:BELONGS_TO]-(c:Category) RETURN c.categoryName as Category, count(i) as Incidents ORDER BY Incidents DESC LIMIT 5")))
result3
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>Category</th>
      <th>Incidents</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>LARCENY/THEFT</td>
      <td>526062</td>
    </tr>
    <tr>
      <th>1</th>
      <td>OTHER OFFENSES</td>
      <td>462496</td>
    </tr>
    <tr>
      <th>2</th>
      <td>NON-CRIMINAL</td>
      <td>280029</td>
    </tr>
    <tr>
      <th>3</th>
      <td>ASSAULT</td>
      <td>275567</td>
    </tr>
    <tr>
      <th>4</th>
      <td>DRUG/NARCOTIC</td>
      <td>192184</td>
    </tr>
  </tbody>
</table>
</div>




```python
categories = result3['Category']
incidents = result3['Incidents']

index = np.arange(len(categories))
plt.bar(index, incidents)
plt.xlabel('Categories', fontsize=10)
plt.ylabel('nº of incidents', fontsize=7)
plt.xticks(index, categories, fontsize=7, rotation=30)
plt.title('5 delitos más comunes')
plt.show()

```


![png](output_13_0.png)

