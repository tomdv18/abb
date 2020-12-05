#include "abb.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo_abb{
	struct nodo_abb * izq;
	struct nodo_abb * der;
	char *clave;
	void * elemento;
}nodo_abb_t;

typedef struct abb{
	nodo_abb_t * raiz; 
	abb_comparar_clave_t comparador;
	abb_destruir_dato_t destructor;
	size_t cantidad;
}abb_t;

/*Crea un arbol asignandole su memoria, si falla devuelve NULL
 *
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t * nuevo_arbol = malloc(sizeof(abb_t));
	if (!nuevo_arbol){
		return NULL;
	}
	nuevo_arbol->cantidad = 0;
	nuevo_arbol->comparador = NULL;
	nuevo_arbol->destructor = NULL;
	nuevo_arbol->raiz = NULL;
	return nuevo_arbol;
}


/* Guarda un elemento en el arbol, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);


/* Borra un elemento del arbol y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *abb_borrar(abb_t *arbol, const char *clave);


/* Obtiene el valor de un elemento del arbol, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura fue inicializada
 */
void *abb_obtener(const abb_t *arbol, const char *clave);


/*Devuelve verdadero si la clave pertenece al arbol
 *Pre: La estructura fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);


/* Devuelve la cantidad de elementos del arbol.
 * Pre: La estructura fue inicializada
 */
size_t abb_cantidad(abb_t *arbol){
	return (abb->cantidad);
}

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura arnol fue inicializada
 * Post: La estructura arbol fue destruida
 */
void abb_destruir(abb_t *arbol);