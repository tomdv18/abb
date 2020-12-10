
#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear(){
    abb_t* arbol = abb_crear(strcmp, NULL);

    print_test("Prueba arbol crear arbol vacio", arbol);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test("Prueba arbol obtener clave A, es NULL, no existe", !abb_obtener(arbol, "A"));
    print_test("Prueba arbol pertenece clave A, es false, no existe", !abb_pertenece(arbol, "A"));
    print_test("Prueba arbol borrar clave A, es NULL, no existe", !abb_borrar(arbol, "A"));

    abb_destruir(arbol);
}
/*
static void prueba_iterar_arbol_vacio(){
    abb_t* arbol = abb_crear(strcmp, NULL);
    abb_iter_t * abb_iter = abb_iter_in_crear(arbol)
    print_test("Prueba arbol iter crear iterador arbol vacio", abb_iter);
    print_test("Prueba arbol iter esta al final", abb_iter_in_al_final(abb_iter));
    print_test("Prueba arbol iter avanzar es false", !abb_iter_in_avanzar(abb_iter));
    print_test("Prueba arbol iter ver actual es NULL", !abb_iter_in_ver_actual(abb_iter));

    abb_iter_in_destruir(iter);
    abb_destruir(arbol);
}
/*/
static void prueba_arbol_insertar(){
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba arbol insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba arbol borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el arbol entero) */
    print_test("Prueba arbol insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba arbol insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    
    print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}


/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_abb()
{
    /* Ejecuta todas las pruebas unitarias.
     */
    prueba_crear();
    //prueba_iterar_arbol_vacio();
    prueba_arbol_insertar();
    /*prueba_hash_reemplazar();
    prueba_hash_reemplazar_con_destruir();
    prueba_hash_borrar();
    prueba_hash_clave_vacia();
    prueba_hash_valor_null();
    prueba_hash_volumen(5000, true);
    prueba_hash_iterar();
    prueba_hash_iterar_volumen(5000);
}

void pruebas_volumen_catedra(size_t largo)
{
    prueba_hash_volumen(largo, false);
}
*/
}