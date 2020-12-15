
#define CORRECTOR
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_abb_estudiante(void);
void pruebas_volumen_catedra(size_t largo);
void nuevas_pruebas(void);

int main(int argc, char *argv[]) {
#ifdef CORRECTOR
      if (argc > 1) {
         //Asumimos que nos están pidiendo pruebas de volumen.
        long largo = strtol(argv[1], NULL, 10);
       pruebas_volumen_catedra((size_t) largo);

        return failure_count() > 0;
    }
    printf("\n~~~ PRUEBAS G22 ~~~\n");
    printf("\nCualquier semejanza con las pruebas de la catedra es mera coincidencia\n");
    pruebas_abb_estudiante();
    //nuevas_pruebas();
#endif

    return failure_count() > 0;
}
