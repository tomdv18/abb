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

struct abb{
	nodo_abb_t * raiz; 
	abb_comparar_clave_t comparador;
	abb_destruir_dato_t destructor;
	size_t cantidad;
};

/*Crea un arbol asignandole su memoria, si falla devuelve NULL
 *
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	if(!cmp){
		return NULL;
	}
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


/* 
 * Recibe un arbol previamente inicializado 
 * Devuelve verdadero si su cantidad de elementos es igual a cero
 */
bool abb_vacio(const abb_t * arbol){
	return(abb_cantidad(arbol) == 0);
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


/* Pre: Todas las estructuras fueron inicializadas, el arbol tiene al menos un elemento
 * Y ese elemento tiene la misma clave que la recibida 
 * Post: devuelve verdadero si solo si la clave a insertar es la misma que la de la raiz 
 */
bool es_raiz(abb_t * arbol, const char* clave){
	return(arbol->comparador(arbol->raiz->clave, clave) == 0);
}


/* Pre: Todas las estructuras fueron inicializadas, la clave del nuevo nodo SI se encuentra en el arbol
 * Recibe tres nodos y un arbol
 * Devuelve verdadero si se pudo insertar un nodo, reemplazando el anterior y liberando su memoria
 */
bool reemplazar_nodo(abb_t * arbol, nodo_abb_t * nodo_anterior, nodo_abb_t * nodo, nodo_abb_t * nodo_insertar){
	if ((arbol->comparador(nodo->clave, nodo_insertar->clave) < 0)){
		return reemplazar_nodo(arbol, nodo, nodo->izq, nodo_insertar);
	}	
	if ((arbol->comparador(nodo->clave, nodo_insertar->clave) > 0)){
		return reemplazar_nodo(arbol, nodo, nodo->der, nodo_insertar);
	}
	if (nodo_anterior->izq == nodo){
		nodo_anterior->izq = nodo_insertar;
	}
	if (nodo_anterior->der == nodo){
		nodo_anterior->der = nodo_insertar;
	}
	reemplazar(arbol, nodo, nodo_insertar);
	return true;
}


/* Pre: Todas las estructuras fueron inicializadas, la clave del nuevo nodo NO se encuentra en el arbol
 * Recibe dos nodos  y un comparador
 * Devuelve verdadero si se pudo insertar un nuevo nodo
 */
bool insertar_nuevo( nodo_abb_t * nodo, nodo_abb_t * nodo_insertar, abb_comparar_clave_t comparador){
	if (comparador(nodo->clave, nodo_insertar->clave)  > 0){
		if (nodo->der != NULL){
			return insertar_nuevo(nodo->der, nodo_insertar, comparador);
		}
		else{
			nodo->der = nodo_insertar;
			return true;
		}
	}
	else{
		if (nodo->izq != NULL){
			return insertar_nuevo(nodo->izq, nodo_insertar, comparador);
		}
		else {
			nodo->izq = nodo_insertar;
			return true;
		}
	}
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
	nodo_insertar->izq = NULL;
	nodo_insertar->der = NULL;
	if (abb_vacio(arbol)){
		arbol->raiz = nodo_insertar;
		arbol->cantidad++;
		return true;
	}
	bool pertenece = abb_pertenece(arbol, clave);
	int comparacion = arbol->comparador(arbol->raiz->clave, clave);
	if (pertenece == true){
		bool cambiar_raiz = es_raiz(arbol, clave);
		if (cambiar_raiz != true){
			if (comparacion < 0){
				return reemplazar_nodo(arbol, arbol->raiz, arbol->raiz->izq, nodo_insertar);
			}	
			if (comparacion > 0){
				return reemplazar_nodo(arbol, arbol->raiz, arbol->raiz->der, nodo_insertar);
			}
		}
		reemplazar(arbol, arbol->raiz, nodo_insertar);
		arbol->raiz = nodo_insertar;
		return true;
	}
	else{
		bool se_pudo = true;
		se_pudo = se_pudo && insertar_nuevo(arbol->raiz , nodo_insertar, arbol->comparador);
		if (se_pudo){
			arbol->cantidad++;
		}
		return se_pudo;
	}
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


/* Pre: La clave existe en el arbol
 * Recibe dos nodos, inicializados, una clave y una funcion de comparacion
 * Devuelve el dato asociado a esa clave
 */
void * abb_borrar_(nodo_abb_t * nodo_anterior, nodo_abb_t * nodo, const char *clave,  abb_comparar_clave_t cmp){
	if (cmp(clave, nodo->clave) == 0){
		void * dato = nodo->elemento;
		int hijos = cantidad_de_hijos(nodo);
		if ( hijos == DOS_HIJOS){
			nodo_abb_t * anterior_reemplazante = NULL;
			nodo_abb_t * reemplazante = buscar_reemplazante(nodo, anterior_reemplazante, false);
			void * dato_suplente = abb_borrar_(anterior_reemplazante, reemplazante, reemplazante->clave, cmp);
			nodo->elemento = dato_suplente;
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
		borrar_nodo(nodo);
		return dato;
	}
	if (cmp(clave, nodo->clave) > 0){
		return abb_borrar_(nodo, nodo->izq, clave, cmp);
	}
	return abb_borrar_(nodo, nodo->der, clave, cmp);
}



/* 
 * Pre: recibe un arbol con al menos un elemento, y una clave que pertenece al arbol
 *  Si la raiz es el elemento a borrar, la borra y remplaza
 * Si no, llama a la funcion de borrado para cualquier elemento
 */
void * raiz_borrar(abb_t *arbol, const char * clave){
	if (arbol->comparador(clave, arbol->raiz->clave) == 0){
		nodo_abb_t * a_borrar = arbol->raiz;
		void * dato = NULL;
		dato = a_borrar->elemento;
		if ( cantidad_de_hijos(a_borrar) == DOS_HIJOS){
			nodo_abb_t * anterior_reemplazante = NULL; 
			nodo_abb_t * reemplazante = buscar_reemplazante(arbol->raiz, anterior_reemplazante, true);
			void * dato_suplente = abb_borrar_(anterior_reemplazante, reemplazante, reemplazante->clave, arbol->comparador);
			arbol->raiz->elemento = dato_suplente;
			strcpy(arbol->raiz->clave, reemplazante->clave);
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
		return abb_borrar_(arbol->raiz, arbol->raiz->izq, clave, arbol->comparador);
	}
	return abb_borrar_(arbol->raiz, arbol->raiz->der, clave, arbol->comparador);
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
	return raiz_borrar(arbol, clave);
}

void *abb_obtener_(nodo_abb_t * nodo, const char* clave, const abb_t * arbol){
	if (arbol->comparador(nodo->clave, clave) == 0){
		return nodo->elemento;
	}
	if (arbol->comparador(clave, nodo->clave) < 0){
		if (nodo->der == NULL){
				return NULL;
		}	
		return abb_obtener_(nodo->der, clave, arbol);
	}
	else{
		if (nodo->izq == NULL){
			return NULL;
		}
		else{
			return abb_obtener_(nodo->izq, clave, arbol);
		}
	}

}


/* Obtiene el valor de un elemento del arbol, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura fue inicializada
 */
void *abb_obtener(const abb_t *arbol, const char *clave){
	if (abb_vacio(arbol)){
		return NULL;
	}
	return abb_obtener_(arbol->raiz, clave, arbol);
}




/*  Devuelve verdadero si la clave recibida existe en el arbol
 * Pre: La estructura arbol fue inicializada, recibe un nodo y una clave previamente inicializados
 */
bool _abb_pertenece(nodo_abb_t * nodo, const char *clave_buscada, abb_comparar_clave_t cmp){
	if (cmp(clave_buscada,  nodo->clave) == 0){
		return true;
	}
	if (cmp(clave_buscada,  nodo->clave) > 0){
		if (nodo->izq == NULL){
			return false;
		}
		else{
			return _abb_pertenece(nodo->izq, clave_buscada, cmp);
		}
	}
	else {
		if (nodo->der == NULL){
			return false;
		}
		else{
			return _abb_pertenece(nodo->der, clave_buscada, cmp);
		}
	}	
}

/*Devuelve verdadero si la clave pertenece al arbol
 *Pre: La estructura fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave){
	if (abb_vacio(arbol)){
		return false;
	}
	return _abb_pertenece(arbol->raiz, clave, arbol->comparador);
}


/* Devuelve la cantidad de elementos del arbol.
 * Pre: La estructura fue inicializada
 */
size_t abb_cantidad(const abb_t *arbol){
	return (arbol->cantidad);
}

void destruir_nodos(nodo_abb_t * nodo, abb_t *arbol){
	if (nodo->izq){
		destruir_nodos(nodo->izq, arbol);
		nodo->izq = NULL;
	}
	if (nodo->der){
		destruir_nodos(nodo->der, arbol);
		nodo->der = NULL;
	}
	if (arbol->destructor){
		arbol->destructor(nodo->elemento);
	}
	borrar_nodo(nodo);
}

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura arnol fue inicializada
 * Post: La estructura arbol fue destruida
 */
void abb_destruir(abb_t *arbol){
	if (!abb_vacio(arbol)){
		destruir_nodos(arbol->raiz, arbol);
	}
	free(arbol);

}

//EL ITERADOR INTERNO SERA IN-ORDER
//==============================================================================
/*

void abb_in_order_(nodo_abb_t * nodo, bool visitar(const char *cadena, void *dato, void *extra), void *extra, bool * continuar){
	if(nodo->izq != NULL && (*continuar == true)){
    abb_in_order_(nodo->izq, visitar(const char *cadena, void *dato, void *extra), extra, &(*continuar));
	}
	*continuar = *continuar && visitar(nodo->clave, nodo->elemento, extra, &(*continuar));
	if(nodo->der != NULL && (*continuar == true)){
    abb_in_order_(nodo->der, visitar(const char *cadena, void *dato, void *extra), extra, &(*continuar));
	}
}

void abb_in_order(abb_t *arbol, bool visitar(const char *cadena, void *dato, void *extra), void *extra){
	if (!abb_vacio(arbol)){
		bool continuar = true;
		abb_in_order_(arbol->raiz, visitar(const char *, void *, void *), extra, &continuar);
		
	}
}
	*/
//==============================================================================
struct abb_iter{
  pila_t* pila;
  
};

//Crea un iterador. Devuelve NULL si falla
//Pre: La estructura arbol recibida fue inicializada
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

	if(!arbol){
		return NULL;
	}
	abb_iter_t *iter = malloc(sizeof(abb_iter_t));
	if (!iter)
		return NULL;

	pila_t *pila = pila_crear();
	if (!pila){
		free(iter);
		return NULL;
	}	
	iter->pila = pila;
	nodo_abb_t *nodo = arbol->raiz;
    while(nodo){
		pila_apilar(iter->pila, nodo);
		nodo = nodo->izq;
    }
	 
	return iter;
	
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)){
		return false;
	}
	nodo_abb_t *nodo = pila_desapilar(iter->pila);
	nodo = nodo->der;
	while(nodo){
	
		pila_apilar(iter->pila, nodo);
		nodo = nodo->izq;
	}
	return true;
}


bool abb_iter_in_al_final(const abb_iter_t *iter){
	return (pila_esta_vacia(iter->pila));
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)) {
    	return NULL;
  	}
	nodo_abb_t *nodo_actual = pila_ver_tope(iter->pila);

	return nodo_actual->clave;
}


void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}