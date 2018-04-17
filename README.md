# Data Science Project

Búsqueda de datos entre un conjunto de incidencias del departamento de policía de San Francisco.

Se utilizarán los siguientes motores de bases de datos NoSQL para el análisis:

* MongoDB

* Cassandra

* Neo4j

Adicionalmente se ha creado un pequeño motor en C++ que lee filas de un archivo CSV, principalmente para comparar el rendimiento y los resultados de las consultas.

Para los motores NoSQL se han propuesto las siguientes búsquedas:

&nbsp;&nbsp;&nbsp;&nbsp; - Distritos con mayor número de incidencias

&nbsp;&nbsp;&nbsp;&nbsp; - Día de la semana con mayor número de incidencias

&nbsp;&nbsp;&nbsp;&nbsp; - Incidencias que impliquen la acción de un perro (aparece "DOG" en el camp Descipt)

&nbsp;&nbsp;&nbsp;&nbsp; - Las 5 categorías más frecuentes.

&nbsp;&nbsp;&nbsp;&nbsp; - Porcentaje de incidencias sin resolución.
