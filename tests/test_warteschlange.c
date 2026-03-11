#include <stdlib.h>
#include <assert.h>
#include "parkhaus.h"
#include "kfz.h"
#include "warteschlange.h"

void test_kfz_hinzufuegen_warteschlange_leer(){
    Parkhaus *p_parkhaus = init_parkhaus(1, 40);
    Kfz *p_kfz = init_kfz(p_parkhaus, 1, 60);

    kfz_hinzufuegen_warteschlange(p_parkhaus, p_kfz);
    assert(p_parkhaus->p_erstes_kfz_in_der_warteschlange == p_kfz);
    free(p_parkhaus);
    free(p_kfz);
}

void test_kfz_hinzufuegen_warteschlange_normal(){
    Parkhaus *p_parkhaus = init_parkhaus(1, 40);
    Kfz *p_kfz = init_kfz(p_parkhaus, 4, 63);

    p_parkhaus->p_erstes_kfz_in_der_warteschlange = init_kfz(p_parkhaus, 1, 60);
    p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz = init_kfz(p_parkhaus, 2, 61);
    p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz->p_naechstes_kfz = init_kfz(p_parkhaus, 3, 62);

    kfz_hinzufuegen_warteschlange(p_parkhaus, p_kfz);
    assert(p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz->p_naechstes_kfz->p_naechstes_kfz == p_kfz);
    
    free(p_parkhaus);
    free(p_kfz);
}

void test_entferne_kfz_warteschlange_normal(){
    Parkhaus *p_parkhaus = init_parkhaus(1, 40);
    Kfz *p_kfz1 = init_kfz(p_parkhaus, 1, 60);
    Kfz *p_kfz2 = init_kfz(p_parkhaus, 2, 61);
    Kfz *p_kfz3 = init_kfz(p_parkhaus, 3, 62);

    p_parkhaus->p_erstes_kfz_in_der_warteschlange = p_kfz1;
    p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz = p_kfz2;
    p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz->p_naechstes_kfz = p_kfz3;

    entferne_kfz_warteschlange(p_parkhaus);
    assert(p_parkhaus->p_erstes_kfz_in_der_warteschlange == p_kfz2);
    assert(p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz == p_kfz3);
    assert(p_kfz1->p_naechstes_kfz == NULL);

    free(p_parkhaus);
    free(p_kfz1);
    free(p_kfz2);
    free(p_kfz3);
}

void test_entferne_kfz_warteschlange_leer(){
    Parkhaus *p_parkhaus = init_parkhaus(1, 40);
    
    entferne_kfz_warteschlange(p_parkhaus);
    
    assert(p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL);
    
    free(p_parkhaus);
}

int main() {
    test_kfz_hinzufuegen_warteschlange_leer();
    test_kfz_hinzufuegen_warteschlange_normal();
    test_entferne_kfz_warteschlange_normal();
    test_entferne_kfz_warteschlange_leer();
    return 0;
}