#include "abb.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
const int SIN_HIJOS = 0;
const int UN_HIJO = 1;
const int DOS_HIJOS = 2;

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

// FUNCION QUE LIBERA LA MEMORIA DE UN NODO  
// SIN AFECTAR SU DATO
void  borrar_nodo(nodo_abb_t * nodo){
	free(nodo->clave);
	free(nodo);
}

/*Pre: Recibe un arbol y dos nodos
 * Destruye un nodo, liberando su memoria y reemplazandola por un nuevo nodo
 */
void reemplazar(abb_t * arbol, nodo_abb_t * nodo_a_borrar, nodo_abb_t * nodo_insertar){
	nodo_abb_t * copiaizq = nodo_a_borrar->izq;
	nodo_abb_t * copiader = nodo_a_borrar->der;
	if (arbol->destructor != NULL){
		void * dato = nodo_a_borrar->elemento;
		arbol->destructor(dato);
	}
	borrar_nodo (nodo_a_borrar);
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
	nodo_insertar->elemento = dato;
	nodo_insertar->clave = copia;
	bool pertenece = abb_pertenece(arbol, clave);


// ACA ME FALTA SEGUIR TRABAJANDO
}


/* 
 * Pre: Recibe un nodo
 * Devuelve la cantidad de hijos del nodo
 */
int cantidad_de_hijos(const nodo_abb_t * nodo){
	if (nodo->der == NULL && nodo->izq == NULL){
		return SIN_HIJOS;
	}
	if(nodo->der != NULL && nodo->izq != NULL){
		return DOS_HIJOS;
	}
	return UN_HIJO;
}


//	Pre: recibe un nodo con dos hijos
//  Devuelve el nodo reemplazante, el cual servira para borrar el nodo actual
//
nodo_abb_t * buscar_reemplazante(nodo_abb_t * nodo, nodo_abb_t * anterior, bool es_raiz){
	
	if (es_raiz == false){
	anterior = nodo;	
	}
	nodo_abb_t * nodo_reem = nodo->der;
	while(nodo_reem->izq != NULL){
		if (es_raiz == false){
			anterior = nodo;
		}
		nodo_reem = nodo_reem->izq;
	}
	return nodo_reem;
}




/* 
 * Pre: recibe un arbol con al menos un elemento, y una clave que pertenece al arbol
 *  Si la raiz es el elemento a borrar, la borra y remplaza
 * Si no, llama a la funcion de borrado para cualquier elemento
 */
void * raiz_borrar(abb_t *arbol, const char * clave){
	if (arbol->comparador(clave, arbol->raiz->clave) == 0){
		nodo_abb_t * a_borrar = arbol->raiz;
		void * dato = a_borrar->elemento;
		if ( cantidad_de_hijos(a_borrar) == DOS_HIJOS){
			nodo_abb_t * anterior_reemplazante;
			nodo_abb_t * reemplazante = buscar_reemplazante(arbol->raiz, anterior_reemplazante, true);
			char* clave_reemplazante;
			strcpy(clave_reemplazante, reemplazante->clave);
			void * dato_suplente = abb_borrar_(anterior_reemplazante, reemplazante, clave_reemplazante, arbol->comparador);
			arbol->raiz->elemento = dato_suplente;
			strcpy(arbol->raiz->clave, clave_reemplazante);
			return dato;	
		}
		if ( cantidad_de_hijos(a_borrar) == UN_HIJO){
			if (a_borrar->der == NULL){
				arbol->raiz = a_borrar->izq;
			}
			else{
				arbol->raiz = a_borrar->der;
			}
		}
		else{
			arbol->raiz = NULL;
		}
		borrar_nodo(a_borrar);
		return dato;
	}
	if (arbol->comparador(clave, arbol->raiz->clave) > 0){
		return abb_borrar_(abb->raiz, abb->raiz->izq, clave, abb->comparador);
	}
	return abb_borrar_(abb->raiz, abb->raiz->der, clave, abb->comparador);
}


/* Pre: La clave existe en el arbol
 * Recibe dos nodos, inicializados, una clave y una funcion de comparacion
 * Devuelve el dato asociado a esa clave
 */
void * abb_borrar_(nodo_abb_t * nodo_anterior, nodo_abb_t * nodo, const char *clave,  abb_comparar_clave_t cmp){
	if (cmp(clave, nodo->clave) == 0){
		void * dato = nodo->elemento;
		int hijos = cantidad_de_hijos(nodo);
		if ( hijos == DOS_HIJOS){
			nodo_abb_t * anterior_reemplazante;
			nodo_abb_t * reemplazante = buscar_reemplazante(nodo, anterior_reemplazante, false);
			char* clave_reemplazante;
			strcpy(clave_reemplazante, reemplazante->clave);
			void * dato_suplente = abb_borrar_(anterior_reemplazante, reemplazante, clave_reemplazante, cmp);
			nodo->elemento = dato_suplente;
			strcpy(nodo->clave, clave_reemplazante);
			return dato;
		}
		if ( hijos == UN_HIJO){
			if (nodo_anterior->izq == nodo){
				if (nodo->izq != NULL){
					nodo_anterior->izq = nodo->izq;
				}
				if(nodo->izq == NULL){
					nodo_anterior->izq = nodo->der;
				}
			}
			if (nodo_anterior->der == nodo){
				if (nodo->izq != NULL){
					nodo_anterior->der = nodo->izq;
				}
				if(nodo->izq == NULL){
					nodo_anterior->der = nodo->der;
				}
			}
		}
		if (hijos == SIN_HIJOS){
			if (nodo_anterior->izq == nodo){
				nodo_anterior->izq = NULL;
			}
			else{
				nodo_anterior->der = NULL;
			}
		}
		borar_nodo(nodo);
		return dato;
	}
	if (cmp(clave, nodo->clave) > 0){
		return abb_borrar_(nodo, nodo->izq, clave, cmp);
	}
	return abb_borrar_(nodo, nodo->der, clave, cmp);
}



/* Borra un elemento del arbol y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *abb_borrar(abb_t *arbol, const char *clave){
	if (!abb_pertenece(arbol, clave) || abb_vacio(arbol)){
		return NULL;
	}
	arbol->cantidad--;
	return raiz_borrar(arbol, const char* clave);
}


/* Obtiene el valor de un elemento del arbol, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura fue inicializada
 */
void *abb_obtener(const abb_t *arbol, const char *clave);




/*  Devuelve verdadero si la clave recibida existe en el arbol
 * Pre: La estructura arbol fue inicializada, recibe un nodo y una clave previamente inicializados
 */
bool _abb_pertenece(nodo_abb_t * nodo, const char *clave_buscada, char *clave_obtenida, abb_comparar_clave_t cmp){
	strcpy(clave_obtenida, nodo->clave);
	if (cmp(clave_buscada, clave_obtenida) == 0){
		return true;
	}
	if (cmp(clave_buscada, clave_obtenida) < 0){
		if (nodo->izq == NULL){
			return false;
		}
		_abb_pertenece(nodo->izq, clave_buscada, clave_obtenida, cmp);
	}
	if (cmp(clave_buscada, clave_obtenida) > 0){
		if (nodo->der == NULL){
			return false;
		}
		_abb_pertenece(nodo->der, clave_buscada, clave_obtenida, cmp);
	}	
}

/*Devuelve verdadero si la clave pertenece al arbol
 *Pre: La estructura fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave){
	char * clave2;
	strcpy(clave2, arbol->raiz->clave);
	return _abb_pertenece(arbol->raiz, clave, clave2, arbol->comparador);
}

/* 
 * Recibe un arbol previamente inicializado 
 * Devuelve verdadero si su cantidad de elementos es igual a cero
 */
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


void abb_in_order_(nodo_abb_t * nodo, bool visitar(const char *c, void *dato, void *extra), void *extra, bool * continuar){
	if(nodo->izq != NULL && (*continuar == true)){
    abb_in_order_(nodo->izq, visitar(c, dato, extra), extra, &(*continuar));
	}
	continuar = continuar && visitar(nodo->clave, nodo->elemento, extra, &(*continuar));
	if(nodo->der != NULL && (*continuar == true)){
    abb_in_order_(nodo->der, visitar(c, dato, extra), extra, &(*continuar));
	}
}

void abb_in_order(abb_t *arbol, bool visitar(const char *c, void *dato, void *extra), void *extra){
	if (!abb_vacio(arbol)){
		bool continuar = true;
		abb_in_order_(abb->raiz, visitar(c, dato, extra), extra, &continuar);
		
	}

}
	

//==============================================================================


typedef struct abb_iter {
	abb_t *arbol;
}abb_iter_t;


abb_iter_t *abb_iter_in_crear(const abb_t *arbol);


bool abb_iter_in_avanzar(abb_iter_t *iter);


const char *abb_iter_in_ver_actual(const abb_iter_t *iter);


bool abb_iter_in_al_final(const abb_iter_t *iter);


void abb_iter_in_destruir(abb_iter_t* iter);
