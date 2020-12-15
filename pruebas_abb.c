
#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.
typedef struct nodo_abb{
    struct nodo_abb * izq;
    struct nodo_abb * der;
    char *clave;
    void * elemento;
}nodo_abb_t;

struct abb{
    nodo_abb_t * raiz; 
    abb_comparar_clave_t comparador;
    abb_destruir_dato_t destructor;
    size_t cantidad;
};

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

static void prueba_crear_sin_funcion_comparacion(){
    abb_t* arbol = abb_crear(NULL, NULL);
    print_test("Prueba arbol crear arbol sin comparacion", !arbol);
}

static void prueba_iterar_arbol_vacio(){
    abb_t* arbol = abb_crear(strcmp, NULL);
    abb_iter_t * abb_iter = abb_iter_in_crear(arbol);
    print_test("Prueba arbol iter crear iterador arbol vacio", abb_iter);
    print_test("Prueba arbol iter esta al final", abb_iter_in_al_final(abb_iter));
    print_test("Prueba arbol iter avanzar es false", !abb_iter_in_avanzar(abb_iter));
    print_test("Prueba arbol iter ver actual es NULL", !abb_iter_in_ver_actual(abb_iter));

    abb_iter_in_destruir(abb_iter);
    abb_destruir(arbol);
}

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

static void prueba_arbol_reemplazar(){
    
    abb_t* abb = abb_crear(strcmp, NULL);
    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

   
    valor1a = "Dog Chow";
    valor1b = "Firulais";
    valor2a = "Whiskas";
    valor2b = "Michi";


    print_test("Prueba arbol insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba arbol insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


static void prueba_arbol_reemplazar_con_destructor(){
    
    abb_t* abb = abb_crear(strcmp, free);
    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));



    print_test("Prueba arbol insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba arbol insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


static void prueba_arbol_borrar(){
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba arbol insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba arbol insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba arbol insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba arbol pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba arbol borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba arbol borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba arbol pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba arbol obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba arbol pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba arbol borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba arbol borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba arbol pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba arbol obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba arbol pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba arbol borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba arbol borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba arbol pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba arbol obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);
 
    abb_destruir(abb);
}


static void prueba_abb_clave_vacia(){
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba arbol insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba arbol obtener clave vacia es valor",abb_obtener(abb, clave) == valor);
    print_test("Prueba arbol pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba arbol borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_arbol_valor_null(){
     abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba arbol insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba arbol obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba arbol pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba arbol borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}
static void prueba_abb_volumen(size_t largo, bool debug){
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba arbolbb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba arbolbb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba arbolbb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba arbolbb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba arbolbb borrar muchos elementos", ok);
    if (debug) print_test("Prueba arbolbb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

  
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el arbol - debería liberar los enteros */
    abb_destruir(abb);

}

static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

static void prueba_abb_iterar(){

    abb_t* arbol = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(arbol, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t *iter = abb_iter_in_crear(arbol);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(arbol);
}

static void prueba_abb_iterar_volumen(size_t largo)
{
    abb_t* arbol = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(arbol, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t *iter = abb_iter_in_crear(arbol);
    
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(arbol, clave); 
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(arbol);
}

/*
bool visitar_imprimiendo(const char* clave, void * dato, void *extra){
    int * punchi = extra;
        printf(" %d. %s \n", (*punchi)++, clave);
    return true;
}
*/
void pruebas_insertar_borrar_5(){

    char *primero = "aaaa";
    char *sehgun = "bbbb";
    char *terce = "cccc";
    char *cuarto = "dddd";
    char *quint = "eeee";
    
    char * valor1_no = "18";
    char * valor2_no = "8";
    char * valor3_no = "2000";
    char * valor4_no = "123";
    char * valor5_no = "321";


    abb_t* arbol = abb_crear(strcmp, NULL);
    bool ok = true;
    
    ok = ok && abb_guardar(arbol, primero, valor1_no);
    ok = ok && abb_guardar(arbol, sehgun, valor2_no);
    ok = ok && abb_guardar(arbol, terce, valor3_no); 
    ok = ok && abb_guardar(arbol, cuarto, valor4_no);
    ok = ok && abb_guardar(arbol, quint, valor5_no);

    print_test("Insertados 5", ok);
    abb_iter_t * iter = abb_iter_in_crear(arbol);

    print_test("Iterador creado. No estoy al final", !abb_iter_in_al_final(iter));
    bool avanzando = true;
    avanzando = abb_iter_in_avanzar(iter);
    print_test("Avanzando Iterador", avanzando);
    print_test("No estoy al final", !abb_iter_in_al_final(iter));
    avanzando = abb_iter_in_avanzar(iter);
    print_test("Avanzando Iterador", avanzando);
    print_test("No estoy al final", !abb_iter_in_al_final(iter));  
    avanzando = abb_iter_in_avanzar(iter);    
    print_test("Avanzando Iterador", avanzando);
    print_test("No estoy al final", 
    !abb_iter_in_al_final(iter));  
    avanzando = abb_iter_in_avanzar(iter);    
    print_test("Avanzando Iterador", avanzando);
    print_test("No estoy al final", !abb_iter_in_al_final(iter));  
    avanzando = abb_iter_in_avanzar(iter);
    print_test("Avanzando Iterador", avanzando);
    print_test("estoy al final", abb_iter_in_al_final(iter));
    abb_iter_in_destruir(iter);
    bool elementos_correctos = true;
    
    //int extra = 0;
    //abb_in_order(arbol, visitar_imprimiendo, &extra);

    void * primer_borrado =    abb_borrar(arbol, primero);
    elementos_correctos = elementos_correctos && (valor1_no == primer_borrado);      
    void * segundo_borrado =    abb_borrar(arbol, sehgun);
    elementos_correctos = elementos_correctos && ((valor2_no == segundo_borrado));    
    void * tercer_borrado =    abb_borrar(arbol, terce);
    elementos_correctos = elementos_correctos && ((valor3_no ==tercer_borrado));   
    void * cuarto_borrado =    abb_borrar(arbol, cuarto);
    elementos_correctos = elementos_correctos && ((valor4_no ==cuarto_borrado));      
    void * quinto_borrado =    abb_borrar(arbol, quint);
    elementos_correctos = elementos_correctos && ((valor5_no == quinto_borrado));    
    


    print_test("Cantidad correcta",abb_cantidad(arbol) == 0);
    print_test("Quitados del arbol correctamente", elementos_correctos);

    abb_destruir(arbol);
}

void pruebas_insertar_borrar_3_memoria(){

    char *primero = "a";
    char *sehgun = "b";
    char *terce = "c";
    int * valor  =  malloc(sizeof(int));
    int * valor2 =  malloc(sizeof(int));
    int * valor3 =  malloc(sizeof(int));



    abb_t* arbol = abb_crear(strcmp, free);
    bool ok = true;
    ok = ok && abb_guardar(arbol, sehgun, valor2);
    ok = ok && abb_guardar(arbol, primero, valor);
    ok = ok && abb_guardar(arbol, terce, valor3);

    print_test("Insertados 3 elementos con memoria reservada", ok);
    abb_iter_t * iter = abb_iter_in_crear(arbol);

    print_test("Iterador creado. No estoy al final", !abb_iter_in_al_final(iter));
    bool avanzando = true;
    avanzando = abb_iter_in_avanzar(iter);
    print_test("Avanzando Iterador", avanzando);
    print_test("No estoy al final", !abb_iter_in_al_final(iter));
    avanzando = abb_iter_in_avanzar(iter);
    print_test("Avanzando Iterador", avanzando);
    print_test("No estoy al final", !abb_iter_in_al_final(iter));  
    avanzando = abb_iter_in_avanzar(iter);
    //print_test("Avanzando", avanzando);
    //print_test("No estoy al final", !abb_iter_in_al_final(iter));  
    //avanzando = abb_iter_in_avanzar(iter);
    print_test("Avanzando Iterador", avanzando);
    print_test("estoy al final", abb_iter_in_al_final(iter));
    abb_iter_in_destruir(iter);
    print_test("Cantidad correcta",abb_cantidad(arbol) == 3);
    bool elementos_correctos = true;
    void * segundo_borrado =   abb_borrar(arbol, sehgun);
    printf("aca\n");
    void * tercer_borrado =    abb_borrar(arbol, terce);
    printf("ac2\n");
    void * primer_borrado =    abb_borrar(arbol, primero);
    elementos_correctos = elementos_correctos && ((valor2 == segundo_borrado));    
    elementos_correctos = elementos_correctos && (valor == primer_borrado);      
    elementos_correctos = elementos_correctos && ((valor3 ==tercer_borrado));    
    print_test("Cantidad correcta en arbol vacio",abb_cantidad(arbol) == 0);
    print_test("Quitados del arbol correctamente", elementos_correctos);
    free(primer_borrado);
    free(tercer_borrado);
    free(segundo_borrado);
    abb_destruir(arbol);
}


/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/




void pruebas_abb_estudiante(){
    /* Ejecuta todas las pruebas unitarias.
     */
    prueba_crear();
    prueba_crear_sin_funcion_comparacion();
    prueba_iterar_arbol_vacio();
    prueba_arbol_insertar();
    pruebas_insertar_borrar_5();
    pruebas_insertar_borrar_3_memoria();
}
void pruebas_volumen_catedra(size_t largo){
    prueba_arbol_reemplazar();
    prueba_arbol_reemplazar_con_destructor();
    prueba_arbol_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_volumen(3000, true);
    prueba_arbol_valor_null();
    prueba_abb_iterar();
    prueba_abb_iterar_volumen(5000);
    printf("Aa\n");
}
void nuevas_pruebas(){
    printf("Aa\n");
}
