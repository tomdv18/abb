#define CORRECTOR

#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_abb(void);

int main(int argc, char *argv[]) {
#ifdef CORRECTOR
    printf("\n~~~ PRUEBAS G22 ~~~\n");
    printf("\nCualquier semejanza con las pruebas de la catedra es mera coincidencia\n");
    pruebas_abb();
#endif

    return failure_count() > 0;
}
// HOY NO ES 25 DE MAYO