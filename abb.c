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
	if (nuevo_arbol){
	nuevo_arbol->cantidad = 0;
	nuevo_arbol->raiz = NULL;
	nuevo_arbol->comparador = cmp;
	nuevo_arbol->destructor = destruir_dato;
	}
	return nuevo_arbol;
}

/*Pre: Recibe un arbol y dos nodos
 * Destruye un nodo, liberando su memoria y reemplazandola por un nuevo nodo
 */
void reemplazar(abb_t * arbol, nodo_abb_t * nodo_a_borrar, nodo_abb_t * nodo_insertar){
	nodo_abb_t * copiaizq = nodo_a_borrar->izq;
	nodo_abb_t * copiader = nodo_a_borrar->der;
	if (arbol->destructor != NULL){
		void * dato = nodo_a_borrar->dato;
		arbol->destructor(dato);
	}
	free(nodo_a_borrar->clave);
	free(nodo_a_borrar);
	nodo_insertar->izq = copiaizq;
	nodo_insertar->der = copiader;

}


/* Guarda un elemento en el arbol, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	char * copia = strdup(clave);
	if (!copia){
		return false;
	}
	nodo_abb_t * nodo_insertar = malloc(sizeof(nodo_abb_t));
	if (!nodo_insertar){
		free(copia);
		return false;
	}

// ACA ME FALTA SEGUIR TRABAJANDO
}


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

bool _abb_pertenece(const abb_t *arbol, const char *clave_buscada, char *clave_obtenida){

// ACA ME FALTA SEGUIR TRABAJANDO PERO EN SI ES BUSCAR UN NODO
}

/*Devuelve verdadero si la clave pertenece al arbol
 *Pre: La estructura fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave){
	char * clave2;
	strcpy(clave2, arbol->raiz);
	return _abb_pertenece(arbol, clave, clave2);
}

bool abb_vacio(abb_t * arbol){
	return(abb_cantidad(arbol) == 0);
}


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


//==============================================================================


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);


//==============================================================================


typedef struct abb_iter {
	abb_t *arbol;
}abb_iter_t;


abb_iter_t *abb_iter_in_crear(const abb_t *arbol);


bool abb_iter_in_avanzar(abb_iter_t *iter);


const char *abb_iter_in_ver_actual(const abb_iter_t *iter);


bool abb_iter_in_al_final(const abb_iter_t *iter);


void abb_iter_in_destruir(abb_iter_t* iter);
