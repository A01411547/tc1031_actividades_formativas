Un Splay tree, es un arbol binario de busqueda, 
con el plus de que los elementos a los que se tuvieron acceso recientemente 
se accederan de una manera mas rapida en acceso posteriores 
Esto se hace ya que se reorganiza el arbol para un cierto elemento,
siendo colocado en la raiz este mismo.


Funciones

Add 
Esta funcion se encarga de agregar un nuevo nodo en la siguiente posición mediante recursividad
Si el arbol esta vacio se agrega el valor en el nodo. complejidad o(logn)

remove
Esta funcion trabaja como los remove de arboles, buscando el elemento que se quiere eliminar 
buscando de manera recursiva hasta dar con el elemento. Copmlejidad o(logn)

find 
Esta funcion se encarga de buscar el valor dentro de la estructura de datos y reacomodarlo de 
acuardo a la cantidad de busquedas que se le han realidazo. Complejidad o(1) para los datos mas
consultados, o(logn) para los datos menos buscados

empty
esta funcion revisa si el arbol esta vacio mediante el valor de su nodo raiz. regresa un
valor boolean con la respuesta. complejidad o(!)
