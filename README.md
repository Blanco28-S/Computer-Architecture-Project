# Computer-Architecture-Project

#TITUTO

Análisis de acceso a memoria en algoritmos de ordenamiento avanzados.

#DESCRIPCION

Este proyecto es unaa implementacion de algoritmos de ordenamientos (QuickSort y MergeSort) en c++ 11.
el objetivo es demostrar mediante las estructuras de datos (archivos binarios) la medicion de la cantidad
de accesos a l amemoria cache en dichos algoritmos, analizando su impacto en grandes DataSet. de acuerdo 
a esto, obtimizar el ordenamiento para minimizar fallos de cache (de existir) y el ajuste de tamaño de bloque
para minimizar E/S.

#CARACTERISTICAS

-Implementacion de Mergesort y Quicksort.

-Generar grandes cantidades de datos numericos:

    -Datos con duplicados.

    -Datos parcialmente ordenados.

    -Datos aleatorios.
    
    -Datos orenados.

#


Explicación del Diseño
Simulador de Caché: Implementé una caché de correspondencia directa porque:

Es más simple de implementar y entender

Proporciona un buen equilibrio entre complejidad y rendimiento

Es adecuada para analizar patrones de acceso a memoria

Algoritmos de Ordenamiento:

Implementé QuickSort y MergeSort con callbacks para rastrear accesos a memoria

Cada acceso a un elemento del array se registra en el simulador de caché

Análisis de Memoria:

La clase MemoryAnalyzer coordina todo el proceso

Genera datos aleatorios y los mezcla para evitar sesgos

Mide hits, misses, tasa de hits y tiempo de ejecución

Experimentos:

Compara el rendimiento con diferentes tamaños de datos

Analiza el impacto de diferentes configuraciones de caché

Proporciona resultados tabulados para fácil interpretación

Este proyecto permite analizar cómo los diferentes algoritmos de ordenamiento interactúan con la jerarquía de memoria, lo que es crucial para optimizar el rendimiento en aplicaciones que manejan grandes volúmenes de datos.