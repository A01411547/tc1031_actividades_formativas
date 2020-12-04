Funciones complementarias para estructuras de grafos trabajadas en el curso


isTree. este algoritmo busca si dentro del grafo se cierra algun ciclo, ademas de revisar que el grafo
este conectado. Se encarga de revisar mediante busqueda que no se llegue dos veces al mismo
nodo y a la vez que todos los vertices sean alcanzables. complejidad o(v+e) ya que se recorre todo 
el grafo

topological sort. este algortimo se usa para ordenar vertices de forma lineal para que por cada
arco dirigirdo u v, el vertice u venga antes que v de manera ordenada. 
Este algorimo cuenta con una complejidad o(v+e)

bipartiteGraph . este algortimo revisa si los vertices de el grafo se pueden dividir en dos
subconjuntos que estan interconectados uno con el otro, como si fueran dos conjuntos separados que
se conectan solo con miembros de otro conjunto. Complejidad o(v+e)

