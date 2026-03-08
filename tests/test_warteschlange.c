#include <stdlib.h>
#include <assert.h>
#include "parkhaus.h"
#include "kfz.h"
#include "warteschlange.h"

void test_kfz_hinzufuegen_warteschlange_leer(){
    Parkhaus *p_parkhaus = init_parkhaus(0, 40);
    Kfz *p_kfz = init_kfz(p_parkhaus, 1, 60);

    kfz_hinzufuegen_warteschlange(p_parkhaus, p_kfz);
    assert(p_parkhaus->p_erster_in_der_warteschlange == p_kfz);
    free(p_parkhaus);
    free(p_kfz);
}

void test_kfz_hinzufuegen_warteschlange_normal(){
    Parkhaus *p_parkhaus = init_parkhaus(0, 40);
    Kfz *p_kfz = init_kfz(p_parkhaus, 4, 63);

    p_parkhaus->p_erster_in_der_warteschlange = init_kfz(p_parkhaus, 1, 60);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster = init_kfz(p_parkhaus, 2, 61);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster->p_naechster = init_kfz(p_parkhaus, 3, 62);

    kfz_hinzufuegen_warteschlange(p_parkhaus, p_kfz);
    assert(p_parkhaus->p_erster_in_der_warteschlange->p_naechster->p_naechster->p_naechster == p_kfz);
    
    free(p_parkhaus);
    free(p_kfz);
}