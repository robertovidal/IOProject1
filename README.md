# IOPROJECT1
Estudiantes:
Jose Pablo Fernández Cubillo, 2019047740
Roberto Vidal Patiño, 2019065537

Primero es necesario tener instalado Latex con
todas sus funcionalidades, para ello podemos
hacerlo con el siguiente comando:

sudo apt install texlive-full

Para compilar el proyecto lo único que se debe hacer
es ingresar el comando make en la consola

Para correr el programa hay dos formas:

./mochila -X

De esta forma el programa resolverá un solo caso
aleatorio del problema 0/1 de la mochila con un
algoritmo de programación dinámica, un greedy
básico y un greedy proporcional. La mochila tiene
una capacidad de 15. Habrá 6 objetos con sus
capacidades c_i <= 7 y sus valores 0 < v_i <= 20
ambos generados aleatoriamente. Se despliega un
pdf hecho en Latex con los resultados.

./mochila -E=n

En este caso n debe ser un número entero positivo
distinto de 0. El programa resolverá 100n casos
diferentes del problema 0/1 de la mochila con un
algoritmo de programación dinámica, un greedy básico
y un greedy proporcional. La capacidad de la mochila
se varı́a desde 100 hasta 1000, y la cantidad de
objetos se varı́a desde 10 hasta 100 objetos Para cada
uno de los n casos en la combinación de cierta
capacidad de mochila y cantidad de objetos, se
generarán aleatoriamente las capacidades y valores
de cada objeto, con las restricciones de que todas las
capacidades sean mayores que 0, pero que ninguno sea 
mayor al 40% de la capacidad de la mochila, y que
0 < v_i <= 100, donde v_i es cada valor del objeto. 
Se muestran los resultados de ejecución de los tres
algoritmos con tablas de promedios de tiempo de 
ejecución y para los greedy se les coloca también
tablas con los porcentajes de éxito.

Si el comando se coloca mal o no se coloca ninguno
de los dos el programa despliega un tipo de ayuda
que indica al usuario cómo es que se utilizan los
comandos.